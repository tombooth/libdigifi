/*
 *  comm_out.h
 *  libdigifi.new
 *
 *  Created by Tom Booth on 08/04/2010.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

#ifndef COMMOUT_H
#define COMMOUT_H

#include <pthread.h>
#include "extraction.h"


#define COMMAND_TIMEOUT_SECS 60


typedef struct {
	int fd;
	pthread_mutex_t fd_lock;
	unsigned int backlog;
	unsigned long done;
} out_socket;


struct __out_response {
	char *tag;
	
	extraction_result *result;
	
	/*struct __out_response *next;*/
};
typedef struct __out_response out_response;


struct __out_request{
	char *tag;
	
	out_socket *socket;
	char *send;
	
	unsigned int response_count;
	regex_t *response_regex;
	
	void (*callback)(struct __out_request*, out_response*, int, void*);
	void *context;
	unsigned int requested_count;
	
};

typedef struct __out_request out_request;




void comm_out_push_request(out_request *request);

void comm_out_clear_requests_for(out_socket *fds, int num_fds);



void* comm_out_thread_start(void *args);



#endif