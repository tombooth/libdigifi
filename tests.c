/*
 *  tests.c
 *  libdigifi.new
 *
 *  Created by Tom Booth on 10/04/2010.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

#include "tests.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "formatting.h"
#include "debugging.h"

static int randomise_bool(int range, int limit);
static int randomise_int(int max);


#define MAX_CONNECTIONS 7
static df_connection *test_conns[MAX_CONNECTIONS];
static int num_connections = 0;


static void test_getroom_handler(int num, df_roomrow *rows, void *context) { DFDEBUG("Receieved get room rows"); df_roomrow_free(rows); }
static void test_getartists_handler(int num, df_artistrow *rows, void *context) { DFDEBUG("Received get artists rows"); df_artistrow_free(rows); }
static void test_getalbums_handler(int num, df_albumrow *rows, void *context) { DFDEBUG("Received get albums rows"); df_albumrow_free(rows); }

static void test_trackposition_handler(df_time *time, void *context) { DFDEBUG("Received a trackposition rget callback"); }
static void test_detailedtrack_handler(df_detailedtrack *dt, void *context) { DFDEBUG("Received a detailedtrack rget callback"); }
static void test_playerstatus_handler(char *status, void *context) { DFDEBUG("Received a playerstatus rget callback"); }

void main_conn_test(pthread_mutex_t *parent_lock) {
	
	printf("Starting connection test...\n");
	
	num_connections = 0;
	
	while (1) {
		// create some connections
		if (randomise_bool(10, 2) && num_connections != MAX_CONNECTIONS) {
			DFDEBUG("Connecting to digifi in slot %d", num_connections);
			test_conns[num_connections] = df_connect("192.168.0.242", 2);
			num_connections++;
		}
		
		// connect to some rgets
		if (num_connections > 0) {
			switch (randomise_int(3)) {
				case 0:
					dfrget_trackposition(test_conns[randomise_int(num_connections)], 1, test_trackposition_handler, NULL);
					break;
				case 1:
					dfrget_detailedtrackinfo(test_conns[randomise_int(num_connections)], 1, test_detailedtrack_handler, NULL);
					break;
				case 2:
					dfrget_playerstatus(test_conns[randomise_int(num_connections)], 1, test_playerstatus_handler, NULL);
					break;
				case 3:
					DFDEBUG("Clearing commands for a room");
					dfrget_clearcommands(test_conns[randomise_int(num_connections)], 1);
					break;

				default:
					break;
			}
		}
		
		// execute some calls
		if (num_connections > 0) {
			switch (randomise_int(3)) {
				case 0:
					df_GetArtists(test_conns[randomise_int(num_connections)], 0, test_getartists_handler, NULL);
					break;
				case 1:
					df_GetRooms(test_conns[randomise_int(num_connections)], 0, test_getroom_handler, NULL);
					break;
				case 2:
					df_GetAlbums(test_conns[randomise_int(num_connections)], "", "", test_getalbums_handler, NULL);
					break;
				default:
					break;
			}
		}
			
		
		// disconnect some connections
		if (randomise_bool(10, 9) && num_connections > 0) {
			num_connections--;
			DFDEBUG("Disconnecting digifi in slot %d", num_connections);
			df_disconnect(test_conns[num_connections]);
		}
		
		sleep(1);
	}
	
	
	pthread_mutex_unlock(parent_lock);
}
			
static int randomise_int(int max) {
	int r;
	struct timeval tv;
	gettimeofday(&tv, NULL);
	
	srand48((long)tv.tv_usec);
	r = (int)(((double)lrand48()/(double)RAND_MAX) * max);
	
	return r;
}

static int randomise_bool(int range, int limit) {
	return (randomise_int(range)>=limit);
}





void misc_test(pthread_mutex_t *parent_lock) {
	char *string, *result;
	
	string = "Simple Things \\[UK\\]";
	
	result = formatting_process(string);
	fprintf(stdout, "Result from formatting of %s was %s\n", string, result);
	
	pthread_mutex_unlock(parent_lock);
}

