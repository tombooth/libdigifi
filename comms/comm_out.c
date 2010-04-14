/*
 *  comm_out.c
 *  libdigifi.new
 *
 *  Created by Tom Booth on 08/04/2010.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

#include "comm_out.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

#include "queue.h"
#include "timing.h"
#include "debugging.h"


struct clear_context {
	out_socket *fds;
	int num_fds;
};
static int clear_queue_filter(void *item, void *context);

static void free_request(out_request *request);
static void free_response(out_response *response);


void comm_out_push_request(out_request *request) {
	// increase the backlog on this socket to show its got an extra request to process
	request->socket->backlog++;
	
	queue_push((void *)request);
	
}



void comm_out_clear_requests_for(out_socket *fds, int num_fds) {
	int i;
	struct clear_context *context = malloc(sizeof(struct clear_context));
	
	context->fds = fds;
	context->num_fds = num_fds;
	
	for (i = 0; i < num_fds; i++) {
		pthread_mutex_lock(&(fds[i].fd_lock));
	}
	
	queue_filter(clear_queue_filter, context);
	
	for (i = 0; i < num_fds; i++) {
		pthread_mutex_unlock(&(fds[i].fd_lock));
	}
	
	free(context);
}

static int clear_queue_filter(void *item, void *context) {
	int i;
	struct clear_context *cc = (struct clear_context *) context;
	out_request *request = (out_request *) item;
	
	for (i = 0; i < cc->num_fds; i++) {
		if (request->socket->fd == cc->fds[i].fd) {
			free_request(request);
			return 1;
		}
	}
			
	return 0;
}




void* comm_out_thread_start(void *args) {
	out_request *request;
	out_response *response_set;
	cbuf *buffer;
	regex_t *error_regex;
	int i, error_occurred, timeout_occurred, extracted_rows;
	timing_obj *tmr;
	
	error_regex = NULL;
	
	while (1) {
		
		pthread_testcancel();
		
		error_occurred = 0;
		timeout_occurred = 0;
		
		request = queue_pop();
		
		// lock the socket for use
		pthread_mutex_lock(&(request->socket->fd_lock));
		
		tmr = timing_create();
		timing_set_duration(tmr, COMMAND_TIMEOUT_SECS, 0, 0);
		timing_start(tmr);
		
		DFDEBUG("Sending %s for request [%p] on %d", request->send, request, request->socket->fd);
		
		// send command
		send(request->socket->fd, request->send, strlen(request->send) * sizeof(char), 0);
		
		timing_punch(tmr);
		
		// recieve response set
		buffer = cbuf_new();
		
		response_set = (out_response *) malloc(request->response_count * sizeof(out_response));
		extracted_rows = 0;
		
		for (i = 0; i < request->response_count; i++) {
			response_set[i].result = extraction_run(request->socket->fd, buffer, request->response_regex, error_regex, tmr); extracted_rows++;
			//DFDEBUG("Received on %d: %s", request->socket->fd, response_set[i].result->result->value);
			if (response_set[i].result == NULL) { timeout_occurred = 1; break; }
			else if (response_set[i].result->is_error) { error_occurred = 1; break; }
		}
		
		DFDEBUG("Completed request [%p] on %d num:%d err:%d", request, request->socket->fd, request->response_count, error_occurred);
		
		// process the response that has come in
		if (error_occurred) {
			DFERROR("%s", response_set[0].result->result->value);
		}
		else if (timeout_occurred) {
			DFERROR("TIMEOUT on command %s", request->send);
		}
		else if (request->callback != NULL) {
			request->callback(request, response_set, request->response_count, request->context);
		}
		
		timing_stop(tmr);
		
		// cleanup after communication
		cbuf_free(buffer);
		request->socket->backlog--; // lower the backlog of messages as this one is done
		request->socket->done++;
		timing_destroy(tmr);
		
		
		// clear the response_set
		for (i = 0; i < extracted_rows; i++) {
			free_response(&(response_set[i]));
		}
		free(response_set);
		
		
		// unlock one completed
		pthread_mutex_unlock(&(request->socket->fd_lock));
		
		free_request(request);
		
	}
	
	
	return NULL;
}



static void free_request(out_request *request) {
	free(request->tag);
	free(request->send);
	free(request);
}

static void free_response(out_response *response) {
	extraction_free_result(response->result);
}




