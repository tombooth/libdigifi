/*
 *  queue.c
 *  libdigifi.new
 *
 *  Created by Tom Booth on 09/04/2010.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

#include "queue.h"

#include <stdlib.h>
#include <pthread.h>

struct item {
	void *value;
	struct item *next;
};

struct item *front_pointer = NULL;
struct item *back_pointer = NULL;

static pthread_mutex_t queue_lock = PTHREAD_MUTEX_INITIALIZER;

static pthread_cond_t queue_cond = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t queue_cond_mutex = PTHREAD_MUTEX_INITIALIZER;


void queue_push(void *item) {
	
	struct item *new_item = (struct item *) malloc(sizeof(struct item));
	new_item->value = item;
	new_item->next = NULL;
	
	pthread_mutex_lock(&queue_lock);
	
	if (front_pointer == NULL) {
		front_pointer = new_item;
		back_pointer = new_item;
	} else {
		back_pointer->next = new_item;
		back_pointer = new_item;
	}
	
	pthread_mutex_unlock(&queue_lock);
	
	pthread_cond_broadcast(&queue_cond);
	
}

void queue_filter(int (*filter)(void *, void *), void *context) {
	struct item *current, *last, *tmp;
	
	last = NULL;
	current = front_pointer;
	while (current != NULL) {
		if (filter(current->value, context)) { 
			if (last!=NULL) { last->next = current->next; }
			else { front_pointer = current->next; }
			tmp = current->next;
			free(current);	// the filter needs to take care of cleaning up the value
			current = tmp;
		} else { last = current; current = current->next; }
	}
}

void *queue_pop() {
	void *item;
	struct item *holder;
	
	pthread_mutex_lock(&queue_cond_mutex);
	
	while (front_pointer == NULL) { pthread_cond_wait(&queue_cond, &queue_cond_mutex); }
	
	// get the item from the front of the queue
	pthread_mutex_lock(&queue_lock);
	
	holder = front_pointer;
	item = front_pointer->value;
	if (front_pointer->next == NULL) { 
		front_pointer = NULL; back_pointer = NULL;
	} else {
		front_pointer = front_pointer->next;
	}
	
	free(holder);
	
	pthread_mutex_unlock(&queue_lock);
	
	pthread_mutex_unlock(&queue_cond_mutex);
	
	return item;
	
		
}



