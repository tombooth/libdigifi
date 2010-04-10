/*
 *  comm_in.c
 *  libdigifi.new
 *
 *  Created by Tom Booth on 08/04/2010.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

#include "comm_in.h"

#include <stdlib.h>
#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>


static void ping_thread();
static int update_fd_set(fd_set *descriptors);


struct settings_holder {
	in_settings *settings;
	struct settings_holder *next;
	struct settings_holder *previous;
};

static struct settings_holder *holder_front = NULL;
static struct settings_holder *holder_back = NULL;

static int signal_descriptors[2];

static void (*process_callback)(in_settings*, char*, char*);

void comm_in_init(void (*callback)(in_settings*, char*, char*)) {
	pipe(signal_descriptors);
	process_callback = callback;
}


void comm_in_add(in_settings *settings) {
	if (holder_front == NULL) {
		holder_front = (struct settings_holder*) malloc(sizeof(struct settings_holder));
		holder_front->settings = settings;
		holder_front->previous = NULL;
		holder_front->next = NULL;
		
		holder_back = holder_front;
	} else {
		holder_back->next = (struct settings_holder*) malloc(sizeof(struct settings_holder));
		holder_back->next->settings = settings;
		holder_back->next->next = NULL;
		holder_back->next->previous = holder_back;
		
		holder_back = holder_back->next;
	}
	
	// ping the thread to update the file descriptor set
	ping_thread();
}



void comm_in_remove(in_settings *settings) {
	struct settings_holder *temp = holder_front;
	
	while (temp != NULL && temp->settings != settings) { temp = temp->next; }
	if (temp != NULL) {
		temp->next->previous = temp->previous;
		temp->previous->next = temp->next;
		free(temp);
	}
	
	ping_thread();
}



void* comm_in_thread_start(void *args) {
	fd_set signals;
	int signals_max, err;
	char *signal_buff;
	struct settings_holder *temp;
	extraction_result *result;
	regex_t *find_name_regex;
	
	find_name_regex = regex_get_compiled("findname");
	
	while (1) {
		signals_max = update_fd_set(&signals);
		
		if ((err = select(signals_max, &signals, NULL, NULL, NULL)) > 0) {
			
			// check for signal
			if (FD_ISSET(signal_descriptors[0], &signals)) {
				signal_buff = malloc(sizeof(char));
				read(signal_descriptors[0], signal_buff, sizeof(char));
				free(signal_buff);
				continue;
			}
			
			// recieved data on a descriptor			
			temp = holder_front;
			while (temp != NULL) {
				if (FD_ISSET(temp->settings->client_fd, &signals)) {
					result = extraction_run(temp->settings->client_fd, temp->settings->buffer, find_name_regex, NULL);
					
					process_callback(temp->settings, result->result->subexps[1].value, result->result->value);
					
					extraction_free_result(result);
				}
				
				temp = temp->next;
			}
		}
		
	}
	
	return NULL;
}






static void ping_thread() {
	write(signal_descriptors[1], "X", sizeof(char));
}


static int update_fd_set(fd_set *descriptors) {
	int max_desc;
	struct settings_holder *temp;
	
	// zero current set
	FD_ZERO(descriptors);
	
	FD_SET(signal_descriptors[0], descriptors);
	max_desc = signal_descriptors[0];
	
	// add the descriptors for all connections
	temp = holder_front;
	while (temp != NULL) {
		if (temp->settings->client_fd > max_desc) 
			max_desc = temp->settings->client_fd;
		
		FD_SET(temp->settings->client_fd, descriptors);
		temp = temp->next;
	}	

	return max_desc + 1;
}


