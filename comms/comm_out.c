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
		if (request->socket == cc->fds[i].fd) {
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
	int i, error_occurred, extracted_rows;
	
	error_regex = NULL;
	
	while (1) {
		
		pthread_testcancel();
		
		error_occurred = 0;
		
		request = queue_pop();
		
		// lock the socket for use
		pthread_mutex_lock(&(request->socket->fd_lock));
		
		DFDEBUG("Sending %s for request [%p]", request->send, request);
		
		// send command
		send(request->socket->fd, request->send, strlen(request->send) * sizeof(char), 0);
		
		// recieve response set
		buffer = cbuf_new();
		
		response_set = (out_response *) malloc(request->response_count * sizeof(out_response));
		extracted_rows = 0;
		
		for (i = 0; i < request->response_count; i++) {
			response_set[i].result = extraction_run(request->socket->fd, buffer, request->response_regex, error_regex); extracted_rows++;
			if (response_set[i].result->is_error) { error_occurred = 1; break; }
		}
		
		DFDEBUG("Completed request [%p] num:%d err:%d", request, request->response_count, error_occurred);
		
		// process the response that has come in
		if (error_occurred) {
			fprintf(stdout, "An Error Occurred: %s\n", response_set[0].result->result->value);
		}
		else if (request->callback != NULL) {
			request->callback(request, response_set, request->response_count, request->context);
		}
		
		
		
		// cleanup after communication
		cbuf_free(buffer);
		request->socket->backlog--; // lower the backlog of messages as this one is done
		
		
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




