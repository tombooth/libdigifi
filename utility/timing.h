/*
 *  timing.h
 *  libdigifi.new
 *
 *  Created by Tom Booth on 08/04/2010.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */


#ifndef TIMING_H
#define	TIMING_H

#include <sys/time.h>


typedef struct {
	unsigned seconds;
	unsigned minutes;
	unsigned hours;
} timing_duration;

typedef struct {
	int running;
	
	struct timeval *entries;
	unsigned entries_capacity;
	unsigned num_entries;
	
	timing_duration duration;
} timing_obj;





timing_obj* timing_create();

void timing_start(timing_obj *tmr);

void timing_punch(timing_obj *tmr);

void timing_set_duration(timing_obj *tmr, unsigned seconds, unsigned minutes, unsigned hours);

int timing_has_elapsed(timing_obj *tmr);

void timing_stop(timing_obj *tmr);

void timing_print(timing_obj *tmr);

void timing_destroy(timing_obj *tmr);










#endif

