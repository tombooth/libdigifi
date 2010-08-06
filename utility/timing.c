/*
 *  timing.c
 *  libdigifi.new
 *
 *  Created by Tom Booth on 08/04/2010.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

#include "timing.h"

#include <stdlib.h>
#include <stdio.h>

#include "debugging.h"


#define CAPACITY_INC 1


static void enlarge_entries_capacity(timing_obj *tmr);
static void subtract_timevals(struct timeval *time1, struct timeval *time2, struct timeval *result);


timing_obj* timing_create() {
	timing_obj *obj = (timing_obj *) malloc(sizeof(timing_obj));
	
	obj->running = 0;
	obj->entries = (struct timeval *) malloc(sizeof(struct timeval) * CAPACITY_INC);
	obj->entries_capacity = CAPACITY_INC;
	obj->num_entries = 0;
	
	return obj;
}



void timing_start(timing_obj *tmr) {
	timing_punch(tmr);
	
	tmr->running = 1;
}



void timing_punch(timing_obj *tmr) {
	if (!tmr->running) return;
	if (tmr->num_entries + 1 >= tmr->entries_capacity) enlarge_entries_capacity(tmr);
	
	gettimeofday(&(tmr->entries[tmr->num_entries]), NULL);
	tmr->num_entries++;
}


void timing_set_duration(timing_obj *tmr, unsigned seconds, unsigned minutes, unsigned hours) {
	tmr->duration.seconds = seconds;
	tmr->duration.minutes = minutes;
	tmr->duration.hours = hours;
}


int timing_has_elapsed(timing_obj *tmr) {
	struct timeval diff;
	long int duration_l;
	
	if (!tmr->running) return 0;
	
	timing_punch(tmr);
	subtract_timevals(&(tmr->entries[tmr->num_entries-1]), &(tmr->entries[0]), &diff);
	
	duration_l = tmr->duration.seconds + (tmr->duration.minutes * 60) + (tmr->duration.hours * 3600);
	
	if (diff.tv_sec >= duration_l) DFDEBUG("Has elapsed: %ld >= %ld", diff.tv_sec, duration_l);
	
	return (diff.tv_sec >= duration_l);
}



void timing_stop(timing_obj *tmr) {
	if (!tmr->running) return;
	
	timing_punch(tmr);
	tmr->running = 0;
}


void timing_print(timing_obj *tmr) {
	int i = 0;
	
	printf("Entries in timing object:\n");
	for (i = 0; i < tmr->num_entries; i++) {
		printf("[%d] %lu %lu\n", i, (long unsigned int)tmr->entries[i].tv_sec, (long unsigned int)tmr->entries[i].tv_usec);
	}
}



void timing_destroy(timing_obj *tmr) {
	free(tmr->entries);
	free(tmr);
}




static void enlarge_entries_capacity(timing_obj *tmr) {
	tmr->entries_capacity += CAPACITY_INC;
	tmr->entries = realloc(tmr->entries, sizeof(struct timeval) * tmr->entries_capacity);
}

static void subtract_timevals(struct timeval *time1, struct timeval *time2, struct timeval *result) {
	if ((time1->tv_sec < time2->tv_sec) ||
		((time1->tv_sec == time2->tv_sec) &&
		 (time1->tv_usec <= time2->tv_usec))) {	
        result->tv_sec = result->tv_usec = 0 ;
    } else {						
        result->tv_sec = time1->tv_sec - time2->tv_sec ;
        if (time1->tv_usec < time2->tv_usec) {
            result->tv_usec = time1->tv_usec + 1000000L - time2->tv_usec ;
            result->tv_sec-- ;		
        } else {
            result->tv_usec = time1->tv_usec - time2->tv_usec ;
        }
    }
}

