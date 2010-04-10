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


void comm_out_push_request(out_request *request) {
	// increase the backlog on this socket to show its got an extra request to process
	request->socket->backlog++;
	
	queue_push((void *)request);
	
}



void* comm_out_thread_start(void *args) {
	out_request *request;
	out_response *response_set;
	cbuf *buffer;
	regex_t *error_regex;
	int i, error_occurred;
	
	error_regex = NULL;
	
	while (1) {
		
		pthread_testcancel();
		
		error_occurred = 0;
		
		request = queue_pop();
		
		// lock the socket for use
		pthread_mutex_lock(&(request->socket->fd_lock));
		
		fprintf(stdout, "Sending: %s\n", request->send);
		
		// send command
		send(request->socket->fd, request->send, strlen(request->send) * sizeof(char), 0);
		
		// recieve response set
		buffer = cbuf_new();
		
		response_set = (out_response *) malloc(request->response_count * sizeof(out_response));
		for (i = 0; i < request->response_count; i++) {
			response_set[i].result = extraction_run(request->socket->fd, buffer, request->response_regex, error_regex);
			if (response_set[i].result->is_error) { error_occurred = 1; break; }
		}
		
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
		
		
		// unlock one completed
		pthread_mutex_unlock(&(request->socket->fd_lock));
		
	}
	
	
	return NULL;
}








