/*
 *  rgets.h
 *  libdigifi.new
 *
 *  Created by Tom Booth on 09/04/2010.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

#ifndef RGETS_H
#define RGETS_H


#include "client.h"


int dfrget_albumartist(df_connection *conn, unsigned int room_id, 
					   void (*callback)(int, df_albumartist*, void*), void *context);

int dfrget_clearcommands(df_connection *conn, unsigned int room_id);

int dfrget_detailedtrackinfo(df_connection *conn, unsigned int room_id, 
							 void (*callback)(int, df_detailedtrack*, void*), void *context);

int dfrget_lastplayererror(df_connection *conn, unsigned int room_id,
						   void (*callback)(int, char*, void*), void *context);

int dfrget_playerstatus(df_connection *conn, unsigned int room_id, 
						void (*callback)(int, char*, void*), void *context);

int dfrget_playingchecksum(df_connection *conn, unsigned int room_id,
						   void (*callback)(int, char*, void*), void *context);

int dfrget_repeat(df_connection *conn, unsigned int room_id,
				  void (*callback)(int, int, void*), void *context);

int dfrget_shuffle(df_connection *conn, unsigned int room_id, 
				   void (*callback)(int, int, void*), void *context);

int dfrget_trackname(df_connection *conn, unsigned int room_id, 
					 void (*callback)(int, df_trackname*, void*), void *context);

int dfrget_trackposition(df_connection *conn, unsigned int room_id, 
						 void (*callback)(int, df_time*, void*), void *context);

int dfrget_bufferfill(df_connection *conn, unsigned int room_id,
                   void (*callback)(int, int, void*), void *context);


void process_incoming_rget(in_settings *settings, char *name, char *command);



#endif
