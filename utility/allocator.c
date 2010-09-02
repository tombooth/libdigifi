/*
 *  allocator.c
 *  libdigifi.new
 *
 *  Created by Tom Booth on 09/04/2010.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */


#include "allocator.h"
#include <pthread.h>

#define DFROW_MAX_SEARCHNUMBERS		(sizeof(unsigned long) * 8)

// variables for allocating which search number to use and a store
// for the call back
static unsigned long occupied_numbers = 0;
static unsigned long search_numbers = 0;
pthread_mutex_t dfrow_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t dfrow_cond = PTHREAD_COND_INITIALIZER;



int allocator_get() {
	int i;
	
	while (!(occupied_numbers<DFROW_MAX_SEARCHNUMBERS)) { 
		pthread_cond_wait(&dfrow_cond, &dfrow_mutex); 
	}
	
	for (i=0; i<DFROW_MAX_SEARCHNUMBERS; i++) {
		if (((search_numbers>>i) & 1) == 0) {
			search_numbers = search_numbers | (1<<(i));
			pthread_mutex_unlock(&dfrow_mutex);
			return i + 1;
		}
	}
	
	pthread_mutex_unlock(&dfrow_mutex);
	
	return -1;
}

void allocator_return(int num) {
	pthread_mutex_lock(&dfrow_mutex);
	
	search_numbers = search_numbers & ~(1<<(num-1));
	
	pthread_mutex_unlock(&dfrow_mutex);
	
	pthread_cond_signal(&dfrow_cond);
}



