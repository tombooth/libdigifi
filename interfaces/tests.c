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
#include <string.h>
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
static void test_getcurrentplaylistex_handler(int num, df_type0row *rows, void *context) { DFDEBUG("Received get currentplaylistex rows"); df_type0row_free(rows); }

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
			switch (randomise_int(4)) {
				case 0:
					//df_GetRooms(test_conns[randomise_int(num_connections)], 0, test_getroom_handler, NULL);
					//df_GetArtists(test_conns[randomise_int(num_connections)], 0, test_getartists_handler, NULL);
					break;
				case 1:
					//df_GetRooms(test_conns[randomise_int(num_connections)], 0, test_getroom_handler, NULL);
					//df_GetAlbums(test_conns[randomise_int(num_connections)], "", "", test_getalbums_handler, NULL);
					break;
				case 2:
					//df_GetAlbums(test_conns[randomise_int(num_connections)], "", "", test_getalbums_handler, NULL);
					//df_GetCurrentPlaylistEx(test_conns[randomise_int(num_connections)], 1, 1, 1, test_getcurrentplaylistex_handler, NULL);
					break;
				case 3:
					//df_GetArtists(test_conns[randomise_int(num_connections)], 0, test_getartists_handler, NULL);
					//df_GetCurrentPlaylistEx(test_conns[randomise_int(num_connections)], 1, 1, 1, test_getcurrentplaylistex_handler, NULL);
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

void main_func_test(pthread_mutex_t *parent_lock) {
	df_connection *test_conn;
	
	printf("Starting function test...\n");
	
	test_conn = df_connect("192.168.0.242", 2);
	
	while (1) {
		
		// connect to some rgets
		/*if (num_connections > 0) {
			switch (randomise_int(3)) {
				case 0:
					dfrget_trackposition(test_conn, 1, test_trackposition_handler, NULL);
					break;
				case 1:
					dfrget_detailedtrackinfo(test_conn, 1, test_detailedtrack_handler, NULL);
					break;
				case 2:
					dfrget_playerstatus(test_conn, 1, test_playerstatus_handler, NULL);
					break;
				case 3:
					DFDEBUG("Clearing commands for a room");
					dfrget_clearcommands(test_conn, 1);
					break;
					
				default:
					break;
			}
		}*/
		
		// execute some calls
			switch (randomise_int(4)) {
				case 0:
					//df_GetRooms(test_conn, 0, test_getroom_handler, NULL);
					//df_GetArtists(test_conn, 0, test_getartists_handler, NULL);
					break;
				case 1:
					//df_GetRooms(test_conn, 0, test_getroom_handler, NULL);
					//df_GetAlbums(test_conn, "", "", test_getalbums_handler, NULL);
					break;
				case 2:
					//df_GetAlbums(test_conn, "", "", test_getalbums_handler, NULL);
					//df_GetCurrentPlaylistEx(test_conn, 1, 1, 1, test_getcurrentplaylistex_handler, NULL);
					break;
				case 3:
					//df_GetArtists(test_conn, 0, test_getartists_handler, NULL);
					//df_GetCurrentPlaylistEx(test_conn, 1, 1, 1, test_getcurrentplaylistex_handler, NULL);
					break;
					
				default:
					break;
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





static void test_rget_trackposition_handler(int room, df_time *time, void *context) {
	fprintf(stdout, "TrackPosition [%d]: %d:%d:%d context:%s\n", room, time->hours, time->minutes, time->seconds, (char *)context);
}

static void test_rget_detailedtrack_handler(int room, df_detailedtrack *dt, void *context) {
	fprintf(stdout, "DetailedTrack [%d]: %s - %s - %s  context:%s\n", room, dt->artistname, dt->albumname, dt->name, (char *)context);
}

static void test_rget_playerstatus_handler(int room, char *text, void *context) {
	fprintf(stdout, "PlayerStatus [%d]: %s context:%s\n", room, text, (char *)context);
}
static void test_rget_playingchecksum_handler(int room, char *text, void *context) {
	fprintf(stdout, "PlayingChecksum [%d]: %s context:%s\n", room, text, (char *)context);
}

static void test_rget_getalbums_handler(int num, df_albumrow *albums, void *context) {
	fprintf(stdout, "GetAlbums receieved %d albums from digifi %s\n", num, ((df_connection*)context)->label);
}

void rget_test(pthread_mutex_t *parent_lock) {
	df_connection *conn, *conn1, *curr_conn;
	int i = 1;
	char *message = strdup("context string");
	
	conn = df_connect("192.168.0.242", 2);
	conn1 = df_connect("192.168.0.39", 2);
	
	while (1) {
		curr_conn = (randomise_bool(10, 5)) ? conn : conn1;
		
		fprintf(stdout, "Linking rgets to room %d\n", i);		
		dfrget_trackposition(curr_conn, i, test_rget_trackposition_handler, message);
		dfrget_detailedtrackinfo(curr_conn, i, test_rget_detailedtrack_handler, message);
		dfrget_playerstatus(curr_conn, i, test_rget_playerstatus_handler, message);
		dfrget_playingchecksum(curr_conn, i, test_rget_playingchecksum_handler, message);
		
		//df_GetAlbums(curr_conn, "", "", test_rget_getalbums_handler, curr_conn);
		
		fprintf(stdout, "Sleeping...\n");
		sleep(randomise_int(30));
		
		fprintf(stdout, "Clearing rgets for room %d\n", i);
		dfrget_clearcommands(curr_conn, i);
		
		i++; if (i>2) i = 1;
	}
	
}
















void misc_test(pthread_mutex_t *parent_lock) {
	char *string, *result;
	df_connection *conn;
	
	conn = df_connect("192.168.1.70", 2);
	
	sleep(3);
	
	df_PlayTrack(conn, 1, 1, "a25225 a25221", NULL, NULL);
	
	sleep(3);
	
	df_disconnect(conn);
	
	/*string = "Simple Things \\[UK\\]";
	
	result = formatting_process(string);
	fprintf(stdout, "Result from formatting of %s was %s\n", string, result);*/
	
	pthread_mutex_unlock(parent_lock);
}








static void search_getalbums_handler(int rows, df_albumrow *input, void *context) { 
  df_albumrow *current;
  
	printf("Printing GetAlbums return:\n");
	printf("Total rows: %d\n", rows);
	current = input;
  
	while (current != NULL) {
		printf("PlaylistKey: %d\n", current->PlaylistKey);
		printf("Name: \"%s\"\n", current->Name);
		printf("ArtistKey: %d\n", current->ArtistKey);
		printf("ArtistName: \"%s\"\n", current->ArtistName);
		printf("IsAlbum: %d\n", current->IsAlbum);
		printf("HitCount: %d\n", current->HitCount);
		printf("ExtendedInfoAvail: %d\n", current->ExtendedInfoAvail);
		printf("Storage: %d\n", current->Storage);
    
		current = current->next;
	}
  
	df_albumrow_free(input);
	fflush(stdout);
}

static void search_callback(df_search *search) {
  df_extract_from(search, 1, 1);
}

void search_test(pthread_mutex_t *parent_lock) {
  df_connection *conn;
	
	conn = df_connect("192.168.0.242", 2);
	
	sleep(3);
  
  df_GetAlbums(conn, "", "", search_callback, search_getalbums_handler, NULL);
  
  sleep(10);
	
	pthread_mutex_unlock(parent_lock);
}


