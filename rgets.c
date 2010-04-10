/*
 *  rgets.c
 *  libdigifi.new
 *
 *  Created by Tom Booth on 09/04/2010.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

#include "rgets.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "regex_wrapper.h"



int dfrget_albumartist(df_connection *conn, unsigned int room_id, 
					   void (*callback)(df_albumartist*, void*), void *context) {
	conn->rget_settings.rgets[DFRGET_ALBUMARTIST].callback = (void (*)(void))callback;
	conn->rget_settings.rgets[DFRGET_ALBUMARTIST].context = context;
	return comm_send(conn, 1, "void", 1, NULL, NULL, "[RGetAlbumArtist %u]", room_id);
}

int dfrget_clearcommands(df_connection *conn, unsigned int room_id) {
	return comm_send(conn, 1, "void", 1, NULL, NULL, "[RGetClearCommands %u]", room_id);
}

int dfrget_detailedtrackinfo(df_connection *conn, unsigned int room_id, 
							 void (*callback)(df_detailedtrack*, void*), void *context) {
	conn->rget_settings.rgets[DFRGET_DETAILTRACKINFO].callback = (void (*)(void))callback;
	conn->rget_settings.rgets[DFRGET_DETAILTRACKINFO].context = context;
	return comm_send(conn, 1, "void", 1, NULL, NULL, "[RGetDetailedTrackInfo %u]", room_id);
}

int dfrget_lastplayererror(df_connection *conn, unsigned int room_id,
						   void (*callback)(char*, void*), void *context) {
	conn->rget_settings.rgets[DFRGET_LASTPLAYERERROR].callback = (void (*)(void))callback;
	conn->rget_settings.rgets[DFRGET_LASTPLAYERERROR].context = context;
	return comm_send(conn, 1, "void", 1, NULL, NULL, "[RGetLastPlayerError %u]", room_id);
}

int dfrget_playerstatus(df_connection *conn, unsigned int room_id, 
						void (*callback)(char*, void*), void *context) {
	conn->rget_settings.rgets[DFRGET_PLAYERSTATUS].callback = (void (*)(void))callback;
	conn->rget_settings.rgets[DFRGET_PLAYERSTATUS].context = context;
	return comm_send(conn, 1, "void", 1, NULL, NULL, "[RGetPlayerStatus %u]", room_id);
}

int dfrget_playingchecksum(df_connection *conn, unsigned int room_id,
						   void (*callback)(char*, void*), void *context) {
	conn->rget_settings.rgets[DFRGET_PLAYINGCHECKSUM].callback = (void (*)(void))callback;
	conn->rget_settings.rgets[DFRGET_PLAYINGCHECKSUM].context = context;
	return comm_send(conn, 1, "void", 1, NULL, NULL, "[RGetPlayingChecksum %u]", room_id);
}

int dfrget_repeat(df_connection *conn, unsigned int room_id,
				  void (*callback)(int, void*), void *context) {
	conn->rget_settings.rgets[DFRGET_REPEAT].callback = (void (*)(void))callback;
	conn->rget_settings.rgets[DFRGET_REPEAT].context = context;
	return comm_send(conn, 1, "void", 1, NULL, NULL, "[RGetRepeat %u]", room_id);
}

int dfrget_shuffle(df_connection *conn, unsigned int room_id, 
				   void (*callback)(int, void*), void *context) {
	conn->rget_settings.rgets[DFRGET_SHUFFLE].callback = (void (*)(void))callback;
	conn->rget_settings.rgets[DFRGET_SHUFFLE].context = context;
	return comm_send(conn, 1, "void", 1, NULL, NULL, "[RGetShuffle %u]", room_id);
}

int dfrget_trackname(df_connection *conn, unsigned int room_id, 
					 void (*callback)(df_trackname*, void*), void *context) {
	conn->rget_settings.rgets[DFRGET_TRACKNAME].callback = (void (*)(void))callback;
	conn->rget_settings.rgets[DFRGET_TRACKNAME].context = context;
	return comm_send(conn, 1, "void", 1, NULL, NULL, "[RGetTrackName %u]", room_id);
}

int dfrget_trackposition(df_connection *conn, unsigned int room_id, 
						 void (*callback)(df_time*, void*), void *context) {
	conn->rget_settings.rgets[DFRGET_TRACKPOSITION].callback = (void (*)(void))callback;
	conn->rget_settings.rgets[DFRGET_TRACKPOSITION].context = context;
	return comm_send(conn, 1, "void", 1, NULL, NULL, "[RGetTrackPosition %u]", room_id);
}



void process_incoming_rget(in_settings *settings, char *name, char *command) {
	regex_t *rx_c;
	regex_result *rx;
	df_albumartist *aa;
	df_detailedtrack *dt;
	df_trackname *tn;
	df_time *t;
	char *s;
	int i;
	
	rx = NULL;
	
	if (strcmp(name,"GetAlbumArtist") == 0) {
		rx_c = regex_get_compiled("getalbumartist");
		rx = regex_match(rx_c, command);
		
		
		if ((aa = malloc(sizeof(df_albumartist))) == NULL) {return ;}
		if ((aa->Album = formatting_process(rx->subexps[2].value)) == NULL) {free(aa); return ;}
		if ((aa->Artist = formatting_process(rx->subexps[3].value)) == NULL) {free(aa->Album); free(aa);return ;}
		
		((void (*)(df_albumartist*, void*))settings->rgets[DFRGET_ALBUMARTIST].callback)(aa, settings->rgets[DFRGET_ALBUMARTIST].context);
		
		free(aa->Album);
		free(aa->Artist);
		free(aa);
	}
	else if (strcmp(name,"GetDetailedTrackInfo") == 0) {
		rx_c = regex_get_compiled("getdetailedtrackinfo");
		rx = regex_match(rx_c, command);
		
		if (rx==NULL) { ((void (*)(df_detailedtrack*, void*))(settings->rgets[DFRGET_DETAILTRACKINFO].callback))(dt, settings->rgets[DFRGET_DETAILTRACKINFO].context); return; }
		
		if ((dt = malloc(sizeof(df_detailedtrack))) == NULL) {return;}
		
		sscanf(rx->subexps[2].value, "%d", &dt->key);
		if ((dt->name = formatting_process(rx->subexps[3].value)) == NULL) {return;}
		sscanf(rx->subexps[4].value, "%d", &dt->albumkey);
		if ((dt->albumname = formatting_process(rx->subexps[5].value)) == NULL) {return;}
		sscanf(rx->subexps[6].value, "%d", &dt->artistkey);
		if ((dt->artistname = formatting_process(rx->subexps[7].value)) == NULL) {return;}
		sscanf(rx->subexps[8].value, "%d", &dt->genrekey);
		if ((dt->genrename = formatting_process(rx->subexps[9].value)) == NULL) {return;}
		
		if ((dt->length = malloc(sizeof(df_time))) == NULL) {return;}
		sscanf(rx->subexps[10].value,"%u:%u:%u",&(dt->length->hours), &(dt->length->minutes), &(dt->length->seconds));
		
		sscanf(rx->subexps[11].value, "%d", &dt->source);
		if ((dt->path = strdup(rx->subexps[12].value)) == NULL) {return;}
		
		((void (*)(df_detailedtrack*, void*))(settings->rgets[DFRGET_DETAILTRACKINFO].callback))(dt, settings->rgets[DFRGET_DETAILTRACKINFO].context);
		
		free(dt->length);
		free(dt->name);
		free(dt->albumname);
		free(dt->artistname);
		free(dt->genrename);
		free(dt);
	}
	else if (strcmp(name,"GetLastPlayerError") == 0) {
		rx_c = regex_get_compiled("getlastplayererror");
		rx = regex_match(rx_c, command);
		
		if ((s = formatting_process(rx->subexps[2].value)) == NULL) {return;}
		
		((void (*)(char*, void*))(settings->rgets[DFRGET_LASTPLAYERERROR].callback))(s, settings->rgets[DFRGET_LASTPLAYERERROR].context);
		
		free(s);
		
	}
	else if (strcmp(name,"GetPlayerStatus") == 0) {
		rx_c = regex_get_compiled("getplayerstatus");
		rx = regex_match(rx_c, command);
		
		if ((s = strdup(rx->subexps[2].value)) == NULL) {return;}
		
		((void (*)(char*, void*))(settings->rgets[DFRGET_PLAYERSTATUS].callback))(s, settings->rgets[DFRGET_PLAYERSTATUS].context);
		
		free(s);
	}
	else if (strcmp(name,"GetPlayingCheckSum") == 0) {
		rx_c = regex_get_compiled("getplayingchecksum");
		rx = regex_match(rx_c, command);
		
		if ((s = strdup(rx->subexps[2].value)) == NULL) {return;}
		
		((void (*)(char*, void*))(settings->rgets[DFRGET_PLAYINGCHECKSUM].callback))(s, settings->rgets[DFRGET_PLAYINGCHECKSUM].context);
		
		free(s);
		
	}
	else if (strcmp(name,"GetRepeat") == 0) {
		rx_c = regex_get_compiled("getrepeat");
		rx = regex_match(rx_c, command);
		
		sscanf(rx->subexps[2].value,"%d",&i);
		
		((void (*)(int, void*))(settings->rgets[DFRGET_REPEAT].callback))(i, settings->rgets[DFRGET_REPEAT].context);
	}
	else if (strcmp(name,"GetShuffle") == 0) {
		rx_c = regex_get_compiled("getshuffle");
		rx = regex_match(rx_c, command);
		
		sscanf(rx->subexps[2].value,"%d",&i);
		
		((void (*)(int, void*))(settings->rgets[DFRGET_SHUFFLE].callback))(i, settings->rgets[DFRGET_SHUFFLE].context);
	}
	else if (strcmp(name,"GetTrackName") == 0) {
		rx_c = regex_get_compiled("gettrackname");
		rx = regex_match(rx_c, command);
		
		if ((tn = malloc(sizeof(df_trackname))) == NULL) {return;}
		
		if ((tn->name = formatting_process(rx->subexps[2].value)) == NULL) {return;}
		sscanf(rx->subexps[3].value,"%d",&tn->source);
		if ((tn->path = formatting_process(rx->subexps[4].value)) == NULL) {return;}
		
		((void (*)(df_trackname*, void*))(settings->rgets[DFRGET_TRACKNAME].callback))(tn, settings->rgets[DFRGET_TRACKNAME].context);
		
		free(tn->name);
		free(tn->path);
		free(tn);
	}
	else if (strcmp(name,"GetTrackPosition") == 0) {
		rx_c = regex_get_compiled("gettrackposition");
		rx = regex_match(rx_c, command);
		
		if ((t = malloc(sizeof(df_time))) == NULL) {return;}
		sscanf(rx->subexps[2].value,"%u:%u:%u",&(t->hours), &(t->minutes), &(t->seconds));
		
		((void (*)(df_time*, void*))settings->rgets[DFRGET_TRACKPOSITION].callback)
		(t, settings->rgets[DFRGET_TRACKPOSITION].context);
		
		free(t);
	}
	else {
		fprintf(stdout, "unknown rget (%s) received\n", name);
	}
	
	if (rx!=NULL) regex_free_result(rx);
}



