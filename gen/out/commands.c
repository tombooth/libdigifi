/*
 *  commands.c
 *  libdigifi.new
 *
 *  Created by Tom Booth on 09/04/2010.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

#include "commands.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "comm_out.h"
#include "allocator.h"
#include "formatting.h"
#include "debugging.h"


struct call_holder {
	void (*callback)(void);
	void *context;
};

struct search_call_holder {
  struct call_holder call;
  void (*callback)(df_search*);
};

static void row_handler(out_request *request, out_response *response, int num, void *context);

int df_extract_from(df_search *search, int start, int count) {
  struct call_holder *c;
  
  if ((search->count != -1) && ((search->count < 1) || (((start-1) + count) > search->count))) { 
	  printf("Search Count: %d, start: %d, count: %d\n", search->count, start, count);
	  DFERROR("Failed to extract from a search due to bad parameters"); 
	  return -1; 
  }
  
  c = (struct call_holder *)malloc(sizeof(struct call_holder));
  c->callback = search->callback;
  c->context = search->context;
  
  return comm_send_via_socket(search->socket, search->name, (count < 0) ? search->count : count, row_handler, c, "[GetRows %d %d %d]", search->id, start, count);
}

void df_free_search(df_search *search) { allocator_return(search->id); free(search); }

static void create_search_struct(out_request *request, out_response *response, int num, void *context) {
  regex_result *rx;
  df_search *s = NULL;
  struct search_call_holder *sch;
  
  if (response != NULL) {
    s = (df_search*) malloc(sizeof(df_search));
    rx = response->result->result;
    
    s->socket = request->socket;
    sscanf(rx->subexps[2].value,"%d",&(s->id));
		sscanf(rx->subexps[rx->num_subexps-1].value,"%d",&(s->count));
		s->name = strdup(rx->subexps[1].value);
    
    sch = (struct search_call_holder *)context;
    s->callback = sch->call.callback;
    s->context = sch->call.context;
    
    sch->callback(s);
  }
}

static void pull_rows(out_request *request, out_response *response, int num, void *context) {
	int search_num, row_count;
	char *call_name;
	regex_result *rx;

	if (response != NULL) {
		// get the searchnum and row count
		rx = response->result->result;
		sscanf(rx->subexps[rx->num_subexps-2].value,"%d",&search_num);
		sscanf(rx->subexps[rx->num_subexps-1].value,"%d",&row_count);
		call_name = strdup(rx->subexps[1].value);

		if (row_count < 1) {
			// if there are no rows to return
		} else {	
			// if there are rows
			comm_send_via_socket(request->socket, call_name, row_count, row_handler, context, "[GetRows %d 1 -1]", search_num);
		}

		free(call_name);
	}

	allocator_return(search_num);
}


static char* dfdate_to_string(df_date date) {
	char *datebuffer;

	datebuffer = malloc(sizeof(char) * 16);

	snprintf(datebuffer, 16, "%u-%u-%u", date.year, date.month, date.day);

	return datebuffer;
}

static char* dftime_to_string(df_time time) {
	char *timebuffer;

	timebuffer = malloc(sizeof(char) * 16);

	snprintf(timebuffer, 16, "%u:%u:%u", time.hours, time.minutes, time.seconds);

	return timebuffer;
}






static void GetCurOp_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetCurOp(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetCurOp", 1, GetCurOp_handler, c, "[GetCurOp %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void ReleaseSerialPort_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_ReleaseSerialPort(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ReleaseSerialPort", 1, ReleaseSerialPort_handler, c, "[ReleaseSerialPort %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void Version_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_Version(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "Version", 1, Version_handler, c, "[Version %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetRows_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetRows(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetRows", 1, GetRows_handler, c, "[GetRows %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetCount_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetCount(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetCount", 1, GetCount_handler, c, "[GetCount %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetLastError_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetLastError(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetLastError", 1, GetLastError_handler, c, "[GetLastError %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void LookupError_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_LookupError(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "LookupError", 1, LookupError_handler, c, "[LookupError %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void FindAllRooms_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_FindAllRooms(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "FindAllRooms", 1, FindAllRooms_handler, c, "[FindAllRooms %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void FindNewRooms_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_FindNewRooms(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "FindNewRooms", 1, FindNewRooms_handler, c, "[FindNewRooms %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void RemoveOldRooms_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_RemoveOldRooms(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RemoveOldRooms", 1, RemoveOldRooms_handler, c, "[RemoveOldRooms %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void ServiceMode_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_ServiceMode(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ServiceMode", 1, ServiceMode_handler, c, "[ServiceMode %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetSearchOffset_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetSearchOffset(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetSearchOffset", 1, GetSearchOffset_handler, c, "[GetSearchOffset %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void FilterSearch_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_FilterSearch(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "FilterSearch", 1, FilterSearch_handler, c, "[FilterSearch %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void SortSearch_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_SortSearch(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "SortSearch", 1, SortSearch_handler, c, "[SortSearch %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetSystemTime_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetSystemTime(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetSystemTime", 1, GetSystemTime_handler, c, "[GetSystemTime %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetHostDetails_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetHostDetails(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetHostDetails", 1, GetHostDetails_handler, c, "[GetHostDetails %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetRecycleBinStatus_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetRecycleBinStatus(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetRecycleBinStatus", 1, GetRecycleBinStatus_handler, c, "[GetRecycleBinStatus %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetSetupVal_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetSetupVal(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetSetupVal", 1, GetSetupVal_handler, c, "[GetSetupVal %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void NextTrack_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_NextTrack(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "NextTrack", 1, NextTrack_handler, c, "[NextTrack %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void PrevTrack_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_PrevTrack(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "PrevTrack", 1, PrevTrack_handler, c, "[PrevTrack %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void RemoveTrack_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_RemoveTrack(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RemoveTrack", 1, RemoveTrack_handler, c, "[RemoveTrack %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void PlayAlbums_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_PlayAlbums(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "PlayAlbums", 1, PlayAlbums_handler, c, "[PlayAlbums %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void PlayAll_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_PlayAll(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "PlayAll", 1, PlayAll_handler, c, "[PlayAll %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void PlayAlbum_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_PlayAlbum(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "PlayAlbum", 1, PlayAlbum_handler, c, "[PlayAlbum %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void PlayTrack_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_PlayTrack(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "PlayTrack", 1, PlayTrack_handler, c, "[PlayTrack %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void PlayTracks_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_PlayTracks(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "PlayTracks", 1, PlayTracks_handler, c, "[PlayTracks %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void PlayTracksFromSearch_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_PlayTracksFromSearch(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "PlayTracksFromSearch", 1, PlayTracksFromSearch_handler, c, "[PlayTracksFromSearch %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void PlayAlbumsFromSearch_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_PlayAlbumsFromSearch(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "PlayAlbumsFromSearch", 1, PlayAlbumsFromSearch_handler, c, "[PlayAlbumsFromSearch %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void PlayUrl_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_PlayUrl(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "PlayUrl", 1, PlayUrl_handler, c, "[PlayUrl %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void PlayUrls_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_PlayUrls(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "PlayUrls", 1, PlayUrls_handler, c, "[PlayUrls %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void PlayPlaylist_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_PlayPlaylist(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "PlayPlaylist", 1, PlayPlaylist_handler, c, "[PlayPlaylist %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void PlayRandom_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_PlayRandom(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "PlayRandom", 1, PlayRandom_handler, c, "[PlayRandom %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void PlayArtistAlbum_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_PlayArtistAlbum(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "PlayArtistAlbum", 1, PlayArtistAlbum_handler, c, "[PlayArtistAlbum %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void PlayLastPlayed_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_PlayLastPlayed(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "PlayLastPlayed", 1, PlayLastPlayed_handler, c, "[PlayLastPlayed %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void PlayLastRipped_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_PlayLastRipped(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "PlayLastRipped", 1, PlayLastRipped_handler, c, "[PlayLastRipped %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void PlayMostPopular_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_PlayMostPopular(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "PlayMostPopular", 1, PlayMostPopular_handler, c, "[PlayMostPopular %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void IsCDPlaying_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_IsCDPlaying(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "IsCDPlaying", 1, IsCDPlaying_handler, c, "[IsCDPlaying %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetTrackName_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetTrackName(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTrackName", 1, GetTrackName_handler, c, "[GetTrackName %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetTrackDetailsFromPlayer_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetTrackDetailsFromPlayer(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTrackDetailsFromPlayer", 1, GetTrackDetailsFromPlayer_handler, c, "[GetTrackDetailsFromPlayer %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAlbumArtist_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAlbumArtist(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlbumArtist", 1, GetAlbumArtist_handler, c, "[GetAlbumArtist %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetTrackNum_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetTrackNum(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTrackNum", 1, GetTrackNum_handler, c, "[GetTrackNum %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetTrackCount_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetTrackCount(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTrackCount", 1, GetTrackCount_handler, c, "[GetTrackCount %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetShuffle_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetShuffle(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetShuffle", 1, GetShuffle_handler, c, "[GetShuffle %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetRepeat_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetRepeat(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetRepeat", 1, GetRepeat_handler, c, "[GetRepeat %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetPlayerStatus_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetPlayerStatus(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetPlayerStatus", 1, GetPlayerStatus_handler, c, "[GetPlayerStatus %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetTrackLength_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetTrackLength(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTrackLength", 1, GetTrackLength_handler, c, "[GetTrackLength %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetTrackPosition_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetTrackPosition(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTrackPosition", 1, GetTrackPosition_handler, c, "[GetTrackPosition %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetPlayerVersion_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetPlayerVersion(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetPlayerVersion", 1, GetPlayerVersion_handler, c, "[GetPlayerVersion %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetVolume_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetVolume(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetVolume", 1, GetVolume_handler, c, "[GetVolume %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void QueryAllPlayback_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_QueryAllPlayback(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "QueryAllPlayback", 1, QueryAllPlayback_handler, c, "[QueryAllPlayback %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetRooms_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetRooms(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetRooms", 1, GetRooms_handler, c, "[GetRooms %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetRoomsWithPlayBack_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetRoomsWithPlayBack(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetRoomsWithPlayBack", 1, GetRoomsWithPlayBack_handler, c, "[GetRoomsWithPlayBack %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetRoomsWithRipping_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetRoomsWithRipping(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetRoomsWithRipping", 1, GetRoomsWithRipping_handler, c, "[GetRoomsWithRipping %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetNonLinkedRooms_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetNonLinkedRooms(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetNonLinkedRooms", 1, GetNonLinkedRooms_handler, c, "[GetNonLinkedRooms %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetLinkedRooms_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetLinkedRooms(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetLinkedRooms", 1, GetLinkedRooms_handler, c, "[GetLinkedRooms %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAdvancedStatus_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAdvancedStatus(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAdvancedStatus", 1, GetAdvancedStatus_handler, c, "[GetAdvancedStatus %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetUserStatus_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetUserStatus(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetUserStatus", 1, GetUserStatus_handler, c, "[GetUserStatus %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetStatusMessages_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetStatusMessages(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetStatusMessages", 1, GetStatusMessages_handler, c, "[GetStatusMessages %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetStatusMessageDetail_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetStatusMessageDetail(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetStatusMessageDetail", 1, GetStatusMessageDetail_handler, c, "[GetStatusMessageDetail %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetCurrentPlayList_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetCurrentPlayList(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetCurrentPlayList", 1, GetCurrentPlayList_handler, c, "[GetCurrentPlayList %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetCurrentPlaylistEx_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetCurrentPlaylistEx(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetCurrentPlaylistEx", 1, GetCurrentPlaylistEx_handler, c, "[GetCurrentPlaylistEx %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetRippingAlerts_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetRippingAlerts(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetRippingAlerts", 1, GetRippingAlerts_handler, c, "[GetRippingAlerts %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAlertDetails_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAlertDetails(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlertDetails", 1, GetAlertDetails_handler, c, "[GetAlertDetails %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetRippingStatus_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetRippingStatus(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetRippingStatus", 1, GetRippingStatus_handler, c, "[GetRippingStatus %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetRipEncSettings_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetRipEncSettings(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetRipEncSettings", 1, GetRipEncSettings_handler, c, "[GetRipEncSettings %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetRipEncSettingsEx_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetRipEncSettingsEx(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetRipEncSettingsEx", 1, GetRipEncSettingsEx_handler, c, "[GetRipEncSettingsEx %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetSettings_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetSettings(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetSettings", 1, GetSettings_handler, c, "[GetSettings %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetSettingsEx_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetSettingsEx(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetSettingsEx", 1, GetSettingsEx_handler, c, "[GetSettingsEx %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAvailableValues_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAvailableValues(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAvailableValues", 1, GetAvailableValues_handler, c, "[GetAvailableValues %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetSystemDrives_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetSystemDrives(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetSystemDrives", 1, GetSystemDrives_handler, c, "[GetSystemDrives %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetEncodingQueue_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetEncodingQueue(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetEncodingQueue", 1, GetEncodingQueue_handler, c, "[GetEncodingQueue %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetLibraryCheckSum_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetLibraryCheckSum(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetLibraryCheckSum", 1, GetLibraryCheckSum_handler, c, "[GetLibraryCheckSum %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void CancelRipping_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_CancelRipping(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CancelRipping", 1, CancelRipping_handler, c, "[CancelRipping %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetEncodingStatus_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetEncodingStatus(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetEncodingStatus", 1, GetEncodingStatus_handler, c, "[GetEncodingStatus %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetPlayerInstances_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetPlayerInstances(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetPlayerInstances", 1, GetPlayerInstances_handler, c, "[GetPlayerInstances %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetOutputDevices_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetOutputDevices(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetOutputDevices", 1, GetOutputDevices_handler, c, "[GetOutputDevices %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetOutputChannels_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetOutputChannels(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetOutputChannels", 1, GetOutputChannels_handler, c, "[GetOutputChannels %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetUpnpMediaRenderers_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetUpnpMediaRenderers(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetUpnpMediaRenderers", 1, GetUpnpMediaRenderers_handler, c, "[GetUpnpMediaRenderers %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAsio4AllChannels_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAsio4AllChannels(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAsio4AllChannels", 1, GetAsio4AllChannels_handler, c, "[GetAsio4AllChannels %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetDevices_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetDevices(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetDevices", 1, GetDevices_handler, c, "[GetDevices %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetDeviceDetails_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetDeviceDetails(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetDeviceDetails", 1, GetDeviceDetails_handler, c, "[GetDeviceDetails %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExternalStorages_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExternalStorages(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExternalStorages", 1, GetExternalStorages_handler, c, "[GetExternalStorages %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void BackupUserPlaylists_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_BackupUserPlaylists(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "BackupUserPlaylists", 1, BackupUserPlaylists_handler, c, "[BackupUserPlaylists %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void RestoreUserPlaylists_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_RestoreUserPlaylists(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RestoreUserPlaylists", 1, RestoreUserPlaylists_handler, c, "[RestoreUserPlaylists %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void SetNetworkBackup_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_SetNetworkBackup(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "SetNetworkBackup", 1, SetNetworkBackup_handler, c, "[SetNetworkBackup %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetNetworkBackup_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetNetworkBackup(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetNetworkBackup", 1, GetNetworkBackup_handler, c, "[GetNetworkBackup %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetDriveDetail_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetDriveDetail(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetDriveDetail", 1, GetDriveDetail_handler, c, "[GetDriveDetail %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetFileSystemDriveDetail_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetFileSystemDriveDetail(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetFileSystemDriveDetail", 1, GetFileSystemDriveDetail_handler, c, "[GetFileSystemDriveDetail %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void AddNewDrive_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_AddNewDrive(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "AddNewDrive", 1, AddNewDrive_handler, c, "[AddNewDrive %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void UpdateDrive_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_UpdateDrive(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "UpdateDrive", 1, UpdateDrive_handler, c, "[UpdateDrive %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void DeleteDrive_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_DeleteDrive(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "DeleteDrive", 1, DeleteDrive_handler, c, "[DeleteDrive %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void DeleteRoom_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_DeleteRoom(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "DeleteRoom", 1, DeleteRoom_handler, c, "[DeleteRoom %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void DeleteLinkedRoom_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_DeleteLinkedRoom(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "DeleteLinkedRoom", 1, DeleteLinkedRoom_handler, c, "[DeleteLinkedRoom %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetSingleSystemSetting_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetSingleSystemSetting(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetSingleSystemSetting", 1, GetSingleSystemSetting_handler, c, "[GetSingleSystemSetting %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetSingleRipEncSetting_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetSingleRipEncSetting(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetSingleRipEncSetting", 1, GetSingleRipEncSetting_handler, c, "[GetSingleRipEncSetting %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void UpdateSingleRipEncSetting_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_UpdateSingleRipEncSetting(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "UpdateSingleRipEncSetting", 1, UpdateSingleRipEncSetting_handler, c, "[UpdateSingleRipEncSetting %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void UpdateSingleSystemSetting_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_UpdateSingleSystemSetting(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "UpdateSingleSystemSetting", 1, UpdateSingleSystemSetting_handler, c, "[UpdateSingleSystemSetting %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetRoomDetail_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetRoomDetail(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetRoomDetail", 1, GetRoomDetail_handler, c, "[GetRoomDetail %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetLinkedRoomDetail_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetLinkedRoomDetail(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetLinkedRoomDetail", 1, GetLinkedRoomDetail_handler, c, "[GetLinkedRoomDetail %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void AddNewLinkedRoom_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_AddNewLinkedRoom(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "AddNewLinkedRoom", 1, AddNewLinkedRoom_handler, c, "[AddNewLinkedRoom %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void UpdateLinkedRoom_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_UpdateLinkedRoom(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "UpdateLinkedRoom", 1, UpdateLinkedRoom_handler, c, "[UpdateLinkedRoom %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void AddNewRoom_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_AddNewRoom(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "AddNewRoom", 1, AddNewRoom_handler, c, "[AddNewRoom %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void UpdateRoom_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_UpdateRoom(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "UpdateRoom", 1, UpdateRoom_handler, c, "[UpdateRoom %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetGenreDetail_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetGenreDetail(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetGenreDetail", 1, GetGenreDetail_handler, c, "[GetGenreDetail %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void AddNewGenre_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_AddNewGenre(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "AddNewGenre", 1, AddNewGenre_handler, c, "[AddNewGenre %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void UpdateGenre_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_UpdateGenre(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "UpdateGenre", 1, UpdateGenre_handler, c, "[UpdateGenre %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void DeleteGenre_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_DeleteGenre(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "DeleteGenre", 1, DeleteGenre_handler, c, "[DeleteGenre %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetSubGenreDetail_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetSubGenreDetail(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetSubGenreDetail", 1, GetSubGenreDetail_handler, c, "[GetSubGenreDetail %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void AddNewSubGenre_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_AddNewSubGenre(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "AddNewSubGenre", 1, AddNewSubGenre_handler, c, "[AddNewSubGenre %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void UpdateSubGenre_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_UpdateSubGenre(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "UpdateSubGenre", 1, UpdateSubGenre_handler, c, "[UpdateSubGenre %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void DeleteSubGenre_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_DeleteSubGenre(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "DeleteSubGenre", 1, DeleteSubGenre_handler, c, "[DeleteSubGenre %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void CompactGenreOrdinals_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_CompactGenreOrdinals(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CompactGenreOrdinals", 1, CompactGenreOrdinals_handler, c, "[CompactGenreOrdinals %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void TestRows_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_TestRows(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "TestRows", 1, TestRows_handler, c, "[TestRows %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void SavePlayerInstance_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_SavePlayerInstance(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "SavePlayerInstance", 1, SavePlayerInstance_handler, c, "[SavePlayerInstance %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void RemovePlayerInstance_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_RemovePlayerInstance(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RemovePlayerInstance", 1, RemovePlayerInstance_handler, c, "[RemovePlayerInstance %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void DisconnectDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_DisconnectDevice(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "DisconnectDevice", 1, DisconnectDevice_handler, c, "[DisconnectDevice %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void DeviceChecksum_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_DeviceChecksum(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "DeviceChecksum", 1, DeviceChecksum_handler, c, "[DeviceChecksum %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void DeleteDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_DeleteDevice(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "DeleteDevice", 1, DeleteDevice_handler, c, "[DeleteDevice %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void ToggleDeviceSync_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_ToggleDeviceSync(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ToggleDeviceSync", 1, ToggleDeviceSync_handler, c, "[ToggleDeviceSync %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void IgnoreExternalStorage_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_IgnoreExternalStorage(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "IgnoreExternalStorage", 1, IgnoreExternalStorage_handler, c, "[IgnoreExternalStorage %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void ExternalStorageCancelScan_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_ExternalStorageCancelScan(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ExternalStorageCancelScan", 1, ExternalStorageCancelScan_handler, c, "[ExternalStorageCancelScan %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void ActivateExternalStorage_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_ActivateExternalStorage(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ActivateExternalStorage", 1, ActivateExternalStorage_handler, c, "[ActivateExternalStorage %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void AddExternalStorage_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_AddExternalStorage(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "AddExternalStorage", 1, AddExternalStorage_handler, c, "[AddExternalStorage %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void ScanForExternalStorages_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_ScanForExternalStorages(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ScanForExternalStorages", 1, ScanForExternalStorages_handler, c, "[ScanForExternalStorages %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void RescanExternalStorages_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_RescanExternalStorages(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RescanExternalStorages", 1, RescanExternalStorages_handler, c, "[RescanExternalStorages %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void ScanExternalStorage_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_ScanExternalStorage(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ScanExternalStorage", 1, ScanExternalStorage_handler, c, "[ScanExternalStorage %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void RemoveExternalStorage_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_RemoveExternalStorage(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RemoveExternalStorage", 1, RemoveExternalStorage_handler, c, "[RemoveExternalStorage %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExternalStorageDetail_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExternalStorageDetail(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExternalStorageDetail", 1, GetExternalStorageDetail_handler, c, "[GetExternalStorageDetail %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void UpdateExternalStorage_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_UpdateExternalStorage(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "UpdateExternalStorage", 1, UpdateExternalStorage_handler, c, "[UpdateExternalStorage %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void NewOutputChannel_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_NewOutputChannel(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "NewOutputChannel", 1, NewOutputChannel_handler, c, "[NewOutputChannel %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void UpdateOutputChannel_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_UpdateOutputChannel(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "UpdateOutputChannel", 1, UpdateOutputChannel_handler, c, "[UpdateOutputChannel %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void DeleteOutputChannel_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_DeleteOutputChannel(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "DeleteOutputChannel", 1, DeleteOutputChannel_handler, c, "[DeleteOutputChannel %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void SetDriveUsage_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_SetDriveUsage(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "SetDriveUsage", 1, SetDriveUsage_handler, c, "[SetDriveUsage %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void BackupDrive_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_BackupDrive(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "BackupDrive", 1, BackupDrive_handler, c, "[BackupDrive %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void StopBackupDrive_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_StopBackupDrive(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "StopBackupDrive", 1, StopBackupDrive_handler, c, "[StopBackupDrive %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetBackupStatus_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetBackupStatus(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetBackupStatus", 1, GetBackupStatus_handler, c, "[GetBackupStatus %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void AddNewBackupJob_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_AddNewBackupJob(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "AddNewBackupJob", 1, AddNewBackupJob_handler, c, "[AddNewBackupJob %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void UpdateBackupJob_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_UpdateBackupJob(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "UpdateBackupJob", 1, UpdateBackupJob_handler, c, "[UpdateBackupJob %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void DeleteBackupJob_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_DeleteBackupJob(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "DeleteBackupJob", 1, DeleteBackupJob_handler, c, "[DeleteBackupJob %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetBackupJobs_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetBackupJobs(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetBackupJobs", 1, GetBackupJobs_handler, c, "[GetBackupJobs %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetBackupJobDetail_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetBackupJobDetail(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetBackupJobDetail", 1, GetBackupJobDetail_handler, c, "[GetBackupJobDetail %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetBackupLogs_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetBackupLogs(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetBackupLogs", 1, GetBackupLogs_handler, c, "[GetBackupLogs %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetBackupLogDetail_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetBackupLogDetail(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetBackupLogDetail", 1, GetBackupLogDetail_handler, c, "[GetBackupLogDetail %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void ChangeNetworkDhcp_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_ChangeNetworkDhcp(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ChangeNetworkDhcp", 1, ChangeNetworkDhcp_handler, c, "[ChangeNetworkDhcp %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void ChangeNetworkStatic_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_ChangeNetworkStatic(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ChangeNetworkStatic", 1, ChangeNetworkStatic_handler, c, "[ChangeNetworkStatic %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void ChangeNetworkAutoIP_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_ChangeNetworkAutoIP(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ChangeNetworkAutoIP", 1, ChangeNetworkAutoIP_handler, c, "[ChangeNetworkAutoIP %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void ChangeNetworkWorkgroup_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_ChangeNetworkWorkgroup(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ChangeNetworkWorkgroup", 1, ChangeNetworkWorkgroup_handler, c, "[ChangeNetworkWorkgroup %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void ChangeNetworkMachineName_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_ChangeNetworkMachineName(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ChangeNetworkMachineName", 1, ChangeNetworkMachineName_handler, c, "[ChangeNetworkMachineName %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void ChangeSystemSerialNumber_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_ChangeSystemSerialNumber(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ChangeSystemSerialNumber", 1, ChangeSystemSerialNumber_handler, c, "[ChangeSystemSerialNumber %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void ProcessEmbeddedInit_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_ProcessEmbeddedInit(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ProcessEmbeddedInit", 1, ProcessEmbeddedInit_handler, c, "[ProcessEmbeddedInit %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetNetworkActiveAdapters_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetNetworkActiveAdapters(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetNetworkActiveAdapters", 1, GetNetworkActiveAdapters_handler, c, "[GetNetworkActiveAdapters %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetNetworkWorkgroup_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetNetworkWorkgroup(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetNetworkWorkgroup", 1, GetNetworkWorkgroup_handler, c, "[GetNetworkWorkgroup %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void ComplexSearchGetAlbums_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_ComplexSearchGetAlbums(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ComplexSearchGetAlbums", 1, ComplexSearchGetAlbums_handler, c, "[ComplexSearchGetAlbums %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void ComplexSearchCountAlbums_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_ComplexSearchCountAlbums(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ComplexSearchCountAlbums", 1, ComplexSearchCountAlbums_handler, c, "[ComplexSearchCountAlbums %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void ComplexSearchGetTracks_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_ComplexSearchGetTracks(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ComplexSearchGetTracks", 1, ComplexSearchGetTracks_handler, c, "[ComplexSearchGetTracks %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void ComplexSearchCountTracks_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_ComplexSearchCountTracks(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ComplexSearchCountTracks", 1, ComplexSearchCountTracks_handler, c, "[ComplexSearchCountTracks %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void ComplexSearchGetArtists_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_ComplexSearchGetArtists(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ComplexSearchGetArtists", 1, ComplexSearchGetArtists_handler, c, "[ComplexSearchGetArtists %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void ComplexSearchCountArtists_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_ComplexSearchCountArtists(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ComplexSearchCountArtists", 1, ComplexSearchCountArtists_handler, c, "[ComplexSearchCountArtists %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void ComplexSearchGetContributors_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_ComplexSearchGetContributors(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ComplexSearchGetContributors", 1, ComplexSearchGetContributors_handler, c, "[ComplexSearchGetContributors %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void ComplexSearchCountContributors_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_ComplexSearchCountContributors(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ComplexSearchCountContributors", 1, ComplexSearchCountContributors_handler, c, "[ComplexSearchCountContributors %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAlbums_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAlbums(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlbums", 1, GetAlbums_handler, c, "[GetAlbums %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAlbumsForStore_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAlbumsForStore(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlbumsForStore", 1, GetAlbumsForStore_handler, c, "[GetAlbumsForStore %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAlbumsForArtists_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAlbumsForArtists(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlbumsForArtists", 1, GetAlbumsForArtists_handler, c, "[GetAlbumsForArtists %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAlbumsForArtistsInSubGenre_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAlbumsForArtistsInSubGenre(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlbumsForArtistsInSubGenre", 1, GetAlbumsForArtistsInSubGenre_handler, c, "[GetAlbumsForArtistsInSubGenre %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAlbumsForArtistsInSubGenreForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAlbumsForArtistsInSubGenreForDevice(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlbumsForArtistsInSubGenreForDevice", 1, GetAlbumsForArtistsInSubGenreForDevice_handler, c, "[GetAlbumsForArtistsInSubGenreForDevice %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAlbumsForArtistsInSubGenreForServer_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAlbumsForArtistsInSubGenreForServer(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlbumsForArtistsInSubGenreForServer", 1, GetAlbumsForArtistsInSubGenreForServer_handler, c, "[GetAlbumsForArtistsInSubGenreForServer %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAlbumsForArtistsInSubGenreForShare_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAlbumsForArtistsInSubGenreForShare(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlbumsForArtistsInSubGenreForShare", 1, GetAlbumsForArtistsInSubGenreForShare_handler, c, "[GetAlbumsForArtistsInSubGenreForShare %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAlbumsForArtistsInGenre_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAlbumsForArtistsInGenre(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlbumsForArtistsInGenre", 1, GetAlbumsForArtistsInGenre_handler, c, "[GetAlbumsForArtistsInGenre %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAlbumsForArtistsForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAlbumsForArtistsForDevice(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlbumsForArtistsForDevice", 1, GetAlbumsForArtistsForDevice_handler, c, "[GetAlbumsForArtistsForDevice %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAlbumsForArtistsForShare_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAlbumsForArtistsForShare(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlbumsForArtistsForShare", 1, GetAlbumsForArtistsForShare_handler, c, "[GetAlbumsForArtistsForShare %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAlbumsForArtistsForServer_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAlbumsForArtistsForServer(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlbumsForArtistsForServer", 1, GetAlbumsForArtistsForServer_handler, c, "[GetAlbumsForArtistsForServer %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAlbumsForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAlbumsForDevice(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlbumsForDevice", 1, GetAlbumsForDevice_handler, c, "[GetAlbumsForDevice %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAlbumsForShare_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAlbumsForShare(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlbumsForShare", 1, GetAlbumsForShare_handler, c, "[GetAlbumsForShare %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAlbumsForServer_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAlbumsForServer(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlbumsForServer", 1, GetAlbumsForServer_handler, c, "[GetAlbumsForServer %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAlbumsForPlaylist_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAlbumsForPlaylist(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlbumsForPlaylist", 1, GetAlbumsForPlaylist_handler, c, "[GetAlbumsForPlaylist %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAlbumsSearchAlbumArtist_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAlbumsSearchAlbumArtist(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlbumsSearchAlbumArtist", 1, GetAlbumsSearchAlbumArtist_handler, c, "[GetAlbumsSearchAlbumArtist %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetLatestPlayedAlbums_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetLatestPlayedAlbums(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetLatestPlayedAlbums", 1, GetLatestPlayedAlbums_handler, c, "[GetLatestPlayedAlbums %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetNewestAlbums_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetNewestAlbums(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetNewestAlbums", 1, GetNewestAlbums_handler, c, "[GetNewestAlbums %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetPlayListsByLetter_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetPlayListsByLetter(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetPlayListsByLetter", 1, GetPlayListsByLetter_handler, c, "[GetPlayListsByLetter %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetPlaylistsForGenre_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetPlaylistsForGenre(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetPlaylistsForGenre", 1, GetPlaylistsForGenre_handler, c, "[GetPlaylistsForGenre %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetPlaylistsForSubGenre_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetPlaylistsForSubGenre(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetPlaylistsForSubGenre", 1, GetPlaylistsForSubGenre_handler, c, "[GetPlaylistsForSubGenre %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetPlaylistsForSubGenreForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetPlaylistsForSubGenreForDevice(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetPlaylistsForSubGenreForDevice", 1, GetPlaylistsForSubGenreForDevice_handler, c, "[GetPlaylistsForSubGenreForDevice %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetPlaylistsForSubGenreForShare_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetPlaylistsForSubGenreForShare(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetPlaylistsForSubGenreForShare", 1, GetPlaylistsForSubGenreForShare_handler, c, "[GetPlaylistsForSubGenreForShare %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetPlaylistsForSubGenreForServer_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetPlaylistsForSubGenreForServer(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetPlaylistsForSubGenreForServer", 1, GetPlaylistsForSubGenreForServer_handler, c, "[GetPlaylistsForSubGenreForServer %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetUserPlaylistsForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetUserPlaylistsForDevice(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetUserPlaylistsForDevice", 1, GetUserPlaylistsForDevice_handler, c, "[GetUserPlaylistsForDevice %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetUserPlaylistsForShare_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetUserPlaylistsForShare(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetUserPlaylistsForShare", 1, GetUserPlaylistsForShare_handler, c, "[GetUserPlaylistsForShare %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetUserPlaylistsForServer_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetUserPlaylistsForServer(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetUserPlaylistsForServer", 1, GetUserPlaylistsForServer_handler, c, "[GetUserPlaylistsForServer %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetUserPlaylists_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetUserPlaylists(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetUserPlaylists", 1, GetUserPlaylists_handler, c, "[GetUserPlaylists %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetTopPlayedAlbums_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetTopPlayedAlbums(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTopPlayedAlbums", 1, GetTopPlayedAlbums_handler, c, "[GetTopPlayedAlbums %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAlbumsOtherInfo_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAlbumsOtherInfo(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlbumsOtherInfo", 1, GetAlbumsOtherInfo_handler, c, "[GetAlbumsOtherInfo %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAlbumsOtherInfoForServer_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAlbumsOtherInfoForServer(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlbumsOtherInfoForServer", 1, GetAlbumsOtherInfoForServer_handler, c, "[GetAlbumsOtherInfoForServer %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAlbumsOtherInfoForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAlbumsOtherInfoForDevice(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlbumsOtherInfoForDevice", 1, GetAlbumsOtherInfoForDevice_handler, c, "[GetAlbumsOtherInfoForDevice %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAlbumsOtherInfoForShare_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAlbumsOtherInfoForShare(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlbumsOtherInfoForShare", 1, GetAlbumsOtherInfoForShare_handler, c, "[GetAlbumsOtherInfoForShare %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAlbumsOtherInfoAll_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAlbumsOtherInfoAll(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlbumsOtherInfoAll", 1, GetAlbumsOtherInfoAll_handler, c, "[GetAlbumsOtherInfoAll %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAlbumDetails_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAlbumDetails(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlbumDetails", 1, GetAlbumDetails_handler, c, "[GetAlbumDetails %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetTracksAll_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetTracksAll(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTracksAll", 1, GetTracksAll_handler, c, "[GetTracksAll %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetTrackRange_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetTrackRange(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTrackRange", 1, GetTrackRange_handler, c, "[GetTrackRange %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetTracksForArtist_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetTracksForArtist(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTracksForArtist", 1, GetTracksForArtist_handler, c, "[GetTracksForArtist %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetTracksForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetTracksForDevice(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTracksForDevice", 1, GetTracksForDevice_handler, c, "[GetTracksForDevice %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetTracksForShare_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetTracksForShare(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTracksForShare", 1, GetTracksForShare_handler, c, "[GetTracksForShare %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetTracksForServer_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetTracksForServer(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTracksForServer", 1, GetTracksForServer_handler, c, "[GetTracksForServer %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetTracksForGenre_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetTracksForGenre(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTracksForGenre", 1, GetTracksForGenre_handler, c, "[GetTracksForGenre %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetTracksForPlaylist_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetTracksForPlaylist(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTracksForPlaylist", 1, GetTracksForPlaylist_handler, c, "[GetTracksForPlaylist %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetTracksForSubGenre_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetTracksForSubGenre(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTracksForSubGenre", 1, GetTracksForSubGenre_handler, c, "[GetTracksForSubGenre %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetTracksOtherInfo_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetTracksOtherInfo(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTracksOtherInfo", 1, GetTracksOtherInfo_handler, c, "[GetTracksOtherInfo %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetTracksSearchName_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetTracksSearchName(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTracksSearchName", 1, GetTracksSearchName_handler, c, "[GetTracksSearchName %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void AdvancedSearch_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_AdvancedSearch(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "AdvancedSearch", 1, AdvancedSearch_handler, c, "[AdvancedSearch %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetTracksForNamedEntity_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetTracksForNamedEntity(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTracksForNamedEntity", 1, GetTracksForNamedEntity_handler, c, "[GetTracksForNamedEntity %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetTracksForAlbumInUPL_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetTracksForAlbumInUPL(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTracksForAlbumInUPL", 1, GetTracksForAlbumInUPL_handler, c, "[GetTracksForAlbumInUPL %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetArtistDetails_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetArtistDetails(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetArtistDetails", 1, GetArtistDetails_handler, c, "[GetArtistDetails %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetArtists_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetArtists(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetArtists", 1, GetArtists_handler, c, "[GetArtists %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetArtistsInGenre_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetArtistsInGenre(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetArtistsInGenre", 1, GetArtistsInGenre_handler, c, "[GetArtistsInGenre %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetArtistsInSubGenre_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetArtistsInSubGenre(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetArtistsInSubGenre", 1, GetArtistsInSubGenre_handler, c, "[GetArtistsInSubGenre %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetArtistsInSubGenreForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetArtistsInSubGenreForDevice(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetArtistsInSubGenreForDevice", 1, GetArtistsInSubGenreForDevice_handler, c, "[GetArtistsInSubGenreForDevice %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetArtistsInSubGenreForServer_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetArtistsInSubGenreForServer(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetArtistsInSubGenreForServer", 1, GetArtistsInSubGenreForServer_handler, c, "[GetArtistsInSubGenreForServer %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetArtistsInSubGenreForShare_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetArtistsInSubGenreForShare(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetArtistsInSubGenreForShare", 1, GetArtistsInSubGenreForShare_handler, c, "[GetArtistsInSubGenreForShare %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetArtistsForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetArtistsForDevice(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetArtistsForDevice", 1, GetArtistsForDevice_handler, c, "[GetArtistsForDevice %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetArtistsForShare_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetArtistsForShare(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetArtistsForShare", 1, GetArtistsForShare_handler, c, "[GetArtistsForShare %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetArtistsForServer_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetArtistsForServer(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetArtistsForServer", 1, GetArtistsForServer_handler, c, "[GetArtistsForServer %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetGenres_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetGenres(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetGenres", 1, GetGenres_handler, c, "[GetGenres %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetSubGenresForGenre_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetSubGenresForGenre(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetSubGenresForGenre", 1, GetSubGenresForGenre_handler, c, "[GetSubGenresForGenre %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetGenresSubGenres_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetGenresSubGenres(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetGenresSubGenres", 1, GetGenresSubGenres_handler, c, "[GetGenresSubGenres %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetSubGenresForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetSubGenresForDevice(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetSubGenresForDevice", 1, GetSubGenresForDevice_handler, c, "[GetSubGenresForDevice %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetSubGenresForShare_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetSubGenresForShare(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetSubGenresForShare", 1, GetSubGenresForShare_handler, c, "[GetSubGenresForShare %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetSubGenresForServer_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetSubGenresForServer(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetSubGenresForServer", 1, GetSubGenresForServer_handler, c, "[GetSubGenresForServer %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetCDDBGenres_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetCDDBGenres(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetCDDBGenres", 1, GetCDDBGenres_handler, c, "[GetCDDBGenres %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void SaveCurrentPlayList_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_SaveCurrentPlayList(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "SaveCurrentPlayList", 1, SaveCurrentPlayList_handler, c, "[SaveCurrentPlayList %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void CreateRandomPlaylistEx_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_CreateRandomPlaylistEx(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CreateRandomPlaylistEx", 1, CreateRandomPlaylistEx_handler, c, "[CreateRandomPlaylistEx %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void CreateRandomPlaylist_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_CreateRandomPlaylist(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CreateRandomPlaylist", 1, CreateRandomPlaylist_handler, c, "[CreateRandomPlaylist %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void CreatePlaylist_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_CreatePlaylist(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CreatePlaylist", 1, CreatePlaylist_handler, c, "[CreatePlaylist %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void RenamePlaylist_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_RenamePlaylist(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RenamePlaylist", 1, RenamePlaylist_handler, c, "[RenamePlaylist %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void AddTracksToUserPlaylist_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_AddTracksToUserPlaylist(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "AddTracksToUserPlaylist", 1, AddTracksToUserPlaylist_handler, c, "[AddTracksToUserPlaylist %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void AddAlbumsToUserPlaylist_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_AddAlbumsToUserPlaylist(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "AddAlbumsToUserPlaylist", 1, AddAlbumsToUserPlaylist_handler, c, "[AddAlbumsToUserPlaylist %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void RemoveAlbumsFromUserPlaylist_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_RemoveAlbumsFromUserPlaylist(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RemoveAlbumsFromUserPlaylist", 1, RemoveAlbumsFromUserPlaylist_handler, c, "[RemoveAlbumsFromUserPlaylist %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void DeleteTrack_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_DeleteTrack(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "DeleteTrack", 1, DeleteTrack_handler, c, "[DeleteTrack %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void ChangeTrackOrdinal_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_ChangeTrackOrdinal(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ChangeTrackOrdinal", 1, ChangeTrackOrdinal_handler, c, "[ChangeTrackOrdinal %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void UpdatePlaylist_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_UpdatePlaylist(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "UpdatePlaylist", 1, UpdatePlaylist_handler, c, "[UpdatePlaylist %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void DeleteAlbum_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_DeleteAlbum(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "DeleteAlbum", 1, DeleteAlbum_handler, c, "[DeleteAlbum %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void RenameAlbum_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_RenameAlbum(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RenameAlbum", 1, RenameAlbum_handler, c, "[RenameAlbum %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void SetAlbumLowQuality_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_SetAlbumLowQuality(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "SetAlbumLowQuality", 1, SetAlbumLowQuality_handler, c, "[SetAlbumLowQuality %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void RenameTrack_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_RenameTrack(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RenameTrack", 1, RenameTrack_handler, c, "[RenameTrack %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void UndoUserEdits_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_UndoUserEdits(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "UndoUserEdits", 1, UndoUserEdits_handler, c, "[UndoUserEdits %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void RenameArtist_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_RenameArtist(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RenameArtist", 1, RenameArtist_handler, c, "[RenameArtist %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void ChangeAlbumSubGenre_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_ChangeAlbumSubGenre(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ChangeAlbumSubGenre", 1, ChangeAlbumSubGenre_handler, c, "[ChangeAlbumSubGenre %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void UpdateHitCount_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_UpdateHitCount(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "UpdateHitCount", 1, UpdateHitCount_handler, c, "[UpdateHitCount %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void CountAlbums_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_CountAlbums(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountAlbums", 1, CountAlbums_handler, c, "[CountAlbums %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void CountAlbumsForArtist_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_CountAlbumsForArtist(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountAlbumsForArtist", 1, CountAlbumsForArtist_handler, c, "[CountAlbumsForArtist %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void CountArtists_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_CountArtists(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountArtists", 1, CountArtists_handler, c, "[CountArtists %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void CountGenres_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_CountGenres(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountGenres", 1, CountGenres_handler, c, "[CountGenres %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void CountPlaylistsForSubGenre_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_CountPlaylistsForSubGenre(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountPlaylistsForSubGenre", 1, CountPlaylistsForSubGenre_handler, c, "[CountPlaylistsForSubGenre %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void CountSubGenresForGenre_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_CountSubGenresForGenre(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountSubGenresForGenre", 1, CountSubGenresForGenre_handler, c, "[CountSubGenresForGenre %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void CountTracksAll_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_CountTracksAll(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountTracksAll", 1, CountTracksAll_handler, c, "[CountTracksAll %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void CountTracksForPlaylist_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_CountTracksForPlaylist(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountTracksForPlaylist", 1, CountTracksForPlaylist_handler, c, "[CountTracksForPlaylist %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void CountUserPlaylists_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_CountUserPlaylists(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountUserPlaylists", 1, CountUserPlaylists_handler, c, "[CountUserPlaylists %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void CountDevices_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_CountDevices(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountDevices", 1, CountDevices_handler, c, "[CountDevices %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void CountAlbumsForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_CountAlbumsForDevice(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountAlbumsForDevice", 1, CountAlbumsForDevice_handler, c, "[CountAlbumsForDevice %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void CountArtistsForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_CountArtistsForDevice(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountArtistsForDevice", 1, CountArtistsForDevice_handler, c, "[CountArtistsForDevice %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void CountSubGenresForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_CountSubGenresForDevice(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountSubGenresForDevice", 1, CountSubGenresForDevice_handler, c, "[CountSubGenresForDevice %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void CountTracksForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_CountTracksForDevice(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountTracksForDevice", 1, CountTracksForDevice_handler, c, "[CountTracksForDevice %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void CountUserPlaylistsForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_CountUserPlaylistsForDevice(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountUserPlaylistsForDevice", 1, CountUserPlaylistsForDevice_handler, c, "[CountUserPlaylistsForDevice %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void CountShares_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_CountShares(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountShares", 1, CountShares_handler, c, "[CountShares %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void CountAlbumsForShare_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_CountAlbumsForShare(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountAlbumsForShare", 1, CountAlbumsForShare_handler, c, "[CountAlbumsForShare %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void CountArtistsForShare_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_CountArtistsForShare(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountArtistsForShare", 1, CountArtistsForShare_handler, c, "[CountArtistsForShare %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void CountSubGenresForShare_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_CountSubGenresForShare(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountSubGenresForShare", 1, CountSubGenresForShare_handler, c, "[CountSubGenresForShare %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void CountTracksForShare_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_CountTracksForShare(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountTracksForShare", 1, CountTracksForShare_handler, c, "[CountTracksForShare %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void CountUserPlaylistsForShare_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_CountUserPlaylistsForShare(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountUserPlaylistsForShare", 1, CountUserPlaylistsForShare_handler, c, "[CountUserPlaylistsForShare %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void CountAlbumsForServer_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_CountAlbumsForServer(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountAlbumsForServer", 1, CountAlbumsForServer_handler, c, "[CountAlbumsForServer %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void CountArtistsForServer_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_CountArtistsForServer(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountArtistsForServer", 1, CountArtistsForServer_handler, c, "[CountArtistsForServer %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void CountSubGenresForServer_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_CountSubGenresForServer(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountSubGenresForServer", 1, CountSubGenresForServer_handler, c, "[CountSubGenresForServer %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void CountTracksForServer_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_CountTracksForServer(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountTracksForServer", 1, CountTracksForServer_handler, c, "[CountTracksForServer %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void CountUserPlaylistsForServer_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_CountUserPlaylistsForServer(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountUserPlaylistsForServer", 1, CountUserPlaylistsForServer_handler, c, "[CountUserPlaylistsForServer %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void CountAlbumsForArtistForServer_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_CountAlbumsForArtistForServer(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountAlbumsForArtistForServer", 1, CountAlbumsForArtistForServer_handler, c, "[CountAlbumsForArtistForServer %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void CountAlbumsForArtistForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_CountAlbumsForArtistForDevice(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountAlbumsForArtistForDevice", 1, CountAlbumsForArtistForDevice_handler, c, "[CountAlbumsForArtistForDevice %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void CountAlbumsForArtistForShare_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_CountAlbumsForArtistForShare(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountAlbumsForArtistForShare", 1, CountAlbumsForArtistForShare_handler, c, "[CountAlbumsForArtistForShare %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void CountPlaylistsForSubGenreForServer_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_CountPlaylistsForSubGenreForServer(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountPlaylistsForSubGenreForServer", 1, CountPlaylistsForSubGenreForServer_handler, c, "[CountPlaylistsForSubGenreForServer %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void CountPlaylistsForSubGenreForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_CountPlaylistsForSubGenreForDevice(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountPlaylistsForSubGenreForDevice", 1, CountPlaylistsForSubGenreForDevice_handler, c, "[CountPlaylistsForSubGenreForDevice %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void CountPlaylistsForSubGenreForShare_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_CountPlaylistsForSubGenreForShare(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountPlaylistsForSubGenreForShare", 1, CountPlaylistsForSubGenreForShare_handler, c, "[CountPlaylistsForSubGenreForShare %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetTracksForArtistForServer_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetTracksForArtistForServer(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTracksForArtistForServer", 1, GetTracksForArtistForServer_handler, c, "[GetTracksForArtistForServer %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetTracksForArtistForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetTracksForArtistForDevice(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTracksForArtistForDevice", 1, GetTracksForArtistForDevice_handler, c, "[GetTracksForArtistForDevice %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetTracksForArtistForShare_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetTracksForArtistForShare(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTracksForArtistForShare", 1, GetTracksForArtistForShare_handler, c, "[GetTracksForArtistForShare %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetTracksForSubGenreForServer_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetTracksForSubGenreForServer(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTracksForSubGenreForServer", 1, GetTracksForSubGenreForServer_handler, c, "[GetTracksForSubGenreForServer %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetTracksForSubGenreForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetTracksForSubGenreForDevice(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTracksForSubGenreForDevice", 1, GetTracksForSubGenreForDevice_handler, c, "[GetTracksForSubGenreForDevice %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetTracksForSubGenreForShare_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetTracksForSubGenreForShare(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTracksForSubGenreForShare", 1, GetTracksForSubGenreForShare_handler, c, "[GetTracksForSubGenreForShare %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAlbumsWithAlbumLookupMessages_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAlbumsWithAlbumLookupMessages(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlbumsWithAlbumLookupMessages", 1, GetAlbumsWithAlbumLookupMessages_handler, c, "[GetAlbumsWithAlbumLookupMessages %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAlbumsForDeletion_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAlbumsForDeletion(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlbumsForDeletion", 1, GetAlbumsForDeletion_handler, c, "[GetAlbumsForDeletion %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetTracksForDeletion_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetTracksForDeletion(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTracksForDeletion", 1, GetTracksForDeletion_handler, c, "[GetTracksForDeletion %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void RestoreSingleAlbum_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_RestoreSingleAlbum(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RestoreSingleAlbum", 1, RestoreSingleAlbum_handler, c, "[RestoreSingleAlbum %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void RestoreSingleTrack_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_RestoreSingleTrack(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RestoreSingleTrack", 1, RestoreSingleTrack_handler, c, "[RestoreSingleTrack %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void SetCoverImage_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_SetCoverImage(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "SetCoverImage", 1, SetCoverImage_handler, c, "[SetCoverImage %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void RemoveCoverImage_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_RemoveCoverImage(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RemoveCoverImage", 1, RemoveCoverImage_handler, c, "[RemoveCoverImage %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void CheckCoverImage_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_CheckCoverImage(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CheckCoverImage", 1, CheckCoverImage_handler, c, "[CheckCoverImage %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void ForceGenrePlaylistBackup_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_ForceGenrePlaylistBackup(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ForceGenrePlaylistBackup", 1, ForceGenrePlaylistBackup_handler, c, "[ForceGenrePlaylistBackup %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void ForceGenrePlaylistRestore_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_ForceGenrePlaylistRestore(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ForceGenrePlaylistRestore", 1, ForceGenrePlaylistRestore_handler, c, "[ForceGenrePlaylistRestore %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void BulkCDLookup_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_BulkCDLookup(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "BulkCDLookup", 1, BulkCDLookup_handler, c, "[BulkCDLookup %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void BulkCDLookupEx_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_BulkCDLookupEx(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "BulkCDLookupEx", 1, BulkCDLookupEx_handler, c, "[BulkCDLookupEx %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void CDLookupGetStatus_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_CDLookupGetStatus(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CDLookupGetStatus", 1, CDLookupGetStatus_handler, c, "[CDLookupGetStatus %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void CDLookupGetQueue_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_CDLookupGetQueue(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CDLookupGetQueue", 1, CDLookupGetQueue_handler, c, "[CDLookupGetQueue %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void UploadMessages_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_UploadMessages(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "UploadMessages", 1, UploadMessages_handler, c, "[UploadMessages %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetComponentVersions_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetComponentVersions(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetComponentVersions", 1, GetComponentVersions_handler, c, "[GetComponentVersions %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetOperationActivity_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetOperationActivity(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetOperationActivity", 1, GetOperationActivity_handler, c, "[GetOperationActivity %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void RequestAlbumCover_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_RequestAlbumCover(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RequestAlbumCover", 1, RequestAlbumCover_handler, c, "[RequestAlbumCover %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void RGetTrackPosition_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_RGetTrackPosition(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RGetTrackPosition", 1, RGetTrackPosition_handler, c, "[RGetTrackPosition %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void RGetTrackName_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_RGetTrackName(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RGetTrackName", 1, RGetTrackName_handler, c, "[RGetTrackName %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void RGetAlbumArtist_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_RGetAlbumArtist(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RGetAlbumArtist", 1, RGetAlbumArtist_handler, c, "[RGetAlbumArtist %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void RGetPlayerStatus_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_RGetPlayerStatus(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RGetPlayerStatus", 1, RGetPlayerStatus_handler, c, "[RGetPlayerStatus %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void RGetRepeat_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_RGetRepeat(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RGetRepeat", 1, RGetRepeat_handler, c, "[RGetRepeat %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void RGetShuffle_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_RGetShuffle(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RGetShuffle", 1, RGetShuffle_handler, c, "[RGetShuffle %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void RGetPlayingCheckSum_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_RGetPlayingCheckSum(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RGetPlayingCheckSum", 1, RGetPlayingCheckSum_handler, c, "[RGetPlayingCheckSum %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void RGetDetailedTrackInfo_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_RGetDetailedTrackInfo(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RGetDetailedTrackInfo", 1, RGetDetailedTrackInfo_handler, c, "[RGetDetailedTrackInfo %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void RGetLastPlayerError_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_RGetLastPlayerError(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RGetLastPlayerError", 1, RGetLastPlayerError_handler, c, "[RGetLastPlayerError %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtAlbumCredits_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtAlbumCredits(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtAlbumCredits", 1, GetExtAlbumCredits_handler, c, "[GetExtAlbumCredits %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtAlbumsByContributor_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtAlbumsByContributor(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtAlbumsByContributor", 1, GetExtAlbumsByContributor_handler, c, "[GetExtAlbumsByContributor %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtAlbumsByContributorForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtAlbumsByContributorForDevice(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtAlbumsByContributorForDevice", 1, GetExtAlbumsByContributorForDevice_handler, c, "[GetExtAlbumsByContributorForDevice %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtAlbumsByContributorForShare_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtAlbumsByContributorForShare(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtAlbumsByContributorForShare", 1, GetExtAlbumsByContributorForShare_handler, c, "[GetExtAlbumsByContributorForShare %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtAlbumsByContributorForServer_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtAlbumsByContributorForServer(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtAlbumsByContributorForServer", 1, GetExtAlbumsByContributorForServer_handler, c, "[GetExtAlbumsByContributorForServer %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtAlbumsByCredit_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtAlbumsByCredit(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtAlbumsByCredit", 1, GetExtAlbumsByCredit_handler, c, "[GetExtAlbumsByCredit %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtAlbumsByWork_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtAlbumsByWork(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtAlbumsByWork", 1, GetExtAlbumsByWork_handler, c, "[GetExtAlbumsByWork %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtAlbumsInfo_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtAlbumsInfo(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtAlbumsInfo", 1, GetExtAlbumsInfo_handler, c, "[GetExtAlbumsInfo %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtContributors_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtContributors(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtContributors", 1, GetExtContributors_handler, c, "[GetExtContributors %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtContributorsForAlbum_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtContributorsForAlbum(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtContributorsForAlbum", 1, GetExtContributorsForAlbum_handler, c, "[GetExtContributorsForAlbum %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtContributorsForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtContributorsForDevice(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtContributorsForDevice", 1, GetExtContributorsForDevice_handler, c, "[GetExtContributorsForDevice %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtContributorsForShare_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtContributorsForShare(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtContributorsForShare", 1, GetExtContributorsForShare_handler, c, "[GetExtContributorsForShare %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtContributorsForServer_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtContributorsForServer(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtContributorsForServer", 1, GetExtContributorsForServer_handler, c, "[GetExtContributorsForServer %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtTrackContributors_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtTrackContributors(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtTrackContributors", 1, GetExtTrackContributors_handler, c, "[GetExtTrackContributors %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtTracksByContributor_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtTracksByContributor(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtTracksByContributor", 1, GetExtTracksByContributor_handler, c, "[GetExtTracksByContributor %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtTracksByWork_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtTracksByWork(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtTracksByWork", 1, GetExtTracksByWork_handler, c, "[GetExtTracksByWork %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtTracksInfo_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtTracksInfo(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtTracksInfo", 1, GetExtTracksInfo_handler, c, "[GetExtTracksInfo %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtWorks_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtWorks(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtWorks", 1, GetExtWorks_handler, c, "[GetExtWorks %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtContributorDetails_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtContributorDetails(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtContributorDetails", 1, GetExtContributorDetails_handler, c, "[GetExtContributorDetails %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtCountContributors_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtCountContributors(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtCountContributors", 1, GetExtCountContributors_handler, c, "[GetExtCountContributors %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtCountContributorsForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtCountContributorsForDevice(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtCountContributorsForDevice", 1, GetExtCountContributorsForDevice_handler, c, "[GetExtCountContributorsForDevice %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtCountContributorsForShare_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtCountContributorsForShare(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtCountContributorsForShare", 1, GetExtCountContributorsForShare_handler, c, "[GetExtCountContributorsForShare %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtCountContributorsForServer_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtCountContributorsForServer(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtCountContributorsForServer", 1, GetExtCountContributorsForServer_handler, c, "[GetExtCountContributorsForServer %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtCountAlbumsByContributor_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtCountAlbumsByContributor(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtCountAlbumsByContributor", 1, GetExtCountAlbumsByContributor_handler, c, "[GetExtCountAlbumsByContributor %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtCountAlbumsByContributorForServer_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtCountAlbumsByContributorForServer(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtCountAlbumsByContributorForServer", 1, GetExtCountAlbumsByContributorForServer_handler, c, "[GetExtCountAlbumsByContributorForServer %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtCountAlbumsByContributorForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtCountAlbumsByContributorForDevice(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtCountAlbumsByContributorForDevice", 1, GetExtCountAlbumsByContributorForDevice_handler, c, "[GetExtCountAlbumsByContributorForDevice %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtCountAlbumsByContributorForShare_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtCountAlbumsByContributorForShare(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtCountAlbumsByContributorForShare", 1, GetExtCountAlbumsByContributorForShare_handler, c, "[GetExtCountAlbumsByContributorForShare %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtTracksByContributorForServer_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtTracksByContributorForServer(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtTracksByContributorForServer", 1, GetExtTracksByContributorForServer_handler, c, "[GetExtTracksByContributorForServer %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtTracksByContributorForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtTracksByContributorForDevice(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtTracksByContributorForDevice", 1, GetExtTracksByContributorForDevice_handler, c, "[GetExtTracksByContributorForDevice %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtTracksByContributorForShare_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtTracksByContributorForShare(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtTracksByContributorForShare", 1, GetExtTracksByContributorForShare_handler, c, "[GetExtTracksByContributorForShare %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtAlbumsSearchPeople_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtAlbumsSearchPeople(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtAlbumsSearchPeople", 1, GetExtAlbumsSearchPeople_handler, c, "[GetExtAlbumsSearchPeople %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void vTunerLookupById_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_vTunerLookupById(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "vTunerLookupById", 1, vTunerLookupById_handler, c, "[vTunerLookupById %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void vTunerAddRemoveFavourite_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_vTunerAddRemoveFavourite(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "vTunerAddRemoveFavourite", 1, vTunerAddRemoveFavourite_handler, c, "[vTunerAddRemoveFavourite %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void vTunerGetChildNodes_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_vTunerGetChildNodes(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "vTunerGetChildNodes", 1, vTunerGetChildNodes_handler, c, "[vTunerGetChildNodes %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void vTunerPlayById_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_vTunerPlayById(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "vTunerPlayById", 1, vTunerPlayById_handler, c, "[vTunerPlayById %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void vTunerPlayByIds_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_vTunerPlayByIds(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "vTunerPlayByIds", 1, vTunerPlayByIds_handler, c, "[vTunerPlayByIds %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void vTunerGetMostPlayed_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_vTunerGetMostPlayed(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "vTunerGetMostPlayed", 1, vTunerGetMostPlayed_handler, c, "[vTunerGetMostPlayed %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void vTunerGetLastPlayed_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_vTunerGetLastPlayed(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "vTunerGetLastPlayed", 1, vTunerGetLastPlayed_handler, c, "[vTunerGetLastPlayed %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void vTunerGetRadioStatisticsChecksum_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_vTunerGetRadioStatisticsChecksum(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "vTunerGetRadioStatisticsChecksum", 1, vTunerGetRadioStatisticsChecksum_handler, c, "[vTunerGetRadioStatisticsChecksum %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void vTunerSetPresetChannel_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_vTunerSetPresetChannel(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "vTunerSetPresetChannel", 1, vTunerSetPresetChannel_handler, c, "[vTunerSetPresetChannel %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void vTunerGetPresetChannels_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_vTunerGetPresetChannels(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "vTunerGetPresetChannels", 1, vTunerGetPresetChannels_handler, c, "[vTunerGetPresetChannels %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void vTunerGetNodeFromPlayedUrl_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_vTunerGetNodeFromPlayedUrl(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "vTunerGetNodeFromPlayedUrl", 1, vTunerGetNodeFromPlayedUrl_handler, c, "[vTunerGetNodeFromPlayedUrl %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void vTunerCheckAvailability_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_vTunerCheckAvailability(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "vTunerCheckAvailability", 1, vTunerCheckAvailability_handler, c, "[vTunerCheckAvailability %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void MoveAlbumToMusicStore_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_MoveAlbumToMusicStore(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "MoveAlbumToMusicStore", 1, MoveAlbumToMusicStore_handler, c, "[MoveAlbumToMusicStore %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void PromoteShareToMusicStore_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_PromoteShareToMusicStore(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "PromoteShareToMusicStore", 1, PromoteShareToMusicStore_handler, c, "[PromoteShareToMusicStore %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void DemoteMusicStoreToShare_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_DemoteMusicStoreToShare(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "DemoteMusicStoreToShare", 1, DemoteMusicStoreToShare_handler, c, "[DemoteMusicStoreToShare %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void RescanMusicStore_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_RescanMusicStore(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RescanMusicStore", 1, RescanMusicStore_handler, c, "[RescanMusicStore %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void SetMusicStorePriority_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_SetMusicStorePriority(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "SetMusicStorePriority", 1, SetMusicStorePriority_handler, c, "[SetMusicStorePriority %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetStores_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetStores(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetStores", 1, GetStores_handler, c, "[GetStores %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetStoreDetail_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetStoreDetail(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetStoreDetail", 1, GetStoreDetail_handler, c, "[GetStoreDetail %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void SetMusicStoreCredentials_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_SetMusicStoreCredentials(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "SetMusicStoreCredentials", 1, SetMusicStoreCredentials_handler, c, "[SetMusicStoreCredentials %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void MoveAlbumGetStatus_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_MoveAlbumGetStatus(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "MoveAlbumGetStatus", 1, MoveAlbumGetStatus_handler, c, "[MoveAlbumGetStatus %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void MoveAlbumGetQueue_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_MoveAlbumGetQueue(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "MoveAlbumGetQueue", 1, MoveAlbumGetQueue_handler, c, "[MoveAlbumGetQueue %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtContributorsExist_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtContributorsExist(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtContributorsExist", 1, GetExtContributorsExist_handler, c, "[GetExtContributorsExist %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}


static void SetConnOption_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_SetConnOption(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "SetConnOption", 1, SetConnOption_handler, c, "[SetConnOption %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void Status_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_Status(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "Status", 1, Status_handler, c, "[Status %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void SetLength_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_SetLength(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "SetLength", 1, SetLength_handler, c, "[SetLength %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void EnableField_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_EnableField(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "EnableField", 1, EnableField_handler, c, "[EnableField %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void DisableField_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_DisableField(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "DisableField", 1, DisableField_handler, c, "[DisableField %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void EffFormat_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_EffFormat(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "EffFormat", 1, EffFormat_handler, c, "[EffFormat %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void RoomIpChanged_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_RoomIpChanged(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RoomIpChanged", 1, RoomIpChanged_handler, c, "[RoomIpChanged %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void MasterIpChanged_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_MasterIpChanged(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "MasterIpChanged", 1, MasterIpChanged_handler, c, "[MasterIpChanged %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void SetRippingStatus_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_SetRippingStatus(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "SetRippingStatus", 1, SetRippingStatus_handler, c, "[SetRippingStatus %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void SetCDDetected_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_SetCDDetected(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "SetCDDetected", 1, SetCDDetected_handler, c, "[SetCDDetected %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void SetRecycleBinStatus_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_SetRecycleBinStatus(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "SetRecycleBinStatus", 1, SetRecycleBinStatus_handler, c, "[SetRecycleBinStatus %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void Stop_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_Stop(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "Stop", 1, Stop_handler, c, "[Stop %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void Play_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_Play(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "Play", 1, Play_handler, c, "[Play %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void Pause_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_Pause(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "Pause", 1, Pause_handler, c, "[Pause %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void ClearPlaylist_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_ClearPlaylist(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ClearPlaylist", 1, ClearPlaylist_handler, c, "[ClearPlaylist %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void FastForward_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_FastForward(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "FastForward", 1, FastForward_handler, c, "[FastForward %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void FastRewind_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_FastRewind(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "FastRewind", 1, FastRewind_handler, c, "[FastRewind %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void RandomisePlaylist_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_RandomisePlaylist(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RandomisePlaylist", 1, RandomisePlaylist_handler, c, "[RandomisePlaylist %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void SetTrack_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_SetTrack(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "SetTrack", 1, SetTrack_handler, c, "[SetTrack %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void SetTrackPosition_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_SetTrackPosition(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "SetTrackPosition", 1, SetTrackPosition_handler, c, "[SetTrackPosition %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void EjectCD_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_EjectCD(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "EjectCD", 1, EjectCD_handler, c, "[EjectCD %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void SetVolume_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_SetVolume(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "SetVolume", 1, SetVolume_handler, c, "[SetVolume %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void SetShuffle_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_SetShuffle(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "SetShuffle", 1, SetShuffle_handler, c, "[SetShuffle %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void SetRepeat_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_SetRepeat(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "SetRepeat", 1, SetRepeat_handler, c, "[SetRepeat %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void ClearAllPlaying_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_ClearAllPlaying(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ClearAllPlaying", 1, ClearAllPlaying_handler, c, "[ClearAllPlaying %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void RestartDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_RestartDevice(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RestartDevice", 1, RestartDevice_handler, c, "[RestartDevice %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void ChangeCDDBSubGenreAssociation_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_ChangeCDDBSubGenreAssociation(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ChangeCDDBSubGenreAssociation", 1, ChangeCDDBSubGenreAssociation_handler, c, "[ChangeCDDBSubGenreAssociation %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void ForceHostUpgrade_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_ForceHostUpgrade(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ForceHostUpgrade", 1, ForceHostUpgrade_handler, c, "[ForceHostUpgrade %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void ForceDBRebuild_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_ForceDBRebuild(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ForceDBRebuild", 1, ForceDBRebuild_handler, c, "[ForceDBRebuild %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void PurgeImageCache_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_PurgeImageCache(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "PurgeImageCache", 1, PurgeImageCache_handler, c, "[PurgeImageCache %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void CDLookupCancel_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_CDLookupCancel(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CDLookupCancel", 1, CDLookupCancel_handler, c, "[CDLookupCancel %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void CdLookupCancelAll_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_CdLookupCancelAll(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CdLookupCancelAll", 1, CdLookupCancelAll_handler, c, "[CdLookupCancelAll %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void EmptyRecycleBin_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_EmptyRecycleBin(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "EmptyRecycleBin", 1, EmptyRecycleBin_handler, c, "[EmptyRecycleBin %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void EmptyRipShare_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_EmptyRipShare(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "EmptyRipShare", 1, EmptyRipShare_handler, c, "[EmptyRipShare %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void ClearDownloadFolder_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_ClearDownloadFolder(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ClearDownloadFolder", 1, ClearDownloadFolder_handler, c, "[ClearDownloadFolder %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void RGetRegisterClient_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_RGetRegisterClient(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RGetRegisterClient", 1, RGetRegisterClient_handler, c, "[RGetRegisterClient %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void RGetClearCommands_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_RGetClearCommands(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RGetClearCommands", 1, RGetClearCommands_handler, c, "[RGetClearCommands %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void vTunerCleanStatistics_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_vTunerCleanStatistics(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "vTunerCleanStatistics", 1, vTunerCleanStatistics_handler, c, "[vTunerCleanStatistics %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void vTunerClearPresetChannel_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_vTunerClearPresetChannel(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "vTunerClearPresetChannel", 1, vTunerClearPresetChannel_handler, c, "[vTunerClearPresetChannel %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void MoveAlbumCancel_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_MoveAlbumCancel(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "MoveAlbumCancel", 1, MoveAlbumCancel_handler, c, "[MoveAlbumCancel %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void MoveAlbumCancelAll_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_MoveAlbumCancelAll(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "MoveAlbumCancelAll", 1, MoveAlbumCancelAll_handler, c, "[MoveAlbumCancelAll %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}


static void Status_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_Status(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "Status", 1, Status_handler, c, "[Status %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void EffFormat_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_EffFormat(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "EffFormat", 1, EffFormat_handler, c, "[EffFormat %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void FilterSearch_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_FilterSearch(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "FilterSearch", 1, FilterSearch_handler, c, "[FilterSearch %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void SortSearch_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_SortSearch(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "SortSearch", 1, SortSearch_handler, c, "[SortSearch %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetRooms_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetRooms(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetRooms", 1, GetRooms_handler, c, "[GetRooms %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetRoomsWithPlayBack_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetRoomsWithPlayBack(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetRoomsWithPlayBack", 1, GetRoomsWithPlayBack_handler, c, "[GetRoomsWithPlayBack %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetRoomsWithRipping_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetRoomsWithRipping(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetRoomsWithRipping", 1, GetRoomsWithRipping_handler, c, "[GetRoomsWithRipping %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetNonLinkedRooms_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetNonLinkedRooms(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetNonLinkedRooms", 1, GetNonLinkedRooms_handler, c, "[GetNonLinkedRooms %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetLinkedRooms_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetLinkedRooms(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetLinkedRooms", 1, GetLinkedRooms_handler, c, "[GetLinkedRooms %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAdvancedStatus_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAdvancedStatus(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAdvancedStatus", 1, GetAdvancedStatus_handler, c, "[GetAdvancedStatus %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetUserStatus_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetUserStatus(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetUserStatus", 1, GetUserStatus_handler, c, "[GetUserStatus %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetStatusMessages_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetStatusMessages(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetStatusMessages", 1, GetStatusMessages_handler, c, "[GetStatusMessages %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetCurrentPlayList_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetCurrentPlayList(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetCurrentPlayList", 1, GetCurrentPlayList_handler, c, "[GetCurrentPlayList %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetCurrentPlaylistEx_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetCurrentPlaylistEx(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetCurrentPlaylistEx", 1, GetCurrentPlaylistEx_handler, c, "[GetCurrentPlaylistEx %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetRippingAlerts_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetRippingAlerts(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetRippingAlerts", 1, GetRippingAlerts_handler, c, "[GetRippingAlerts %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAlertDetails_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAlertDetails(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlertDetails", 1, GetAlertDetails_handler, c, "[GetAlertDetails %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetRippingStatus_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetRippingStatus(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetRippingStatus", 1, GetRippingStatus_handler, c, "[GetRippingStatus %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetRipEncSettings_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetRipEncSettings(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetRipEncSettings", 1, GetRipEncSettings_handler, c, "[GetRipEncSettings %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetRipEncSettingsEx_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetRipEncSettingsEx(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetRipEncSettingsEx", 1, GetRipEncSettingsEx_handler, c, "[GetRipEncSettingsEx %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetSettings_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetSettings(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetSettings", 1, GetSettings_handler, c, "[GetSettings %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetSettingsEx_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetSettingsEx(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetSettingsEx", 1, GetSettingsEx_handler, c, "[GetSettingsEx %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAvailableValues_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAvailableValues(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAvailableValues", 1, GetAvailableValues_handler, c, "[GetAvailableValues %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetSystemDrives_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetSystemDrives(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetSystemDrives", 1, GetSystemDrives_handler, c, "[GetSystemDrives %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetEncodingQueue_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetEncodingQueue(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetEncodingQueue", 1, GetEncodingQueue_handler, c, "[GetEncodingQueue %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetEncodingStatus_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetEncodingStatus(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetEncodingStatus", 1, GetEncodingStatus_handler, c, "[GetEncodingStatus %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetPlayerInstances_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetPlayerInstances(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetPlayerInstances", 1, GetPlayerInstances_handler, c, "[GetPlayerInstances %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetOutputDevices_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetOutputDevices(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetOutputDevices", 1, GetOutputDevices_handler, c, "[GetOutputDevices %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetOutputChannels_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetOutputChannels(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetOutputChannels", 1, GetOutputChannels_handler, c, "[GetOutputChannels %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetUpnpMediaRenderers_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetUpnpMediaRenderers(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetUpnpMediaRenderers", 1, GetUpnpMediaRenderers_handler, c, "[GetUpnpMediaRenderers %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAsio4AllChannels_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAsio4AllChannels(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAsio4AllChannels", 1, GetAsio4AllChannels_handler, c, "[GetAsio4AllChannels %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetDevices_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetDevices(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetDevices", 1, GetDevices_handler, c, "[GetDevices %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetDeviceDetails_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetDeviceDetails(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetDeviceDetails", 1, GetDeviceDetails_handler, c, "[GetDeviceDetails %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExternalStorages_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExternalStorages(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExternalStorages", 1, GetExternalStorages_handler, c, "[GetExternalStorages %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetNetworkBackup_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetNetworkBackup(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetNetworkBackup", 1, GetNetworkBackup_handler, c, "[GetNetworkBackup %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetLinkedRoomDetail_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetLinkedRoomDetail(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetLinkedRoomDetail", 1, GetLinkedRoomDetail_handler, c, "[GetLinkedRoomDetail %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void TestRows_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_TestRows(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "TestRows", 1, TestRows_handler, c, "[TestRows %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetBackupJobs_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetBackupJobs(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetBackupJobs", 1, GetBackupJobs_handler, c, "[GetBackupJobs %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetBackupJobDetail_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetBackupJobDetail(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetBackupJobDetail", 1, GetBackupJobDetail_handler, c, "[GetBackupJobDetail %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetBackupLogs_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetBackupLogs(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetBackupLogs", 1, GetBackupLogs_handler, c, "[GetBackupLogs %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetBackupLogDetail_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetBackupLogDetail(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetBackupLogDetail", 1, GetBackupLogDetail_handler, c, "[GetBackupLogDetail %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetNetworkActiveAdapters_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetNetworkActiveAdapters(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetNetworkActiveAdapters", 1, GetNetworkActiveAdapters_handler, c, "[GetNetworkActiveAdapters %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void ComplexSearchGetAlbums_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_ComplexSearchGetAlbums(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ComplexSearchGetAlbums", 1, ComplexSearchGetAlbums_handler, c, "[ComplexSearchGetAlbums %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void ComplexSearchGetTracks_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_ComplexSearchGetTracks(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ComplexSearchGetTracks", 1, ComplexSearchGetTracks_handler, c, "[ComplexSearchGetTracks %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void ComplexSearchGetArtists_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_ComplexSearchGetArtists(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ComplexSearchGetArtists", 1, ComplexSearchGetArtists_handler, c, "[ComplexSearchGetArtists %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void ComplexSearchGetContributors_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_ComplexSearchGetContributors(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ComplexSearchGetContributors", 1, ComplexSearchGetContributors_handler, c, "[ComplexSearchGetContributors %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAlbums_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAlbums(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlbums", 1, GetAlbums_handler, c, "[GetAlbums %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAlbumsForStore_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAlbumsForStore(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlbumsForStore", 1, GetAlbumsForStore_handler, c, "[GetAlbumsForStore %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAlbumsForArtists_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAlbumsForArtists(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlbumsForArtists", 1, GetAlbumsForArtists_handler, c, "[GetAlbumsForArtists %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAlbumsForArtistsInSubGenre_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAlbumsForArtistsInSubGenre(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlbumsForArtistsInSubGenre", 1, GetAlbumsForArtistsInSubGenre_handler, c, "[GetAlbumsForArtistsInSubGenre %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAlbumsForArtistsInSubGenreForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAlbumsForArtistsInSubGenreForDevice(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlbumsForArtistsInSubGenreForDevice", 1, GetAlbumsForArtistsInSubGenreForDevice_handler, c, "[GetAlbumsForArtistsInSubGenreForDevice %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAlbumsForArtistsInSubGenreForServer_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAlbumsForArtistsInSubGenreForServer(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlbumsForArtistsInSubGenreForServer", 1, GetAlbumsForArtistsInSubGenreForServer_handler, c, "[GetAlbumsForArtistsInSubGenreForServer %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAlbumsForArtistsInSubGenreForShare_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAlbumsForArtistsInSubGenreForShare(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlbumsForArtistsInSubGenreForShare", 1, GetAlbumsForArtistsInSubGenreForShare_handler, c, "[GetAlbumsForArtistsInSubGenreForShare %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAlbumsForArtistsInGenre_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAlbumsForArtistsInGenre(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlbumsForArtistsInGenre", 1, GetAlbumsForArtistsInGenre_handler, c, "[GetAlbumsForArtistsInGenre %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAlbumsForArtistsForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAlbumsForArtistsForDevice(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlbumsForArtistsForDevice", 1, GetAlbumsForArtistsForDevice_handler, c, "[GetAlbumsForArtistsForDevice %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAlbumsForArtistsForShare_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAlbumsForArtistsForShare(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlbumsForArtistsForShare", 1, GetAlbumsForArtistsForShare_handler, c, "[GetAlbumsForArtistsForShare %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAlbumsForArtistsForServer_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAlbumsForArtistsForServer(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlbumsForArtistsForServer", 1, GetAlbumsForArtistsForServer_handler, c, "[GetAlbumsForArtistsForServer %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAlbumsForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAlbumsForDevice(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlbumsForDevice", 1, GetAlbumsForDevice_handler, c, "[GetAlbumsForDevice %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAlbumsForShare_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAlbumsForShare(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlbumsForShare", 1, GetAlbumsForShare_handler, c, "[GetAlbumsForShare %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAlbumsForServer_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAlbumsForServer(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlbumsForServer", 1, GetAlbumsForServer_handler, c, "[GetAlbumsForServer %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAlbumsForPlaylist_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAlbumsForPlaylist(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlbumsForPlaylist", 1, GetAlbumsForPlaylist_handler, c, "[GetAlbumsForPlaylist %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAlbumsSearchAlbumArtist_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAlbumsSearchAlbumArtist(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlbumsSearchAlbumArtist", 1, GetAlbumsSearchAlbumArtist_handler, c, "[GetAlbumsSearchAlbumArtist %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetLatestPlayedAlbums_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetLatestPlayedAlbums(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetLatestPlayedAlbums", 1, GetLatestPlayedAlbums_handler, c, "[GetLatestPlayedAlbums %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetNewestAlbums_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetNewestAlbums(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetNewestAlbums", 1, GetNewestAlbums_handler, c, "[GetNewestAlbums %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetPlayListsByLetter_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetPlayListsByLetter(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetPlayListsByLetter", 1, GetPlayListsByLetter_handler, c, "[GetPlayListsByLetter %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetPlaylistsForGenre_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetPlaylistsForGenre(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetPlaylistsForGenre", 1, GetPlaylistsForGenre_handler, c, "[GetPlaylistsForGenre %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetPlaylistsForSubGenre_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetPlaylistsForSubGenre(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetPlaylistsForSubGenre", 1, GetPlaylistsForSubGenre_handler, c, "[GetPlaylistsForSubGenre %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetPlaylistsForSubGenreForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetPlaylistsForSubGenreForDevice(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetPlaylistsForSubGenreForDevice", 1, GetPlaylistsForSubGenreForDevice_handler, c, "[GetPlaylistsForSubGenreForDevice %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetPlaylistsForSubGenreForShare_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetPlaylistsForSubGenreForShare(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetPlaylistsForSubGenreForShare", 1, GetPlaylistsForSubGenreForShare_handler, c, "[GetPlaylistsForSubGenreForShare %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetPlaylistsForSubGenreForServer_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetPlaylistsForSubGenreForServer(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetPlaylistsForSubGenreForServer", 1, GetPlaylistsForSubGenreForServer_handler, c, "[GetPlaylistsForSubGenreForServer %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetUserPlaylistsForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetUserPlaylistsForDevice(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetUserPlaylistsForDevice", 1, GetUserPlaylistsForDevice_handler, c, "[GetUserPlaylistsForDevice %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetUserPlaylistsForShare_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetUserPlaylistsForShare(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetUserPlaylistsForShare", 1, GetUserPlaylistsForShare_handler, c, "[GetUserPlaylistsForShare %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetUserPlaylistsForServer_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetUserPlaylistsForServer(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetUserPlaylistsForServer", 1, GetUserPlaylistsForServer_handler, c, "[GetUserPlaylistsForServer %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetUserPlaylists_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetUserPlaylists(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetUserPlaylists", 1, GetUserPlaylists_handler, c, "[GetUserPlaylists %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetTopPlayedAlbums_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetTopPlayedAlbums(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTopPlayedAlbums", 1, GetTopPlayedAlbums_handler, c, "[GetTopPlayedAlbums %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAlbumsOtherInfo_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAlbumsOtherInfo(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlbumsOtherInfo", 1, GetAlbumsOtherInfo_handler, c, "[GetAlbumsOtherInfo %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAlbumsOtherInfoForServer_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAlbumsOtherInfoForServer(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlbumsOtherInfoForServer", 1, GetAlbumsOtherInfoForServer_handler, c, "[GetAlbumsOtherInfoForServer %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAlbumsOtherInfoForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAlbumsOtherInfoForDevice(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlbumsOtherInfoForDevice", 1, GetAlbumsOtherInfoForDevice_handler, c, "[GetAlbumsOtherInfoForDevice %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAlbumsOtherInfoForShare_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAlbumsOtherInfoForShare(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlbumsOtherInfoForShare", 1, GetAlbumsOtherInfoForShare_handler, c, "[GetAlbumsOtherInfoForShare %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAlbumsOtherInfoAll_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAlbumsOtherInfoAll(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlbumsOtherInfoAll", 1, GetAlbumsOtherInfoAll_handler, c, "[GetAlbumsOtherInfoAll %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAlbumDetails_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAlbumDetails(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlbumDetails", 1, GetAlbumDetails_handler, c, "[GetAlbumDetails %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetTracksAll_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetTracksAll(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTracksAll", 1, GetTracksAll_handler, c, "[GetTracksAll %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetTrackRange_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetTrackRange(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTrackRange", 1, GetTrackRange_handler, c, "[GetTrackRange %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetTracksForArtist_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetTracksForArtist(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTracksForArtist", 1, GetTracksForArtist_handler, c, "[GetTracksForArtist %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetTracksForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetTracksForDevice(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTracksForDevice", 1, GetTracksForDevice_handler, c, "[GetTracksForDevice %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetTracksForShare_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetTracksForShare(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTracksForShare", 1, GetTracksForShare_handler, c, "[GetTracksForShare %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetTracksForServer_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetTracksForServer(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTracksForServer", 1, GetTracksForServer_handler, c, "[GetTracksForServer %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetTracksForGenre_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetTracksForGenre(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTracksForGenre", 1, GetTracksForGenre_handler, c, "[GetTracksForGenre %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetTracksForPlaylist_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetTracksForPlaylist(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTracksForPlaylist", 1, GetTracksForPlaylist_handler, c, "[GetTracksForPlaylist %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetTracksForSubGenre_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetTracksForSubGenre(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTracksForSubGenre", 1, GetTracksForSubGenre_handler, c, "[GetTracksForSubGenre %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetTracksOtherInfo_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetTracksOtherInfo(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTracksOtherInfo", 1, GetTracksOtherInfo_handler, c, "[GetTracksOtherInfo %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetTracksSearchName_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetTracksSearchName(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTracksSearchName", 1, GetTracksSearchName_handler, c, "[GetTracksSearchName %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void AdvancedSearch_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_AdvancedSearch(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "AdvancedSearch", 1, AdvancedSearch_handler, c, "[AdvancedSearch %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetTracksForNamedEntity_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetTracksForNamedEntity(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTracksForNamedEntity", 1, GetTracksForNamedEntity_handler, c, "[GetTracksForNamedEntity %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetTracksForAlbumInUPL_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetTracksForAlbumInUPL(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTracksForAlbumInUPL", 1, GetTracksForAlbumInUPL_handler, c, "[GetTracksForAlbumInUPL %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetArtistDetails_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetArtistDetails(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetArtistDetails", 1, GetArtistDetails_handler, c, "[GetArtistDetails %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetArtists_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetArtists(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetArtists", 1, GetArtists_handler, c, "[GetArtists %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetArtistsInGenre_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetArtistsInGenre(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetArtistsInGenre", 1, GetArtistsInGenre_handler, c, "[GetArtistsInGenre %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetArtistsInSubGenre_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetArtistsInSubGenre(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetArtistsInSubGenre", 1, GetArtistsInSubGenre_handler, c, "[GetArtistsInSubGenre %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetArtistsInSubGenreForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetArtistsInSubGenreForDevice(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetArtistsInSubGenreForDevice", 1, GetArtistsInSubGenreForDevice_handler, c, "[GetArtistsInSubGenreForDevice %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetArtistsInSubGenreForServer_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetArtistsInSubGenreForServer(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetArtistsInSubGenreForServer", 1, GetArtistsInSubGenreForServer_handler, c, "[GetArtistsInSubGenreForServer %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetArtistsInSubGenreForShare_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetArtistsInSubGenreForShare(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetArtistsInSubGenreForShare", 1, GetArtistsInSubGenreForShare_handler, c, "[GetArtistsInSubGenreForShare %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetArtistsForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetArtistsForDevice(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetArtistsForDevice", 1, GetArtistsForDevice_handler, c, "[GetArtistsForDevice %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetArtistsForShare_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetArtistsForShare(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetArtistsForShare", 1, GetArtistsForShare_handler, c, "[GetArtistsForShare %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetArtistsForServer_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetArtistsForServer(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetArtistsForServer", 1, GetArtistsForServer_handler, c, "[GetArtistsForServer %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetGenres_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetGenres(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetGenres", 1, GetGenres_handler, c, "[GetGenres %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetSubGenresForGenre_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetSubGenresForGenre(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetSubGenresForGenre", 1, GetSubGenresForGenre_handler, c, "[GetSubGenresForGenre %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetGenresSubGenres_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetGenresSubGenres(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetGenresSubGenres", 1, GetGenresSubGenres_handler, c, "[GetGenresSubGenres %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetSubGenresForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetSubGenresForDevice(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetSubGenresForDevice", 1, GetSubGenresForDevice_handler, c, "[GetSubGenresForDevice %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetSubGenresForShare_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetSubGenresForShare(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetSubGenresForShare", 1, GetSubGenresForShare_handler, c, "[GetSubGenresForShare %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetSubGenresForServer_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetSubGenresForServer(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetSubGenresForServer", 1, GetSubGenresForServer_handler, c, "[GetSubGenresForServer %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetCDDBGenres_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetCDDBGenres(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetCDDBGenres", 1, GetCDDBGenres_handler, c, "[GetCDDBGenres %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void UndoUserEdits_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_UndoUserEdits(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "UndoUserEdits", 1, UndoUserEdits_handler, c, "[UndoUserEdits %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetTracksForArtistForServer_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetTracksForArtistForServer(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTracksForArtistForServer", 1, GetTracksForArtistForServer_handler, c, "[GetTracksForArtistForServer %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetTracksForArtistForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetTracksForArtistForDevice(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTracksForArtistForDevice", 1, GetTracksForArtistForDevice_handler, c, "[GetTracksForArtistForDevice %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetTracksForArtistForShare_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetTracksForArtistForShare(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTracksForArtistForShare", 1, GetTracksForArtistForShare_handler, c, "[GetTracksForArtistForShare %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetTracksForSubGenreForServer_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetTracksForSubGenreForServer(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTracksForSubGenreForServer", 1, GetTracksForSubGenreForServer_handler, c, "[GetTracksForSubGenreForServer %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetTracksForSubGenreForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetTracksForSubGenreForDevice(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTracksForSubGenreForDevice", 1, GetTracksForSubGenreForDevice_handler, c, "[GetTracksForSubGenreForDevice %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetTracksForSubGenreForShare_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetTracksForSubGenreForShare(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTracksForSubGenreForShare", 1, GetTracksForSubGenreForShare_handler, c, "[GetTracksForSubGenreForShare %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAlbumsWithAlbumLookupMessages_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAlbumsWithAlbumLookupMessages(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlbumsWithAlbumLookupMessages", 1, GetAlbumsWithAlbumLookupMessages_handler, c, "[GetAlbumsWithAlbumLookupMessages %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetAlbumsForDeletion_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetAlbumsForDeletion(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlbumsForDeletion", 1, GetAlbumsForDeletion_handler, c, "[GetAlbumsForDeletion %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetTracksForDeletion_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetTracksForDeletion(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTracksForDeletion", 1, GetTracksForDeletion_handler, c, "[GetTracksForDeletion %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void BulkCDLookup_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_BulkCDLookup(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "BulkCDLookup", 1, BulkCDLookup_handler, c, "[BulkCDLookup %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void CDLookupGetQueue_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_CDLookupGetQueue(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CDLookupGetQueue", 1, CDLookupGetQueue_handler, c, "[CDLookupGetQueue %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetComponentVersions_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetComponentVersions(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetComponentVersions", 1, GetComponentVersions_handler, c, "[GetComponentVersions %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtAlbumCredits_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtAlbumCredits(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtAlbumCredits", 1, GetExtAlbumCredits_handler, c, "[GetExtAlbumCredits %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtAlbumsByContributor_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtAlbumsByContributor(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtAlbumsByContributor", 1, GetExtAlbumsByContributor_handler, c, "[GetExtAlbumsByContributor %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtAlbumsByContributorForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtAlbumsByContributorForDevice(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtAlbumsByContributorForDevice", 1, GetExtAlbumsByContributorForDevice_handler, c, "[GetExtAlbumsByContributorForDevice %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtAlbumsByContributorForShare_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtAlbumsByContributorForShare(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtAlbumsByContributorForShare", 1, GetExtAlbumsByContributorForShare_handler, c, "[GetExtAlbumsByContributorForShare %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtAlbumsByContributorForServer_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtAlbumsByContributorForServer(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtAlbumsByContributorForServer", 1, GetExtAlbumsByContributorForServer_handler, c, "[GetExtAlbumsByContributorForServer %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtAlbumsByCredit_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtAlbumsByCredit(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtAlbumsByCredit", 1, GetExtAlbumsByCredit_handler, c, "[GetExtAlbumsByCredit %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtAlbumsByWork_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtAlbumsByWork(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtAlbumsByWork", 1, GetExtAlbumsByWork_handler, c, "[GetExtAlbumsByWork %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtAlbumsInfo_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtAlbumsInfo(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtAlbumsInfo", 1, GetExtAlbumsInfo_handler, c, "[GetExtAlbumsInfo %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtContributors_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtContributors(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtContributors", 1, GetExtContributors_handler, c, "[GetExtContributors %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtContributorsForAlbum_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtContributorsForAlbum(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtContributorsForAlbum", 1, GetExtContributorsForAlbum_handler, c, "[GetExtContributorsForAlbum %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtContributorsForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtContributorsForDevice(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtContributorsForDevice", 1, GetExtContributorsForDevice_handler, c, "[GetExtContributorsForDevice %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtContributorsForShare_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtContributorsForShare(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtContributorsForShare", 1, GetExtContributorsForShare_handler, c, "[GetExtContributorsForShare %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtContributorsForServer_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtContributorsForServer(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtContributorsForServer", 1, GetExtContributorsForServer_handler, c, "[GetExtContributorsForServer %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtTrackContributors_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtTrackContributors(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtTrackContributors", 1, GetExtTrackContributors_handler, c, "[GetExtTrackContributors %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtTracksByContributor_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtTracksByContributor(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtTracksByContributor", 1, GetExtTracksByContributor_handler, c, "[GetExtTracksByContributor %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtTracksByWork_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtTracksByWork(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtTracksByWork", 1, GetExtTracksByWork_handler, c, "[GetExtTracksByWork %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtTracksInfo_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtTracksInfo(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtTracksInfo", 1, GetExtTracksInfo_handler, c, "[GetExtTracksInfo %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtWorks_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtWorks(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtWorks", 1, GetExtWorks_handler, c, "[GetExtWorks %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtContributorDetails_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtContributorDetails(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtContributorDetails", 1, GetExtContributorDetails_handler, c, "[GetExtContributorDetails %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtTracksByContributorForServer_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtTracksByContributorForServer(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtTracksByContributorForServer", 1, GetExtTracksByContributorForServer_handler, c, "[GetExtTracksByContributorForServer %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtTracksByContributorForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtTracksByContributorForDevice(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtTracksByContributorForDevice", 1, GetExtTracksByContributorForDevice_handler, c, "[GetExtTracksByContributorForDevice %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtTracksByContributorForShare_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtTracksByContributorForShare(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtTracksByContributorForShare", 1, GetExtTracksByContributorForShare_handler, c, "[GetExtTracksByContributorForShare %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetExtAlbumsSearchPeople_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetExtAlbumsSearchPeople(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtAlbumsSearchPeople", 1, GetExtAlbumsSearchPeople_handler, c, "[GetExtAlbumsSearchPeople %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void vTunerLookupById_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_vTunerLookupById(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "vTunerLookupById", 1, vTunerLookupById_handler, c, "[vTunerLookupById %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void vTunerGetChildNodes_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_vTunerGetChildNodes(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "vTunerGetChildNodes", 1, vTunerGetChildNodes_handler, c, "[vTunerGetChildNodes %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void vTunerGetMostPlayed_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_vTunerGetMostPlayed(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "vTunerGetMostPlayed", 1, vTunerGetMostPlayed_handler, c, "[vTunerGetMostPlayed %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void vTunerGetLastPlayed_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_vTunerGetLastPlayed(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "vTunerGetLastPlayed", 1, vTunerGetLastPlayed_handler, c, "[vTunerGetLastPlayed %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void vTunerGetPresetChannels_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_vTunerGetPresetChannels(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "vTunerGetPresetChannels", 1, vTunerGetPresetChannels_handler, c, "[vTunerGetPresetChannels %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void vTunerGetNodeFromPlayedUrl_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_vTunerGetNodeFromPlayedUrl(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "vTunerGetNodeFromPlayedUrl", 1, vTunerGetNodeFromPlayedUrl_handler, c, "[vTunerGetNodeFromPlayedUrl %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetStores_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetStores(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetStores", 1, GetStores_handler, c, "[GetStores %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void GetStoreDetail_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_GetStoreDetail(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetStoreDetail", 1, GetStoreDetail_handler, c, "[GetStoreDetail %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

static void MoveAlbumGetQueue_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==NULL) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_MoveAlbumGetQueue(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "MoveAlbumGetQueue", 1, MoveAlbumGetQueue_handler, c, "[MoveAlbumGetQueue %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}

