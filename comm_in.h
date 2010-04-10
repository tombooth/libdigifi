/*
 *  comm_in.h
 *  libdigifi.new
 *
 *  Created by Tom Booth on 08/04/2010.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */


#ifndef COMMIN_H
#define COMMIN_H


#include <pthread.h>
#include "charbuffer.h"
#include "extraction.h"


typedef enum {
	DFRGET_ALBUMARTIST = 0,
	DFRGET_DETAILTRACKINFO = 1,
	DFRGET_LASTPLAYERERROR = 2,
	DFRGET_PLAYERSTATUS = 3,
	DFRGET_PLAYINGCHECKSUM = 4,
	DFRGET_REPEAT = 5,
	DFRGET_SHUFFLE = 6,
	DFRGET_TRACKNAME = 7,
	DFRGET_TRACKPOSITION = 8
} in_rget_enum;

typedef struct {
	void (*callback)(void);
	void *context;
} in_rget;

typedef struct {
	int server_fd;
	int client_fd;
	
	cbuf *buffer;
	
	in_rget rgets[9];
	
} in_settings;


void comm_in_init(void (*callback)(in_settings*, char*, char*));


void comm_in_add(in_settings *settings);

void comm_in_remove(in_settings *settings);


void* comm_in_thread_start(void *args);



#endif

