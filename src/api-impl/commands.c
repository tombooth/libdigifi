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
#include "../comms/comm_out.h"
#include "../utility/allocator.h"
#include "../utility/formatting.h"
#include "../utility/debugging.h"


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
  df_search *s = 0;
  struct search_call_holder *sch;
  
  if (response != 0) {
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

	if (response != 0) {
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
	struct call_holder *holder = context;
	char* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   tmp= formatting_process(rx->subexps[2].value);
   
	((void (*)(char*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_GetCurOp(df_connection *conn, void (*callback)(char*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetCurOp", 1, GetCurOp_handler, c, "[GetCurOp]");
}


static void ReleaseSerialPort_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_ReleaseSerialPort(df_connection *conn, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ReleaseSerialPort", 1, ReleaseSerialPort_handler, c, "[ReleaseSerialPort]");
}


static void Version_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_60* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_60));
   memset(tmp, 0, sizeof(type_60));

   tmp->Version_Service= formatting_process(rx->subexps[2].value);
   tmp->Version_Protocol= formatting_process(rx->subexps[3].value);
   tmp->Version_CommandDef= formatting_process(rx->subexps[4].value);
   tmp->Version_System= formatting_process(rx->subexps[5].value);
   
	((void (*)(type_60*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_Version(df_connection *conn, void (*callback)(type_60*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "Version", 1, Version_handler, c, "[Version]");
}


static void GetRows_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_7* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_7));
   memset(tmp, 0, sizeof(type_7));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   sscanf(rx->subexps[3].value,"%d",&(tmp->GetRooms_Return));
   
	((void (*)(type_7*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_GetRows(df_connection *conn, int SearchNumber, int StartRow, int RowCount, char* FormatList, void (*callback)(type_7*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetRows", 1, GetRows_handler, c, "[GetRows %d %d %d \"%s\"]", SearchNumber, StartRow, RowCount, FormatList);
}


static void GetCount_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_7* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_7));
   memset(tmp, 0, sizeof(type_7));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   sscanf(rx->subexps[3].value,"%d",&(tmp->GetRooms_Return));
   
	((void (*)(type_7*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_GetCount(df_connection *conn, int SearchNumber, void (*callback)(type_7*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetCount", 1, GetCount_handler, c, "[GetCount %d]", SearchNumber);
}


static void GetLastError_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	char* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   tmp= formatting_process(rx->subexps[2].value);
   
	((void (*)(char*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_GetLastError(df_connection *conn, void (*callback)(char*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetLastError", 1, GetLastError_handler, c, "[GetLastError]");
}


static void LookupError_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_3* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_3));
   memset(tmp, 0, sizeof(type_3));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   tmp->CommandName= formatting_process(rx->subexps[3].value);
   
	((void (*)(type_3*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_LookupError(df_connection *conn, int ErrorCode, void (*callback)(type_3*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "LookupError", 1, LookupError_handler, c, "[LookupError %d]", ErrorCode);
}


static void FindAllRooms_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_7* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_7));
   memset(tmp, 0, sizeof(type_7));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   sscanf(rx->subexps[3].value,"%d",&(tmp->GetRooms_Return));
   
	((void (*)(type_7*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_FindAllRooms(df_connection *conn, int TimeoutPerHost, void (*callback)(type_7*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "FindAllRooms", 1, FindAllRooms_handler, c, "[FindAllRooms %d]", TimeoutPerHost);
}


static void FindNewRooms_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_7* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_7));
   memset(tmp, 0, sizeof(type_7));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   sscanf(rx->subexps[3].value,"%d",&(tmp->GetRooms_Return));
   
	((void (*)(type_7*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_FindNewRooms(df_connection *conn, int TimeoutPerHost, void (*callback)(type_7*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "FindNewRooms", 1, FindNewRooms_handler, c, "[FindNewRooms %d]", TimeoutPerHost);
}


static void RemoveOldRooms_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_7* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_7));
   memset(tmp, 0, sizeof(type_7));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   sscanf(rx->subexps[3].value,"%d",&(tmp->GetRooms_Return));
   
	((void (*)(type_7*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_RemoveOldRooms(df_connection *conn, int TimeoutPerHost, void (*callback)(type_7*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RemoveOldRooms", 1, RemoveOldRooms_handler, c, "[RemoveOldRooms %d]", TimeoutPerHost);
}


static void ServiceMode_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_3* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_3));
   memset(tmp, 0, sizeof(type_3));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   tmp->CommandName= formatting_process(rx->subexps[3].value);
   
	((void (*)(type_3*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_ServiceMode(df_connection *conn, void (*callback)(type_3*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ServiceMode", 1, ServiceMode_handler, c, "[ServiceMode]");
}


static void GetSearchOffset_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_5* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_5));
   memset(tmp, 0, sizeof(type_5));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   sscanf(rx->subexps[3].value,"%d",&(tmp->TargetSearchNumber));
   sscanf(rx->subexps[4].value,"%d",&(tmp->FilterSearch_Return));
   
	((void (*)(type_5*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_GetSearchOffset(df_connection *conn, int SearchNumber, char* SearchValue, char* SearchColumn, int SearchType, void (*callback)(type_5*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetSearchOffset", 1, GetSearchOffset_handler, c, "[GetSearchOffset %d \"%s\" \"%s\" %d]", SearchNumber, SearchValue, SearchColumn, SearchType);
}


static void GetSystemTime_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_61* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_61));
   memset(tmp, 0, sizeof(type_61));

   sscanf(rx->subexps[2].value,"%u-%u-%u", &(tmp->GetSystemTime_Date.year), &(tmp->GetSystemTime_Date.month), &(tmp->GetSystemTime_Date.day));
   sscanf(rx->subexps[3].value,"%u-%u-%u", &(tmp->GetSystemTime_Time.hours), &(tmp->GetSystemTime_Time.minutes), &(tmp->GetSystemTime_Time.seconds));
   
	((void (*)(type_61*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_GetSystemTime(df_connection *conn, void (*callback)(type_61*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetSystemTime", 1, GetSystemTime_handler, c, "[GetSystemTime]");
}


static void GetHostDetails_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_62* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_62));
   memset(tmp, 0, sizeof(type_62));

   tmp->GetHostDetails_Name= formatting_process(rx->subexps[2].value);
   tmp->GetHostDetails_Address= formatting_process(rx->subexps[3].value);
   
	((void (*)(type_62*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_GetHostDetails(df_connection *conn, void (*callback)(type_62*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetHostDetails", 1, GetHostDetails_handler, c, "[GetHostDetails]");
}


static void GetRecycleBinStatus_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_63* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_63));
   memset(tmp, 0, sizeof(type_63));

   sscanf(rx->subexps[2].value,"%d",&(tmp->IsBusy));
   tmp->Status= formatting_process(rx->subexps[3].value);
   sscanf(rx->subexps[4].value,"%d",&(tmp->PercentComplete));
   
	((void (*)(type_63*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_GetRecycleBinStatus(df_connection *conn, void (*callback)(type_63*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetRecycleBinStatus", 1, GetRecycleBinStatus_handler, c, "[GetRecycleBinStatus]");
}


static void GetSetupVal_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_GetSetupVal(df_connection *conn, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetSetupVal", 1, GetSetupVal_handler, c, "[GetSetupVal]");
}


static void NextTrack_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_7* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_7));
   memset(tmp, 0, sizeof(type_7));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   sscanf(rx->subexps[3].value,"%d",&(tmp->GetRooms_Return));
   
	((void (*)(type_7*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_NextTrack(df_connection *conn, int RoomID, void (*callback)(type_7*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "NextTrack", 1, NextTrack_handler, c, "[NextTrack %d]", RoomID);
}


static void PrevTrack_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_7* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_7));
   memset(tmp, 0, sizeof(type_7));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   sscanf(rx->subexps[3].value,"%d",&(tmp->GetRooms_Return));
   
	((void (*)(type_7*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_PrevTrack(df_connection *conn, int RoomID, void (*callback)(type_7*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "PrevTrack", 1, PrevTrack_handler, c, "[PrevTrack %d]", RoomID);
}


static void RemoveTrack_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_55* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_55));
   memset(tmp, 0, sizeof(type_55));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   sscanf(rx->subexps[3].value,"%d",&(tmp->GetStoreDetail_Success));
   
	((void (*)(type_55*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_RemoveTrack(df_connection *conn, int RoomID, int TrackNumber, void (*callback)(type_55*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RemoveTrack", 1, RemoveTrack_handler, c, "[RemoveTrack %d %d]", RoomID, TrackNumber);
}


static void PlayAlbums_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_7* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_7));
   memset(tmp, 0, sizeof(type_7));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   sscanf(rx->subexps[3].value,"%d",&(tmp->GetRooms_Return));
   
	((void (*)(type_7*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_PlayAlbums(df_connection *conn, int RoomID, int Replace, char* Address, void (*callback)(type_7*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "PlayAlbums", 1, PlayAlbums_handler, c, "[PlayAlbums %d %d \"%s\"]", RoomID, Replace, Address);
}


static void PlayAll_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_7* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_7));
   memset(tmp, 0, sizeof(type_7));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   sscanf(rx->subexps[3].value,"%d",&(tmp->GetRooms_Return));
   
	((void (*)(type_7*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_PlayAll(df_connection *conn, int RoomID, int Replace, int PlayScope, char* ScopeKey, int PlayType, char* Address, void (*callback)(type_7*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "PlayAll", 1, PlayAll_handler, c, "[PlayAll %d %d %d \"%s\" %d \"%s\"]", RoomID, Replace, PlayScope, ScopeKey, PlayType, Address);
}


static void PlayAlbum_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_7* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_7));
   memset(tmp, 0, sizeof(type_7));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   sscanf(rx->subexps[3].value,"%d",&(tmp->GetRooms_Return));
   
	((void (*)(type_7*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_PlayAlbum(df_connection *conn, int RoomID, int Replace, char* Address, int StartTrack, void (*callback)(type_7*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "PlayAlbum", 1, PlayAlbum_handler, c, "[PlayAlbum %d %d \"%s\" %d]", RoomID, Replace, Address, StartTrack);
}


static void PlayTrack_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_7* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_7));
   memset(tmp, 0, sizeof(type_7));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   sscanf(rx->subexps[3].value,"%d",&(tmp->GetRooms_Return));
   
	((void (*)(type_7*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_PlayTrack(df_connection *conn, int RoomID, int Replace, char* Address, void (*callback)(type_7*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "PlayTrack", 1, PlayTrack_handler, c, "[PlayTrack %d %d \"%s\"]", RoomID, Replace, Address);
}


static void PlayTracks_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_7* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_7));
   memset(tmp, 0, sizeof(type_7));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   sscanf(rx->subexps[3].value,"%d",&(tmp->GetRooms_Return));
   
	((void (*)(type_7*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_PlayTracks(df_connection *conn, int RoomID, int Replace, char* Address, int StartTrack, void (*callback)(type_7*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "PlayTracks", 1, PlayTracks_handler, c, "[PlayTracks %d %d \"%s\" %d]", RoomID, Replace, Address, StartTrack);
}


static void PlayTracksFromSearch_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_7* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_7));
   memset(tmp, 0, sizeof(type_7));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   sscanf(rx->subexps[3].value,"%d",&(tmp->GetRooms_Return));
   
	((void (*)(type_7*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_PlayTracksFromSearch(df_connection *conn, int RoomID, int SearchNumber, int Replace, int StartTrack, void (*callback)(type_7*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "PlayTracksFromSearch", 1, PlayTracksFromSearch_handler, c, "[PlayTracksFromSearch %d %d %d %d]", RoomID, SearchNumber, Replace, StartTrack);
}


static void PlayAlbumsFromSearch_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_7* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_7));
   memset(tmp, 0, sizeof(type_7));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   sscanf(rx->subexps[3].value,"%d",&(tmp->GetRooms_Return));
   
	((void (*)(type_7*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_PlayAlbumsFromSearch(df_connection *conn, int RoomID, int SearchNumber, int Replace, void (*callback)(type_7*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "PlayAlbumsFromSearch", 1, PlayAlbumsFromSearch_handler, c, "[PlayAlbumsFromSearch %d %d %d]", RoomID, SearchNumber, Replace);
}


static void PlayUrl_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_7* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_7));
   memset(tmp, 0, sizeof(type_7));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   sscanf(rx->subexps[3].value,"%d",&(tmp->GetRooms_Return));
   
	((void (*)(type_7*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_PlayUrl(df_connection *conn, int RoomID, int Replace, char* Url, void (*callback)(type_7*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "PlayUrl", 1, PlayUrl_handler, c, "[PlayUrl %d %d \"%s\"]", RoomID, Replace, Url);
}


static void PlayUrls_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_7* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_7));
   memset(tmp, 0, sizeof(type_7));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   sscanf(rx->subexps[3].value,"%d",&(tmp->GetRooms_Return));
   
	((void (*)(type_7*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_PlayUrls(df_connection *conn, int RoomID, int Replace, char* Urls, int StartTrack, void (*callback)(type_7*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "PlayUrls", 1, PlayUrls_handler, c, "[PlayUrls %d %d \"%s\" %d]", RoomID, Replace, Urls, StartTrack);
}


static void PlayPlaylist_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_7* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_7));
   memset(tmp, 0, sizeof(type_7));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   sscanf(rx->subexps[3].value,"%d",&(tmp->GetRooms_Return));
   
	((void (*)(type_7*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_PlayPlaylist(df_connection *conn, int RoomID, char* PlaylistName, int Randomise, int OnErrorBehaviour, void (*callback)(type_7*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "PlayPlaylist", 1, PlayPlaylist_handler, c, "[PlayPlaylist %d \"%s\" %d %d]", RoomID, PlaylistName, Randomise, OnErrorBehaviour);
}


static void PlayRandom_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_7* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_7));
   memset(tmp, 0, sizeof(type_7));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   sscanf(rx->subexps[3].value,"%d",&(tmp->GetRooms_Return));
   
	((void (*)(type_7*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_PlayRandom(df_connection *conn, int RoomID, char* Genre, char* SubGenre, int OnErrorBehaviour, void (*callback)(type_7*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "PlayRandom", 1, PlayRandom_handler, c, "[PlayRandom %d \"%s\" \"%s\" %d]", RoomID, Genre, SubGenre, OnErrorBehaviour);
}


static void PlayArtistAlbum_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_7* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_7));
   memset(tmp, 0, sizeof(type_7));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   sscanf(rx->subexps[3].value,"%d",&(tmp->GetRooms_Return));
   
	((void (*)(type_7*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_PlayArtistAlbum(df_connection *conn, int RoomID, char* Artist, char* Album, int Randomise, int OnErrorBehaviour, void (*callback)(type_7*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "PlayArtistAlbum", 1, PlayArtistAlbum_handler, c, "[PlayArtistAlbum %d \"%s\" \"%s\" %d %d]", RoomID, Artist, Album, Randomise, OnErrorBehaviour);
}


static void PlayLastPlayed_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_7* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_7));
   memset(tmp, 0, sizeof(type_7));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   sscanf(rx->subexps[3].value,"%d",&(tmp->GetRooms_Return));
   
	((void (*)(type_7*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_PlayLastPlayed(df_connection *conn, int RoomID, int Randomise, int Number, void (*callback)(type_7*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "PlayLastPlayed", 1, PlayLastPlayed_handler, c, "[PlayLastPlayed %d %d %d]", RoomID, Randomise, Number);
}


static void PlayLastRipped_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_7* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_7));
   memset(tmp, 0, sizeof(type_7));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   sscanf(rx->subexps[3].value,"%d",&(tmp->GetRooms_Return));
   
	((void (*)(type_7*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_PlayLastRipped(df_connection *conn, int RoomID, int Randomise, int Number, void (*callback)(type_7*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "PlayLastRipped", 1, PlayLastRipped_handler, c, "[PlayLastRipped %d %d %d]", RoomID, Randomise, Number);
}


static void PlayMostPopular_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_7* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_7));
   memset(tmp, 0, sizeof(type_7));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   sscanf(rx->subexps[3].value,"%d",&(tmp->GetRooms_Return));
   
	((void (*)(type_7*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_PlayMostPopular(df_connection *conn, int RoomID, int Randomise, int Number, void (*callback)(type_7*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "PlayMostPopular", 1, PlayMostPopular_handler, c, "[PlayMostPopular %d %d %d]", RoomID, Randomise, Number);
}


static void IsCDPlaying_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_55* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_55));
   memset(tmp, 0, sizeof(type_55));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   sscanf(rx->subexps[3].value,"%d",&(tmp->GetStoreDetail_Success));
   
	((void (*)(type_55*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_IsCDPlaying(df_connection *conn, int RoomID, void (*callback)(type_55*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "IsCDPlaying", 1, IsCDPlaying_handler, c, "[IsCDPlaying %d]", RoomID);
}


static void GetTrackName_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_64* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_64));
   memset(tmp, 0, sizeof(type_64));

   sscanf(rx->subexps[2].value,"%d",&(tmp->RoomID));
   sscanf(rx->subexps[3].value,"%d",&(tmp->TrackKey));
   tmp->Name= formatting_process(rx->subexps[4].value);
   tmp->Type= formatting_process(rx->subexps[5].value);
   sscanf(rx->subexps[6].value,"%u-%u-%u", &(tmp->Length.hours), &(tmp->Length.minutes), &(tmp->Length.seconds));
   sscanf(rx->subexps[7].value,"%d",&(tmp->Source));
   
	((void (*)(type_64*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_GetTrackName(df_connection *conn, int RoomID, void (*callback)(type_64*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTrackName", 1, GetTrackName_handler, c, "[GetTrackName %d]", RoomID);
}


static void GetTrackDetailsFromPlayer_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_65* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_65));
   memset(tmp, 0, sizeof(type_65));

   sscanf(rx->subexps[2].value,"%d",&(tmp->RoomID));
   sscanf(rx->subexps[3].value,"%d",&(tmp->Source));
   tmp->Name= formatting_process(rx->subexps[4].value);
   tmp->Album= formatting_process(rx->subexps[5].value);
   tmp->Artist= formatting_process(rx->subexps[6].value);
   tmp->Genre= formatting_process(rx->subexps[7].value);
   tmp->Comment= formatting_process(rx->subexps[8].value);
   sscanf(rx->subexps[9].value,"%u-%u-%u", &(tmp->Length.hours), &(tmp->Length.minutes), &(tmp->Length.seconds));
   
	((void (*)(type_65*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_GetTrackDetailsFromPlayer(df_connection *conn, int RoomID, char* TrackPath, void (*callback)(type_65*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTrackDetailsFromPlayer", 1, GetTrackDetailsFromPlayer_handler, c, "[GetTrackDetailsFromPlayer %d \"%s\"]", RoomID, TrackPath);
}


static void GetAlbumArtist_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_66* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_66));
   memset(tmp, 0, sizeof(type_66));

   sscanf(rx->subexps[2].value,"%d",&(tmp->RoomID));
   tmp->Album= formatting_process(rx->subexps[3].value);
   tmp->Artist= formatting_process(rx->subexps[4].value);
   
	((void (*)(type_66*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_GetAlbumArtist(df_connection *conn, int RoomID, void (*callback)(type_66*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetAlbumArtist", 1, GetAlbumArtist_handler, c, "[GetAlbumArtist %d]", RoomID);
}


static void GetTrackNum_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_7* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_7));
   memset(tmp, 0, sizeof(type_7));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   sscanf(rx->subexps[3].value,"%d",&(tmp->GetRooms_Return));
   
	((void (*)(type_7*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_GetTrackNum(df_connection *conn, int RoomID, void (*callback)(type_7*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTrackNum", 1, GetTrackNum_handler, c, "[GetTrackNum %d]", RoomID);
}


static void GetTrackCount_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_7* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_7));
   memset(tmp, 0, sizeof(type_7));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   sscanf(rx->subexps[3].value,"%d",&(tmp->GetRooms_Return));
   
	((void (*)(type_7*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_GetTrackCount(df_connection *conn, int RoomID, void (*callback)(type_7*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTrackCount", 1, GetTrackCount_handler, c, "[GetTrackCount %d]", RoomID);
}


static void GetShuffle_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_55* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_55));
   memset(tmp, 0, sizeof(type_55));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   sscanf(rx->subexps[3].value,"%d",&(tmp->GetStoreDetail_Success));
   
	((void (*)(type_55*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_GetShuffle(df_connection *conn, int RoomID, void (*callback)(type_55*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetShuffle", 1, GetShuffle_handler, c, "[GetShuffle %d]", RoomID);
}


static void GetRepeat_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_55* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_55));
   memset(tmp, 0, sizeof(type_55));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   sscanf(rx->subexps[3].value,"%d",&(tmp->GetStoreDetail_Success));
   
	((void (*)(type_55*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_GetRepeat(df_connection *conn, int RoomID, void (*callback)(type_55*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetRepeat", 1, GetRepeat_handler, c, "[GetRepeat %d]", RoomID);
}


static void GetPlayerStatus_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_3* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_3));
   memset(tmp, 0, sizeof(type_3));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   tmp->CommandName= formatting_process(rx->subexps[3].value);
   
	((void (*)(type_3*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_GetPlayerStatus(df_connection *conn, int RoomID, void (*callback)(type_3*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetPlayerStatus", 1, GetPlayerStatus_handler, c, "[GetPlayerStatus %d]", RoomID);
}


static void GetTrackLength_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_67* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_67));
   memset(tmp, 0, sizeof(type_67));

   sscanf(rx->subexps[2].value,"%d",&(tmp->RoomID));
   sscanf(rx->subexps[3].value,"%u-%u-%u", &(tmp->TrackLength.hours), &(tmp->TrackLength.minutes), &(tmp->TrackLength.seconds));
   
	((void (*)(type_67*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_GetTrackLength(df_connection *conn, int RoomID, void (*callback)(type_67*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTrackLength", 1, GetTrackLength_handler, c, "[GetTrackLength %d]", RoomID);
}


static void GetTrackPosition_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_67* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_67));
   memset(tmp, 0, sizeof(type_67));

   sscanf(rx->subexps[2].value,"%d",&(tmp->RoomID));
   sscanf(rx->subexps[3].value,"%u-%u-%u", &(tmp->TrackLength.hours), &(tmp->TrackLength.minutes), &(tmp->TrackLength.seconds));
   
	((void (*)(type_67*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_GetTrackPosition(df_connection *conn, int RoomID, void (*callback)(type_67*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetTrackPosition", 1, GetTrackPosition_handler, c, "[GetTrackPosition %d]", RoomID);
}


static void GetPlayerVersion_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_3* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_3));
   memset(tmp, 0, sizeof(type_3));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   tmp->CommandName= formatting_process(rx->subexps[3].value);
   
	((void (*)(type_3*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_GetPlayerVersion(df_connection *conn, int RoomID, void (*callback)(type_3*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetPlayerVersion", 1, GetPlayerVersion_handler, c, "[GetPlayerVersion %d]", RoomID);
}


static void GetVolume_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_7* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_7));
   memset(tmp, 0, sizeof(type_7));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   sscanf(rx->subexps[3].value,"%d",&(tmp->GetRooms_Return));
   
	((void (*)(type_7*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_GetVolume(df_connection *conn, int RoomID, void (*callback)(type_7*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetVolume", 1, GetVolume_handler, c, "[GetVolume %d]", RoomID);
}


static void QueryAllPlayback_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_68* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_68));
   memset(tmp, 0, sizeof(type_68));

   sscanf(rx->subexps[2].value,"%d",&(tmp->RoomID));
   sscanf(rx->subexps[3].value,"%d",&(tmp->CDPlaying));
   tmp->TrackName= formatting_process(rx->subexps[4].value);
   tmp->Album= formatting_process(rx->subexps[5].value);
   tmp->Artist= formatting_process(rx->subexps[6].value);
   sscanf(rx->subexps[7].value,"%d",&(tmp->TrackNumber));
   sscanf(rx->subexps[8].value,"%d",&(tmp->TrackCount));
   sscanf(rx->subexps[9].value,"%d",&(tmp->Shuffle));
   sscanf(rx->subexps[10].value,"%d",&(tmp->Repeat));
   tmp->Status= formatting_process(rx->subexps[11].value);
   sscanf(rx->subexps[12].value,"%u-%u-%u", &(tmp->TrackLength.hours), &(tmp->TrackLength.minutes), &(tmp->TrackLength.seconds));
   sscanf(rx->subexps[13].value,"%u-%u-%u", &(tmp->TrackPosition.hours), &(tmp->TrackPosition.minutes), &(tmp->TrackPosition.seconds));
   tmp->Version= formatting_process(rx->subexps[14].value);
   sscanf(rx->subexps[15].value,"%d",&(tmp->Volume));
   
	((void (*)(type_68*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_QueryAllPlayback(df_connection *conn, int RoomID, void (*callback)(type_68*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "QueryAllPlayback", 1, QueryAllPlayback_handler, c, "[QueryAllPlayback %d]", RoomID);
}


static void GetStatusMessageDetail_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_69* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_69));
   memset(tmp, 0, sizeof(type_69));

   tmp->Key= formatting_process(rx->subexps[2].value);
   tmp->Message= formatting_process(rx->subexps[3].value);
   tmp->Category= formatting_process(rx->subexps[4].value);
   sscanf(rx->subexps[5].value,"%u-%u-%u", &(tmp->DateCreated.year), &(tmp->DateCreated.month), &(tmp->DateCreated.day));
   
	((void (*)(type_69*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_GetStatusMessageDetail(df_connection *conn, char* Key, void (*callback)(type_69*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetStatusMessageDetail", 1, GetStatusMessageDetail_handler, c, "[GetStatusMessageDetail \"%s\"]", Key);
}


static void GetLibraryCheckSum_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_7* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_7));
   memset(tmp, 0, sizeof(type_7));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   sscanf(rx->subexps[3].value,"%d",&(tmp->GetRooms_Return));
   
	((void (*)(type_7*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_GetLibraryCheckSum(df_connection *conn, int RoomID, void (*callback)(type_7*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetLibraryCheckSum", 1, GetLibraryCheckSum_handler, c, "[GetLibraryCheckSum %d]", RoomID);
}


static void CancelRipping_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_55* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_55));
   memset(tmp, 0, sizeof(type_55));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   sscanf(rx->subexps[3].value,"%d",&(tmp->GetStoreDetail_Success));
   
	((void (*)(type_55*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_CancelRipping(df_connection *conn, int RoomID, void (*callback)(type_55*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CancelRipping", 1, CancelRipping_handler, c, "[CancelRipping %d]", RoomID);
}


static void BackupUserPlaylists_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_70* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_70));
   memset(tmp, 0, sizeof(type_70));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SuccessCount));
   tmp->SuccessNames= formatting_process(rx->subexps[3].value);
   sscanf(rx->subexps[4].value,"%d",&(tmp->PartialCount));
   tmp->PartialNames= formatting_process(rx->subexps[5].value);
   sscanf(rx->subexps[6].value,"%d",&(tmp->FailureCount));
   tmp->FailureNames= formatting_process(rx->subexps[7].value);
   
	((void (*)(type_70*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_BackupUserPlaylists(df_connection *conn, void (*callback)(type_70*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "BackupUserPlaylists", 1, BackupUserPlaylists_handler, c, "[BackupUserPlaylists]");
}


static void RestoreUserPlaylists_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_70* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_70));
   memset(tmp, 0, sizeof(type_70));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SuccessCount));
   tmp->SuccessNames= formatting_process(rx->subexps[3].value);
   sscanf(rx->subexps[4].value,"%d",&(tmp->PartialCount));
   tmp->PartialNames= formatting_process(rx->subexps[5].value);
   sscanf(rx->subexps[6].value,"%d",&(tmp->FailureCount));
   tmp->FailureNames= formatting_process(rx->subexps[7].value);
   
	((void (*)(type_70*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_RestoreUserPlaylists(df_connection *conn, void (*callback)(type_70*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RestoreUserPlaylists", 1, RestoreUserPlaylists_handler, c, "[RestoreUserPlaylists]");
}


static void SetNetworkBackup_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_SetNetworkBackup(df_connection *conn, int StorageKey, int Backup, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "SetNetworkBackup", 1, SetNetworkBackup_handler, c, "[SetNetworkBackup %d %d]", StorageKey, Backup);
}


static void GetDriveDetail_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_71* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_71));
   memset(tmp, 0, sizeof(type_71));

   tmp->DriveAddress= formatting_process(rx->subexps[2].value);
   sscanf(rx->subexps[3].value,"%d",&(tmp->DriveKey));
   tmp->DriveLetter= formatting_process(rx->subexps[4].value);
   sscanf(rx->subexps[5].value,"%d",&(tmp->Primary));
   tmp->RootPath= formatting_process(rx->subexps[6].value);
   tmp->SharePath= formatting_process(rx->subexps[7].value);
   sscanf(rx->subexps[8].value,"%u-%u-%u", &(tmp->Created.year), &(tmp->Created.month), &(tmp->Created.day));
   sscanf(rx->subexps[9].value,"%u-%u-%u", &(tmp->Modified.year), &(tmp->Modified.month), &(tmp->Modified.day));
   sscanf(rx->subexps[10].value,"%d",&(tmp->Usage));
   sscanf(rx->subexps[11].value,"%u-%u-%u", &(tmp->LastBackup.year), &(tmp->LastBackup.month), &(tmp->LastBackup.day));
   
	((void (*)(type_71*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_GetDriveDetail(df_connection *conn, char* DriveAddress, void (*callback)(type_71*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetDriveDetail", 1, GetDriveDetail_handler, c, "[GetDriveDetail \"%s\"]", DriveAddress);
}


static void GetFileSystemDriveDetail_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_72* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_72));
   memset(tmp, 0, sizeof(type_72));

   tmp->DriveLetter= formatting_process(rx->subexps[2].value);
   tmp->DriveLetterOut= formatting_process(rx->subexps[3].value);
   tmp->RootPath= formatting_process(rx->subexps[4].value);
   tmp->SharePath= formatting_process(rx->subexps[5].value);
   sscanf(rx->subexps[6].value,"%d",&(tmp->Usage));
   
	((void (*)(type_72*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_GetFileSystemDriveDetail(df_connection *conn, char* DriveLetter, void (*callback)(type_72*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetFileSystemDriveDetail", 1, GetFileSystemDriveDetail_handler, c, "[GetFileSystemDriveDetail \"%s\"]", DriveLetter);
}


static void AddNewDrive_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_73* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_73));
   memset(tmp, 0, sizeof(type_73));

   tmp->DriveLetter= formatting_process(rx->subexps[2].value);
   sscanf(rx->subexps[3].value,"%d",&(tmp->AddNewDrive_Return));
   tmp->AddNewDrive_ErrorMessage= formatting_process(rx->subexps[4].value);
   
	((void (*)(type_73*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_AddNewDrive(df_connection *conn, char* DriveLetter, int PrimaryDrive, char* RootPath, char* SharePath, int Usage, int BadPathBehaviour, void (*callback)(type_73*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "AddNewDrive", 1, AddNewDrive_handler, c, "[AddNewDrive \"%s\" %d \"%s\" \"%s\" %d %d]", DriveLetter, PrimaryDrive, RootPath, SharePath, Usage, BadPathBehaviour);
}


static void UpdateDrive_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_74* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_74));
   memset(tmp, 0, sizeof(type_74));

   tmp->DriveKey= formatting_process(rx->subexps[2].value);
   sscanf(rx->subexps[3].value,"%d",&(tmp->UpdateDrive_Return));
   tmp->UpdateDrive_ErrorMessage= formatting_process(rx->subexps[4].value);
   
	((void (*)(type_74*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_UpdateDrive(df_connection *conn, char* DriveKey, char* DriveLetter, int PrimaryDrive, char* RootPath, char* SharePath, int BadPathBehaviour, void (*callback)(type_74*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "UpdateDrive", 1, UpdateDrive_handler, c, "[UpdateDrive \"%s\" \"%s\" %d \"%s\" \"%s\" %d]", DriveKey, DriveLetter, PrimaryDrive, RootPath, SharePath, BadPathBehaviour);
}


static void DeleteDrive_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_75* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_75));
   memset(tmp, 0, sizeof(type_75));

   tmp->DriveKey= formatting_process(rx->subexps[2].value);
   sscanf(rx->subexps[3].value,"%d",&(tmp->DeleteDrive_Return));
   
	((void (*)(type_75*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_DeleteDrive(df_connection *conn, char* DriveKey, void (*callback)(type_75*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "DeleteDrive", 1, DeleteDrive_handler, c, "[DeleteDrive \"%s\"]", DriveKey);
}


static void DeleteRoom_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_75* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_75));
   memset(tmp, 0, sizeof(type_75));

   tmp->DriveKey= formatting_process(rx->subexps[2].value);
   sscanf(rx->subexps[3].value,"%d",&(tmp->DeleteDrive_Return));
   
	((void (*)(type_75*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_DeleteRoom(df_connection *conn, char* RoomKey, void (*callback)(type_75*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "DeleteRoom", 1, DeleteRoom_handler, c, "[DeleteRoom \"%s\"]", RoomKey);
}


static void DeleteLinkedRoom_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_75* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_75));
   memset(tmp, 0, sizeof(type_75));

   tmp->DriveKey= formatting_process(rx->subexps[2].value);
   sscanf(rx->subexps[3].value,"%d",&(tmp->DeleteDrive_Return));
   
	((void (*)(type_75*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_DeleteLinkedRoom(df_connection *conn, char* RoomKey, void (*callback)(type_75*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "DeleteLinkedRoom", 1, DeleteLinkedRoom_handler, c, "[DeleteLinkedRoom \"%s\"]", RoomKey);
}


static void GetSingleSystemSetting_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_3* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_3));
   memset(tmp, 0, sizeof(type_3));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   tmp->CommandName= formatting_process(rx->subexps[3].value);
   
	((void (*)(type_3*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_GetSingleSystemSetting(df_connection *conn, int RoomID, char* SettingName, void (*callback)(type_3*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetSingleSystemSetting", 1, GetSingleSystemSetting_handler, c, "[GetSingleSystemSetting %d \"%s\"]", RoomID, SettingName);
}


static void GetSingleRipEncSetting_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_3* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_3));
   memset(tmp, 0, sizeof(type_3));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   tmp->CommandName= formatting_process(rx->subexps[3].value);
   
	((void (*)(type_3*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_GetSingleRipEncSetting(df_connection *conn, int RoomID, char* SettingName, void (*callback)(type_3*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetSingleRipEncSetting", 1, GetSingleRipEncSetting_handler, c, "[GetSingleRipEncSetting %d \"%s\"]", RoomID, SettingName);
}


static void UpdateSingleRipEncSetting_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_3* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_3));
   memset(tmp, 0, sizeof(type_3));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   tmp->CommandName= formatting_process(rx->subexps[3].value);
   
	((void (*)(type_3*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_UpdateSingleRipEncSetting(df_connection *conn, int RoomID, char* SettingName, char* NewValue, void (*callback)(type_3*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "UpdateSingleRipEncSetting", 1, UpdateSingleRipEncSetting_handler, c, "[UpdateSingleRipEncSetting %d \"%s\" \"%s\"]", RoomID, SettingName, NewValue);
}


static void UpdateSingleSystemSetting_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_3* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_3));
   memset(tmp, 0, sizeof(type_3));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   tmp->CommandName= formatting_process(rx->subexps[3].value);
   
	((void (*)(type_3*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_UpdateSingleSystemSetting(df_connection *conn, int RoomID, char* SettingName, char* NewValue, void (*callback)(type_3*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "UpdateSingleSystemSetting", 1, UpdateSingleSystemSetting_handler, c, "[UpdateSingleSystemSetting %d \"%s\" \"%s\"]", RoomID, SettingName, NewValue);
}


static void AddNewLinkedRoom_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_76* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_76));
   memset(tmp, 0, sizeof(type_76));

   tmp->RoomName= formatting_process(rx->subexps[2].value);
   sscanf(rx->subexps[3].value,"%d",&(tmp->AddNewLinkedRoom_Return));
   
	((void (*)(type_76*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_AddNewLinkedRoom(df_connection *conn, char* RoomName, char* ShortName, int RoomID, char* ChildRoomKey, void (*callback)(type_76*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "AddNewLinkedRoom", 1, AddNewLinkedRoom_handler, c, "[AddNewLinkedRoom \"%s\" \"%s\" %d \"%s\"]", RoomName, ShortName, RoomID, ChildRoomKey);
}


static void UpdateLinkedRoom_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_75* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_75));
   memset(tmp, 0, sizeof(type_75));

   tmp->DriveKey= formatting_process(rx->subexps[2].value);
   sscanf(rx->subexps[3].value,"%d",&(tmp->DeleteDrive_Return));
   
	((void (*)(type_75*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_UpdateLinkedRoom(df_connection *conn, char* RoomKey, char* RoomName, char* ShortName, int RoomID, char* ChildRoomKey, void (*callback)(type_75*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "UpdateLinkedRoom", 1, UpdateLinkedRoom_handler, c, "[UpdateLinkedRoom \"%s\" \"%s\" \"%s\" %d \"%s\"]", RoomKey, RoomName, ShortName, RoomID, ChildRoomKey);
}


static void AddNewRoom_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_76* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_76));
   memset(tmp, 0, sizeof(type_76));

   tmp->RoomName= formatting_process(rx->subexps[2].value);
   sscanf(rx->subexps[3].value,"%d",&(tmp->AddNewLinkedRoom_Return));
   
	((void (*)(type_76*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_AddNewRoom(df_connection *conn, char* RoomIP, int Channel, char* RoomName, char* ShortName, int PlaybackCapability, int RippingCapability, int MusicManagementCapability, int RoomID, char* HostName, void (*callback)(type_76*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "AddNewRoom", 1, AddNewRoom_handler, c, "[AddNewRoom \"%s\" %d \"%s\" \"%s\" %d %d %d %d \"%s\"]", RoomIP, Channel, RoomName, ShortName, PlaybackCapability, RippingCapability, MusicManagementCapability, RoomID, HostName);
}


static void UpdateRoom_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_75* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_75));
   memset(tmp, 0, sizeof(type_75));

   tmp->DriveKey= formatting_process(rx->subexps[2].value);
   sscanf(rx->subexps[3].value,"%d",&(tmp->DeleteDrive_Return));
   
	((void (*)(type_75*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_UpdateRoom(df_connection *conn, char* RoomKey, char* RoomIP, int Channel, char* RoomName, char* ShortName, int PlaybackCapability, int RippingCapability, int MusicManagementCapability, int RoomID, char* HostName, void (*callback)(type_75*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "UpdateRoom", 1, UpdateRoom_handler, c, "[UpdateRoom \"%s\" \"%s\" %d \"%s\" \"%s\" %d %d %d %d \"%s\"]", RoomKey, RoomIP, Channel, RoomName, ShortName, PlaybackCapability, RippingCapability, MusicManagementCapability, RoomID, HostName);
}


static void GetGenreDetail_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_77* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_77));
   memset(tmp, 0, sizeof(type_77));

   tmp->GenreAddress= formatting_process(rx->subexps[2].value);
   sscanf(rx->subexps[3].value,"%d",&(tmp->GenreKey));
   tmp->GenreName= formatting_process(rx->subexps[4].value);
   sscanf(rx->subexps[5].value,"%u-%u-%u", &(tmp->Created.year), &(tmp->Created.month), &(tmp->Created.day));
   sscanf(rx->subexps[6].value,"%u-%u-%u", &(tmp->Modified.year), &(tmp->Modified.month), &(tmp->Modified.day));
   sscanf(rx->subexps[7].value,"%d",&(tmp->Ordinal));
   sscanf(rx->subexps[8].value,"%d",&(tmp->Storage));
   
	((void (*)(type_77*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_GetGenreDetail(df_connection *conn, char* GenreAddress, void (*callback)(type_77*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetGenreDetail", 1, GetGenreDetail_handler, c, "[GetGenreDetail \"%s\"]", GenreAddress);
}


static void AddNewGenre_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_76* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_76));
   memset(tmp, 0, sizeof(type_76));

   tmp->RoomName= formatting_process(rx->subexps[2].value);
   sscanf(rx->subexps[3].value,"%d",&(tmp->AddNewLinkedRoom_Return));
   
	((void (*)(type_76*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_AddNewGenre(df_connection *conn, char* GenreName, int Ordinal, void (*callback)(type_76*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "AddNewGenre", 1, AddNewGenre_handler, c, "[AddNewGenre \"%s\" %d]", GenreName, Ordinal);
}


static void UpdateGenre_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_75* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_75));
   memset(tmp, 0, sizeof(type_75));

   tmp->DriveKey= formatting_process(rx->subexps[2].value);
   sscanf(rx->subexps[3].value,"%d",&(tmp->DeleteDrive_Return));
   
	((void (*)(type_75*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_UpdateGenre(df_connection *conn, char* GenreKey, char* GenreName, int Ordinal, void (*callback)(type_75*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "UpdateGenre", 1, UpdateGenre_handler, c, "[UpdateGenre \"%s\" \"%s\" %d]", GenreKey, GenreName, Ordinal);
}


static void DeleteGenre_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_75* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_75));
   memset(tmp, 0, sizeof(type_75));

   tmp->DriveKey= formatting_process(rx->subexps[2].value);
   sscanf(rx->subexps[3].value,"%d",&(tmp->DeleteDrive_Return));
   
	((void (*)(type_75*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_DeleteGenre(df_connection *conn, char* GenreKey, void (*callback)(type_75*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "DeleteGenre", 1, DeleteGenre_handler, c, "[DeleteGenre \"%s\"]", GenreKey);
}


static void GetSubGenreDetail_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_78* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_78));
   memset(tmp, 0, sizeof(type_78));

   tmp->SubGenreAddress= formatting_process(rx->subexps[2].value);
   sscanf(rx->subexps[3].value,"%d",&(tmp->SubGenreKey));
   sscanf(rx->subexps[4].value,"%d",&(tmp->GenreKey));
   tmp->SubGenreName= formatting_process(rx->subexps[5].value);
   sscanf(rx->subexps[6].value,"%u-%u-%u", &(tmp->Created.year), &(tmp->Created.month), &(tmp->Created.day));
   sscanf(rx->subexps[7].value,"%u-%u-%u", &(tmp->Modified.year), &(tmp->Modified.month), &(tmp->Modified.day));
   sscanf(rx->subexps[8].value,"%d",&(tmp->Ordinal));
   
	((void (*)(type_78*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_GetSubGenreDetail(df_connection *conn, char* SubGenreAddress, void (*callback)(type_78*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetSubGenreDetail", 1, GetSubGenreDetail_handler, c, "[GetSubGenreDetail \"%s\"]", SubGenreAddress);
}


static void AddNewSubGenre_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_76* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_76));
   memset(tmp, 0, sizeof(type_76));

   tmp->RoomName= formatting_process(rx->subexps[2].value);
   sscanf(rx->subexps[3].value,"%d",&(tmp->AddNewLinkedRoom_Return));
   
	((void (*)(type_76*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_AddNewSubGenre(df_connection *conn, char* GenreKey, char* SubGenreName, int Ordinal, void (*callback)(type_76*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "AddNewSubGenre", 1, AddNewSubGenre_handler, c, "[AddNewSubGenre \"%s\" \"%s\" %d]", GenreKey, SubGenreName, Ordinal);
}


static void UpdateSubGenre_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_75* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_75));
   memset(tmp, 0, sizeof(type_75));

   tmp->DriveKey= formatting_process(rx->subexps[2].value);
   sscanf(rx->subexps[3].value,"%d",&(tmp->DeleteDrive_Return));
   
	((void (*)(type_75*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_UpdateSubGenre(df_connection *conn, char* SubGenreKey, char* GenreKey, char* SubGenreName, int Ordinal, void (*callback)(type_75*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "UpdateSubGenre", 1, UpdateSubGenre_handler, c, "[UpdateSubGenre \"%s\" \"%s\" \"%s\" %d]", SubGenreKey, GenreKey, SubGenreName, Ordinal);
}


static void DeleteSubGenre_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_75* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_75));
   memset(tmp, 0, sizeof(type_75));

   tmp->DriveKey= formatting_process(rx->subexps[2].value);
   sscanf(rx->subexps[3].value,"%d",&(tmp->DeleteDrive_Return));
   
	((void (*)(type_75*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_DeleteSubGenre(df_connection *conn, char* SubGenreKey, void (*callback)(type_75*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "DeleteSubGenre", 1, DeleteSubGenre_handler, c, "[DeleteSubGenre \"%s\"]", SubGenreKey);
}


static void CompactGenreOrdinals_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_CompactGenreOrdinals(df_connection *conn, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CompactGenreOrdinals", 1, CompactGenreOrdinals_handler, c, "[CompactGenreOrdinals]");
}


static void SavePlayerInstance_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_55* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_55));
   memset(tmp, 0, sizeof(type_55));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   sscanf(rx->subexps[3].value,"%d",&(tmp->GetStoreDetail_Success));
   
	((void (*)(type_55*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_SavePlayerInstance(df_connection *conn, int RoomID, int Key, int OutputDeviceID, int SourceLineID, void (*callback)(type_55*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "SavePlayerInstance", 1, SavePlayerInstance_handler, c, "[SavePlayerInstance %d %d %d %d]", RoomID, Key, OutputDeviceID, SourceLineID);
}


static void RemovePlayerInstance_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_55* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_55));
   memset(tmp, 0, sizeof(type_55));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   sscanf(rx->subexps[3].value,"%d",&(tmp->GetStoreDetail_Success));
   
	((void (*)(type_55*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_RemovePlayerInstance(df_connection *conn, int RoomID, int Key, void (*callback)(type_55*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RemovePlayerInstance", 1, RemovePlayerInstance_handler, c, "[RemovePlayerInstance %d %d]", RoomID, Key);
}


static void DisconnectDevice_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_DisconnectDevice(df_connection *conn, int Key, int ClearPlaying, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "DisconnectDevice", 1, DisconnectDevice_handler, c, "[DisconnectDevice %d %d]", Key, ClearPlaying);
}


static void DeviceChecksum_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	char* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   tmp= formatting_process(rx->subexps[2].value);
   
	((void (*)(char*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_DeviceChecksum(df_connection *conn, void (*callback)(char*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "DeviceChecksum", 1, DeviceChecksum_handler, c, "[DeviceChecksum]");
}


static void DeleteDevice_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_DeleteDevice(df_connection *conn, int Key, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "DeleteDevice", 1, DeleteDevice_handler, c, "[DeleteDevice %d]", Key);
}


static void ToggleDeviceSync_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_ToggleDeviceSync(df_connection *conn, int Key, int Sync, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ToggleDeviceSync", 1, ToggleDeviceSync_handler, c, "[ToggleDeviceSync %d %d]", Key, Sync);
}


static void IgnoreExternalStorage_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_IgnoreExternalStorage(df_connection *conn, int StorageKey, int IgnoreLevel, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "IgnoreExternalStorage", 1, IgnoreExternalStorage_handler, c, "[IgnoreExternalStorage %d %d]", StorageKey, IgnoreLevel);
}


static void ExternalStorageCancelScan_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_75* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_75));
   memset(tmp, 0, sizeof(type_75));

   tmp->DriveKey= formatting_process(rx->subexps[2].value);
   sscanf(rx->subexps[3].value,"%d",&(tmp->DeleteDrive_Return));
   
	((void (*)(type_75*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_ExternalStorageCancelScan(df_connection *conn, char* StorageKey, void (*callback)(type_75*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ExternalStorageCancelScan", 1, ExternalStorageCancelScan_handler, c, "[ExternalStorageCancelScan \"%s\"]", StorageKey);
}


static void ActivateExternalStorage_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_55* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_55));
   memset(tmp, 0, sizeof(type_55));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   sscanf(rx->subexps[3].value,"%d",&(tmp->GetStoreDetail_Success));
   
	((void (*)(type_55*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_ActivateExternalStorage(df_connection *conn, int StorageKey, int ActiveFlag, int ClearPlaying, void (*callback)(type_55*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ActivateExternalStorage", 1, ActivateExternalStorage_handler, c, "[ActivateExternalStorage %d %d %d]", StorageKey, ActiveFlag, ClearPlaying);
}


static void AddExternalStorage_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_79* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_79));
   memset(tmp, 0, sizeof(type_79));

   sscanf(rx->subexps[2].value,"%d",&(tmp->AddExternalStorage_Success));
   tmp->AddExternalStorage_Message= formatting_process(rx->subexps[3].value);
   sscanf(rx->subexps[4].value,"%d",&(tmp->AddExternalStorage_Key));
   tmp->AddExternalStorage_Hostname= formatting_process(rx->subexps[5].value);
   tmp->AddExternalStorage_IPAddress= formatting_process(rx->subexps[6].value);
   tmp->AddExternalStorage_ShareName= formatting_process(rx->subexps[7].value);
   tmp->AddExternalStorage_Username= formatting_process(rx->subexps[8].value);
   tmp->AddExternalStorage_Password= formatting_process(rx->subexps[9].value);
   
	((void (*)(type_79*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_AddExternalStorage(df_connection *conn, char* SharePath, char* Username, char* Password, int Activate, int ForceAdd, void (*callback)(type_79*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "AddExternalStorage", 1, AddExternalStorage_handler, c, "[AddExternalStorage \"%s\" \"%s\" \"%s\" %d %d]", SharePath, Username, Password, Activate, ForceAdd);
}


static void ScanForExternalStorages_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_ScanForExternalStorages(df_connection *conn, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ScanForExternalStorages", 1, ScanForExternalStorages_handler, c, "[ScanForExternalStorages]");
}


static void RescanExternalStorages_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_RescanExternalStorages(df_connection *conn, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RescanExternalStorages", 1, RescanExternalStorages_handler, c, "[RescanExternalStorages]");
}


static void ScanExternalStorage_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_75* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_75));
   memset(tmp, 0, sizeof(type_75));

   tmp->DriveKey= formatting_process(rx->subexps[2].value);
   sscanf(rx->subexps[3].value,"%d",&(tmp->DeleteDrive_Return));
   
	((void (*)(type_75*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_ScanExternalStorage(df_connection *conn, char* StorageKey, void (*callback)(type_75*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ScanExternalStorage", 1, ScanExternalStorage_handler, c, "[ScanExternalStorage \"%s\"]", StorageKey);
}


static void RemoveExternalStorage_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_55* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_55));
   memset(tmp, 0, sizeof(type_55));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   sscanf(rx->subexps[3].value,"%d",&(tmp->GetStoreDetail_Success));
   
	((void (*)(type_55*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_RemoveExternalStorage(df_connection *conn, int StorageKey, void (*callback)(type_55*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RemoveExternalStorage", 1, RemoveExternalStorage_handler, c, "[RemoveExternalStorage %d]", StorageKey);
}


static void GetExternalStorageDetail_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_80* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_80));
   memset(tmp, 0, sizeof(type_80));

   tmp->StorageAddress= formatting_process(rx->subexps[2].value);
   sscanf(rx->subexps[3].value,"%d",&(tmp->StorageKey));
   tmp->IPAddress= formatting_process(rx->subexps[4].value);
   tmp->HostName= formatting_process(rx->subexps[5].value);
   tmp->ShareName= formatting_process(rx->subexps[6].value);
   tmp->FullSharePath= formatting_process(rx->subexps[7].value);
   tmp->State= formatting_process(rx->subexps[8].value);
   tmp->LastState= formatting_process(rx->subexps[9].value);
   sscanf(rx->subexps[10].value,"%d",&(tmp->Active));
   sscanf(rx->subexps[11].value,"%u-%u-%u", &(tmp->Created.year), &(tmp->Created.month), &(tmp->Created.day));
   sscanf(rx->subexps[12].value,"%u-%u-%u", &(tmp->Modified.year), &(tmp->Modified.month), &(tmp->Modified.day));
   sscanf(rx->subexps[13].value,"%u-%u-%u", &(tmp->LastScanDate.year), &(tmp->LastScanDate.month), &(tmp->LastScanDate.day));
   sscanf(rx->subexps[14].value,"%u-%u-%u", &(tmp->LastScanTime.hours), &(tmp->LastScanTime.minutes), &(tmp->LastScanTime.seconds));
   tmp->UserName= formatting_process(rx->subexps[15].value);
   tmp->Password= formatting_process(rx->subexps[16].value);
   tmp->ScanIgnore= formatting_process(rx->subexps[17].value);
   
	((void (*)(type_80*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_GetExternalStorageDetail(df_connection *conn, char* StorageAddress, void (*callback)(type_80*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExternalStorageDetail", 1, GetExternalStorageDetail_handler, c, "[GetExternalStorageDetail \"%s\"]", StorageAddress);
}


static void UpdateExternalStorage_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_75* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_75));
   memset(tmp, 0, sizeof(type_75));

   tmp->DriveKey= formatting_process(rx->subexps[2].value);
   sscanf(rx->subexps[3].value,"%d",&(tmp->DeleteDrive_Return));
   
	((void (*)(type_75*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_UpdateExternalStorage(df_connection *conn, char* StorageKey, char* IPAddress, char* HostName, char* ShareName, char* UserName, char* Password, void (*callback)(type_75*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "UpdateExternalStorage", 1, UpdateExternalStorage_handler, c, "[UpdateExternalStorage \"%s\" \"%s\" \"%s\" \"%s\" \"%s\" \"%s\"]", StorageKey, IPAddress, HostName, ShareName, UserName, Password);
}


static void NewOutputChannel_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_NewOutputChannel(df_connection *conn, int RoomID, char* HostName, int ChannelNumber, char* InitString, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "NewOutputChannel", 1, NewOutputChannel_handler, c, "[NewOutputChannel %d \"%s\" %d \"%s\"]", RoomID, HostName, ChannelNumber, InitString);
}


static void UpdateOutputChannel_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_UpdateOutputChannel(df_connection *conn, int RoomID, char* HostName, int ChannelNumber, char* InitString, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "UpdateOutputChannel", 1, UpdateOutputChannel_handler, c, "[UpdateOutputChannel %d \"%s\" %d \"%s\"]", RoomID, HostName, ChannelNumber, InitString);
}


static void DeleteOutputChannel_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_DeleteOutputChannel(df_connection *conn, int RoomID, char* HostName, int ChannelNumber, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "DeleteOutputChannel", 1, DeleteOutputChannel_handler, c, "[DeleteOutputChannel %d \"%s\" %d]", RoomID, HostName, ChannelNumber);
}


static void SetDriveUsage_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_81* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_81));
   memset(tmp, 0, sizeof(type_81));

   tmp->DriveKey= formatting_process(rx->subexps[2].value);
   sscanf(rx->subexps[3].value,"%d",&(tmp->SetDriveUsage_Success));
   sscanf(rx->subexps[4].value,"%d",&(tmp->SetDriveUsage_DriveInUse));
   tmp->SetDriveUsage_Message= formatting_process(rx->subexps[5].value);
   
	((void (*)(type_81*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_SetDriveUsage(df_connection *conn, char* DriveKey, int Usage, int ForceChange, void (*callback)(type_81*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "SetDriveUsage", 1, SetDriveUsage_handler, c, "[SetDriveUsage \"%s\" %d %d]", DriveKey, Usage, ForceChange);
}


static void BackupDrive_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_82* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_82));
   memset(tmp, 0, sizeof(type_82));

   tmp->SourceDriveKey= formatting_process(rx->subexps[2].value);
   tmp->DestDriveKey= formatting_process(rx->subexps[3].value);
   sscanf(rx->subexps[4].value,"%d",&(tmp->BackupDrive_Success));
   tmp->BackupDrive_Message= formatting_process(rx->subexps[5].value);
   
	((void (*)(type_82*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_BackupDrive(df_connection *conn, char* SourceDriveKey, char* DestDriveKey, int BackupType, int NoFileCheck, void (*callback)(type_82*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "BackupDrive", 1, BackupDrive_handler, c, "[BackupDrive \"%s\" \"%s\" %d %d]", SourceDriveKey, DestDriveKey, BackupType, NoFileCheck);
}


static void StopBackupDrive_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_83* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_83));
   memset(tmp, 0, sizeof(type_83));

   sscanf(rx->subexps[2].value,"%d",&(tmp->StopBackupDrive_Success));
   tmp->StopBackupDrive_Message= formatting_process(rx->subexps[3].value);
   
	((void (*)(type_83*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_StopBackupDrive(df_connection *conn, void (*callback)(type_83*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "StopBackupDrive", 1, StopBackupDrive_handler, c, "[StopBackupDrive]");
}


static void GetBackupStatus_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_84* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_84));
   memset(tmp, 0, sizeof(type_84));

   tmp->Backup_SourceDrive= formatting_process(rx->subexps[2].value);
   tmp->Backup_DestDrive= formatting_process(rx->subexps[3].value);
   tmp->Backup_Type= formatting_process(rx->subexps[4].value);
   tmp->Backup_Status= formatting_process(rx->subexps[5].value);
   tmp->Backup_CurrentFile= formatting_process(rx->subexps[6].value);
   tmp->Backup_LastError= formatting_process(rx->subexps[7].value);
   sscanf(rx->subexps[8].value,"%u-%u-%u", &(tmp->Backup_TimeTaken.hours), &(tmp->Backup_TimeTaken.minutes), &(tmp->Backup_TimeTaken.seconds));
   sscanf(rx->subexps[9].value,"%u-%u-%u", &(tmp->Backup_TimeRemaining.hours), &(tmp->Backup_TimeRemaining.minutes), &(tmp->Backup_TimeRemaining.seconds));
   sscanf(rx->subexps[10].value,"%d",&(tmp->Backup_SourceFileCount));
   sscanf(rx->subexps[11].value,"%d",&(tmp->Backup_SourceFolderCount));
   sscanf(rx->subexps[12].value,"%d",&(tmp->Backup_SourceByteCount));
   sscanf(rx->subexps[13].value,"%d",&(tmp->Backup_ProcessedFileCount));
   sscanf(rx->subexps[14].value,"%d",&(tmp->Backup_ProcessedFolderCount));
   sscanf(rx->subexps[15].value,"%d",&(tmp->Backup_ProcessedByteCount));
   sscanf(rx->subexps[16].value,"%d",&(tmp->Backup_ErrorCount));
   sscanf(rx->subexps[17].value,"%d",&(tmp->Backup_ErrorFileCount));
   sscanf(rx->subexps[18].value,"%d",&(tmp->Backup_ErrorByteCount));
   
	((void (*)(type_84*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_GetBackupStatus(df_connection *conn, void (*callback)(type_84*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetBackupStatus", 1, GetBackupStatus_handler, c, "[GetBackupStatus]");
}


static void AddNewBackupJob_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_85* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_85));
   memset(tmp, 0, sizeof(type_85));

   tmp->SourceDriveAddress= formatting_process(rx->subexps[2].value);
   tmp->DestinationDriveAddress= formatting_process(rx->subexps[3].value);
   sscanf(rx->subexps[4].value,"%d",&(tmp->AddNewBackupJob_Return));
   
	((void (*)(type_85*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_AddNewBackupJob(df_connection *conn, char* SourceDriveAddress, char* DestinationDriveAddress, char* Name, int BackupType, int BackupPeriod, int PeriodValue, df_date RunDate, df_time RunTime, void (*callback)(type_85*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "AddNewBackupJob", 1, AddNewBackupJob_handler, c, "[AddNewBackupJob \"%s\" \"%s\" \"%s\" %d %d %d \"%u-%u-%u\" \"%u:%u:%u\"]", SourceDriveAddress, DestinationDriveAddress, Name, BackupType, BackupPeriod, PeriodValue, RunDate.year, RunDate.month, RunDate.day, RunTime.hours, RunTime.minutes, RunTime.seconds);
}


static void UpdateBackupJob_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_75* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_75));
   memset(tmp, 0, sizeof(type_75));

   tmp->DriveKey= formatting_process(rx->subexps[2].value);
   sscanf(rx->subexps[3].value,"%d",&(tmp->DeleteDrive_Return));
   
	((void (*)(type_75*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_UpdateBackupJob(df_connection *conn, char* Address, char* SourceDriveAddress, char* DestinationDriveAddress, char* Name, int BackupType, int BackupPeriod, int PeriodValue, df_date RunDate, df_time RunTime, void (*callback)(type_75*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "UpdateBackupJob", 1, UpdateBackupJob_handler, c, "[UpdateBackupJob \"%s\" \"%s\" \"%s\" \"%s\" %d %d %d \"%u-%u-%u\" \"%u:%u:%u\"]", Address, SourceDriveAddress, DestinationDriveAddress, Name, BackupType, BackupPeriod, PeriodValue, RunDate.year, RunDate.month, RunDate.day, RunTime.hours, RunTime.minutes, RunTime.seconds);
}


static void DeleteBackupJob_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_75* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_75));
   memset(tmp, 0, sizeof(type_75));

   tmp->DriveKey= formatting_process(rx->subexps[2].value);
   sscanf(rx->subexps[3].value,"%d",&(tmp->DeleteDrive_Return));
   
	((void (*)(type_75*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_DeleteBackupJob(df_connection *conn, char* Address, void (*callback)(type_75*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "DeleteBackupJob", 1, DeleteBackupJob_handler, c, "[DeleteBackupJob \"%s\"]", Address);
}


static void ChangeNetworkDhcp_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_7* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_7));
   memset(tmp, 0, sizeof(type_7));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   sscanf(rx->subexps[3].value,"%d",&(tmp->GetRooms_Return));
   
	((void (*)(type_7*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_ChangeNetworkDhcp(df_connection *conn, int DeviceID, int RestartDevice, void (*callback)(type_7*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ChangeNetworkDhcp", 1, ChangeNetworkDhcp_handler, c, "[ChangeNetworkDhcp %d %d]", DeviceID, RestartDevice);
}


static void ChangeNetworkStatic_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_7* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_7));
   memset(tmp, 0, sizeof(type_7));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   sscanf(rx->subexps[3].value,"%d",&(tmp->GetRooms_Return));
   
	((void (*)(type_7*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_ChangeNetworkStatic(df_connection *conn, int DeviceID, char* IpAddress, char* SubnetMask, char* DefaultGateway, char* DnsServer, int RestartDevice, void (*callback)(type_7*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ChangeNetworkStatic", 1, ChangeNetworkStatic_handler, c, "[ChangeNetworkStatic %d \"%s\" \"%s\" \"%s\" \"%s\" %d]", DeviceID, IpAddress, SubnetMask, DefaultGateway, DnsServer, RestartDevice);
}


static void ChangeNetworkAutoIP_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_7* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_7));
   memset(tmp, 0, sizeof(type_7));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   sscanf(rx->subexps[3].value,"%d",&(tmp->GetRooms_Return));
   
	((void (*)(type_7*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_ChangeNetworkAutoIP(df_connection *conn, int DeviceID, char* AutoIpRange, char* DefaultGateway, char* DnsServer, int RestartDevice, void (*callback)(type_7*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ChangeNetworkAutoIP", 1, ChangeNetworkAutoIP_handler, c, "[ChangeNetworkAutoIP %d \"%s\" \"%s\" \"%s\" %d]", DeviceID, AutoIpRange, DefaultGateway, DnsServer, RestartDevice);
}


static void ChangeNetworkWorkgroup_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_76* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_76));
   memset(tmp, 0, sizeof(type_76));

   tmp->RoomName= formatting_process(rx->subexps[2].value);
   sscanf(rx->subexps[3].value,"%d",&(tmp->AddNewLinkedRoom_Return));
   
	((void (*)(type_76*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_ChangeNetworkWorkgroup(df_connection *conn, char* Workgroup, void (*callback)(type_76*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ChangeNetworkWorkgroup", 1, ChangeNetworkWorkgroup_handler, c, "[ChangeNetworkWorkgroup \"%s\"]", Workgroup);
}


static void ChangeNetworkMachineName_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_76* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_76));
   memset(tmp, 0, sizeof(type_76));

   tmp->RoomName= formatting_process(rx->subexps[2].value);
   sscanf(rx->subexps[3].value,"%d",&(tmp->AddNewLinkedRoom_Return));
   
	((void (*)(type_76*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_ChangeNetworkMachineName(df_connection *conn, char* MachineName, void (*callback)(type_76*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ChangeNetworkMachineName", 1, ChangeNetworkMachineName_handler, c, "[ChangeNetworkMachineName \"%s\"]", MachineName);
}


static void ChangeSystemSerialNumber_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_75* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_75));
   memset(tmp, 0, sizeof(type_75));

   tmp->DriveKey= formatting_process(rx->subexps[2].value);
   sscanf(rx->subexps[3].value,"%d",&(tmp->DeleteDrive_Return));
   
	((void (*)(type_75*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_ChangeSystemSerialNumber(df_connection *conn, char* SerialNumber, void (*callback)(type_75*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ChangeSystemSerialNumber", 1, ChangeSystemSerialNumber_handler, c, "[ChangeSystemSerialNumber \"%s\"]", SerialNumber);
}


static void ProcessEmbeddedInit_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	char* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   tmp= formatting_process(rx->subexps[2].value);
   
	((void (*)(char*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_ProcessEmbeddedInit(df_connection *conn, void (*callback)(char*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ProcessEmbeddedInit", 1, ProcessEmbeddedInit_handler, c, "[ProcessEmbeddedInit]");
}


static void GetNetworkWorkgroup_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	char* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   tmp= formatting_process(rx->subexps[2].value);
   
	((void (*)(char*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_GetNetworkWorkgroup(df_connection *conn, void (*callback)(char*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetNetworkWorkgroup", 1, GetNetworkWorkgroup_handler, c, "[GetNetworkWorkgroup]");
}


static void ComplexSearchCountAlbums_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_ComplexSearchCountAlbums(df_connection *conn, char* SearchParameter, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ComplexSearchCountAlbums", 1, ComplexSearchCountAlbums_handler, c, "[ComplexSearchCountAlbums \"%s\"]", SearchParameter);
}


static void ComplexSearchCountTracks_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_ComplexSearchCountTracks(df_connection *conn, char* SearchParameter, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ComplexSearchCountTracks", 1, ComplexSearchCountTracks_handler, c, "[ComplexSearchCountTracks \"%s\"]", SearchParameter);
}


static void ComplexSearchCountArtists_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_ComplexSearchCountArtists(df_connection *conn, char* SearchParameter, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ComplexSearchCountArtists", 1, ComplexSearchCountArtists_handler, c, "[ComplexSearchCountArtists \"%s\"]", SearchParameter);
}


static void ComplexSearchCountContributors_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_ComplexSearchCountContributors(df_connection *conn, int Type, char* SearchParameter, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ComplexSearchCountContributors", 1, ComplexSearchCountContributors_handler, c, "[ComplexSearchCountContributors %d \"%s\"]", Type, SearchParameter);
}


static void SaveCurrentPlayList_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_7* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_7));
   memset(tmp, 0, sizeof(type_7));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   sscanf(rx->subexps[3].value,"%d",&(tmp->GetRooms_Return));
   
	((void (*)(type_7*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_SaveCurrentPlayList(df_connection *conn, int RoomID, char* NewName, void (*callback)(type_7*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "SaveCurrentPlayList", 1, SaveCurrentPlayList_handler, c, "[SaveCurrentPlayList %d \"%s\"]", RoomID, NewName);
}


static void CreateRandomPlaylistEx_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_7* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_7));
   memset(tmp, 0, sizeof(type_7));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   sscanf(rx->subexps[3].value,"%d",&(tmp->GetRooms_Return));
   
	((void (*)(type_7*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_CreateRandomPlaylistEx(df_connection *conn, int RoomID, int Replace, int PlayScope, char* ScopeKey, char* SubGenre, char* Artists, char* Albums, char* Tracks, void (*callback)(type_7*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CreateRandomPlaylistEx", 1, CreateRandomPlaylistEx_handler, c, "[CreateRandomPlaylistEx %d %d %d \"%s\" \"%s\" \"%s\" \"%s\" \"%s\"]", RoomID, Replace, PlayScope, ScopeKey, SubGenre, Artists, Albums, Tracks);
}


static void CreateRandomPlaylist_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_7* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_7));
   memset(tmp, 0, sizeof(type_7));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   sscanf(rx->subexps[3].value,"%d",&(tmp->GetRooms_Return));
   
	((void (*)(type_7*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_CreateRandomPlaylist(df_connection *conn, int RoomID, char* Genre, char* SubGenre, char* Artists, char* Albums, int MaxTracks, char* Tracks, void (*callback)(type_7*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CreateRandomPlaylist", 1, CreateRandomPlaylist_handler, c, "[CreateRandomPlaylist %d \"%s\" \"%s\" \"%s\" \"%s\" %d \"%s\"]", RoomID, Genre, SubGenre, Artists, Albums, MaxTracks, Tracks);
}


static void CreatePlaylist_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_76* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_76));
   memset(tmp, 0, sizeof(type_76));

   tmp->RoomName= formatting_process(rx->subexps[2].value);
   sscanf(rx->subexps[3].value,"%d",&(tmp->AddNewLinkedRoom_Return));
   
	((void (*)(type_76*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_CreatePlaylist(df_connection *conn, char* Name, char* TrackKey, void (*callback)(type_76*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CreatePlaylist", 1, CreatePlaylist_handler, c, "[CreatePlaylist \"%s\" \"%s\"]", Name, TrackKey);
}


static void RenamePlaylist_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_75* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_75));
   memset(tmp, 0, sizeof(type_75));

   tmp->DriveKey= formatting_process(rx->subexps[2].value);
   sscanf(rx->subexps[3].value,"%d",&(tmp->DeleteDrive_Return));
   
	((void (*)(type_75*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_RenamePlaylist(df_connection *conn, char* PlaylistKey, char* NewName, void (*callback)(type_75*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RenamePlaylist", 1, RenamePlaylist_handler, c, "[RenamePlaylist \"%s\" \"%s\"]", PlaylistKey, NewName);
}


static void AddTracksToUserPlaylist_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_75* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_75));
   memset(tmp, 0, sizeof(type_75));

   tmp->DriveKey= formatting_process(rx->subexps[2].value);
   sscanf(rx->subexps[3].value,"%d",&(tmp->DeleteDrive_Return));
   
	((void (*)(type_75*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_AddTracksToUserPlaylist(df_connection *conn, char* UserPlaylistKey, char* TrackKey, void (*callback)(type_75*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "AddTracksToUserPlaylist", 1, AddTracksToUserPlaylist_handler, c, "[AddTracksToUserPlaylist \"%s\" \"%s\"]", UserPlaylistKey, TrackKey);
}


static void AddAlbumsToUserPlaylist_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_75* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_75));
   memset(tmp, 0, sizeof(type_75));

   tmp->DriveKey= formatting_process(rx->subexps[2].value);
   sscanf(rx->subexps[3].value,"%d",&(tmp->DeleteDrive_Return));
   
	((void (*)(type_75*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_AddAlbumsToUserPlaylist(df_connection *conn, char* UserPlaylistKey, char* AlbumKey, void (*callback)(type_75*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "AddAlbumsToUserPlaylist", 1, AddAlbumsToUserPlaylist_handler, c, "[AddAlbumsToUserPlaylist \"%s\" \"%s\"]", UserPlaylistKey, AlbumKey);
}


static void RemoveAlbumsFromUserPlaylist_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_75* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_75));
   memset(tmp, 0, sizeof(type_75));

   tmp->DriveKey= formatting_process(rx->subexps[2].value);
   sscanf(rx->subexps[3].value,"%d",&(tmp->DeleteDrive_Return));
   
	((void (*)(type_75*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_RemoveAlbumsFromUserPlaylist(df_connection *conn, char* UserPlaylistKey, char* AlbumKey, void (*callback)(type_75*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RemoveAlbumsFromUserPlaylist", 1, RemoveAlbumsFromUserPlaylist_handler, c, "[RemoveAlbumsFromUserPlaylist \"%s\" \"%s\"]", UserPlaylistKey, AlbumKey);
}


static void DeleteTrack_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_75* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_75));
   memset(tmp, 0, sizeof(type_75));

   tmp->DriveKey= formatting_process(rx->subexps[2].value);
   sscanf(rx->subexps[3].value,"%d",&(tmp->DeleteDrive_Return));
   
	((void (*)(type_75*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_DeleteTrack(df_connection *conn, char* TrackKey, char* PlaylistKey, int Ordinal, void (*callback)(type_75*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "DeleteTrack", 1, DeleteTrack_handler, c, "[DeleteTrack \"%s\" \"%s\" %d]", TrackKey, PlaylistKey, Ordinal);
}


static void ChangeTrackOrdinal_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_75* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_75));
   memset(tmp, 0, sizeof(type_75));

   tmp->DriveKey= formatting_process(rx->subexps[2].value);
   sscanf(rx->subexps[3].value,"%d",&(tmp->DeleteDrive_Return));
   
	((void (*)(type_75*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_ChangeTrackOrdinal(df_connection *conn, char* TrackKey, char* PlaylistKey, int Ordinal, int NewPosition, int ReorderPlaylist, void (*callback)(type_75*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ChangeTrackOrdinal", 1, ChangeTrackOrdinal_handler, c, "[ChangeTrackOrdinal \"%s\" \"%s\" %d %d %d]", TrackKey, PlaylistKey, Ordinal, NewPosition, ReorderPlaylist);
}


static void UpdatePlaylist_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_75* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_75));
   memset(tmp, 0, sizeof(type_75));

   tmp->DriveKey= formatting_process(rx->subexps[2].value);
   sscanf(rx->subexps[3].value,"%d",&(tmp->DeleteDrive_Return));
   
	((void (*)(type_75*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_UpdatePlaylist(df_connection *conn, char* PlaylistKey, char* Name, char* TrackKey, void (*callback)(type_75*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "UpdatePlaylist", 1, UpdatePlaylist_handler, c, "[UpdatePlaylist \"%s\" \"%s\" \"%s\"]", PlaylistKey, Name, TrackKey);
}


static void DeleteAlbum_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_75* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_75));
   memset(tmp, 0, sizeof(type_75));

   tmp->DriveKey= formatting_process(rx->subexps[2].value);
   sscanf(rx->subexps[3].value,"%d",&(tmp->DeleteDrive_Return));
   
	((void (*)(type_75*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_DeleteAlbum(df_connection *conn, char* AlbumKey, void (*callback)(type_75*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "DeleteAlbum", 1, DeleteAlbum_handler, c, "[DeleteAlbum \"%s\"]", AlbumKey);
}


static void RenameAlbum_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_62* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_62));
   memset(tmp, 0, sizeof(type_62));

   tmp->GetHostDetails_Name= formatting_process(rx->subexps[2].value);
   tmp->GetHostDetails_Address= formatting_process(rx->subexps[3].value);
   
	((void (*)(type_62*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_RenameAlbum(df_connection *conn, char* AlbumKey, char* NewAlbumName, void (*callback)(type_62*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RenameAlbum", 1, RenameAlbum_handler, c, "[RenameAlbum \"%s\" \"%s\"]", AlbumKey, NewAlbumName);
}


static void SetAlbumLowQuality_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_75* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_75));
   memset(tmp, 0, sizeof(type_75));

   tmp->DriveKey= formatting_process(rx->subexps[2].value);
   sscanf(rx->subexps[3].value,"%d",&(tmp->DeleteDrive_Return));
   
	((void (*)(type_75*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_SetAlbumLowQuality(df_connection *conn, char* AlbumKey, int LowQuality, void (*callback)(type_75*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "SetAlbumLowQuality", 1, SetAlbumLowQuality_handler, c, "[SetAlbumLowQuality \"%s\" %d]", AlbumKey, LowQuality);
}


static void RenameTrack_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_62* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_62));
   memset(tmp, 0, sizeof(type_62));

   tmp->GetHostDetails_Name= formatting_process(rx->subexps[2].value);
   tmp->GetHostDetails_Address= formatting_process(rx->subexps[3].value);
   
	((void (*)(type_62*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_RenameTrack(df_connection *conn, char* TrackKey, char* NewTrackName, void (*callback)(type_62*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RenameTrack", 1, RenameTrack_handler, c, "[RenameTrack \"%s\" \"%s\"]", TrackKey, NewTrackName);
}


static void RenameArtist_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_62* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_62));
   memset(tmp, 0, sizeof(type_62));

   tmp->GetHostDetails_Name= formatting_process(rx->subexps[2].value);
   tmp->GetHostDetails_Address= formatting_process(rx->subexps[3].value);
   
	((void (*)(type_62*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_RenameArtist(df_connection *conn, char* AlbumKey, char* NewArtistName, void (*callback)(type_62*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RenameArtist", 1, RenameArtist_handler, c, "[RenameArtist \"%s\" \"%s\"]", AlbumKey, NewArtistName);
}


static void ChangeAlbumSubGenre_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_62* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_62));
   memset(tmp, 0, sizeof(type_62));

   tmp->GetHostDetails_Name= formatting_process(rx->subexps[2].value);
   tmp->GetHostDetails_Address= formatting_process(rx->subexps[3].value);
   
	((void (*)(type_62*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_ChangeAlbumSubGenre(df_connection *conn, char* AlbumKey, char* SubGenreKey, void (*callback)(type_62*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ChangeAlbumSubGenre", 1, ChangeAlbumSubGenre_handler, c, "[ChangeAlbumSubGenre \"%s\" \"%s\"]", AlbumKey, SubGenreKey);
}


static void UpdateHitCount_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_UpdateHitCount(df_connection *conn, char* Address, int ResetHitCount, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "UpdateHitCount", 1, UpdateHitCount_handler, c, "[UpdateHitCount \"%s\" %d]", Address, ResetHitCount);
}


static void CountAlbums_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_CountAlbums(df_connection *conn, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountAlbums", 1, CountAlbums_handler, c, "[CountAlbums]");
}


static void CountAlbumsForArtist_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_CountAlbumsForArtist(df_connection *conn, char* Address, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountAlbumsForArtist", 1, CountAlbumsForArtist_handler, c, "[CountAlbumsForArtist \"%s\"]", Address);
}


static void CountArtists_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_CountArtists(df_connection *conn, int Allocated, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountArtists", 1, CountArtists_handler, c, "[CountArtists %d]", Allocated);
}


static void CountGenres_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_CountGenres(df_connection *conn, int Allocated, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountGenres", 1, CountGenres_handler, c, "[CountGenres %d]", Allocated);
}


static void CountPlaylistsForSubGenre_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_CountPlaylistsForSubGenre(df_connection *conn, char* Address, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountPlaylistsForSubGenre", 1, CountPlaylistsForSubGenre_handler, c, "[CountPlaylistsForSubGenre \"%s\"]", Address);
}


static void CountSubGenresForGenre_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_CountSubGenresForGenre(df_connection *conn, char* Address, int Allocated, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountSubGenresForGenre", 1, CountSubGenresForGenre_handler, c, "[CountSubGenresForGenre \"%s\" %d]", Address, Allocated);
}


static void CountTracksAll_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_CountTracksAll(df_connection *conn, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountTracksAll", 1, CountTracksAll_handler, c, "[CountTracksAll]");
}


static void CountTracksForPlaylist_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_CountTracksForPlaylist(df_connection *conn, char* Address, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountTracksForPlaylist", 1, CountTracksForPlaylist_handler, c, "[CountTracksForPlaylist \"%s\"]", Address);
}


static void CountUserPlaylists_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_CountUserPlaylists(df_connection *conn, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountUserPlaylists", 1, CountUserPlaylists_handler, c, "[CountUserPlaylists]");
}


static void CountDevices_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_CountDevices(df_connection *conn, int ActiveOnly, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountDevices", 1, CountDevices_handler, c, "[CountDevices %d]", ActiveOnly);
}


static void CountAlbumsForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_CountAlbumsForDevice(df_connection *conn, char* Address, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountAlbumsForDevice", 1, CountAlbumsForDevice_handler, c, "[CountAlbumsForDevice \"%s\"]", Address);
}


static void CountArtistsForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_CountArtistsForDevice(df_connection *conn, char* Address, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountArtistsForDevice", 1, CountArtistsForDevice_handler, c, "[CountArtistsForDevice \"%s\"]", Address);
}


static void CountSubGenresForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_CountSubGenresForDevice(df_connection *conn, char* Address, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountSubGenresForDevice", 1, CountSubGenresForDevice_handler, c, "[CountSubGenresForDevice \"%s\"]", Address);
}


static void CountTracksForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_CountTracksForDevice(df_connection *conn, char* Address, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountTracksForDevice", 1, CountTracksForDevice_handler, c, "[CountTracksForDevice \"%s\"]", Address);
}


static void CountUserPlaylistsForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_CountUserPlaylistsForDevice(df_connection *conn, char* Address, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountUserPlaylistsForDevice", 1, CountUserPlaylistsForDevice_handler, c, "[CountUserPlaylistsForDevice \"%s\"]", Address);
}


static void CountShares_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_CountShares(df_connection *conn, int AvailableOnly, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountShares", 1, CountShares_handler, c, "[CountShares %d]", AvailableOnly);
}


static void CountAlbumsForShare_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_CountAlbumsForShare(df_connection *conn, char* Address, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountAlbumsForShare", 1, CountAlbumsForShare_handler, c, "[CountAlbumsForShare \"%s\"]", Address);
}


static void CountArtistsForShare_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_CountArtistsForShare(df_connection *conn, char* Address, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountArtistsForShare", 1, CountArtistsForShare_handler, c, "[CountArtistsForShare \"%s\"]", Address);
}


static void CountSubGenresForShare_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_CountSubGenresForShare(df_connection *conn, char* Address, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountSubGenresForShare", 1, CountSubGenresForShare_handler, c, "[CountSubGenresForShare \"%s\"]", Address);
}


static void CountTracksForShare_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_CountTracksForShare(df_connection *conn, char* Address, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountTracksForShare", 1, CountTracksForShare_handler, c, "[CountTracksForShare \"%s\"]", Address);
}


static void CountUserPlaylistsForShare_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_CountUserPlaylistsForShare(df_connection *conn, char* Address, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountUserPlaylistsForShare", 1, CountUserPlaylistsForShare_handler, c, "[CountUserPlaylistsForShare \"%s\"]", Address);
}


static void CountAlbumsForServer_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_CountAlbumsForServer(df_connection *conn, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountAlbumsForServer", 1, CountAlbumsForServer_handler, c, "[CountAlbumsForServer]");
}


static void CountArtistsForServer_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_CountArtistsForServer(df_connection *conn, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountArtistsForServer", 1, CountArtistsForServer_handler, c, "[CountArtistsForServer]");
}


static void CountSubGenresForServer_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_CountSubGenresForServer(df_connection *conn, int Allocated, int UserDefined, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountSubGenresForServer", 1, CountSubGenresForServer_handler, c, "[CountSubGenresForServer %d %d]", Allocated, UserDefined);
}


static void CountTracksForServer_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_CountTracksForServer(df_connection *conn, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountTracksForServer", 1, CountTracksForServer_handler, c, "[CountTracksForServer]");
}


static void CountUserPlaylistsForServer_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_CountUserPlaylistsForServer(df_connection *conn, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountUserPlaylistsForServer", 1, CountUserPlaylistsForServer_handler, c, "[CountUserPlaylistsForServer]");
}


static void CountAlbumsForArtistForServer_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_CountAlbumsForArtistForServer(df_connection *conn, char* Address, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountAlbumsForArtistForServer", 1, CountAlbumsForArtistForServer_handler, c, "[CountAlbumsForArtistForServer \"%s\"]", Address);
}


static void CountAlbumsForArtistForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_CountAlbumsForArtistForDevice(df_connection *conn, char* Address, char* DeviceAddress, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountAlbumsForArtistForDevice", 1, CountAlbumsForArtistForDevice_handler, c, "[CountAlbumsForArtistForDevice \"%s\" \"%s\"]", Address, DeviceAddress);
}


static void CountAlbumsForArtistForShare_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_CountAlbumsForArtistForShare(df_connection *conn, char* Address, char* ShareAddress, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountAlbumsForArtistForShare", 1, CountAlbumsForArtistForShare_handler, c, "[CountAlbumsForArtistForShare \"%s\" \"%s\"]", Address, ShareAddress);
}


static void CountPlaylistsForSubGenreForServer_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_CountPlaylistsForSubGenreForServer(df_connection *conn, char* Address, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountPlaylistsForSubGenreForServer", 1, CountPlaylistsForSubGenreForServer_handler, c, "[CountPlaylistsForSubGenreForServer \"%s\"]", Address);
}


static void CountPlaylistsForSubGenreForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_CountPlaylistsForSubGenreForDevice(df_connection *conn, char* Address, char* DeviceAddress, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountPlaylistsForSubGenreForDevice", 1, CountPlaylistsForSubGenreForDevice_handler, c, "[CountPlaylistsForSubGenreForDevice \"%s\" \"%s\"]", Address, DeviceAddress);
}


static void CountPlaylistsForSubGenreForShare_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_CountPlaylistsForSubGenreForShare(df_connection *conn, char* Address, char* ShareAddress, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CountPlaylistsForSubGenreForShare", 1, CountPlaylistsForSubGenreForShare_handler, c, "[CountPlaylistsForSubGenreForShare \"%s\" \"%s\"]", Address, ShareAddress);
}


static void RestoreSingleAlbum_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_75* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_75));
   memset(tmp, 0, sizeof(type_75));

   tmp->DriveKey= formatting_process(rx->subexps[2].value);
   sscanf(rx->subexps[3].value,"%d",&(tmp->DeleteDrive_Return));
   
	((void (*)(type_75*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_RestoreSingleAlbum(df_connection *conn, char* AlbumKey, void (*callback)(type_75*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RestoreSingleAlbum", 1, RestoreSingleAlbum_handler, c, "[RestoreSingleAlbum \"%s\"]", AlbumKey);
}


static void RestoreSingleTrack_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_86* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_86));
   memset(tmp, 0, sizeof(type_86));

   tmp->AlbumKey= formatting_process(rx->subexps[2].value);
   tmp->TrackKey= formatting_process(rx->subexps[3].value);
   sscanf(rx->subexps[4].value,"%d",&(tmp->RestoreSingleTrack_Return));
   
	((void (*)(type_86*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_RestoreSingleTrack(df_connection *conn, char* AlbumKey, char* TrackKey, void (*callback)(type_86*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RestoreSingleTrack", 1, RestoreSingleTrack_handler, c, "[RestoreSingleTrack \"%s\" \"%s\"]", AlbumKey, TrackKey);
}


static void SetCoverImage_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	char* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   tmp= formatting_process(rx->subexps[2].value);
   
	((void (*)(char*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_SetCoverImage(df_connection *conn, char* Address, int ForceOverwrite, char* ImageData, void (*callback)(char*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "SetCoverImage", 1, SetCoverImage_handler, c, "[SetCoverImage \"%s\" %d \"%s\"]", Address, ForceOverwrite, ImageData);
}


static void RemoveCoverImage_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	char* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   tmp= formatting_process(rx->subexps[2].value);
   
	((void (*)(char*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_RemoveCoverImage(df_connection *conn, char* Address, void (*callback)(char*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RemoveCoverImage", 1, RemoveCoverImage_handler, c, "[RemoveCoverImage \"%s\"]", Address);
}


static void CheckCoverImage_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_87* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_87));
   memset(tmp, 0, sizeof(type_87));

   tmp->Address= formatting_process(rx->subexps[2].value);
   tmp->CoverImageName= formatting_process(rx->subexps[3].value);
   tmp->CoverImageURI= formatting_process(rx->subexps[4].value);
   
	((void (*)(type_87*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_CheckCoverImage(df_connection *conn, char* Address, int ImageSize, int AddressType, int Local, char* Protocol, char* ImageFormat, void (*callback)(type_87*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CheckCoverImage", 1, CheckCoverImage_handler, c, "[CheckCoverImage \"%s\" %d %d %d \"%s\" \"%s\"]", Address, ImageSize, AddressType, Local, Protocol, ImageFormat);
}


static void ForceGenrePlaylistBackup_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_ForceGenrePlaylistBackup(df_connection *conn, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ForceGenrePlaylistBackup", 1, ForceGenrePlaylistBackup_handler, c, "[ForceGenrePlaylistBackup]");
}


static void ForceGenrePlaylistRestore_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_ForceGenrePlaylistRestore(df_connection *conn, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ForceGenrePlaylistRestore", 1, ForceGenrePlaylistRestore_handler, c, "[ForceGenrePlaylistRestore]");
}


static void BulkCDLookupEx_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_BulkCDLookupEx(df_connection *conn, int LookupProviderUsed, int Interval, char* AlbumKey, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "BulkCDLookupEx", 1, BulkCDLookupEx_handler, c, "[BulkCDLookupEx %d %d \"%s\"]", LookupProviderUsed, Interval, AlbumKey);
}


static void CDLookupGetStatus_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_88* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_88));
   memset(tmp, 0, sizeof(type_88));

   sscanf(rx->subexps[2].value,"%d",&(tmp->Running));
   sscanf(rx->subexps[3].value,"%d",&(tmp->AlbumKey));
   tmp->AlbumName= formatting_process(rx->subexps[4].value);
   sscanf(rx->subexps[5].value,"%d",&(tmp->Progress));
   
	((void (*)(type_88*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_CDLookupGetStatus(df_connection *conn, void (*callback)(type_88*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "CDLookupGetStatus", 1, CDLookupGetStatus_handler, c, "[CDLookupGetStatus]");
}


static void UploadMessages_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_UploadMessages(df_connection *conn, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "UploadMessages", 1, UploadMessages_handler, c, "[UploadMessages]");
}


static void GetOperationActivity_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_3* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_3));
   memset(tmp, 0, sizeof(type_3));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   tmp->CommandName= formatting_process(rx->subexps[3].value);
   
	((void (*)(type_3*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_GetOperationActivity(df_connection *conn, int RoomID, int Service, void (*callback)(type_3*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetOperationActivity", 1, GetOperationActivity_handler, c, "[GetOperationActivity %d %d]", RoomID, Service);
}


static void RequestAlbumCover_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_75* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_75));
   memset(tmp, 0, sizeof(type_75));

   tmp->DriveKey= formatting_process(rx->subexps[2].value);
   sscanf(rx->subexps[3].value,"%d",&(tmp->DeleteDrive_Return));
   
	((void (*)(type_75*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_RequestAlbumCover(df_connection *conn, char* Address, void (*callback)(type_75*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RequestAlbumCover", 1, RequestAlbumCover_handler, c, "[RequestAlbumCover \"%s\"]", Address);
}


static void RGetTrackPosition_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_67* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_67));
   memset(tmp, 0, sizeof(type_67));

   sscanf(rx->subexps[2].value,"%d",&(tmp->RoomID));
   sscanf(rx->subexps[3].value,"%u-%u-%u", &(tmp->TrackLength.hours), &(tmp->TrackLength.minutes), &(tmp->TrackLength.seconds));
   
	((void (*)(type_67*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_RGetTrackPosition(df_connection *conn, int RoomID, void (*callback)(type_67*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RGetTrackPosition", 1, RGetTrackPosition_handler, c, "[RGetTrackPosition %d]", RoomID);
}


static void RGetTrackName_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_89* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_89));
   memset(tmp, 0, sizeof(type_89));

   sscanf(rx->subexps[2].value,"%d",&(tmp->RoomID));
   tmp->TrackName_Return= formatting_process(rx->subexps[3].value);
   sscanf(rx->subexps[4].value,"%d",&(tmp->TrackSource_Return));
   tmp->TrackPath_Return= formatting_process(rx->subexps[5].value);
   
	((void (*)(type_89*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_RGetTrackName(df_connection *conn, int RoomID, void (*callback)(type_89*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RGetTrackName", 1, RGetTrackName_handler, c, "[RGetTrackName %d]", RoomID);
}


static void RGetAlbumArtist_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_66* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_66));
   memset(tmp, 0, sizeof(type_66));

   sscanf(rx->subexps[2].value,"%d",&(tmp->RoomID));
   tmp->Album= formatting_process(rx->subexps[3].value);
   tmp->Artist= formatting_process(rx->subexps[4].value);
   
	((void (*)(type_66*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_RGetAlbumArtist(df_connection *conn, int RoomID, void (*callback)(type_66*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RGetAlbumArtist", 1, RGetAlbumArtist_handler, c, "[RGetAlbumArtist %d]", RoomID);
}


static void RGetPlayerStatus_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_3* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_3));
   memset(tmp, 0, sizeof(type_3));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   tmp->CommandName= formatting_process(rx->subexps[3].value);
   
	((void (*)(type_3*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_RGetPlayerStatus(df_connection *conn, int RoomID, void (*callback)(type_3*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RGetPlayerStatus", 1, RGetPlayerStatus_handler, c, "[RGetPlayerStatus %d]", RoomID);
}


static void RGetRepeat_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_55* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_55));
   memset(tmp, 0, sizeof(type_55));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   sscanf(rx->subexps[3].value,"%d",&(tmp->GetStoreDetail_Success));
   
	((void (*)(type_55*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_RGetRepeat(df_connection *conn, int RoomID, void (*callback)(type_55*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RGetRepeat", 1, RGetRepeat_handler, c, "[RGetRepeat %d]", RoomID);
}


static void RGetShuffle_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_55* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_55));
   memset(tmp, 0, sizeof(type_55));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   sscanf(rx->subexps[3].value,"%d",&(tmp->GetStoreDetail_Success));
   
	((void (*)(type_55*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_RGetShuffle(df_connection *conn, int RoomID, void (*callback)(type_55*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RGetShuffle", 1, RGetShuffle_handler, c, "[RGetShuffle %d]", RoomID);
}


static void RGetPlayingCheckSum_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_3* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_3));
   memset(tmp, 0, sizeof(type_3));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   tmp->CommandName= formatting_process(rx->subexps[3].value);
   
	((void (*)(type_3*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_RGetPlayingCheckSum(df_connection *conn, int RoomID, void (*callback)(type_3*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RGetPlayingCheckSum", 1, RGetPlayingCheckSum_handler, c, "[RGetPlayingCheckSum %d]", RoomID);
}


static void RGetDetailedTrackInfo_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_90* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_90));
   memset(tmp, 0, sizeof(type_90));

   sscanf(rx->subexps[2].value,"%d",&(tmp->RoomID));
   sscanf(rx->subexps[3].value,"%d",&(tmp->TrackKey));
   tmp->TrackName= formatting_process(rx->subexps[4].value);
   sscanf(rx->subexps[5].value,"%d",&(tmp->AlbumKey));
   tmp->Album= formatting_process(rx->subexps[6].value);
   sscanf(rx->subexps[7].value,"%d",&(tmp->ArtistKey));
   tmp->Artist= formatting_process(rx->subexps[8].value);
   sscanf(rx->subexps[9].value,"%d",&(tmp->GenreKey));
   tmp->Genre= formatting_process(rx->subexps[10].value);
   sscanf(rx->subexps[11].value,"%u-%u-%u", &(tmp->Length.hours), &(tmp->Length.minutes), &(tmp->Length.seconds));
   sscanf(rx->subexps[12].value,"%d",&(tmp->Source));
   tmp->TrackPath= formatting_process(rx->subexps[13].value);
   
	((void (*)(type_90*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_RGetDetailedTrackInfo(df_connection *conn, int RoomID, void (*callback)(type_90*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RGetDetailedTrackInfo", 1, RGetDetailedTrackInfo_handler, c, "[RGetDetailedTrackInfo %d]", RoomID);
}


static void RGetLastPlayerError_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_3* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_3));
   memset(tmp, 0, sizeof(type_3));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   tmp->CommandName= formatting_process(rx->subexps[3].value);
   
	((void (*)(type_3*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_RGetLastPlayerError(df_connection *conn, int RoomID, void (*callback)(type_3*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RGetLastPlayerError", 1, RGetLastPlayerError_handler, c, "[RGetLastPlayerError %d]", RoomID);
}


static void GetExtCountContributors_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_GetExtCountContributors(df_connection *conn, int Type, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtCountContributors", 1, GetExtCountContributors_handler, c, "[GetExtCountContributors %d]", Type);
}


static void GetExtCountContributorsForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_GetExtCountContributorsForDevice(df_connection *conn, char* Address, int Type, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtCountContributorsForDevice", 1, GetExtCountContributorsForDevice_handler, c, "[GetExtCountContributorsForDevice \"%s\" %d]", Address, Type);
}


static void GetExtCountContributorsForShare_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_GetExtCountContributorsForShare(df_connection *conn, char* Address, int Type, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtCountContributorsForShare", 1, GetExtCountContributorsForShare_handler, c, "[GetExtCountContributorsForShare \"%s\" %d]", Address, Type);
}


static void GetExtCountContributorsForServer_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_GetExtCountContributorsForServer(df_connection *conn, int Type, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtCountContributorsForServer", 1, GetExtCountContributorsForServer_handler, c, "[GetExtCountContributorsForServer %d]", Type);
}


static void GetExtCountAlbumsByContributor_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_GetExtCountAlbumsByContributor(df_connection *conn, char* Address, int Type, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtCountAlbumsByContributor", 1, GetExtCountAlbumsByContributor_handler, c, "[GetExtCountAlbumsByContributor \"%s\" %d]", Address, Type);
}


static void GetExtCountAlbumsByContributorForServer_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_GetExtCountAlbumsByContributorForServer(df_connection *conn, char* Address, int Type, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtCountAlbumsByContributorForServer", 1, GetExtCountAlbumsByContributorForServer_handler, c, "[GetExtCountAlbumsByContributorForServer \"%s\" %d]", Address, Type);
}


static void GetExtCountAlbumsByContributorForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_GetExtCountAlbumsByContributorForDevice(df_connection *conn, char* Address, char* DeviceAddress, int Type, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtCountAlbumsByContributorForDevice", 1, GetExtCountAlbumsByContributorForDevice_handler, c, "[GetExtCountAlbumsByContributorForDevice \"%s\" \"%s\" %d]", Address, DeviceAddress, Type);
}


static void GetExtCountAlbumsByContributorForShare_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_GetExtCountAlbumsByContributorForShare(df_connection *conn, char* Address, char* ShareAddress, int Type, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtCountAlbumsByContributorForShare", 1, GetExtCountAlbumsByContributorForShare_handler, c, "[GetExtCountAlbumsByContributorForShare \"%s\" \"%s\" %d]", Address, ShareAddress, Type);
}


static void vTunerAddRemoveFavourite_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_vTunerAddRemoveFavourite(df_connection *conn, char* vTunerUrl, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "vTunerAddRemoveFavourite", 1, vTunerAddRemoveFavourite_handler, c, "[vTunerAddRemoveFavourite \"%s\"]", vTunerUrl);
}


static void vTunerPlayById_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_vTunerPlayById(df_connection *conn, int RoomID, int Replace, char* Address, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "vTunerPlayById", 1, vTunerPlayById_handler, c, "[vTunerPlayById %d %d \"%s\"]", RoomID, Replace, Address);
}


static void vTunerPlayByIds_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_vTunerPlayByIds(df_connection *conn, int RoomID, int Replace, char* Address, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "vTunerPlayByIds", 1, vTunerPlayByIds_handler, c, "[vTunerPlayByIds %d %d \"%s\"]", RoomID, Replace, Address);
}


static void vTunerGetRadioStatisticsChecksum_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_3* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_3));
   memset(tmp, 0, sizeof(type_3));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   tmp->CommandName= formatting_process(rx->subexps[3].value);
   
	((void (*)(type_3*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_vTunerGetRadioStatisticsChecksum(df_connection *conn, int StatisticType, void (*callback)(type_3*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "vTunerGetRadioStatisticsChecksum", 1, vTunerGetRadioStatisticsChecksum_handler, c, "[vTunerGetRadioStatisticsChecksum %d]", StatisticType);
}


static void vTunerSetPresetChannel_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_vTunerSetPresetChannel(df_connection *conn, int ChannelNumber, char* VTunerID, char* ChannelName, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "vTunerSetPresetChannel", 1, vTunerSetPresetChannel_handler, c, "[vTunerSetPresetChannel %d \"%s\" \"%s\"]", ChannelNumber, VTunerID, ChannelName);
}


static void vTunerCheckAvailability_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_vTunerCheckAvailability(df_connection *conn, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "vTunerCheckAvailability", 1, vTunerCheckAvailability_handler, c, "[vTunerCheckAvailability]");
}


static void MoveAlbumToMusicStore_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_MoveAlbumToMusicStore(df_connection *conn, char* Address, char* MusicStoreKey, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "MoveAlbumToMusicStore", 1, MoveAlbumToMusicStore_handler, c, "[MoveAlbumToMusicStore \"%s\" \"%s\"]", Address, MusicStoreKey);
}


static void PromoteShareToMusicStore_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_83* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_83));
   memset(tmp, 0, sizeof(type_83));

   sscanf(rx->subexps[2].value,"%d",&(tmp->StopBackupDrive_Success));
   tmp->StopBackupDrive_Message= formatting_process(rx->subexps[3].value);
   
	((void (*)(type_83*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_PromoteShareToMusicStore(df_connection *conn, char* ShareKey, int ChangeOwnership, void (*callback)(type_83*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "PromoteShareToMusicStore", 1, PromoteShareToMusicStore_handler, c, "[PromoteShareToMusicStore \"%s\" %d]", ShareKey, ChangeOwnership);
}


static void DemoteMusicStoreToShare_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_83* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_83));
   memset(tmp, 0, sizeof(type_83));

   sscanf(rx->subexps[2].value,"%d",&(tmp->StopBackupDrive_Success));
   tmp->StopBackupDrive_Message= formatting_process(rx->subexps[3].value);
   
	((void (*)(type_83*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_DemoteMusicStoreToShare(df_connection *conn, char* MusicStoreKey, int Deactivate, void (*callback)(type_83*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "DemoteMusicStoreToShare", 1, DemoteMusicStoreToShare_handler, c, "[DemoteMusicStoreToShare \"%s\" %d]", MusicStoreKey, Deactivate);
}


static void RescanMusicStore_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_83* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_83));
   memset(tmp, 0, sizeof(type_83));

   sscanf(rx->subexps[2].value,"%d",&(tmp->StopBackupDrive_Success));
   tmp->StopBackupDrive_Message= formatting_process(rx->subexps[3].value);
   
	((void (*)(type_83*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_RescanMusicStore(df_connection *conn, char* MusicStoreKey, void (*callback)(type_83*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RescanMusicStore", 1, RescanMusicStore_handler, c, "[RescanMusicStore \"%s\"]", MusicStoreKey);
}


static void SetMusicStorePriority_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_83* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_83));
   memset(tmp, 0, sizeof(type_83));

   sscanf(rx->subexps[2].value,"%d",&(tmp->StopBackupDrive_Success));
   tmp->StopBackupDrive_Message= formatting_process(rx->subexps[3].value);
   
	((void (*)(type_83*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_SetMusicStorePriority(df_connection *conn, char* MusicStoreKey, int Priority, void (*callback)(type_83*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "SetMusicStorePriority", 1, SetMusicStorePriority_handler, c, "[SetMusicStorePriority \"%s\" %d]", MusicStoreKey, Priority);
}


static void SetMusicStoreCredentials_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_SetMusicStoreCredentials(df_connection *conn, char* MusicStoreKey, char* Username, char* Password, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "SetMusicStoreCredentials", 1, SetMusicStoreCredentials_handler, c, "[SetMusicStoreCredentials \"%s\" \"%s\" \"%s\"]", MusicStoreKey, Username, Password);
}


static void MoveAlbumGetStatus_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_91* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_91));
   memset(tmp, 0, sizeof(type_91));

   sscanf(rx->subexps[2].value,"%d",&(tmp->Running));
   sscanf(rx->subexps[3].value,"%d",&(tmp->AlbumKey));
   tmp->AlbumName= formatting_process(rx->subexps[4].value);
   sscanf(rx->subexps[5].value,"%d",&(tmp->SourceStoreKey));
   sscanf(rx->subexps[6].value,"%d",&(tmp->DestinationStoreKey));
   sscanf(rx->subexps[7].value,"%d",&(tmp->Progress));
   
	((void (*)(type_91*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_MoveAlbumGetStatus(df_connection *conn, void (*callback)(type_91*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "MoveAlbumGetStatus", 1, MoveAlbumGetStatus_handler, c, "[MoveAlbumGetStatus]");
}


static void GetExtContributorsExist_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_GetExtContributorsExist(df_connection *conn, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "GetExtContributorsExist", 1, GetExtContributorsExist_handler, c, "[GetExtContributorsExist]");
}



static void SetConnOption_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	char* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   tmp= formatting_process(rx->subexps[2].value);
   
	((void (*)(char*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_SetConnOption(df_connection *conn, char* OptionName, char* OptionValue, void (*callback)(char*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "SetConnOption", 1, SetConnOption_handler, c, "[SetConnOption \"%s\" \"%s\"]", OptionName, OptionValue);
}


static void SetLength_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_62* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_62));
   memset(tmp, 0, sizeof(type_62));

   tmp->GetHostDetails_Name= formatting_process(rx->subexps[2].value);
   tmp->GetHostDetails_Address= formatting_process(rx->subexps[3].value);
   
	((void (*)(type_62*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_SetLength(df_connection *conn, char* FormatList, char* FieldName, int Length, void (*callback)(type_62*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "SetLength", 1, SetLength_handler, c, "[SetLength \"%s\" \"%s\" %d]", FormatList, FieldName, Length);
}


static void EnableField_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_62* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_62));
   memset(tmp, 0, sizeof(type_62));

   tmp->GetHostDetails_Name= formatting_process(rx->subexps[2].value);
   tmp->GetHostDetails_Address= formatting_process(rx->subexps[3].value);
   
	((void (*)(type_62*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_EnableField(df_connection *conn, char* FormatList, char* FieldName, void (*callback)(type_62*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "EnableField", 1, EnableField_handler, c, "[EnableField \"%s\" \"%s\"]", FormatList, FieldName);
}


static void DisableField_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_62* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_62));
   memset(tmp, 0, sizeof(type_62));

   tmp->GetHostDetails_Name= formatting_process(rx->subexps[2].value);
   tmp->GetHostDetails_Address= formatting_process(rx->subexps[3].value);
   
	((void (*)(type_62*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_DisableField(df_connection *conn, char* FormatList, char* FieldName, void (*callback)(type_62*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "DisableField", 1, DisableField_handler, c, "[DisableField \"%s\" \"%s\"]", FormatList, FieldName);
}



int df_RoomIpChanged(df_connection *conn) {
	return comm_send(conn, 0, "void", 1, 0, 0, "[RoomIpChanged]");
}


static void MasterIpChanged_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_62* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_62));
   memset(tmp, 0, sizeof(type_62));

   tmp->GetHostDetails_Name= formatting_process(rx->subexps[2].value);
   tmp->GetHostDetails_Address= formatting_process(rx->subexps[3].value);
   
	((void (*)(type_62*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_MasterIpChanged(df_connection *conn, char* MasterName, char* MasterAddress, void (*callback)(type_62*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "MasterIpChanged", 1, MasterIpChanged_handler, c, "[MasterIpChanged \"%s\" \"%s\"]", MasterName, MasterAddress);
}



int df_SetRippingStatus(df_connection *conn) {
	return comm_send(conn, 0, "void", 1, 0, 0, "[SetRippingStatus]");
}



int df_SetCDDetected(df_connection *conn) {
	return comm_send(conn, 0, "void", 1, 0, 0, "[SetCDDetected]");
}



int df_SetRecycleBinStatus(df_connection *conn) {
	return comm_send(conn, 0, "void", 1, 0, 0, "[SetRecycleBinStatus]");
}


static void Stop_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_Stop(df_connection *conn, int RoomID, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "Stop", 1, Stop_handler, c, "[Stop %d]", RoomID);
}


static void Play_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_Play(df_connection *conn, int RoomID, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "Play", 1, Play_handler, c, "[Play %d]", RoomID);
}


static void Pause_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_Pause(df_connection *conn, int RoomID, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "Pause", 1, Pause_handler, c, "[Pause %d]", RoomID);
}


static void ClearPlaylist_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_ClearPlaylist(df_connection *conn, int RoomID, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ClearPlaylist", 1, ClearPlaylist_handler, c, "[ClearPlaylist %d]", RoomID);
}


static void FastForward_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_FastForward(df_connection *conn, int RoomID, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "FastForward", 1, FastForward_handler, c, "[FastForward %d]", RoomID);
}


static void FastRewind_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_FastRewind(df_connection *conn, int RoomID, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "FastRewind", 1, FastRewind_handler, c, "[FastRewind %d]", RoomID);
}


static void RandomisePlaylist_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_RandomisePlaylist(df_connection *conn, int RoomID, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RandomisePlaylist", 1, RandomisePlaylist_handler, c, "[RandomisePlaylist %d]", RoomID);
}


static void SetTrack_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_SetTrack(df_connection *conn, int RoomID, int TrackNumber, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "SetTrack", 1, SetTrack_handler, c, "[SetTrack %d %d]", RoomID, TrackNumber);
}


static void SetTrackPosition_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_SetTrackPosition(df_connection *conn, int RoomID, df_time PlayPosition, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "SetTrackPosition", 1, SetTrackPosition_handler, c, "[SetTrackPosition %d \"%u:%u:%u\"]", RoomID, PlayPosition.hours, PlayPosition.minutes, PlayPosition.seconds);
}


static void EjectCD_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_EjectCD(df_connection *conn, int RoomID, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "EjectCD", 1, EjectCD_handler, c, "[EjectCD %d]", RoomID);
}


static void SetVolume_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_SetVolume(df_connection *conn, int RoomID, int Volume, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "SetVolume", 1, SetVolume_handler, c, "[SetVolume %d %d]", RoomID, Volume);
}


static void SetShuffle_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_SetShuffle(df_connection *conn, int RoomID, int Shuffle, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "SetShuffle", 1, SetShuffle_handler, c, "[SetShuffle %d %d]", RoomID, Shuffle);
}


static void SetRepeat_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_SetRepeat(df_connection *conn, int RoomID, int Repeat, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "SetRepeat", 1, SetRepeat_handler, c, "[SetRepeat %d %d]", RoomID, Repeat);
}



int df_ClearAllPlaying(df_connection *conn) {
	return comm_send(conn, 0, "void", 1, 0, 0, "[ClearAllPlaying]");
}



int df_RestartDevice(df_connection *conn) {
	return comm_send(conn, 0, "void", 1, 0, 0, "[RestartDevice]");
}


static void ChangeCDDBSubGenreAssociation_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	char* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   tmp= formatting_process(rx->subexps[2].value);
   
	((void (*)(char*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_ChangeCDDBSubGenreAssociation(df_connection *conn, char* GenreKey, char* NewSubGenreKey, void (*callback)(char*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ChangeCDDBSubGenreAssociation", 1, ChangeCDDBSubGenreAssociation_handler, c, "[ChangeCDDBSubGenreAssociation \"%s\" \"%s\"]", GenreKey, NewSubGenreKey);
}


static void ForceHostUpgrade_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_ForceHostUpgrade(df_connection *conn, int RoomID, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ForceHostUpgrade", 1, ForceHostUpgrade_handler, c, "[ForceHostUpgrade %d]", RoomID);
}



int df_ForceDBRebuild(df_connection *conn) {
	return comm_send(conn, 0, "void", 1, 0, 0, "[ForceDBRebuild]");
}



int df_PurgeImageCache(df_connection *conn) {
	return comm_send(conn, 0, "void", 1, 0, 0, "[PurgeImageCache]");
}



int df_CDLookupCancel(df_connection *conn) {
	return comm_send(conn, 0, "void", 1, 0, 0, "[CDLookupCancel]");
}



int df_CdLookupCancelAll(df_connection *conn) {
	return comm_send(conn, 0, "void", 1, 0, 0, "[CdLookupCancelAll]");
}



int df_EmptyRecycleBin(df_connection *conn) {
	return comm_send(conn, 0, "void", 1, 0, 0, "[EmptyRecycleBin]");
}


static void EmptyRipShare_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_EmptyRipShare(df_connection *conn, int RoomID, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "EmptyRipShare", 1, EmptyRipShare_handler, c, "[EmptyRipShare %d]", RoomID);
}


static void ClearDownloadFolder_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_ClearDownloadFolder(df_connection *conn, int RoomID, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "ClearDownloadFolder", 1, ClearDownloadFolder_handler, c, "[ClearDownloadFolder %d]", RoomID);
}


static void RGetRegisterClient_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	type_3* tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   tmp = malloc(sizeof(type_3));
   memset(tmp, 0, sizeof(type_3));

   sscanf(rx->subexps[2].value,"%d",&(tmp->SearchNumber));
   tmp->CommandName= formatting_process(rx->subexps[3].value);
   
	((void (*)(type_3*, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_RGetRegisterClient(df_connection *conn, int PortNumber, char* IPAddress, void (*callback)(type_3*, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RGetRegisterClient", 1, RGetRegisterClient_handler, c, "[RGetRegisterClient %d \"%s\"]", PortNumber, IPAddress);
}


static void RGetClearCommands_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	int tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   

   sscanf(rx->subexps[2].value,"%d",&(tmp));
   
	((void (*)(int, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_RGetClearCommands(df_connection *conn, int RoomID, void (*callback)(int, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "RGetClearCommands", 1, RGetClearCommands_handler, c, "[RGetClearCommands %d]", RoomID);
}



int df_vTunerCleanStatistics(df_connection *conn) {
	return comm_send(conn, 0, "void", 1, 0, 0, "[vTunerCleanStatistics]");
}



int df_vTunerClearPresetChannel(df_connection *conn) {
	return comm_send(conn, 0, "void", 1, 0, 0, "[vTunerClearPresetChannel]");
}



int df_MoveAlbumCancel(df_connection *conn) {
	return comm_send(conn, 0, "void", 1, 0, 0, "[MoveAlbumCancel]");
}



int df_MoveAlbumCancelAll(df_connection *conn) {
	return comm_send(conn, 0, "void", 1, 0, 0, "[MoveAlbumCancelAll]");
}





static void Status_handler(out_request *request, out_response *response, int num, void* context) {
	type_2 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_2));
      memset(fresh, 0, sizeof(type_2));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      fresh->StatusSettingName= formatting_process(rx->subexps[3].value);
      fresh->StatusSettingValue= formatting_process(rx->subexps[4].value);
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_2*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_Status(df_connection *conn, int SearchNumber, void (*s_callback)(df_search*), void (*callback)(type_2*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[Status %d]", SearchNumber);
}

static void EffFormat_handler(out_request *request, out_response *response, int num, void* context) {
	type_4 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_4));
      memset(fresh, 0, sizeof(type_4));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      fresh->CommandName= formatting_process(rx->subexps[3].value);
      fresh->FieldName= formatting_process(rx->subexps[4].value);
      fresh->FormatSource= formatting_process(rx->subexps[5].value);
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_4*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_EffFormat(df_connection *conn, int SearchNumber, char* CommandName, char* FormatList, void (*s_callback)(df_search*), void (*callback)(type_4*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[EffFormat %d \"%s\" \"%s\"]", SearchNumber, CommandName, FormatList);
}

static void FilterSearch_handler(out_request *request, out_response *response, int num, void* context) {
	type_6 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_6));
      memset(fresh, 0, sizeof(type_6));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->TargetSearchNumber));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_6*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_FilterSearch(df_connection *conn, int SearchNumber, int TargetSearchNumber, char* SearchValue, char* SearchColumn, int SearchType, void (*s_callback)(df_search*), void (*callback)(type_6*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[FilterSearch %d %d \"%s\" \"%s\" %d]", SearchNumber, TargetSearchNumber, SearchValue, SearchColumn, SearchType);
}

static void SortSearch_handler(out_request *request, out_response *response, int num, void* context) {
	type_6 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_6));
      memset(fresh, 0, sizeof(type_6));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->TargetSearchNumber));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_6*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_SortSearch(df_connection *conn, int SearchNumber, int TargetSearchNumber, char* SortColumn, char* SortOrder, void (*s_callback)(df_search*), void (*callback)(type_6*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[SortSearch %d %d \"%s\" \"%s\"]", SearchNumber, TargetSearchNumber, SortColumn, SortOrder);
}

static void GetRooms_handler(out_request *request, out_response *response, int num, void* context) {
	type_8 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_8));
      memset(fresh, 0, sizeof(type_8));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->RoomKey));
      fresh->IPAddress= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->Channel));
      fresh->Name= formatting_process(rx->subexps[6].value);
      fresh->ShortName= formatting_process(rx->subexps[7].value);
      sscanf(rx->subexps[8].value,"%d",&(fresh->IsMultiRoom));
      sscanf(rx->subexps[9].value,"%d",&(fresh->PlaybackCapability));
      sscanf(rx->subexps[10].value,"%d",&(fresh->RippingCapability));
      sscanf(rx->subexps[11].value,"%d",&(fresh->MusicManagementCapability));
      sscanf(rx->subexps[12].value,"%d",&(fresh->RoomID));
      fresh->HostName= formatting_process(rx->subexps[13].value);
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_8*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetRooms(df_connection *conn, int SearchNumber, int LocalOnly, void (*s_callback)(df_search*), void (*callback)(type_8*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetRooms %d %d]", SearchNumber, LocalOnly);
}

static void GetRoomsWithPlayBack_handler(out_request *request, out_response *response, int num, void* context) {
	type_8 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_8));
      memset(fresh, 0, sizeof(type_8));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->RoomKey));
      fresh->IPAddress= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->Channel));
      fresh->Name= formatting_process(rx->subexps[6].value);
      fresh->ShortName= formatting_process(rx->subexps[7].value);
      sscanf(rx->subexps[8].value,"%d",&(fresh->IsMultiRoom));
      sscanf(rx->subexps[9].value,"%d",&(fresh->PlaybackCapability));
      sscanf(rx->subexps[10].value,"%d",&(fresh->RippingCapability));
      sscanf(rx->subexps[11].value,"%d",&(fresh->MusicManagementCapability));
      sscanf(rx->subexps[12].value,"%d",&(fresh->RoomID));
      fresh->HostName= formatting_process(rx->subexps[13].value);
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_8*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetRoomsWithPlayBack(df_connection *conn, int SearchNumber, int LocalOnly, void (*s_callback)(df_search*), void (*callback)(type_8*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetRoomsWithPlayBack %d %d]", SearchNumber, LocalOnly);
}

static void GetRoomsWithRipping_handler(out_request *request, out_response *response, int num, void* context) {
	type_8 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_8));
      memset(fresh, 0, sizeof(type_8));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->RoomKey));
      fresh->IPAddress= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->Channel));
      fresh->Name= formatting_process(rx->subexps[6].value);
      fresh->ShortName= formatting_process(rx->subexps[7].value);
      sscanf(rx->subexps[8].value,"%d",&(fresh->IsMultiRoom));
      sscanf(rx->subexps[9].value,"%d",&(fresh->PlaybackCapability));
      sscanf(rx->subexps[10].value,"%d",&(fresh->RippingCapability));
      sscanf(rx->subexps[11].value,"%d",&(fresh->MusicManagementCapability));
      sscanf(rx->subexps[12].value,"%d",&(fresh->RoomID));
      fresh->HostName= formatting_process(rx->subexps[13].value);
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_8*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetRoomsWithRipping(df_connection *conn, int SearchNumber, int LocalOnly, void (*s_callback)(df_search*), void (*callback)(type_8*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetRoomsWithRipping %d %d]", SearchNumber, LocalOnly);
}

static void GetNonLinkedRooms_handler(out_request *request, out_response *response, int num, void* context) {
	type_8 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_8));
      memset(fresh, 0, sizeof(type_8));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->RoomKey));
      fresh->IPAddress= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->Channel));
      fresh->Name= formatting_process(rx->subexps[6].value);
      fresh->ShortName= formatting_process(rx->subexps[7].value);
      sscanf(rx->subexps[8].value,"%d",&(fresh->IsMultiRoom));
      sscanf(rx->subexps[9].value,"%d",&(fresh->PlaybackCapability));
      sscanf(rx->subexps[10].value,"%d",&(fresh->RippingCapability));
      sscanf(rx->subexps[11].value,"%d",&(fresh->MusicManagementCapability));
      sscanf(rx->subexps[12].value,"%d",&(fresh->RoomID));
      fresh->HostName= formatting_process(rx->subexps[13].value);
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_8*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetNonLinkedRooms(df_connection *conn, int SearchNumber, int LocalOnly, void (*s_callback)(df_search*), void (*callback)(type_8*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetNonLinkedRooms %d %d]", SearchNumber, LocalOnly);
}

static void GetLinkedRooms_handler(out_request *request, out_response *response, int num, void* context) {
	type_8 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_8));
      memset(fresh, 0, sizeof(type_8));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->RoomKey));
      fresh->IPAddress= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->Channel));
      fresh->Name= formatting_process(rx->subexps[6].value);
      fresh->ShortName= formatting_process(rx->subexps[7].value);
      sscanf(rx->subexps[8].value,"%d",&(fresh->IsMultiRoom));
      sscanf(rx->subexps[9].value,"%d",&(fresh->PlaybackCapability));
      sscanf(rx->subexps[10].value,"%d",&(fresh->RippingCapability));
      sscanf(rx->subexps[11].value,"%d",&(fresh->MusicManagementCapability));
      sscanf(rx->subexps[12].value,"%d",&(fresh->RoomID));
      fresh->HostName= formatting_process(rx->subexps[13].value);
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_8*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetLinkedRooms(df_connection *conn, int SearchNumber, int LocalOnly, void (*s_callback)(df_search*), void (*callback)(type_8*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetLinkedRooms %d %d]", SearchNumber, LocalOnly);
}

static void GetAdvancedStatus_handler(out_request *request, out_response *response, int num, void* context) {
	type_2 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_2));
      memset(fresh, 0, sizeof(type_2));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      fresh->StatusSettingName= formatting_process(rx->subexps[3].value);
      fresh->StatusSettingValue= formatting_process(rx->subexps[4].value);
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_2*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetAdvancedStatus(df_connection *conn, int SearchNumber, void (*s_callback)(df_search*), void (*callback)(type_2*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetAdvancedStatus %d]", SearchNumber);
}

static void GetUserStatus_handler(out_request *request, out_response *response, int num, void* context) {
	type_2 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_2));
      memset(fresh, 0, sizeof(type_2));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      fresh->StatusSettingName= formatting_process(rx->subexps[3].value);
      fresh->StatusSettingValue= formatting_process(rx->subexps[4].value);
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_2*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetUserStatus(df_connection *conn, int SearchNumber, void (*s_callback)(df_search*), void (*callback)(type_2*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetUserStatus %d]", SearchNumber);
}

static void GetStatusMessages_handler(out_request *request, out_response *response, int num, void* context) {
	type_9 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_9));
      memset(fresh, 0, sizeof(type_9));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->MessageAddress));
      fresh->Severity= formatting_process(rx->subexps[4].value);
      fresh->Category= formatting_process(rx->subexps[5].value);
      sscanf(rx->subexps[6].value,"%u-%u-%u", &(fresh->DateCreated.year), &(fresh->DateCreated.month), &(fresh->DateCreated.day));
      sscanf(rx->subexps[7].value,"%u-%u-%u", &(fresh->TimeCreated.hours), &(fresh->TimeCreated.minutes), &(fresh->TimeCreated.seconds));
      sscanf(rx->subexps[8].value,"%d",&(fresh->Tag));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_9*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetStatusMessages(df_connection *conn, int SearchNumber, df_date MessageDate, char* Category, int Tag, void (*s_callback)(df_search*), void (*callback)(type_9*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetStatusMessages %d \"%u-%u-%u\" \"%s\" %d]", SearchNumber, MessageDate.year, MessageDate.month, MessageDate.day, Category, Tag);
}

static void GetCurrentPlayList_handler(out_request *request, out_response *response, int num, void* context) {
	type_10 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_10));
      memset(fresh, 0, sizeof(type_10));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->RoomID));
      sscanf(rx->subexps[4].value,"%d",&(fresh->TrackKey));
      fresh->Name= formatting_process(rx->subexps[5].value);
      fresh->SortName= formatting_process(rx->subexps[6].value);
      fresh->Type= formatting_process(rx->subexps[7].value);
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[10].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[11].value,"%d",&(fresh->Ordinal));
      sscanf(rx->subexps[12].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[13].value,"%d",&(fresh->Storage));
      sscanf(rx->subexps[14].value,"%d",&(fresh->SampleRate));
      sscanf(rx->subexps[15].value,"%d",&(fresh->BitsPerSample));
      sscanf(rx->subexps[16].value,"%d",&(fresh->ChannelCount));
      sscanf(rx->subexps[17].value,"%d",&(fresh->Source));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_10*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetCurrentPlayList(df_connection *conn, int SearchNumber, int RoomID, void (*s_callback)(df_search*), void (*callback)(type_10*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetCurrentPlayList %d %d]", SearchNumber, RoomID);
}

static void GetCurrentPlaylistEx_handler(out_request *request, out_response *response, int num, void* context) {
	type_11 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_11));
      memset(fresh, 0, sizeof(type_11));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->RoomID));
      sscanf(rx->subexps[4].value,"%d",&(fresh->TrackKey));
      fresh->Name= formatting_process(rx->subexps[5].value);
      fresh->SortName= formatting_process(rx->subexps[6].value);
      fresh->Type= formatting_process(rx->subexps[7].value);
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[10].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[11].value,"%d",&(fresh->Ordinal));
      sscanf(rx->subexps[12].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[13].value,"%d",&(fresh->Storage));
      sscanf(rx->subexps[14].value,"%d",&(fresh->SampleRate));
      sscanf(rx->subexps[15].value,"%d",&(fresh->BitsPerSample));
      sscanf(rx->subexps[16].value,"%d",&(fresh->ChannelCount));
      sscanf(rx->subexps[17].value,"%d",&(fresh->AlbumKey));
      fresh->AlbumName= formatting_process(rx->subexps[18].value);
      sscanf(rx->subexps[19].value,"%d",&(fresh->ArtistKey));
      fresh->ArtistName= formatting_process(rx->subexps[20].value);
      fresh->SubGenre= formatting_process(rx->subexps[21].value);
      fresh->CoverURL= formatting_process(rx->subexps[22].value);
      sscanf(rx->subexps[23].value,"%d",&(fresh->BitRate));
      sscanf(rx->subexps[24].value,"%d",&(fresh->Source));
      sscanf(rx->subexps[25].value,"%d",&(fresh->CoverAvailable));
      sscanf(rx->subexps[26].value,"%d",&(fresh->Hidden));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_11*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetCurrentPlaylistEx(df_connection *conn, int SearchNumber, int RoomID, int RemoteImagePath, int ImageSize, void (*s_callback)(df_search*), void (*callback)(type_11*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetCurrentPlaylistEx %d %d %d %d]", SearchNumber, RoomID, RemoteImagePath, ImageSize);
}

static void GetRippingAlerts_handler(out_request *request, out_response *response, int num, void* context) {
	type_12 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_12));
      memset(fresh, 0, sizeof(type_12));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->AlertKey));
      fresh->Severity= formatting_process(rx->subexps[4].value);
      fresh->Category= formatting_process(rx->subexps[5].value);
      sscanf(rx->subexps[6].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[7].value,"%u-%u-%u", &(fresh->Time.hours), &(fresh->Time.minutes), &(fresh->Time.seconds));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_12*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetRippingAlerts(df_connection *conn, int SearchNumber, void (*s_callback)(df_search*), void (*callback)(type_12*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetRippingAlerts %d]", SearchNumber);
}

static void GetAlertDetails_handler(out_request *request, out_response *response, int num, void* context) {
	type_13 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_13));
      memset(fresh, 0, sizeof(type_13));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->AlertKey));
      fresh->Severity= formatting_process(rx->subexps[4].value);
      fresh->Category= formatting_process(rx->subexps[5].value);
      fresh->Module= formatting_process(rx->subexps[6].value);
      fresh->Message= formatting_process(rx->subexps[7].value);
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->Modified.year), &(fresh->Modified.month), &(fresh->Modified.day));
      sscanf(rx->subexps[10].value,"%u-%u-%u", &(fresh->Sent.year), &(fresh->Sent.month), &(fresh->Sent.day));
      fresh->UserMessage= formatting_process(rx->subexps[11].value);
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_13*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetAlertDetails(df_connection *conn, int SearchNumber, char* Address, void (*s_callback)(df_search*), void (*callback)(type_13*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetAlertDetails %d \"%s\"]", SearchNumber, Address);
}

static void GetRippingStatus_handler(out_request *request, out_response *response, int num, void* context) {
	type_14 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_14));
      memset(fresh, 0, sizeof(type_14));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      fresh->Artist= formatting_process(rx->subexps[3].value);
      fresh->Album= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->Tracks));
      sscanf(rx->subexps[6].value,"%d",&(fresh->TracksRipped));
      sscanf(rx->subexps[7].value,"%d",&(fresh->Errors));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->TimeTaken.hours), &(fresh->TimeTaken.minutes), &(fresh->TimeTaken.seconds));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->TimeLeft.hours), &(fresh->TimeLeft.minutes), &(fresh->TimeLeft.seconds));
      fresh->Track= formatting_process(rx->subexps[10].value);
      sscanf(rx->subexps[11].value,"%d",&(fresh->TrackPercent));
      fresh->UserMessage= formatting_process(rx->subexps[12].value);
      fresh->LookupProviderUsed= formatting_process(rx->subexps[13].value);
      fresh->Destination= formatting_process(rx->subexps[14].value);
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_14*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetRippingStatus(df_connection *conn, int SearchNumber, int RoomID, void (*s_callback)(df_search*), void (*callback)(type_14*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetRippingStatus %d %d]", SearchNumber, RoomID);
}

static void GetRipEncSettings_handler(out_request *request, out_response *response, int num, void* context) {
	type_15 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_15));
      memset(fresh, 0, sizeof(type_15));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      fresh->RegistryKey= formatting_process(rx->subexps[3].value);
      fresh->Value= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ReadOnly));
      fresh->Default= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->MaxLength));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_15*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetRipEncSettings(df_connection *conn, int SearchNumber, int RoomID, void (*s_callback)(df_search*), void (*callback)(type_15*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetRipEncSettings %d %d]", SearchNumber, RoomID);
}

static void GetRipEncSettingsEx_handler(out_request *request, out_response *response, int num, void* context) {
	type_16 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_16));
      memset(fresh, 0, sizeof(type_16));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      fresh->RegistryKey= formatting_process(rx->subexps[3].value);
      fresh->Value= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ReadOnly));
      fresh->Default= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->MaxLength));
      sscanf(rx->subexps[8].value,"%d",&(fresh->ValueType));
      fresh->TabCaption= formatting_process(rx->subexps[9].value);
      fresh->Category= formatting_process(rx->subexps[10].value);
      fresh->Caption= formatting_process(rx->subexps[11].value);
      fresh->ShortTabCaption= formatting_process(rx->subexps[12].value);
      fresh->ShortCategory= formatting_process(rx->subexps[13].value);
      fresh->ShortCaption= formatting_process(rx->subexps[14].value);
      fresh->Description= formatting_process(rx->subexps[15].value);
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_16*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetRipEncSettingsEx(df_connection *conn, int SearchNumber, int RoomID, void (*s_callback)(df_search*), void (*callback)(type_16*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetRipEncSettingsEx %d %d]", SearchNumber, RoomID);
}

static void GetSettings_handler(out_request *request, out_response *response, int num, void* context) {
	type_15 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_15));
      memset(fresh, 0, sizeof(type_15));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      fresh->RegistryKey= formatting_process(rx->subexps[3].value);
      fresh->Value= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ReadOnly));
      fresh->Default= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->MaxLength));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_15*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetSettings(df_connection *conn, int SearchNumber, int RoomID, void (*s_callback)(df_search*), void (*callback)(type_15*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetSettings %d %d]", SearchNumber, RoomID);
}

static void GetSettingsEx_handler(out_request *request, out_response *response, int num, void* context) {
	type_16 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_16));
      memset(fresh, 0, sizeof(type_16));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      fresh->RegistryKey= formatting_process(rx->subexps[3].value);
      fresh->Value= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ReadOnly));
      fresh->Default= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->MaxLength));
      sscanf(rx->subexps[8].value,"%d",&(fresh->ValueType));
      fresh->TabCaption= formatting_process(rx->subexps[9].value);
      fresh->Category= formatting_process(rx->subexps[10].value);
      fresh->Caption= formatting_process(rx->subexps[11].value);
      fresh->ShortTabCaption= formatting_process(rx->subexps[12].value);
      fresh->ShortCategory= formatting_process(rx->subexps[13].value);
      fresh->ShortCaption= formatting_process(rx->subexps[14].value);
      fresh->Description= formatting_process(rx->subexps[15].value);
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_16*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetSettingsEx(df_connection *conn, int SearchNumber, int RoomID, void (*s_callback)(df_search*), void (*callback)(type_16*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetSettingsEx %d %d]", SearchNumber, RoomID);
}

static void GetAvailableValues_handler(out_request *request, out_response *response, int num, void* context) {
	type_2 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_2));
      memset(fresh, 0, sizeof(type_2));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      fresh->StatusSettingName= formatting_process(rx->subexps[3].value);
      fresh->StatusSettingValue= formatting_process(rx->subexps[4].value);
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_2*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetAvailableValues(df_connection *conn, int SearchNumber, char* Address, void (*s_callback)(df_search*), void (*callback)(type_2*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetAvailableValues %d \"%s\"]", SearchNumber, Address);
}

static void GetSystemDrives_handler(out_request *request, out_response *response, int num, void* context) {
	type_17 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_17));
      memset(fresh, 0, sizeof(type_17));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->DriveKey));
      fresh->DriveLetter= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->IsPrimary));
      fresh->RootPath= formatting_process(rx->subexps[6].value);
      fresh->SharePath= formatting_process(rx->subexps[7].value);
      sscanf(rx->subexps[8].value,"%d",&(fresh->Usage));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastBackup.year), &(fresh->LastBackup.month), &(fresh->LastBackup.day));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_17*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetSystemDrives(df_connection *conn, int SearchNumber, void (*s_callback)(df_search*), void (*callback)(type_17*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetSystemDrives %d]", SearchNumber);
}

static void GetEncodingQueue_handler(out_request *request, out_response *response, int num, void* context) {
	type_18 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_18));
      memset(fresh, 0, sizeof(type_18));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      fresh->Value= formatting_process(rx->subexps[3].value);
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_18*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetEncodingQueue(df_connection *conn, int SearchNumber, int RoomID, void (*s_callback)(df_search*), void (*callback)(type_18*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetEncodingQueue %d %d]", SearchNumber, RoomID);
}

static void GetEncodingStatus_handler(out_request *request, out_response *response, int num, void* context) {
	type_19 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_19));
      memset(fresh, 0, sizeof(type_19));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      fresh->Artist= formatting_process(rx->subexps[3].value);
      fresh->Album= formatting_process(rx->subexps[4].value);
      fresh->Track= formatting_process(rx->subexps[5].value);
      fresh->Activity= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->Max));
      sscanf(rx->subexps[8].value,"%d",&(fresh->Progress));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_19*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetEncodingStatus(df_connection *conn, int SearchNumber, int RoomID, void (*s_callback)(df_search*), void (*callback)(type_19*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetEncodingStatus %d %d]", SearchNumber, RoomID);
}

static void GetPlayerInstances_handler(out_request *request, out_response *response, int num, void* context) {
	type_20 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_20));
      memset(fresh, 0, sizeof(type_20));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->Key));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->OutputDeviceID));
      sscanf(rx->subexps[6].value,"%d",&(fresh->SourceLineID));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_20*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetPlayerInstances(df_connection *conn, int SearchNumber, int RoomID, void (*s_callback)(df_search*), void (*callback)(type_20*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetPlayerInstances %d %d]", SearchNumber, RoomID);
}

static void GetOutputDevices_handler(out_request *request, out_response *response, int num, void* context) {
	type_21 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_21));
      memset(fresh, 0, sizeof(type_21));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      fresh->Name= formatting_process(rx->subexps[3].value);
      sscanf(rx->subexps[4].value,"%d",&(fresh->OutputDeviceID));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_21*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetOutputDevices(df_connection *conn, int SearchNumber, int RoomID, char* HostName, int AsioOutputs, void (*s_callback)(df_search*), void (*callback)(type_21*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetOutputDevices %d %d \"%s\" %d]", SearchNumber, RoomID, HostName, AsioOutputs);
}

static void GetOutputChannels_handler(out_request *request, out_response *response, int num, void* context) {
	type_21 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_21));
      memset(fresh, 0, sizeof(type_21));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      fresh->Name= formatting_process(rx->subexps[3].value);
      sscanf(rx->subexps[4].value,"%d",&(fresh->OutputDeviceID));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_21*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetOutputChannels(df_connection *conn, int SearchNumber, int RoomID, char* HostName, void (*s_callback)(df_search*), void (*callback)(type_21*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetOutputChannels %d %d \"%s\"]", SearchNumber, RoomID, HostName);
}

static void GetUpnpMediaRenderers_handler(out_request *request, out_response *response, int num, void* context) {
	type_22 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_22));
      memset(fresh, 0, sizeof(type_22));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      fresh->FriendlyName= formatting_process(rx->subexps[3].value);
      fresh->UDN= formatting_process(rx->subexps[4].value);
      fresh->Manufacturer= formatting_process(rx->subexps[5].value);
      fresh->ModelNumber= formatting_process(rx->subexps[6].value);
      fresh->SupportedExtensions= formatting_process(rx->subexps[7].value);
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_22*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetUpnpMediaRenderers(df_connection *conn, int SearchNumber, void (*s_callback)(df_search*), void (*callback)(type_22*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetUpnpMediaRenderers %d]", SearchNumber);
}

static void GetAsio4AllChannels_handler(out_request *request, out_response *response, int num, void* context) {
	type_23 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_23));
      memset(fresh, 0, sizeof(type_23));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->ChannelNumber));
      fresh->ChannelDescription= formatting_process(rx->subexps[4].value);
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_23*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetAsio4AllChannels(df_connection *conn, int SearchNumber, void (*s_callback)(df_search*), void (*callback)(type_23*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetAsio4AllChannels %d]", SearchNumber);
}

static void GetDevices_handler(out_request *request, out_response *response, int num, void* context) {
	type_24 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_24));
      memset(fresh, 0, sizeof(type_24));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->DeviceKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      fresh->SerialNumber= formatting_process(rx->subexps[5].value);
      fresh->Type= formatting_process(rx->subexps[6].value);
      fresh->State= formatting_process(rx->subexps[7].value);
      fresh->LastState= formatting_process(rx->subexps[8].value);
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastConnected.year), &(fresh->LastConnected.month), &(fresh->LastConnected.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->Connections));
      sscanf(rx->subexps[11].value,"%d",&(fresh->Sync));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_24*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetDevices(df_connection *conn, int SearchNumber, int ActiveOnly, void (*s_callback)(df_search*), void (*callback)(type_24*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetDevices %d %d]", SearchNumber, ActiveOnly);
}

static void GetDeviceDetails_handler(out_request *request, out_response *response, int num, void* context) {
	type_24 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_24));
      memset(fresh, 0, sizeof(type_24));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->DeviceKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      fresh->SerialNumber= formatting_process(rx->subexps[5].value);
      fresh->Type= formatting_process(rx->subexps[6].value);
      fresh->State= formatting_process(rx->subexps[7].value);
      fresh->LastState= formatting_process(rx->subexps[8].value);
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastConnected.year), &(fresh->LastConnected.month), &(fresh->LastConnected.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->Connections));
      sscanf(rx->subexps[11].value,"%d",&(fresh->Sync));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_24*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetDeviceDetails(df_connection *conn, int SearchNumber, char* DeviceAddress, void (*s_callback)(df_search*), void (*callback)(type_24*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetDeviceDetails %d \"%s\"]", SearchNumber, DeviceAddress);
}

static void GetExternalStorages_handler(out_request *request, out_response *response, int num, void* context) {
	type_25 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_25));
      memset(fresh, 0, sizeof(type_25));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->StorageKey));
      fresh->IPAddress= formatting_process(rx->subexps[4].value);
      fresh->HostName= formatting_process(rx->subexps[5].value);
      fresh->ShareName= formatting_process(rx->subexps[6].value);
      fresh->FullSharePath= formatting_process(rx->subexps[7].value);
      fresh->State= formatting_process(rx->subexps[8].value);
      fresh->LastState= formatting_process(rx->subexps[9].value);
      sscanf(rx->subexps[10].value,"%d",&(fresh->Active));
      sscanf(rx->subexps[11].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[12].value,"%u-%u-%u", &(fresh->Modified.year), &(fresh->Modified.month), &(fresh->Modified.day));
      sscanf(rx->subexps[13].value,"%u-%u-%u", &(fresh->LastScanDate.year), &(fresh->LastScanDate.month), &(fresh->LastScanDate.day));
      sscanf(rx->subexps[14].value,"%u-%u-%u", &(fresh->LastScanTime.hours), &(fresh->LastScanTime.minutes), &(fresh->LastScanTime.seconds));
      fresh->UserName= formatting_process(rx->subexps[15].value);
      fresh->Password= formatting_process(rx->subexps[16].value);
      fresh->ScanIgnore= formatting_process(rx->subexps[17].value);
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_25*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetExternalStorages(df_connection *conn, int SearchNumber, int AvailableOnly, void (*s_callback)(df_search*), void (*callback)(type_25*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetExternalStorages %d %d]", SearchNumber, AvailableOnly);
}

static void GetNetworkBackup_handler(out_request *request, out_response *response, int num, void* context) {
	type_25 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_25));
      memset(fresh, 0, sizeof(type_25));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->StorageKey));
      fresh->IPAddress= formatting_process(rx->subexps[4].value);
      fresh->HostName= formatting_process(rx->subexps[5].value);
      fresh->ShareName= formatting_process(rx->subexps[6].value);
      fresh->FullSharePath= formatting_process(rx->subexps[7].value);
      fresh->State= formatting_process(rx->subexps[8].value);
      fresh->LastState= formatting_process(rx->subexps[9].value);
      sscanf(rx->subexps[10].value,"%d",&(fresh->Active));
      sscanf(rx->subexps[11].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[12].value,"%u-%u-%u", &(fresh->Modified.year), &(fresh->Modified.month), &(fresh->Modified.day));
      sscanf(rx->subexps[13].value,"%u-%u-%u", &(fresh->LastScanDate.year), &(fresh->LastScanDate.month), &(fresh->LastScanDate.day));
      sscanf(rx->subexps[14].value,"%u-%u-%u", &(fresh->LastScanTime.hours), &(fresh->LastScanTime.minutes), &(fresh->LastScanTime.seconds));
      fresh->UserName= formatting_process(rx->subexps[15].value);
      fresh->Password= formatting_process(rx->subexps[16].value);
      fresh->ScanIgnore= formatting_process(rx->subexps[17].value);
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_25*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetNetworkBackup(df_connection *conn, int SearchNumber, void (*s_callback)(df_search*), void (*callback)(type_25*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetNetworkBackup %d]", SearchNumber);
}

static void GetLinkedRoomDetail_handler(out_request *request, out_response *response, int num, void* context) {
	type_27 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_27));
      memset(fresh, 0, sizeof(type_27));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->RoomKey));
      fresh->IPAddress= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->Channel));
      fresh->RoomName= formatting_process(rx->subexps[6].value);
      fresh->ShortName= formatting_process(rx->subexps[7].value);
      sscanf(rx->subexps[8].value,"%d",&(fresh->IsMultiRoom));
      sscanf(rx->subexps[9].value,"%d",&(fresh->PlaybackCapability));
      sscanf(rx->subexps[10].value,"%d",&(fresh->RippingCapability));
      sscanf(rx->subexps[11].value,"%d",&(fresh->MusicManagementCapability));
      sscanf(rx->subexps[12].value,"%d",&(fresh->RoomID));
      fresh->HostName= formatting_process(rx->subexps[13].value);
      sscanf(rx->subexps[14].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[15].value,"%u-%u-%u", &(fresh->Modified.year), &(fresh->Modified.month), &(fresh->Modified.day));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_27*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetLinkedRoomDetail(df_connection *conn, int SearchNumber, char* RoomKey, void (*s_callback)(df_search*), void (*callback)(type_27*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetLinkedRoomDetail %d \"%s\"]", SearchNumber, RoomKey);
}

static void TestRows_handler(out_request *request, out_response *response, int num, void* context) {
	type_28 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_28));
      memset(fresh, 0, sizeof(type_28));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      fresh->Col1= formatting_process(rx->subexps[3].value);
      fresh->Col2= formatting_process(rx->subexps[4].value);
      fresh->Col3= formatting_process(rx->subexps[5].value);
      fresh->Col4= formatting_process(rx->subexps[6].value);
      fresh->Col5= formatting_process(rx->subexps[7].value);
      fresh->Col6= formatting_process(rx->subexps[8].value);
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_28*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_TestRows(df_connection *conn, int SearchNumber, int NumRowsToGenerate, int MinFieldLength, int MaxFieldLength, void (*s_callback)(df_search*), void (*callback)(type_28*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[TestRows %d %d %d %d]", SearchNumber, NumRowsToGenerate, MinFieldLength, MaxFieldLength);
}

static void GetBackupJobs_handler(out_request *request, out_response *response, int num, void* context) {
	type_29 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_29));
      memset(fresh, 0, sizeof(type_29));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->BackupJobKey));
      sscanf(rx->subexps[4].value,"%d",&(fresh->SourceDriveKey));
      sscanf(rx->subexps[5].value,"%d",&(fresh->DestinationDriveKey));
      fresh->Name= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->BackupType));
      sscanf(rx->subexps[8].value,"%d",&(fresh->BackupPeriod));
      sscanf(rx->subexps[9].value,"%d",&(fresh->PeriodValue));
      sscanf(rx->subexps[10].value,"%u-%u-%u", &(fresh->RunDate.year), &(fresh->RunDate.month), &(fresh->RunDate.day));
      sscanf(rx->subexps[11].value,"%u-%u-%u", &(fresh->RunTime.hours), &(fresh->RunTime.minutes), &(fresh->RunTime.seconds));
      sscanf(rx->subexps[12].value,"%u-%u-%u", &(fresh->NextRunDate.year), &(fresh->NextRunDate.month), &(fresh->NextRunDate.day));
      sscanf(rx->subexps[13].value,"%u-%u-%u", &(fresh->NextRunTime.hours), &(fresh->NextRunTime.minutes), &(fresh->NextRunTime.seconds));
      sscanf(rx->subexps[14].value,"%u-%u-%u", &(fresh->LastRunDate.year), &(fresh->LastRunDate.month), &(fresh->LastRunDate.day));
      sscanf(rx->subexps[15].value,"%u-%u-%u", &(fresh->LastRunTime.hours), &(fresh->LastRunTime.minutes), &(fresh->LastRunTime.seconds));
      sscanf(rx->subexps[16].value,"%d",&(fresh->JobStatus));
      sscanf(rx->subexps[17].value,"%d",&(fresh->LastResult));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_29*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetBackupJobs(df_connection *conn, int SearchNumber, void (*s_callback)(df_search*), void (*callback)(type_29*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetBackupJobs %d]", SearchNumber);
}

static void GetBackupJobDetail_handler(out_request *request, out_response *response, int num, void* context) {
	type_29 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_29));
      memset(fresh, 0, sizeof(type_29));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->BackupJobKey));
      sscanf(rx->subexps[4].value,"%d",&(fresh->SourceDriveKey));
      sscanf(rx->subexps[5].value,"%d",&(fresh->DestinationDriveKey));
      fresh->Name= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->BackupType));
      sscanf(rx->subexps[8].value,"%d",&(fresh->BackupPeriod));
      sscanf(rx->subexps[9].value,"%d",&(fresh->PeriodValue));
      sscanf(rx->subexps[10].value,"%u-%u-%u", &(fresh->RunDate.year), &(fresh->RunDate.month), &(fresh->RunDate.day));
      sscanf(rx->subexps[11].value,"%u-%u-%u", &(fresh->RunTime.hours), &(fresh->RunTime.minutes), &(fresh->RunTime.seconds));
      sscanf(rx->subexps[12].value,"%u-%u-%u", &(fresh->NextRunDate.year), &(fresh->NextRunDate.month), &(fresh->NextRunDate.day));
      sscanf(rx->subexps[13].value,"%u-%u-%u", &(fresh->NextRunTime.hours), &(fresh->NextRunTime.minutes), &(fresh->NextRunTime.seconds));
      sscanf(rx->subexps[14].value,"%u-%u-%u", &(fresh->LastRunDate.year), &(fresh->LastRunDate.month), &(fresh->LastRunDate.day));
      sscanf(rx->subexps[15].value,"%u-%u-%u", &(fresh->LastRunTime.hours), &(fresh->LastRunTime.minutes), &(fresh->LastRunTime.seconds));
      sscanf(rx->subexps[16].value,"%d",&(fresh->JobStatus));
      sscanf(rx->subexps[17].value,"%d",&(fresh->LastResult));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_29*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetBackupJobDetail(df_connection *conn, int SearchNumber, char* Address, void (*s_callback)(df_search*), void (*callback)(type_29*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetBackupJobDetail %d \"%s\"]", SearchNumber, Address);
}

static void GetBackupLogs_handler(out_request *request, out_response *response, int num, void* context) {
	type_30 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_30));
      memset(fresh, 0, sizeof(type_30));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->BackupLogKey));
      sscanf(rx->subexps[4].value,"%d",&(fresh->BackupJobKey));
      sscanf(rx->subexps[5].value,"%d",&(fresh->ExecutionType));
      fresh->Name= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->BackupType));
      fresh->SourcePath= formatting_process(rx->subexps[8].value);
      fresh->DestinationPath= formatting_process(rx->subexps[9].value);
      sscanf(rx->subexps[10].value,"%u-%u-%u", &(fresh->StartDate.year), &(fresh->StartDate.month), &(fresh->StartDate.day));
      sscanf(rx->subexps[11].value,"%u-%u-%u", &(fresh->StartTime.hours), &(fresh->StartTime.minutes), &(fresh->StartTime.seconds));
      sscanf(rx->subexps[12].value,"%u-%u-%u", &(fresh->FinishDate.year), &(fresh->FinishDate.month), &(fresh->FinishDate.day));
      sscanf(rx->subexps[13].value,"%u-%u-%u", &(fresh->FinishTime.hours), &(fresh->FinishTime.minutes), &(fresh->FinishTime.seconds));
      sscanf(rx->subexps[14].value,"%d",&(fresh->Result));
      sscanf(rx->subexps[15].value,"%d",&(fresh->TotalFolders));
      sscanf(rx->subexps[16].value,"%d",&(fresh->TotalFiles));
      sscanf(rx->subexps[17].value,"%d",&(fresh->TotalKiloBytes));
      sscanf(rx->subexps[18].value,"%d",&(fresh->TotalErrors));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_30*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetBackupLogs(df_connection *conn, int SearchNumber, char* Address, void (*s_callback)(df_search*), void (*callback)(type_30*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetBackupLogs %d \"%s\"]", SearchNumber, Address);
}

static void GetBackupLogDetail_handler(out_request *request, out_response *response, int num, void* context) {
	type_31 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_31));
      memset(fresh, 0, sizeof(type_31));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->BackupLogKey));
      sscanf(rx->subexps[4].value,"%d",&(fresh->BackupJobKey));
      sscanf(rx->subexps[5].value,"%d",&(fresh->ExecutionType));
      fresh->Name= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->BackupType));
      fresh->SourcePath= formatting_process(rx->subexps[8].value);
      fresh->DestinationPath= formatting_process(rx->subexps[9].value);
      sscanf(rx->subexps[10].value,"%u-%u-%u", &(fresh->StartDate.year), &(fresh->StartDate.month), &(fresh->StartDate.day));
      sscanf(rx->subexps[11].value,"%u-%u-%u", &(fresh->StartTime.hours), &(fresh->StartTime.minutes), &(fresh->StartTime.seconds));
      sscanf(rx->subexps[12].value,"%u-%u-%u", &(fresh->FinishDate.year), &(fresh->FinishDate.month), &(fresh->FinishDate.day));
      sscanf(rx->subexps[13].value,"%u-%u-%u", &(fresh->FinishTime.hours), &(fresh->FinishTime.minutes), &(fresh->FinishTime.seconds));
      sscanf(rx->subexps[14].value,"%d",&(fresh->Result));
      sscanf(rx->subexps[15].value,"%d",&(fresh->TotalFolders));
      sscanf(rx->subexps[16].value,"%d",&(fresh->TotalFiles));
      sscanf(rx->subexps[17].value,"%d",&(fresh->TotalKiloBytes));
      sscanf(rx->subexps[18].value,"%d",&(fresh->TotalErrors));
      fresh->ErrorDetail= formatting_process(rx->subexps[19].value);
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_31*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetBackupLogDetail(df_connection *conn, int SearchNumber, char* Address, void (*s_callback)(df_search*), void (*callback)(type_31*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetBackupLogDetail %d \"%s\"]", SearchNumber, Address);
}

static void GetNetworkActiveAdapters_handler(out_request *request, out_response *response, int num, void* context) {
	type_32 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_32));
      memset(fresh, 0, sizeof(type_32));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->DeviceID));
      fresh->Description= formatting_process(rx->subexps[4].value);
      fresh->MacAddress= formatting_process(rx->subexps[5].value);
      sscanf(rx->subexps[6].value,"%d",&(fresh->DhcpEnabled));
      fresh->IpAddress= formatting_process(rx->subexps[7].value);
      fresh->SubnetMask= formatting_process(rx->subexps[8].value);
      fresh->DefaultGateway= formatting_process(rx->subexps[9].value);
      fresh->DnsServer= formatting_process(rx->subexps[10].value);
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_32*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetNetworkActiveAdapters(df_connection *conn, int SearchNumber, int IncludeWireless, void (*s_callback)(df_search*), void (*callback)(type_32*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetNetworkActiveAdapters %d %d]", SearchNumber, IncludeWireless);
}

static void ComplexSearchGetAlbums_handler(out_request *request, out_response *response, int num, void* context) {
	type_33 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_33));
      memset(fresh, 0, sizeof(type_33));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
      fresh->ArtistName= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_33*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_ComplexSearchGetAlbums(df_connection *conn, int SearchNumber, char* SearchParameter, char* SortColumn, char* SortOrder, void (*s_callback)(df_search*), void (*callback)(type_33*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[ComplexSearchGetAlbums %d \"%s\" \"%s\" \"%s\"]", SearchNumber, SearchParameter, SortColumn, SortOrder);
}

static void ComplexSearchGetTracks_handler(out_request *request, out_response *response, int num, void* context) {
	type_34 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_34));
      memset(fresh, 0, sizeof(type_34));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      fresh->SortName= formatting_process(rx->subexps[5].value);
      fresh->Type= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%u-%u-%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
      sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
      sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_34*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_ComplexSearchGetTracks(df_connection *conn, int SearchNumber, char* SearchParameter, void (*s_callback)(df_search*), void (*callback)(type_34*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[ComplexSearchGetTracks %d \"%s\"]", SearchNumber, SearchParameter);
}

static void ComplexSearchGetArtists_handler(out_request *request, out_response *response, int num, void* context) {
	type_23 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_23));
      memset(fresh, 0, sizeof(type_23));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->ChannelNumber));
      fresh->ChannelDescription= formatting_process(rx->subexps[4].value);
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_23*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_ComplexSearchGetArtists(df_connection *conn, int SearchNumber, char* SearchParameter, void (*s_callback)(df_search*), void (*callback)(type_23*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[ComplexSearchGetArtists %d \"%s\"]", SearchNumber, SearchParameter);
}

static void ComplexSearchGetContributors_handler(out_request *request, out_response *response, int num, void* context) {
	type_35 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_35));
      memset(fresh, 0, sizeof(type_35));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->ContributorKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ContributorType));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_35*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_ComplexSearchGetContributors(df_connection *conn, int SearchNumber, int Type, char* SearchParameter, void (*s_callback)(df_search*), void (*callback)(type_35*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[ComplexSearchGetContributors %d %d \"%s\"]", SearchNumber, Type, SearchParameter);
}

static void GetAlbums_handler(out_request *request, out_response *response, int num, void* context) {
	type_33 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_33));
      memset(fresh, 0, sizeof(type_33));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
      fresh->ArtistName= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_33*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetAlbums(df_connection *conn, int SearchNumber, char* SortColumn, char* SortOrder, void (*s_callback)(df_search*), void (*callback)(type_33*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetAlbums %d \"%s\" \"%s\"]", SearchNumber, SortColumn, SortOrder);
}

static void GetAlbumsForStore_handler(out_request *request, out_response *response, int num, void* context) {
	type_33 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_33));
      memset(fresh, 0, sizeof(type_33));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
      fresh->ArtistName= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_33*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetAlbumsForStore(df_connection *conn, int SearchNumber, char* StoreKey, int IncludeDeleted, char* SortColumn, char* SortOrder, void (*s_callback)(df_search*), void (*callback)(type_33*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetAlbumsForStore %d \"%s\" %d \"%s\" \"%s\"]", SearchNumber, StoreKey, IncludeDeleted, SortColumn, SortOrder);
}

static void GetAlbumsForArtists_handler(out_request *request, out_response *response, int num, void* context) {
	type_33 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_33));
      memset(fresh, 0, sizeof(type_33));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
      fresh->ArtistName= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_33*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetAlbumsForArtists(df_connection *conn, int SearchNumber, char* Address, char* SortColumn, char* SortOrder, void (*s_callback)(df_search*), void (*callback)(type_33*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetAlbumsForArtists %d \"%s\" \"%s\" \"%s\"]", SearchNumber, Address, SortColumn, SortOrder);
}

static void GetAlbumsForArtistsInSubGenre_handler(out_request *request, out_response *response, int num, void* context) {
	type_33 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_33));
      memset(fresh, 0, sizeof(type_33));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
      fresh->ArtistName= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_33*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetAlbumsForArtistsInSubGenre(df_connection *conn, int SearchNumber, char* Address, char* SubGenreAddress, char* SortColumn, char* SortOrder, void (*s_callback)(df_search*), void (*callback)(type_33*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetAlbumsForArtistsInSubGenre %d \"%s\" \"%s\" \"%s\" \"%s\"]", SearchNumber, Address, SubGenreAddress, SortColumn, SortOrder);
}

static void GetAlbumsForArtistsInSubGenreForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	type_33 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_33));
      memset(fresh, 0, sizeof(type_33));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
      fresh->ArtistName= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_33*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetAlbumsForArtistsInSubGenreForDevice(df_connection *conn, int SearchNumber, char* Address, char* SubGenreAddress, char* DeviceAddress, char* SortColumn, char* SortOrder, void (*s_callback)(df_search*), void (*callback)(type_33*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetAlbumsForArtistsInSubGenreForDevice %d \"%s\" \"%s\" \"%s\" \"%s\" \"%s\"]", SearchNumber, Address, SubGenreAddress, DeviceAddress, SortColumn, SortOrder);
}

static void GetAlbumsForArtistsInSubGenreForServer_handler(out_request *request, out_response *response, int num, void* context) {
	type_33 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_33));
      memset(fresh, 0, sizeof(type_33));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
      fresh->ArtistName= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_33*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetAlbumsForArtistsInSubGenreForServer(df_connection *conn, int SearchNumber, char* Address, char* SubGenreAddress, char* SortColumn, char* SortOrder, void (*s_callback)(df_search*), void (*callback)(type_33*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetAlbumsForArtistsInSubGenreForServer %d \"%s\" \"%s\" \"%s\" \"%s\"]", SearchNumber, Address, SubGenreAddress, SortColumn, SortOrder);
}

static void GetAlbumsForArtistsInSubGenreForShare_handler(out_request *request, out_response *response, int num, void* context) {
	type_33 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_33));
      memset(fresh, 0, sizeof(type_33));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
      fresh->ArtistName= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_33*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetAlbumsForArtistsInSubGenreForShare(df_connection *conn, int SearchNumber, char* Address, char* SubGenreAddress, char* ShareAddress, char* SortColumn, char* SortOrder, void (*s_callback)(df_search*), void (*callback)(type_33*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetAlbumsForArtistsInSubGenreForShare %d \"%s\" \"%s\" \"%s\" \"%s\" \"%s\"]", SearchNumber, Address, SubGenreAddress, ShareAddress, SortColumn, SortOrder);
}

static void GetAlbumsForArtistsInGenre_handler(out_request *request, out_response *response, int num, void* context) {
	type_33 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_33));
      memset(fresh, 0, sizeof(type_33));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
      fresh->ArtistName= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_33*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetAlbumsForArtistsInGenre(df_connection *conn, int SearchNumber, char* Address, char* GenreAddress, char* SortColumn, char* SortOrder, void (*s_callback)(df_search*), void (*callback)(type_33*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetAlbumsForArtistsInGenre %d \"%s\" \"%s\" \"%s\" \"%s\"]", SearchNumber, Address, GenreAddress, SortColumn, SortOrder);
}

static void GetAlbumsForArtistsForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	type_33 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_33));
      memset(fresh, 0, sizeof(type_33));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
      fresh->ArtistName= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_33*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetAlbumsForArtistsForDevice(df_connection *conn, int SearchNumber, char* Address, char* DeviceAddress, char* SortColumn, char* SortOrder, void (*s_callback)(df_search*), void (*callback)(type_33*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetAlbumsForArtistsForDevice %d \"%s\" \"%s\" \"%s\" \"%s\"]", SearchNumber, Address, DeviceAddress, SortColumn, SortOrder);
}

static void GetAlbumsForArtistsForShare_handler(out_request *request, out_response *response, int num, void* context) {
	type_33 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_33));
      memset(fresh, 0, sizeof(type_33));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
      fresh->ArtistName= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_33*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetAlbumsForArtistsForShare(df_connection *conn, int SearchNumber, char* Address, char* ShareAddress, char* SortColumn, char* SortOrder, void (*s_callback)(df_search*), void (*callback)(type_33*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetAlbumsForArtistsForShare %d \"%s\" \"%s\" \"%s\" \"%s\"]", SearchNumber, Address, ShareAddress, SortColumn, SortOrder);
}

static void GetAlbumsForArtistsForServer_handler(out_request *request, out_response *response, int num, void* context) {
	type_33 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_33));
      memset(fresh, 0, sizeof(type_33));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
      fresh->ArtistName= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_33*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetAlbumsForArtistsForServer(df_connection *conn, int SearchNumber, char* Address, char* SortColumn, char* SortOrder, void (*s_callback)(df_search*), void (*callback)(type_33*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetAlbumsForArtistsForServer %d \"%s\" \"%s\" \"%s\"]", SearchNumber, Address, SortColumn, SortOrder);
}

static void GetAlbumsForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	type_33 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_33));
      memset(fresh, 0, sizeof(type_33));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
      fresh->ArtistName= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_33*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetAlbumsForDevice(df_connection *conn, int SearchNumber, char* Address, char* SortColumn, char* SortOrder, void (*s_callback)(df_search*), void (*callback)(type_33*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetAlbumsForDevice %d \"%s\" \"%s\" \"%s\"]", SearchNumber, Address, SortColumn, SortOrder);
}

static void GetAlbumsForShare_handler(out_request *request, out_response *response, int num, void* context) {
	type_33 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_33));
      memset(fresh, 0, sizeof(type_33));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
      fresh->ArtistName= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_33*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetAlbumsForShare(df_connection *conn, int SearchNumber, char* Address, char* SortColumn, char* SortOrder, void (*s_callback)(df_search*), void (*callback)(type_33*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetAlbumsForShare %d \"%s\" \"%s\" \"%s\"]", SearchNumber, Address, SortColumn, SortOrder);
}

static void GetAlbumsForServer_handler(out_request *request, out_response *response, int num, void* context) {
	type_33 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_33));
      memset(fresh, 0, sizeof(type_33));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
      fresh->ArtistName= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_33*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetAlbumsForServer(df_connection *conn, int SearchNumber, char* SortColumn, char* SortOrder, void (*s_callback)(df_search*), void (*callback)(type_33*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetAlbumsForServer %d \"%s\" \"%s\"]", SearchNumber, SortColumn, SortOrder);
}

static void GetAlbumsForPlaylist_handler(out_request *request, out_response *response, int num, void* context) {
	type_33 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_33));
      memset(fresh, 0, sizeof(type_33));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
      fresh->ArtistName= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_33*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetAlbumsForPlaylist(df_connection *conn, int SearchNumber, char* Address, char* SortColumn, char* SortOrder, void (*s_callback)(df_search*), void (*callback)(type_33*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetAlbumsForPlaylist %d \"%s\" \"%s\" \"%s\"]", SearchNumber, Address, SortColumn, SortOrder);
}

static void GetAlbumsSearchAlbumArtist_handler(out_request *request, out_response *response, int num, void* context) {
	type_33 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_33));
      memset(fresh, 0, sizeof(type_33));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
      fresh->ArtistName= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_33*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetAlbumsSearchAlbumArtist(df_connection *conn, int SearchNumber, char* SearchString, char* SortColumn, char* SortOrder, int SearchType, void (*s_callback)(df_search*), void (*callback)(type_33*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetAlbumsSearchAlbumArtist %d \"%s\" \"%s\" \"%s\" %d]", SearchNumber, SearchString, SortColumn, SortOrder, SearchType);
}

static void GetLatestPlayedAlbums_handler(out_request *request, out_response *response, int num, void* context) {
	type_33 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_33));
      memset(fresh, 0, sizeof(type_33));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
      fresh->ArtistName= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_33*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetLatestPlayedAlbums(df_connection *conn, int SearchNumber, int TopCount, char* SortColumn, char* SortOrder, void (*s_callback)(df_search*), void (*callback)(type_33*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetLatestPlayedAlbums %d %d \"%s\" \"%s\"]", SearchNumber, TopCount, SortColumn, SortOrder);
}

static void GetNewestAlbums_handler(out_request *request, out_response *response, int num, void* context) {
	type_33 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_33));
      memset(fresh, 0, sizeof(type_33));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
      fresh->ArtistName= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_33*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetNewestAlbums(df_connection *conn, int SearchNumber, int TopCount, char* SortColumn, char* SortOrder, void (*s_callback)(df_search*), void (*callback)(type_33*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetNewestAlbums %d %d \"%s\" \"%s\"]", SearchNumber, TopCount, SortColumn, SortOrder);
}

static void GetPlayListsByLetter_handler(out_request *request, out_response *response, int num, void* context) {
	type_33 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_33));
      memset(fresh, 0, sizeof(type_33));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
      fresh->ArtistName= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_33*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetPlayListsByLetter(df_connection *conn, int SearchNumber, char* SearchLetter, char* SortColumn, char* SortOrder, void (*s_callback)(df_search*), void (*callback)(type_33*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetPlayListsByLetter %d \"%s\" \"%s\" \"%s\"]", SearchNumber, SearchLetter, SortColumn, SortOrder);
}

static void GetPlaylistsForGenre_handler(out_request *request, out_response *response, int num, void* context) {
	type_33 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_33));
      memset(fresh, 0, sizeof(type_33));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
      fresh->ArtistName= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_33*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetPlaylistsForGenre(df_connection *conn, int SearchNumber, char* Address, char* SortColumn, char* SortOrder, void (*s_callback)(df_search*), void (*callback)(type_33*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetPlaylistsForGenre %d \"%s\" \"%s\" \"%s\"]", SearchNumber, Address, SortColumn, SortOrder);
}

static void GetPlaylistsForSubGenre_handler(out_request *request, out_response *response, int num, void* context) {
	type_33 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_33));
      memset(fresh, 0, sizeof(type_33));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
      fresh->ArtistName= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_33*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetPlaylistsForSubGenre(df_connection *conn, int SearchNumber, char* Address, char* SortColumn, char* SortOrder, void (*s_callback)(df_search*), void (*callback)(type_33*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetPlaylistsForSubGenre %d \"%s\" \"%s\" \"%s\"]", SearchNumber, Address, SortColumn, SortOrder);
}

static void GetPlaylistsForSubGenreForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	type_33 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_33));
      memset(fresh, 0, sizeof(type_33));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
      fresh->ArtistName= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_33*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetPlaylistsForSubGenreForDevice(df_connection *conn, int SearchNumber, char* Address, char* DeviceAddress, char* SortColumn, char* SortOrder, void (*s_callback)(df_search*), void (*callback)(type_33*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetPlaylistsForSubGenreForDevice %d \"%s\" \"%s\" \"%s\" \"%s\"]", SearchNumber, Address, DeviceAddress, SortColumn, SortOrder);
}

static void GetPlaylistsForSubGenreForShare_handler(out_request *request, out_response *response, int num, void* context) {
	type_33 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_33));
      memset(fresh, 0, sizeof(type_33));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
      fresh->ArtistName= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_33*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetPlaylistsForSubGenreForShare(df_connection *conn, int SearchNumber, char* Address, char* ShareAddress, char* SortColumn, char* SortOrder, void (*s_callback)(df_search*), void (*callback)(type_33*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetPlaylistsForSubGenreForShare %d \"%s\" \"%s\" \"%s\" \"%s\"]", SearchNumber, Address, ShareAddress, SortColumn, SortOrder);
}

static void GetPlaylistsForSubGenreForServer_handler(out_request *request, out_response *response, int num, void* context) {
	type_33 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_33));
      memset(fresh, 0, sizeof(type_33));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
      fresh->ArtistName= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_33*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetPlaylistsForSubGenreForServer(df_connection *conn, int SearchNumber, char* Address, char* SortColumn, char* SortOrder, void (*s_callback)(df_search*), void (*callback)(type_33*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetPlaylistsForSubGenreForServer %d \"%s\" \"%s\" \"%s\"]", SearchNumber, Address, SortColumn, SortOrder);
}

static void GetUserPlaylistsForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	type_33 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_33));
      memset(fresh, 0, sizeof(type_33));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
      fresh->ArtistName= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_33*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetUserPlaylistsForDevice(df_connection *conn, int SearchNumber, char* Address, char* SortColumn, char* SortOrder, void (*s_callback)(df_search*), void (*callback)(type_33*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetUserPlaylistsForDevice %d \"%s\" \"%s\" \"%s\"]", SearchNumber, Address, SortColumn, SortOrder);
}

static void GetUserPlaylistsForShare_handler(out_request *request, out_response *response, int num, void* context) {
	type_33 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_33));
      memset(fresh, 0, sizeof(type_33));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
      fresh->ArtistName= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_33*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetUserPlaylistsForShare(df_connection *conn, int SearchNumber, char* Address, char* SortColumn, char* SortOrder, void (*s_callback)(df_search*), void (*callback)(type_33*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetUserPlaylistsForShare %d \"%s\" \"%s\" \"%s\"]", SearchNumber, Address, SortColumn, SortOrder);
}

static void GetUserPlaylistsForServer_handler(out_request *request, out_response *response, int num, void* context) {
	type_33 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_33));
      memset(fresh, 0, sizeof(type_33));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
      fresh->ArtistName= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_33*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetUserPlaylistsForServer(df_connection *conn, int SearchNumber, char* SortColumn, char* SortOrder, void (*s_callback)(df_search*), void (*callback)(type_33*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetUserPlaylistsForServer %d \"%s\" \"%s\"]", SearchNumber, SortColumn, SortOrder);
}

static void GetUserPlaylists_handler(out_request *request, out_response *response, int num, void* context) {
	type_33 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_33));
      memset(fresh, 0, sizeof(type_33));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
      fresh->ArtistName= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_33*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetUserPlaylists(df_connection *conn, int SearchNumber, char* SortColumn, char* SortOrder, void (*s_callback)(df_search*), void (*callback)(type_33*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetUserPlaylists %d \"%s\" \"%s\"]", SearchNumber, SortColumn, SortOrder);
}

static void GetTopPlayedAlbums_handler(out_request *request, out_response *response, int num, void* context) {
	type_33 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_33));
      memset(fresh, 0, sizeof(type_33));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
      fresh->ArtistName= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_33*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetTopPlayedAlbums(df_connection *conn, int SearchNumber, int TopCount, char* SortColumn, char* SortOrder, void (*s_callback)(df_search*), void (*callback)(type_33*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetTopPlayedAlbums %d %d \"%s\" \"%s\"]", SearchNumber, TopCount, SortColumn, SortOrder);
}

static void GetAlbumsOtherInfo_handler(out_request *request, out_response *response, int num, void* context) {
	type_36 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_36));
      memset(fresh, 0, sizeof(type_36));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
      fresh->ArtistName= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      sscanf(rx->subexps[13].value,"%d",&(fresh->GenreKey));
      fresh->Genre= formatting_process(rx->subexps[14].value);
      sscanf(rx->subexps[15].value,"%d",&(fresh->SubGenreKey));
      fresh->SubGenre= formatting_process(rx->subexps[16].value);
      sscanf(rx->subexps[17].value,"%d",&(fresh->TrackCount));
      sscanf(rx->subexps[18].value,"%d",&(fresh->LowQuality));
      sscanf(rx->subexps[19].value,"%d",&(fresh->StorageKey));
      fresh->StorageName= formatting_process(rx->subexps[20].value);
      sscanf(rx->subexps[21].value,"%d",&(fresh->ProviderUsed));
      fresh->CoverURL= formatting_process(rx->subexps[22].value);
      sscanf(rx->subexps[23].value,"%d",&(fresh->CoverAvailable));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_36*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetAlbumsOtherInfo(df_connection *conn, int SearchNumber, char* Address, char* SortColumn, char* SortOrder, int RemoteImagePath, int ImageSize, void (*s_callback)(df_search*), void (*callback)(type_36*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetAlbumsOtherInfo %d \"%s\" \"%s\" \"%s\" %d %d]", SearchNumber, Address, SortColumn, SortOrder, RemoteImagePath, ImageSize);
}

static void GetAlbumsOtherInfoForServer_handler(out_request *request, out_response *response, int num, void* context) {
	type_36 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_36));
      memset(fresh, 0, sizeof(type_36));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
      fresh->ArtistName= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      sscanf(rx->subexps[13].value,"%d",&(fresh->GenreKey));
      fresh->Genre= formatting_process(rx->subexps[14].value);
      sscanf(rx->subexps[15].value,"%d",&(fresh->SubGenreKey));
      fresh->SubGenre= formatting_process(rx->subexps[16].value);
      sscanf(rx->subexps[17].value,"%d",&(fresh->TrackCount));
      sscanf(rx->subexps[18].value,"%d",&(fresh->LowQuality));
      sscanf(rx->subexps[19].value,"%d",&(fresh->StorageKey));
      fresh->StorageName= formatting_process(rx->subexps[20].value);
      sscanf(rx->subexps[21].value,"%d",&(fresh->ProviderUsed));
      fresh->CoverURL= formatting_process(rx->subexps[22].value);
      sscanf(rx->subexps[23].value,"%d",&(fresh->CoverAvailable));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_36*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetAlbumsOtherInfoForServer(df_connection *conn, int SearchNumber, char* SortColumn, char* SortOrder, int RemoteImagePath, int ImageSize, void (*s_callback)(df_search*), void (*callback)(type_36*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetAlbumsOtherInfoForServer %d \"%s\" \"%s\" %d %d]", SearchNumber, SortColumn, SortOrder, RemoteImagePath, ImageSize);
}

static void GetAlbumsOtherInfoForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	type_36 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_36));
      memset(fresh, 0, sizeof(type_36));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
      fresh->ArtistName= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      sscanf(rx->subexps[13].value,"%d",&(fresh->GenreKey));
      fresh->Genre= formatting_process(rx->subexps[14].value);
      sscanf(rx->subexps[15].value,"%d",&(fresh->SubGenreKey));
      fresh->SubGenre= formatting_process(rx->subexps[16].value);
      sscanf(rx->subexps[17].value,"%d",&(fresh->TrackCount));
      sscanf(rx->subexps[18].value,"%d",&(fresh->LowQuality));
      sscanf(rx->subexps[19].value,"%d",&(fresh->StorageKey));
      fresh->StorageName= formatting_process(rx->subexps[20].value);
      sscanf(rx->subexps[21].value,"%d",&(fresh->ProviderUsed));
      fresh->CoverURL= formatting_process(rx->subexps[22].value);
      sscanf(rx->subexps[23].value,"%d",&(fresh->CoverAvailable));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_36*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetAlbumsOtherInfoForDevice(df_connection *conn, int SearchNumber, char* Address, char* SortColumn, char* SortOrder, int RemoteImagePath, int ImageSize, void (*s_callback)(df_search*), void (*callback)(type_36*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetAlbumsOtherInfoForDevice %d \"%s\" \"%s\" \"%s\" %d %d]", SearchNumber, Address, SortColumn, SortOrder, RemoteImagePath, ImageSize);
}

static void GetAlbumsOtherInfoForShare_handler(out_request *request, out_response *response, int num, void* context) {
	type_36 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_36));
      memset(fresh, 0, sizeof(type_36));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
      fresh->ArtistName= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      sscanf(rx->subexps[13].value,"%d",&(fresh->GenreKey));
      fresh->Genre= formatting_process(rx->subexps[14].value);
      sscanf(rx->subexps[15].value,"%d",&(fresh->SubGenreKey));
      fresh->SubGenre= formatting_process(rx->subexps[16].value);
      sscanf(rx->subexps[17].value,"%d",&(fresh->TrackCount));
      sscanf(rx->subexps[18].value,"%d",&(fresh->LowQuality));
      sscanf(rx->subexps[19].value,"%d",&(fresh->StorageKey));
      fresh->StorageName= formatting_process(rx->subexps[20].value);
      sscanf(rx->subexps[21].value,"%d",&(fresh->ProviderUsed));
      fresh->CoverURL= formatting_process(rx->subexps[22].value);
      sscanf(rx->subexps[23].value,"%d",&(fresh->CoverAvailable));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_36*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetAlbumsOtherInfoForShare(df_connection *conn, int SearchNumber, char* Address, char* SortColumn, char* SortOrder, int RemoteImagePath, int ImageSize, void (*s_callback)(df_search*), void (*callback)(type_36*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetAlbumsOtherInfoForShare %d \"%s\" \"%s\" \"%s\" %d %d]", SearchNumber, Address, SortColumn, SortOrder, RemoteImagePath, ImageSize);
}

static void GetAlbumsOtherInfoAll_handler(out_request *request, out_response *response, int num, void* context) {
	type_36 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_36));
      memset(fresh, 0, sizeof(type_36));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
      fresh->ArtistName= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      sscanf(rx->subexps[13].value,"%d",&(fresh->GenreKey));
      fresh->Genre= formatting_process(rx->subexps[14].value);
      sscanf(rx->subexps[15].value,"%d",&(fresh->SubGenreKey));
      fresh->SubGenre= formatting_process(rx->subexps[16].value);
      sscanf(rx->subexps[17].value,"%d",&(fresh->TrackCount));
      sscanf(rx->subexps[18].value,"%d",&(fresh->LowQuality));
      sscanf(rx->subexps[19].value,"%d",&(fresh->StorageKey));
      fresh->StorageName= formatting_process(rx->subexps[20].value);
      sscanf(rx->subexps[21].value,"%d",&(fresh->ProviderUsed));
      fresh->CoverURL= formatting_process(rx->subexps[22].value);
      sscanf(rx->subexps[23].value,"%d",&(fresh->CoverAvailable));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_36*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetAlbumsOtherInfoAll(df_connection *conn, int SearchNumber, char* SortColumn, char* SortOrder, int RemoteImagePath, int ImageSize, void (*s_callback)(df_search*), void (*callback)(type_36*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetAlbumsOtherInfoAll %d \"%s\" \"%s\" %d %d]", SearchNumber, SortColumn, SortOrder, RemoteImagePath, ImageSize);
}

static void GetAlbumDetails_handler(out_request *request, out_response *response, int num, void* context) {
	type_37 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_37));
      memset(fresh, 0, sizeof(type_37));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
      fresh->ArtistName= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      fresh->Genre= formatting_process(rx->subexps[13].value);
      sscanf(rx->subexps[14].value,"%d",&(fresh->TrackCount));
      fresh->CoverImage= formatting_process(rx->subexps[15].value);
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_37*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetAlbumDetails(df_connection *conn, int SearchNumber, char* Address, void (*s_callback)(df_search*), void (*callback)(type_37*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetAlbumDetails %d \"%s\"]", SearchNumber, Address);
}

static void GetTracksAll_handler(out_request *request, out_response *response, int num, void* context) {
	type_34 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_34));
      memset(fresh, 0, sizeof(type_34));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      fresh->SortName= formatting_process(rx->subexps[5].value);
      fresh->Type= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%u-%u-%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
      sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
      sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_34*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetTracksAll(df_connection *conn, int SearchNumber, void (*s_callback)(df_search*), void (*callback)(type_34*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetTracksAll %d]", SearchNumber);
}

static void GetTrackRange_handler(out_request *request, out_response *response, int num, void* context) {
	type_38 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_38));
      memset(fresh, 0, sizeof(type_38));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      fresh->SortName= formatting_process(rx->subexps[5].value);
      fresh->Type= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%u-%u-%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
      sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
      sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
      sscanf(rx->subexps[16].value,"%d",&(fresh->AllTracksOffset));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_38*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetTrackRange(df_connection *conn, int SearchNumber, int StartRow, int RowCount, char* Filter, char* Address, int Storage, void (*s_callback)(df_search*), void (*callback)(type_38*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetTrackRange %d %d %d \"%s\" \"%s\" %d]", SearchNumber, StartRow, RowCount, Filter, Address, Storage);
}

static void GetTracksForArtist_handler(out_request *request, out_response *response, int num, void* context) {
	type_34 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_34));
      memset(fresh, 0, sizeof(type_34));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      fresh->SortName= formatting_process(rx->subexps[5].value);
      fresh->Type= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%u-%u-%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
      sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
      sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_34*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetTracksForArtist(df_connection *conn, int SearchNumber, char* Address, void (*s_callback)(df_search*), void (*callback)(type_34*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetTracksForArtist %d \"%s\"]", SearchNumber, Address);
}

static void GetTracksForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	type_34 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_34));
      memset(fresh, 0, sizeof(type_34));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      fresh->SortName= formatting_process(rx->subexps[5].value);
      fresh->Type= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%u-%u-%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
      sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
      sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_34*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetTracksForDevice(df_connection *conn, int SearchNumber, char* Address, void (*s_callback)(df_search*), void (*callback)(type_34*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetTracksForDevice %d \"%s\"]", SearchNumber, Address);
}

static void GetTracksForShare_handler(out_request *request, out_response *response, int num, void* context) {
	type_34 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_34));
      memset(fresh, 0, sizeof(type_34));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      fresh->SortName= formatting_process(rx->subexps[5].value);
      fresh->Type= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%u-%u-%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
      sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
      sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_34*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetTracksForShare(df_connection *conn, int SearchNumber, char* Address, void (*s_callback)(df_search*), void (*callback)(type_34*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetTracksForShare %d \"%s\"]", SearchNumber, Address);
}

static void GetTracksForServer_handler(out_request *request, out_response *response, int num, void* context) {
	type_34 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_34));
      memset(fresh, 0, sizeof(type_34));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      fresh->SortName= formatting_process(rx->subexps[5].value);
      fresh->Type= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%u-%u-%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
      sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
      sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_34*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetTracksForServer(df_connection *conn, int SearchNumber, void (*s_callback)(df_search*), void (*callback)(type_34*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetTracksForServer %d]", SearchNumber);
}

static void GetTracksForGenre_handler(out_request *request, out_response *response, int num, void* context) {
	type_34 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_34));
      memset(fresh, 0, sizeof(type_34));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      fresh->SortName= formatting_process(rx->subexps[5].value);
      fresh->Type= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%u-%u-%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
      sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
      sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_34*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetTracksForGenre(df_connection *conn, int SearchNumber, char* Address, void (*s_callback)(df_search*), void (*callback)(type_34*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetTracksForGenre %d \"%s\"]", SearchNumber, Address);
}

static void GetTracksForPlaylist_handler(out_request *request, out_response *response, int num, void* context) {
	type_39 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_39));
      memset(fresh, 0, sizeof(type_39));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      fresh->SortName= formatting_process(rx->subexps[5].value);
      fresh->Type= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%u-%u-%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
      sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
      sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
      sscanf(rx->subexps[16].value,"%d",&(fresh->Hidden));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_39*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetTracksForPlaylist(df_connection *conn, int SearchNumber, char* Address, int ShowHidden, void (*s_callback)(df_search*), void (*callback)(type_39*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetTracksForPlaylist %d \"%s\" %d]", SearchNumber, Address, ShowHidden);
}

static void GetTracksForSubGenre_handler(out_request *request, out_response *response, int num, void* context) {
	type_34 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_34));
      memset(fresh, 0, sizeof(type_34));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      fresh->SortName= formatting_process(rx->subexps[5].value);
      fresh->Type= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%u-%u-%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
      sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
      sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_34*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetTracksForSubGenre(df_connection *conn, int SearchNumber, char* Address, void (*s_callback)(df_search*), void (*callback)(type_34*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetTracksForSubGenre %d \"%s\"]", SearchNumber, Address);
}

static void GetTracksOtherInfo_handler(out_request *request, out_response *response, int num, void* context) {
	type_40 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_40));
      memset(fresh, 0, sizeof(type_40));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      fresh->SortName= formatting_process(rx->subexps[5].value);
      fresh->Type= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%u-%u-%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
      sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
      sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
      sscanf(rx->subexps[16].value,"%d",&(fresh->AlbumKey));
      fresh->AlbumName= formatting_process(rx->subexps[17].value);
      sscanf(rx->subexps[18].value,"%d",&(fresh->ArtistKey));
      fresh->ArtistName= formatting_process(rx->subexps[19].value);
      fresh->SubGenre= formatting_process(rx->subexps[20].value);
      fresh->CoverURL= formatting_process(rx->subexps[21].value);
      sscanf(rx->subexps[22].value,"%d",&(fresh->BitRate));
      sscanf(rx->subexps[23].value,"%d",&(fresh->CoverAvailable));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_40*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetTracksOtherInfo(df_connection *conn, int SearchNumber, char* Address, int RemoteImagePath, int ImageSize, void (*s_callback)(df_search*), void (*callback)(type_40*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetTracksOtherInfo %d \"%s\" %d %d]", SearchNumber, Address, RemoteImagePath, ImageSize);
}

static void GetTracksSearchName_handler(out_request *request, out_response *response, int num, void* context) {
	type_40 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_40));
      memset(fresh, 0, sizeof(type_40));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      fresh->SortName= formatting_process(rx->subexps[5].value);
      fresh->Type= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%u-%u-%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
      sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
      sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
      sscanf(rx->subexps[16].value,"%d",&(fresh->AlbumKey));
      fresh->AlbumName= formatting_process(rx->subexps[17].value);
      sscanf(rx->subexps[18].value,"%d",&(fresh->ArtistKey));
      fresh->ArtistName= formatting_process(rx->subexps[19].value);
      fresh->SubGenre= formatting_process(rx->subexps[20].value);
      fresh->CoverURL= formatting_process(rx->subexps[21].value);
      sscanf(rx->subexps[22].value,"%d",&(fresh->BitRate));
      sscanf(rx->subexps[23].value,"%d",&(fresh->CoverAvailable));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_40*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetTracksSearchName(df_connection *conn, int SearchNumber, char* SearchString, int SearchType, int RemoteImagePath, int ImageSize, void (*s_callback)(df_search*), void (*callback)(type_40*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetTracksSearchName %d \"%s\" %d %d %d]", SearchNumber, SearchString, SearchType, RemoteImagePath, ImageSize);
}

static void AdvancedSearch_handler(out_request *request, out_response *response, int num, void* context) {
	type_40 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_40));
      memset(fresh, 0, sizeof(type_40));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      fresh->SortName= formatting_process(rx->subexps[5].value);
      fresh->Type= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%u-%u-%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
      sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
      sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
      sscanf(rx->subexps[16].value,"%d",&(fresh->AlbumKey));
      fresh->AlbumName= formatting_process(rx->subexps[17].value);
      sscanf(rx->subexps[18].value,"%d",&(fresh->ArtistKey));
      fresh->ArtistName= formatting_process(rx->subexps[19].value);
      fresh->SubGenre= formatting_process(rx->subexps[20].value);
      fresh->CoverURL= formatting_process(rx->subexps[21].value);
      sscanf(rx->subexps[22].value,"%d",&(fresh->BitRate));
      sscanf(rx->subexps[23].value,"%d",&(fresh->CoverAvailable));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_40*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_AdvancedSearch(df_connection *conn, int SearchNumber, char* EntityName, char* SearchString, int SearchType, int Match, char* EntityName2, char* SearchString2, int SearchType2, int RemoteImagePath, int ImageSize, void (*s_callback)(df_search*), void (*callback)(type_40*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[AdvancedSearch %d \"%s\" \"%s\" %d %d \"%s\" \"%s\" %d %d %d]", SearchNumber, EntityName, SearchString, SearchType, Match, EntityName2, SearchString2, SearchType2, RemoteImagePath, ImageSize);
}

static void GetTracksForNamedEntity_handler(out_request *request, out_response *response, int num, void* context) {
	type_34 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_34));
      memset(fresh, 0, sizeof(type_34));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      fresh->SortName= formatting_process(rx->subexps[5].value);
      fresh->Type= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%u-%u-%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
      sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
      sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_34*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetTracksForNamedEntity(df_connection *conn, int SearchNumber, char* EntityName, char* EntityValue, int ExactMatch, void (*s_callback)(df_search*), void (*callback)(type_34*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetTracksForNamedEntity %d \"%s\" \"%s\" %d]", SearchNumber, EntityName, EntityValue, ExactMatch);
}

static void GetTracksForAlbumInUPL_handler(out_request *request, out_response *response, int num, void* context) {
	type_34 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_34));
      memset(fresh, 0, sizeof(type_34));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      fresh->SortName= formatting_process(rx->subexps[5].value);
      fresh->Type= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%u-%u-%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
      sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
      sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_34*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetTracksForAlbumInUPL(df_connection *conn, int SearchNumber, char* Address, void (*s_callback)(df_search*), void (*callback)(type_34*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetTracksForAlbumInUPL %d \"%s\"]", SearchNumber, Address);
}

static void GetArtistDetails_handler(out_request *request, out_response *response, int num, void* context) {
	type_23 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_23));
      memset(fresh, 0, sizeof(type_23));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->ChannelNumber));
      fresh->ChannelDescription= formatting_process(rx->subexps[4].value);
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_23*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetArtistDetails(df_connection *conn, int SearchNumber, char* Address, void (*s_callback)(df_search*), void (*callback)(type_23*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetArtistDetails %d \"%s\"]", SearchNumber, Address);
}

static void GetArtists_handler(out_request *request, out_response *response, int num, void* context) {
	type_23 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_23));
      memset(fresh, 0, sizeof(type_23));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->ChannelNumber));
      fresh->ChannelDescription= formatting_process(rx->subexps[4].value);
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_23*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetArtists(df_connection *conn, int SearchNumber, int Allocated, void (*s_callback)(df_search*), void (*callback)(type_23*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetArtists %d %d]", SearchNumber, Allocated);
}

static void GetArtistsInGenre_handler(out_request *request, out_response *response, int num, void* context) {
	type_23 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_23));
      memset(fresh, 0, sizeof(type_23));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->ChannelNumber));
      fresh->ChannelDescription= formatting_process(rx->subexps[4].value);
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_23*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetArtistsInGenre(df_connection *conn, int SearchNumber, char* Address, void (*s_callback)(df_search*), void (*callback)(type_23*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetArtistsInGenre %d \"%s\"]", SearchNumber, Address);
}

static void GetArtistsInSubGenre_handler(out_request *request, out_response *response, int num, void* context) {
	type_23 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_23));
      memset(fresh, 0, sizeof(type_23));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->ChannelNumber));
      fresh->ChannelDescription= formatting_process(rx->subexps[4].value);
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_23*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetArtistsInSubGenre(df_connection *conn, int SearchNumber, char* Address, void (*s_callback)(df_search*), void (*callback)(type_23*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetArtistsInSubGenre %d \"%s\"]", SearchNumber, Address);
}

static void GetArtistsInSubGenreForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	type_23 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_23));
      memset(fresh, 0, sizeof(type_23));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->ChannelNumber));
      fresh->ChannelDescription= formatting_process(rx->subexps[4].value);
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_23*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetArtistsInSubGenreForDevice(df_connection *conn, int SearchNumber, char* Address, char* DeviceAddress, void (*s_callback)(df_search*), void (*callback)(type_23*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetArtistsInSubGenreForDevice %d \"%s\" \"%s\"]", SearchNumber, Address, DeviceAddress);
}

static void GetArtistsInSubGenreForServer_handler(out_request *request, out_response *response, int num, void* context) {
	type_23 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_23));
      memset(fresh, 0, sizeof(type_23));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->ChannelNumber));
      fresh->ChannelDescription= formatting_process(rx->subexps[4].value);
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_23*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetArtistsInSubGenreForServer(df_connection *conn, int SearchNumber, char* Address, void (*s_callback)(df_search*), void (*callback)(type_23*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetArtistsInSubGenreForServer %d \"%s\"]", SearchNumber, Address);
}

static void GetArtistsInSubGenreForShare_handler(out_request *request, out_response *response, int num, void* context) {
	type_23 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_23));
      memset(fresh, 0, sizeof(type_23));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->ChannelNumber));
      fresh->ChannelDescription= formatting_process(rx->subexps[4].value);
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_23*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetArtistsInSubGenreForShare(df_connection *conn, int SearchNumber, char* Address, char* ShareAddress, void (*s_callback)(df_search*), void (*callback)(type_23*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetArtistsInSubGenreForShare %d \"%s\" \"%s\"]", SearchNumber, Address, ShareAddress);
}

static void GetArtistsForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	type_23 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_23));
      memset(fresh, 0, sizeof(type_23));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->ChannelNumber));
      fresh->ChannelDescription= formatting_process(rx->subexps[4].value);
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_23*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetArtistsForDevice(df_connection *conn, int SearchNumber, char* Address, void (*s_callback)(df_search*), void (*callback)(type_23*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetArtistsForDevice %d \"%s\"]", SearchNumber, Address);
}

static void GetArtistsForShare_handler(out_request *request, out_response *response, int num, void* context) {
	type_23 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_23));
      memset(fresh, 0, sizeof(type_23));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->ChannelNumber));
      fresh->ChannelDescription= formatting_process(rx->subexps[4].value);
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_23*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetArtistsForShare(df_connection *conn, int SearchNumber, char* Address, void (*s_callback)(df_search*), void (*callback)(type_23*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetArtistsForShare %d \"%s\"]", SearchNumber, Address);
}

static void GetArtistsForServer_handler(out_request *request, out_response *response, int num, void* context) {
	type_23 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_23));
      memset(fresh, 0, sizeof(type_23));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->ChannelNumber));
      fresh->ChannelDescription= formatting_process(rx->subexps[4].value);
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_23*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetArtistsForServer(df_connection *conn, int SearchNumber, void (*s_callback)(df_search*), void (*callback)(type_23*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetArtistsForServer %d]", SearchNumber);
}

static void GetGenres_handler(out_request *request, out_response *response, int num, void* context) {
	type_41 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_41));
      memset(fresh, 0, sizeof(type_41));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->GenreKey));
      fresh->Genre= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[6].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[7].value,"%d",&(fresh->GenreOrdinal));
      sscanf(rx->subexps[8].value,"%d",&(fresh->Storage));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_41*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetGenres(df_connection *conn, int SearchNumber, int Allocated, char* SortColumn, char* SortOrder, void (*s_callback)(df_search*), void (*callback)(type_41*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetGenres %d %d \"%s\" \"%s\"]", SearchNumber, Allocated, SortColumn, SortOrder);
}

static void GetSubGenresForGenre_handler(out_request *request, out_response *response, int num, void* context) {
	type_42 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_42));
      memset(fresh, 0, sizeof(type_42));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->SubGenreKey));
      fresh->SubGenre= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[6].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[7].value,"%d",&(fresh->SubGenreOrdinal));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_42*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetSubGenresForGenre(df_connection *conn, int SearchNumber, char* Address, int Allocated, char* SortColumn, char* SortOrder, void (*s_callback)(df_search*), void (*callback)(type_42*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetSubGenresForGenre %d \"%s\" %d \"%s\" \"%s\"]", SearchNumber, Address, Allocated, SortColumn, SortOrder);
}

static void GetGenresSubGenres_handler(out_request *request, out_response *response, int num, void* context) {
	type_43 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_43));
      memset(fresh, 0, sizeof(type_43));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->SubGenreKey));
      fresh->SubGenre= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->GenreKey));
      fresh->Genre= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->GenreOrdinal));
      sscanf(rx->subexps[8].value,"%d",&(fresh->SubGenreOrdinal));
      sscanf(rx->subexps[9].value,"%d",&(fresh->Storage));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_43*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetGenresSubGenres(df_connection *conn, int SearchNumber, int Allocated, char* SortColumn, char* SortOrder, void (*s_callback)(df_search*), void (*callback)(type_43*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetGenresSubGenres %d %d \"%s\" \"%s\"]", SearchNumber, Allocated, SortColumn, SortOrder);
}

static void GetSubGenresForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	type_42 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_42));
      memset(fresh, 0, sizeof(type_42));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->SubGenreKey));
      fresh->SubGenre= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[6].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[7].value,"%d",&(fresh->SubGenreOrdinal));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_42*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetSubGenresForDevice(df_connection *conn, int SearchNumber, char* Address, char* SortColumn, char* SortOrder, void (*s_callback)(df_search*), void (*callback)(type_42*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetSubGenresForDevice %d \"%s\" \"%s\" \"%s\"]", SearchNumber, Address, SortColumn, SortOrder);
}

static void GetSubGenresForShare_handler(out_request *request, out_response *response, int num, void* context) {
	type_42 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_42));
      memset(fresh, 0, sizeof(type_42));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->SubGenreKey));
      fresh->SubGenre= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[6].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[7].value,"%d",&(fresh->SubGenreOrdinal));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_42*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetSubGenresForShare(df_connection *conn, int SearchNumber, char* Address, char* SortColumn, char* SortOrder, void (*s_callback)(df_search*), void (*callback)(type_42*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetSubGenresForShare %d \"%s\" \"%s\" \"%s\"]", SearchNumber, Address, SortColumn, SortOrder);
}

static void GetSubGenresForServer_handler(out_request *request, out_response *response, int num, void* context) {
	type_42 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_42));
      memset(fresh, 0, sizeof(type_42));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->SubGenreKey));
      fresh->SubGenre= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[6].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[7].value,"%d",&(fresh->SubGenreOrdinal));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_42*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetSubGenresForServer(df_connection *conn, int SearchNumber, int Allocated, int UserDefined, char* SortColumn, char* SortOrder, void (*s_callback)(df_search*), void (*callback)(type_42*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetSubGenresForServer %d %d %d \"%s\" \"%s\"]", SearchNumber, Allocated, UserDefined, SortColumn, SortOrder);
}

static void GetCDDBGenres_handler(out_request *request, out_response *response, int num, void* context) {
	type_44 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_44));
      memset(fresh, 0, sizeof(type_44));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->CDDBGenreKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->SubGenreKey));
      fresh->SubGenreName= formatting_process(rx->subexps[6].value);
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_44*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetCDDBGenres(df_connection *conn, int SearchNumber, void (*s_callback)(df_search*), void (*callback)(type_44*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetCDDBGenres %d]", SearchNumber);
}

static void UndoUserEdits_handler(out_request *request, out_response *response, int num, void* context) {
	type_45 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_45));
      memset(fresh, 0, sizeof(type_45));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
      sscanf(rx->subexps[4].value,"%d",&(fresh->Success));
      fresh->Message= formatting_process(rx->subexps[5].value);
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_45*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_UndoUserEdits(df_connection *conn, int SearchNumber, char* AlbumKeys, void (*s_callback)(df_search*), void (*callback)(type_45*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[UndoUserEdits %d \"%s\"]", SearchNumber, AlbumKeys);
}

static void GetTracksForArtistForServer_handler(out_request *request, out_response *response, int num, void* context) {
	type_34 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_34));
      memset(fresh, 0, sizeof(type_34));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      fresh->SortName= formatting_process(rx->subexps[5].value);
      fresh->Type= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%u-%u-%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
      sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
      sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_34*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetTracksForArtistForServer(df_connection *conn, int SearchNumber, char* Address, void (*s_callback)(df_search*), void (*callback)(type_34*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetTracksForArtistForServer %d \"%s\"]", SearchNumber, Address);
}

static void GetTracksForArtistForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	type_34 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_34));
      memset(fresh, 0, sizeof(type_34));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      fresh->SortName= formatting_process(rx->subexps[5].value);
      fresh->Type= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%u-%u-%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
      sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
      sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_34*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetTracksForArtistForDevice(df_connection *conn, int SearchNumber, char* Address, char* DeviceAddress, void (*s_callback)(df_search*), void (*callback)(type_34*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetTracksForArtistForDevice %d \"%s\" \"%s\"]", SearchNumber, Address, DeviceAddress);
}

static void GetTracksForArtistForShare_handler(out_request *request, out_response *response, int num, void* context) {
	type_34 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_34));
      memset(fresh, 0, sizeof(type_34));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      fresh->SortName= formatting_process(rx->subexps[5].value);
      fresh->Type= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%u-%u-%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
      sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
      sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_34*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetTracksForArtistForShare(df_connection *conn, int SearchNumber, char* Address, char* ShareAddress, void (*s_callback)(df_search*), void (*callback)(type_34*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetTracksForArtistForShare %d \"%s\" \"%s\"]", SearchNumber, Address, ShareAddress);
}

static void GetTracksForSubGenreForServer_handler(out_request *request, out_response *response, int num, void* context) {
	type_34 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_34));
      memset(fresh, 0, sizeof(type_34));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      fresh->SortName= formatting_process(rx->subexps[5].value);
      fresh->Type= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%u-%u-%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
      sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
      sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_34*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetTracksForSubGenreForServer(df_connection *conn, int SearchNumber, char* Address, void (*s_callback)(df_search*), void (*callback)(type_34*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetTracksForSubGenreForServer %d \"%s\"]", SearchNumber, Address);
}

static void GetTracksForSubGenreForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	type_34 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_34));
      memset(fresh, 0, sizeof(type_34));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      fresh->SortName= formatting_process(rx->subexps[5].value);
      fresh->Type= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%u-%u-%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
      sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
      sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_34*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetTracksForSubGenreForDevice(df_connection *conn, int SearchNumber, char* Address, char* DeviceAddress, void (*s_callback)(df_search*), void (*callback)(type_34*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetTracksForSubGenreForDevice %d \"%s\" \"%s\"]", SearchNumber, Address, DeviceAddress);
}

static void GetTracksForSubGenreForShare_handler(out_request *request, out_response *response, int num, void* context) {
	type_34 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_34));
      memset(fresh, 0, sizeof(type_34));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      fresh->SortName= formatting_process(rx->subexps[5].value);
      fresh->Type= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%u-%u-%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
      sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
      sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_34*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetTracksForSubGenreForShare(df_connection *conn, int SearchNumber, char* Address, char* ShareAddress, void (*s_callback)(df_search*), void (*callback)(type_34*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetTracksForSubGenreForShare %d \"%s\" \"%s\"]", SearchNumber, Address, ShareAddress);
}

static void GetAlbumsWithAlbumLookupMessages_handler(out_request *request, out_response *response, int num, void* context) {
	type_33 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_33));
      memset(fresh, 0, sizeof(type_33));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
      fresh->ArtistName= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_33*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetAlbumsWithAlbumLookupMessages(df_connection *conn, int SearchNumber, void (*s_callback)(df_search*), void (*callback)(type_33*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetAlbumsWithAlbumLookupMessages %d]", SearchNumber);
}

static void GetAlbumsForDeletion_handler(out_request *request, out_response *response, int num, void* context) {
	type_33 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_33));
      memset(fresh, 0, sizeof(type_33));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
      fresh->ArtistName= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_33*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetAlbumsForDeletion(df_connection *conn, int SearchNumber, char* SortColumn, char* SortOrder, void (*s_callback)(df_search*), void (*callback)(type_33*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetAlbumsForDeletion %d \"%s\" \"%s\"]", SearchNumber, SortColumn, SortOrder);
}

static void GetTracksForDeletion_handler(out_request *request, out_response *response, int num, void* context) {
	type_40 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_40));
      memset(fresh, 0, sizeof(type_40));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      fresh->SortName= formatting_process(rx->subexps[5].value);
      fresh->Type= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%u-%u-%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
      sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
      sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
      sscanf(rx->subexps[16].value,"%d",&(fresh->AlbumKey));
      fresh->AlbumName= formatting_process(rx->subexps[17].value);
      sscanf(rx->subexps[18].value,"%d",&(fresh->ArtistKey));
      fresh->ArtistName= formatting_process(rx->subexps[19].value);
      fresh->SubGenre= formatting_process(rx->subexps[20].value);
      fresh->CoverURL= formatting_process(rx->subexps[21].value);
      sscanf(rx->subexps[22].value,"%d",&(fresh->BitRate));
      sscanf(rx->subexps[23].value,"%d",&(fresh->CoverAvailable));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_40*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetTracksForDeletion(df_connection *conn, int SearchNumber, int RemoteImagePath, int ImageSize, void (*s_callback)(df_search*), void (*callback)(type_40*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetTracksForDeletion %d %d %d]", SearchNumber, RemoteImagePath, ImageSize);
}

static void BulkCDLookup_handler(out_request *request, out_response *response, int num, void* context) {
	type_45 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_45));
      memset(fresh, 0, sizeof(type_45));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
      sscanf(rx->subexps[4].value,"%d",&(fresh->Success));
      fresh->Message= formatting_process(rx->subexps[5].value);
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_45*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_BulkCDLookup(df_connection *conn, int SearchNumber, int AllAlbums, int Interval, int IgnoreProviderUsed, char* AlbumKey, void (*s_callback)(df_search*), void (*callback)(type_45*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[BulkCDLookup %d %d %d %d \"%s\"]", SearchNumber, AllAlbums, Interval, IgnoreProviderUsed, AlbumKey);
}

static void CDLookupGetQueue_handler(out_request *request, out_response *response, int num, void* context) {
	type_46 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_46));
      memset(fresh, 0, sizeof(type_46));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->QueueKey));
      fresh->Status= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->Retries));
      fresh->LastError= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%u-%u-%u", &(fresh->CreatedDate.year), &(fresh->CreatedDate.month), &(fresh->CreatedDate.day));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->CreatedTime.hours), &(fresh->CreatedTime.minutes), &(fresh->CreatedTime.seconds));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->ModifiedDate.year), &(fresh->ModifiedDate.month), &(fresh->ModifiedDate.day));
      sscanf(rx->subexps[10].value,"%u-%u-%u", &(fresh->ModifiedTime.hours), &(fresh->ModifiedTime.minutes), &(fresh->ModifiedTime.seconds));
      sscanf(rx->subexps[11].value,"%u-%u-%u", &(fresh->LastRetryDate.year), &(fresh->LastRetryDate.month), &(fresh->LastRetryDate.day));
      sscanf(rx->subexps[12].value,"%u-%u-%u", &(fresh->LastRetryTime.hours), &(fresh->LastRetryTime.minutes), &(fresh->LastRetryTime.seconds));
      sscanf(rx->subexps[13].value,"%d",&(fresh->AlbumKey));
      fresh->AlbumName= formatting_process(rx->subexps[14].value);
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_46*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_CDLookupGetQueue(df_connection *conn, int SearchNumber, void (*s_callback)(df_search*), void (*callback)(type_46*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[CDLookupGetQueue %d]", SearchNumber);
}

static void GetComponentVersions_handler(out_request *request, out_response *response, int num, void* context) {
	type_2 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_2));
      memset(fresh, 0, sizeof(type_2));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      fresh->StatusSettingName= formatting_process(rx->subexps[3].value);
      fresh->StatusSettingValue= formatting_process(rx->subexps[4].value);
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_2*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetComponentVersions(df_connection *conn, int SearchNumber, int RoomID, void (*s_callback)(df_search*), void (*callback)(type_2*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetComponentVersions %d %d]", SearchNumber, RoomID);
}

static void GetExtAlbumCredits_handler(out_request *request, out_response *response, int num, void* context) {
	type_47 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_47));
      memset(fresh, 0, sizeof(type_47));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->CreditKey));
      sscanf(rx->subexps[4].value,"%d",&(fresh->PlaylistKey));
      fresh->Description= formatting_process(rx->subexps[5].value);
      sscanf(rx->subexps[6].value,"%d",&(fresh->ContributorKey));
      fresh->ContributorName= formatting_process(rx->subexps[7].value);
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_47*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetExtAlbumCredits(df_connection *conn, int SearchNumber, char* Address, void (*s_callback)(df_search*), void (*callback)(type_47*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetExtAlbumCredits %d \"%s\"]", SearchNumber, Address);
}

static void GetExtAlbumsByContributor_handler(out_request *request, out_response *response, int num, void* context) {
	type_33 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_33));
      memset(fresh, 0, sizeof(type_33));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
      fresh->ArtistName= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_33*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetExtAlbumsByContributor(df_connection *conn, int SearchNumber, char* Address, int Type, char* SortColumn, char* SortOrder, void (*s_callback)(df_search*), void (*callback)(type_33*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetExtAlbumsByContributor %d \"%s\" %d \"%s\" \"%s\"]", SearchNumber, Address, Type, SortColumn, SortOrder);
}

static void GetExtAlbumsByContributorForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	type_33 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_33));
      memset(fresh, 0, sizeof(type_33));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
      fresh->ArtistName= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_33*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetExtAlbumsByContributorForDevice(df_connection *conn, int SearchNumber, char* Address, char* DeviceAddress, int Type, char* SortColumn, char* SortOrder, void (*s_callback)(df_search*), void (*callback)(type_33*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetExtAlbumsByContributorForDevice %d \"%s\" \"%s\" %d \"%s\" \"%s\"]", SearchNumber, Address, DeviceAddress, Type, SortColumn, SortOrder);
}

static void GetExtAlbumsByContributorForShare_handler(out_request *request, out_response *response, int num, void* context) {
	type_33 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_33));
      memset(fresh, 0, sizeof(type_33));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
      fresh->ArtistName= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_33*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetExtAlbumsByContributorForShare(df_connection *conn, int SearchNumber, char* Address, char* ShareAddress, int Type, char* SortColumn, char* SortOrder, void (*s_callback)(df_search*), void (*callback)(type_33*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetExtAlbumsByContributorForShare %d \"%s\" \"%s\" %d \"%s\" \"%s\"]", SearchNumber, Address, ShareAddress, Type, SortColumn, SortOrder);
}

static void GetExtAlbumsByContributorForServer_handler(out_request *request, out_response *response, int num, void* context) {
	type_33 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_33));
      memset(fresh, 0, sizeof(type_33));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
      fresh->ArtistName= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_33*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetExtAlbumsByContributorForServer(df_connection *conn, int SearchNumber, char* Address, int Type, char* SortColumn, char* SortOrder, void (*s_callback)(df_search*), void (*callback)(type_33*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetExtAlbumsByContributorForServer %d \"%s\" %d \"%s\" \"%s\"]", SearchNumber, Address, Type, SortColumn, SortOrder);
}

static void GetExtAlbumsByCredit_handler(out_request *request, out_response *response, int num, void* context) {
	type_33 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_33));
      memset(fresh, 0, sizeof(type_33));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
      fresh->ArtistName= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_33*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetExtAlbumsByCredit(df_connection *conn, int SearchNumber, char* Address, char* SortColumn, char* SortOrder, void (*s_callback)(df_search*), void (*callback)(type_33*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetExtAlbumsByCredit %d \"%s\" \"%s\" \"%s\"]", SearchNumber, Address, SortColumn, SortOrder);
}

static void GetExtAlbumsByWork_handler(out_request *request, out_response *response, int num, void* context) {
	type_33 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_33));
      memset(fresh, 0, sizeof(type_33));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
      fresh->ArtistName= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_33*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetExtAlbumsByWork(df_connection *conn, int SearchNumber, char* Work, char* SortColumn, char* SortOrder, void (*s_callback)(df_search*), void (*callback)(type_33*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetExtAlbumsByWork %d \"%s\" \"%s\" \"%s\"]", SearchNumber, Work, SortColumn, SortOrder);
}

static void GetExtAlbumsInfo_handler(out_request *request, out_response *response, int num, void* context) {
	type_48 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_48));
      memset(fresh, 0, sizeof(type_48));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
      sscanf(rx->subexps[4].value,"%d",&(fresh->Discs));
      sscanf(rx->subexps[5].value,"%d",&(fresh->DiscNumber));
      fresh->CatalogID= formatting_process(rx->subexps[6].value);
      fresh->ImageURL= formatting_process(rx->subexps[7].value);
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_48*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetExtAlbumsInfo(df_connection *conn, int SearchNumber, char* Address, void (*s_callback)(df_search*), void (*callback)(type_48*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetExtAlbumsInfo %d \"%s\"]", SearchNumber, Address);
}

static void GetExtContributors_handler(out_request *request, out_response *response, int num, void* context) {
	type_35 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_35));
      memset(fresh, 0, sizeof(type_35));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->ContributorKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ContributorType));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_35*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetExtContributors(df_connection *conn, int SearchNumber, int Type, void (*s_callback)(df_search*), void (*callback)(type_35*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetExtContributors %d %d]", SearchNumber, Type);
}

static void GetExtContributorsForAlbum_handler(out_request *request, out_response *response, int num, void* context) {
	type_35 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_35));
      memset(fresh, 0, sizeof(type_35));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->ContributorKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ContributorType));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_35*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetExtContributorsForAlbum(df_connection *conn, int SearchNumber, char* Address, int Type, void (*s_callback)(df_search*), void (*callback)(type_35*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetExtContributorsForAlbum %d \"%s\" %d]", SearchNumber, Address, Type);
}

static void GetExtContributorsForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	type_35 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_35));
      memset(fresh, 0, sizeof(type_35));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->ContributorKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ContributorType));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_35*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetExtContributorsForDevice(df_connection *conn, int SearchNumber, char* Address, int Type, void (*s_callback)(df_search*), void (*callback)(type_35*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetExtContributorsForDevice %d \"%s\" %d]", SearchNumber, Address, Type);
}

static void GetExtContributorsForShare_handler(out_request *request, out_response *response, int num, void* context) {
	type_35 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_35));
      memset(fresh, 0, sizeof(type_35));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->ContributorKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ContributorType));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_35*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetExtContributorsForShare(df_connection *conn, int SearchNumber, char* Address, int Type, void (*s_callback)(df_search*), void (*callback)(type_35*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetExtContributorsForShare %d \"%s\" %d]", SearchNumber, Address, Type);
}

static void GetExtContributorsForServer_handler(out_request *request, out_response *response, int num, void* context) {
	type_35 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_35));
      memset(fresh, 0, sizeof(type_35));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->ContributorKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ContributorType));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_35*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetExtContributorsForServer(df_connection *conn, int SearchNumber, int Type, void (*s_callback)(df_search*), void (*callback)(type_35*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetExtContributorsForServer %d %d]", SearchNumber, Type);
}

static void GetExtTrackContributors_handler(out_request *request, out_response *response, int num, void* context) {
	type_49 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_49));
      memset(fresh, 0, sizeof(type_49));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
      sscanf(rx->subexps[4].value,"%d",&(fresh->ContributorKey));
      fresh->Name= formatting_process(rx->subexps[5].value);
      sscanf(rx->subexps[6].value,"%d",&(fresh->ContributorType));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_49*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetExtTrackContributors(df_connection *conn, int SearchNumber, char* Address, int Type, void (*s_callback)(df_search*), void (*callback)(type_49*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetExtTrackContributors %d \"%s\" %d]", SearchNumber, Address, Type);
}

static void GetExtTracksByContributor_handler(out_request *request, out_response *response, int num, void* context) {
	type_34 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_34));
      memset(fresh, 0, sizeof(type_34));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      fresh->SortName= formatting_process(rx->subexps[5].value);
      fresh->Type= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%u-%u-%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
      sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
      sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_34*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetExtTracksByContributor(df_connection *conn, int SearchNumber, char* Address, int Type, char* Album, void (*s_callback)(df_search*), void (*callback)(type_34*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetExtTracksByContributor %d \"%s\" %d \"%s\"]", SearchNumber, Address, Type, Album);
}

static void GetExtTracksByWork_handler(out_request *request, out_response *response, int num, void* context) {
	type_34 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_34));
      memset(fresh, 0, sizeof(type_34));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      fresh->SortName= formatting_process(rx->subexps[5].value);
      fresh->Type= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%u-%u-%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
      sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
      sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_34*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetExtTracksByWork(df_connection *conn, int SearchNumber, char* Work, void (*s_callback)(df_search*), void (*callback)(type_34*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetExtTracksByWork %d \"%s\"]", SearchNumber, Work);
}

static void GetExtTracksInfo_handler(out_request *request, out_response *response, int num, void* context) {
	type_50 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_50));
      memset(fresh, 0, sizeof(type_50));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
      fresh->CompositionDate= formatting_process(rx->subexps[4].value);
      fresh->Part= formatting_process(rx->subexps[5].value);
      fresh->PerformanceDate= formatting_process(rx->subexps[6].value);
      fresh->Work= formatting_process(rx->subexps[7].value);
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_50*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetExtTracksInfo(df_connection *conn, int SearchNumber, char* Address, void (*s_callback)(df_search*), void (*callback)(type_50*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetExtTracksInfo %d \"%s\"]", SearchNumber, Address);
}

static void GetExtWorks_handler(out_request *request, out_response *response, int num, void* context) {
	type_18 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_18));
      memset(fresh, 0, sizeof(type_18));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      fresh->Value= formatting_process(rx->subexps[3].value);
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_18*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetExtWorks(df_connection *conn, int SearchNumber, void (*s_callback)(df_search*), void (*callback)(type_18*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetExtWorks %d]", SearchNumber);
}

static void GetExtContributorDetails_handler(out_request *request, out_response *response, int num, void* context) {
	type_35 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_35));
      memset(fresh, 0, sizeof(type_35));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->ContributorKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ContributorType));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_35*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetExtContributorDetails(df_connection *conn, int SearchNumber, char* Address, int Type, void (*s_callback)(df_search*), void (*callback)(type_35*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetExtContributorDetails %d \"%s\" %d]", SearchNumber, Address, Type);
}

static void GetExtTracksByContributorForServer_handler(out_request *request, out_response *response, int num, void* context) {
	type_34 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_34));
      memset(fresh, 0, sizeof(type_34));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      fresh->SortName= formatting_process(rx->subexps[5].value);
      fresh->Type= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%u-%u-%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
      sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
      sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_34*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetExtTracksByContributorForServer(df_connection *conn, int SearchNumber, char* Address, int Type, char* Album, void (*s_callback)(df_search*), void (*callback)(type_34*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetExtTracksByContributorForServer %d \"%s\" %d \"%s\"]", SearchNumber, Address, Type, Album);
}

static void GetExtTracksByContributorForDevice_handler(out_request *request, out_response *response, int num, void* context) {
	type_34 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_34));
      memset(fresh, 0, sizeof(type_34));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      fresh->SortName= formatting_process(rx->subexps[5].value);
      fresh->Type= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%u-%u-%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
      sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
      sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_34*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetExtTracksByContributorForDevice(df_connection *conn, int SearchNumber, char* Address, char* DeviceAddress, int Type, char* Album, void (*s_callback)(df_search*), void (*callback)(type_34*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetExtTracksByContributorForDevice %d \"%s\" \"%s\" %d \"%s\"]", SearchNumber, Address, DeviceAddress, Type, Album);
}

static void GetExtTracksByContributorForShare_handler(out_request *request, out_response *response, int num, void* context) {
	type_34 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_34));
      memset(fresh, 0, sizeof(type_34));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->TrackKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      fresh->SortName= formatting_process(rx->subexps[5].value);
      fresh->Type= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%u-%u-%u", &(fresh->Length.hours), &(fresh->Length.minutes), &(fresh->Length.seconds));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->Ordinal));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      sscanf(rx->subexps[13].value,"%d",&(fresh->SampleRate));
      sscanf(rx->subexps[14].value,"%d",&(fresh->BitsPerSample));
      sscanf(rx->subexps[15].value,"%d",&(fresh->ChannelCount));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_34*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetExtTracksByContributorForShare(df_connection *conn, int SearchNumber, char* Address, char* ShareAddress, int Type, char* Album, void (*s_callback)(df_search*), void (*callback)(type_34*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetExtTracksByContributorForShare %d \"%s\" \"%s\" %d \"%s\"]", SearchNumber, Address, ShareAddress, Type, Album);
}

static void GetExtAlbumsSearchPeople_handler(out_request *request, out_response *response, int num, void* context) {
	type_33 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_33));
      memset(fresh, 0, sizeof(type_33));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->PlaylistKey));
      fresh->Name= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->ArtistKey));
      fresh->ArtistName= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->IsAlbum));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      sscanf(rx->subexps[10].value,"%d",&(fresh->HitCount));
      sscanf(rx->subexps[11].value,"%d",&(fresh->ExtendedInfoAvail));
      sscanf(rx->subexps[12].value,"%d",&(fresh->Storage));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_33*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetExtAlbumsSearchPeople(df_connection *conn, int SearchNumber, char* SearchString, int SearchType, char* SortColumn, char* SortOrder, void (*s_callback)(df_search*), void (*callback)(type_33*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetExtAlbumsSearchPeople %d \"%s\" %d \"%s\" \"%s\"]", SearchNumber, SearchString, SearchType, SortColumn, SortOrder);
}

static void vTunerLookupById_handler(out_request *request, out_response *response, int num, void* context) {
	type_51 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_51));
      memset(fresh, 0, sizeof(type_51));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      fresh->Name= formatting_process(rx->subexps[3].value);
      sscanf(rx->subexps[4].value,"%d",&(fresh->NodeType));
      fresh->UrlBookmark= formatting_process(rx->subexps[5].value);
      fresh->UrlPlay= formatting_process(rx->subexps[6].value);
      fresh->UrlChildren= formatting_process(rx->subexps[7].value);
      fresh->UrlChildrenBackup= formatting_process(rx->subexps[8].value);
      fresh->ID= formatting_process(rx->subexps[9].value);
      fresh->Description= formatting_process(rx->subexps[10].value);
      fresh->ParentDescription= formatting_process(rx->subexps[11].value);
      fresh->Format= formatting_process(rx->subexps[12].value);
      fresh->Language= formatting_process(rx->subexps[13].value);
      fresh->City= formatting_process(rx->subexps[14].value);
      fresh->State= formatting_process(rx->subexps[15].value);
      fresh->Country= formatting_process(rx->subexps[16].value);
      fresh->Location= formatting_process(rx->subexps[17].value);
      sscanf(rx->subexps[18].value,"%d",&(fresh->Bandwidth));
      fresh->MimeType= formatting_process(rx->subexps[19].value);
      sscanf(rx->subexps[20].value,"%d",&(fresh->ReliabilityRating));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_51*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_vTunerLookupById(df_connection *conn, int SearchNumber, char* vTunerId, int vTunerLookupType, void (*s_callback)(df_search*), void (*callback)(type_51*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[vTunerLookupById %d \"%s\" %d]", SearchNumber, vTunerId, vTunerLookupType);
}

static void vTunerGetChildNodes_handler(out_request *request, out_response *response, int num, void* context) {
	type_51 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_51));
      memset(fresh, 0, sizeof(type_51));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      fresh->Name= formatting_process(rx->subexps[3].value);
      sscanf(rx->subexps[4].value,"%d",&(fresh->NodeType));
      fresh->UrlBookmark= formatting_process(rx->subexps[5].value);
      fresh->UrlPlay= formatting_process(rx->subexps[6].value);
      fresh->UrlChildren= formatting_process(rx->subexps[7].value);
      fresh->UrlChildrenBackup= formatting_process(rx->subexps[8].value);
      fresh->ID= formatting_process(rx->subexps[9].value);
      fresh->Description= formatting_process(rx->subexps[10].value);
      fresh->ParentDescription= formatting_process(rx->subexps[11].value);
      fresh->Format= formatting_process(rx->subexps[12].value);
      fresh->Language= formatting_process(rx->subexps[13].value);
      fresh->City= formatting_process(rx->subexps[14].value);
      fresh->State= formatting_process(rx->subexps[15].value);
      fresh->Country= formatting_process(rx->subexps[16].value);
      fresh->Location= formatting_process(rx->subexps[17].value);
      sscanf(rx->subexps[18].value,"%d",&(fresh->Bandwidth));
      fresh->MimeType= formatting_process(rx->subexps[19].value);
      sscanf(rx->subexps[20].value,"%d",&(fresh->ReliabilityRating));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_51*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_vTunerGetChildNodes(df_connection *conn, int SearchNumber, char* vTunerUrl, char* vTunerBackupUrl, void (*s_callback)(df_search*), void (*callback)(type_51*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[vTunerGetChildNodes %d \"%s\" \"%s\"]", SearchNumber, vTunerUrl, vTunerBackupUrl);
}

static void vTunerGetMostPlayed_handler(out_request *request, out_response *response, int num, void* context) {
	type_52 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_52));
      memset(fresh, 0, sizeof(type_52));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->Key));
      sscanf(rx->subexps[4].value,"%d",&(fresh->HitCount));
      sscanf(rx->subexps[5].value,"%u-%u-%u", &(fresh->LastPlayed.year), &(fresh->LastPlayed.month), &(fresh->LastPlayed.day));
      sscanf(rx->subexps[6].value,"%u-%u-%u", &(fresh->LastPlayedTime.hours), &(fresh->LastPlayedTime.minutes), &(fresh->LastPlayedTime.seconds));
      sscanf(rx->subexps[7].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->CreatedTime.hours), &(fresh->CreatedTime.minutes), &(fresh->CreatedTime.seconds));
      fresh->Name= formatting_process(rx->subexps[9].value);
      sscanf(rx->subexps[10].value,"%d",&(fresh->NodeType));
      fresh->UrlBookmark= formatting_process(rx->subexps[11].value);
      fresh->UrlPlay= formatting_process(rx->subexps[12].value);
      fresh->UrlChildren= formatting_process(rx->subexps[13].value);
      fresh->UrlChildrenBackup= formatting_process(rx->subexps[14].value);
      fresh->ID= formatting_process(rx->subexps[15].value);
      fresh->Description= formatting_process(rx->subexps[16].value);
      fresh->ParentDescription= formatting_process(rx->subexps[17].value);
      fresh->Format= formatting_process(rx->subexps[18].value);
      fresh->Language= formatting_process(rx->subexps[19].value);
      fresh->City= formatting_process(rx->subexps[20].value);
      fresh->State= formatting_process(rx->subexps[21].value);
      fresh->Country= formatting_process(rx->subexps[22].value);
      fresh->Location= formatting_process(rx->subexps[23].value);
      sscanf(rx->subexps[24].value,"%d",&(fresh->Bandwidth));
      fresh->MimeType= formatting_process(rx->subexps[25].value);
      sscanf(rx->subexps[26].value,"%d",&(fresh->ReliabilityRating));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_52*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_vTunerGetMostPlayed(df_connection *conn, int SearchNumber, int MaxRows, void (*s_callback)(df_search*), void (*callback)(type_52*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[vTunerGetMostPlayed %d %d]", SearchNumber, MaxRows);
}

static void vTunerGetLastPlayed_handler(out_request *request, out_response *response, int num, void* context) {
	type_52 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_52));
      memset(fresh, 0, sizeof(type_52));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->Key));
      sscanf(rx->subexps[4].value,"%d",&(fresh->HitCount));
      sscanf(rx->subexps[5].value,"%u-%u-%u", &(fresh->LastPlayed.year), &(fresh->LastPlayed.month), &(fresh->LastPlayed.day));
      sscanf(rx->subexps[6].value,"%u-%u-%u", &(fresh->LastPlayedTime.hours), &(fresh->LastPlayedTime.minutes), &(fresh->LastPlayedTime.seconds));
      sscanf(rx->subexps[7].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->CreatedTime.hours), &(fresh->CreatedTime.minutes), &(fresh->CreatedTime.seconds));
      fresh->Name= formatting_process(rx->subexps[9].value);
      sscanf(rx->subexps[10].value,"%d",&(fresh->NodeType));
      fresh->UrlBookmark= formatting_process(rx->subexps[11].value);
      fresh->UrlPlay= formatting_process(rx->subexps[12].value);
      fresh->UrlChildren= formatting_process(rx->subexps[13].value);
      fresh->UrlChildrenBackup= formatting_process(rx->subexps[14].value);
      fresh->ID= formatting_process(rx->subexps[15].value);
      fresh->Description= formatting_process(rx->subexps[16].value);
      fresh->ParentDescription= formatting_process(rx->subexps[17].value);
      fresh->Format= formatting_process(rx->subexps[18].value);
      fresh->Language= formatting_process(rx->subexps[19].value);
      fresh->City= formatting_process(rx->subexps[20].value);
      fresh->State= formatting_process(rx->subexps[21].value);
      fresh->Country= formatting_process(rx->subexps[22].value);
      fresh->Location= formatting_process(rx->subexps[23].value);
      sscanf(rx->subexps[24].value,"%d",&(fresh->Bandwidth));
      fresh->MimeType= formatting_process(rx->subexps[25].value);
      sscanf(rx->subexps[26].value,"%d",&(fresh->ReliabilityRating));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_52*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_vTunerGetLastPlayed(df_connection *conn, int SearchNumber, int MaxRows, void (*s_callback)(df_search*), void (*callback)(type_52*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[vTunerGetLastPlayed %d %d]", SearchNumber, MaxRows);
}

static void vTunerGetPresetChannels_handler(out_request *request, out_response *response, int num, void* context) {
	type_53 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_53));
      memset(fresh, 0, sizeof(type_53));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->Key));
      sscanf(rx->subexps[4].value,"%d",&(fresh->ChannelNumber));
      fresh->ChannelName= formatting_process(rx->subexps[5].value);
      sscanf(rx->subexps[6].value,"%u-%u-%u", &(fresh->Modified.year), &(fresh->Modified.month), &(fresh->Modified.day));
      sscanf(rx->subexps[7].value,"%u-%u-%u", &(fresh->ModifiedTime.hours), &(fresh->ModifiedTime.minutes), &(fresh->ModifiedTime.seconds));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->CreatedTime.hours), &(fresh->CreatedTime.minutes), &(fresh->CreatedTime.seconds));
      fresh->Name= formatting_process(rx->subexps[10].value);
      sscanf(rx->subexps[11].value,"%d",&(fresh->NodeType));
      fresh->UrlBookmark= formatting_process(rx->subexps[12].value);
      fresh->UrlPlay= formatting_process(rx->subexps[13].value);
      fresh->UrlChildren= formatting_process(rx->subexps[14].value);
      fresh->UrlChildrenBackup= formatting_process(rx->subexps[15].value);
      fresh->ID= formatting_process(rx->subexps[16].value);
      fresh->Description= formatting_process(rx->subexps[17].value);
      fresh->ParentDescription= formatting_process(rx->subexps[18].value);
      fresh->Format= formatting_process(rx->subexps[19].value);
      fresh->Language= formatting_process(rx->subexps[20].value);
      fresh->City= formatting_process(rx->subexps[21].value);
      fresh->State= formatting_process(rx->subexps[22].value);
      fresh->Country= formatting_process(rx->subexps[23].value);
      fresh->Location= formatting_process(rx->subexps[24].value);
      sscanf(rx->subexps[25].value,"%d",&(fresh->Bandwidth));
      fresh->MimeType= formatting_process(rx->subexps[26].value);
      sscanf(rx->subexps[27].value,"%d",&(fresh->ReliabilityRating));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_53*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_vTunerGetPresetChannels(df_connection *conn, int SearchNumber, void (*s_callback)(df_search*), void (*callback)(type_53*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[vTunerGetPresetChannels %d]", SearchNumber);
}

static void vTunerGetNodeFromPlayedUrl_handler(out_request *request, out_response *response, int num, void* context) {
	type_51 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_51));
      memset(fresh, 0, sizeof(type_51));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      fresh->Name= formatting_process(rx->subexps[3].value);
      sscanf(rx->subexps[4].value,"%d",&(fresh->NodeType));
      fresh->UrlBookmark= formatting_process(rx->subexps[5].value);
      fresh->UrlPlay= formatting_process(rx->subexps[6].value);
      fresh->UrlChildren= formatting_process(rx->subexps[7].value);
      fresh->UrlChildrenBackup= formatting_process(rx->subexps[8].value);
      fresh->ID= formatting_process(rx->subexps[9].value);
      fresh->Description= formatting_process(rx->subexps[10].value);
      fresh->ParentDescription= formatting_process(rx->subexps[11].value);
      fresh->Format= formatting_process(rx->subexps[12].value);
      fresh->Language= formatting_process(rx->subexps[13].value);
      fresh->City= formatting_process(rx->subexps[14].value);
      fresh->State= formatting_process(rx->subexps[15].value);
      fresh->Country= formatting_process(rx->subexps[16].value);
      fresh->Location= formatting_process(rx->subexps[17].value);
      sscanf(rx->subexps[18].value,"%d",&(fresh->Bandwidth));
      fresh->MimeType= formatting_process(rx->subexps[19].value);
      sscanf(rx->subexps[20].value,"%d",&(fresh->ReliabilityRating));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_51*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_vTunerGetNodeFromPlayedUrl(df_connection *conn, int SearchNumber, char* URLPlayed, void (*s_callback)(df_search*), void (*callback)(type_51*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[vTunerGetNodeFromPlayedUrl %d \"%s\"]", SearchNumber, URLPlayed);
}

static void GetStores_handler(out_request *request, out_response *response, int num, void* context) {
	type_54 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_54));
      memset(fresh, 0, sizeof(type_54));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->MusicStoreKey));
      fresh->Path= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->Local));
      fresh->IPAddress= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->Online));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      fresh->State= formatting_process(rx->subexps[10].value);
      sscanf(rx->subexps[11].value,"%d",&(fresh->Priority));
      sscanf(rx->subexps[12].value,"%u-%u-%u", &(fresh->LastConnected.year), &(fresh->LastConnected.month), &(fresh->LastConnected.day));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_54*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetStores(df_connection *conn, int SearchNumber, int IncludeReadOnly, int MusicStoreType, void (*s_callback)(df_search*), void (*callback)(type_54*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetStores %d %d %d]", SearchNumber, IncludeReadOnly, MusicStoreType);
}

static void GetStoreDetail_handler(out_request *request, out_response *response, int num, void* context) {
	type_56 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_56));
      memset(fresh, 0, sizeof(type_56));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->MusicStoreKey));
      fresh->Path= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->Local));
      fresh->IPAddress= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%d",&(fresh->Online));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->Created.year), &(fresh->Created.month), &(fresh->Created.day));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->LastModified.year), &(fresh->LastModified.month), &(fresh->LastModified.day));
      fresh->State= formatting_process(rx->subexps[10].value);
      sscanf(rx->subexps[11].value,"%d",&(fresh->Priority));
      sscanf(rx->subexps[12].value,"%u-%u-%u", &(fresh->LastConnected.year), &(fresh->LastConnected.month), &(fresh->LastConnected.day));
      fresh->Username= formatting_process(rx->subexps[13].value);
      fresh->Password= formatting_process(rx->subexps[14].value);
      sscanf(rx->subexps[15].value,"%u-%u-%u", &(fresh->LastScanned.year), &(fresh->LastScanned.month), &(fresh->LastScanned.day));
      fresh->SpaceUsed= formatting_process(rx->subexps[16].value);
      fresh->SpaceAvailable= formatting_process(rx->subexps[17].value);
      sscanf(rx->subexps[18].value,"%d",&(fresh->NumberOfAlbums));
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_56*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_GetStoreDetail(df_connection *conn, int SearchNumber, char* MusicStoreKey, void (*s_callback)(df_search*), void (*callback)(type_56*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[GetStoreDetail %d \"%s\"]", SearchNumber, MusicStoreKey);
}

static void MoveAlbumGetQueue_handler(out_request *request, out_response *response, int num, void* context) {
	type_57 *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(type_57));
      memset(fresh, 0, sizeof(type_57));

      sscanf(rx->subexps[2].value,"%d",&(fresh->SearchNumber));
      sscanf(rx->subexps[3].value,"%d",&(fresh->QueueKey));
      fresh->Status= formatting_process(rx->subexps[4].value);
      sscanf(rx->subexps[5].value,"%d",&(fresh->Retries));
      fresh->LastError= formatting_process(rx->subexps[6].value);
      sscanf(rx->subexps[7].value,"%u-%u-%u", &(fresh->CreatedDate.year), &(fresh->CreatedDate.month), &(fresh->CreatedDate.day));
      sscanf(rx->subexps[8].value,"%u-%u-%u", &(fresh->CreatedTime.hours), &(fresh->CreatedTime.minutes), &(fresh->CreatedTime.seconds));
      sscanf(rx->subexps[9].value,"%u-%u-%u", &(fresh->ModifiedDate.year), &(fresh->ModifiedDate.month), &(fresh->ModifiedDate.day));
      sscanf(rx->subexps[10].value,"%u-%u-%u", &(fresh->ModifiedTime.hours), &(fresh->ModifiedTime.minutes), &(fresh->ModifiedTime.seconds));
      sscanf(rx->subexps[11].value,"%u-%u-%u", &(fresh->LastRetryDate.year), &(fresh->LastRetryDate.month), &(fresh->LastRetryDate.day));
      sscanf(rx->subexps[12].value,"%u-%u-%u", &(fresh->LastRetryTime.hours), &(fresh->LastRetryTime.minutes), &(fresh->LastRetryTime.seconds));
      sscanf(rx->subexps[13].value,"%d",&(fresh->AlbumKey));
      sscanf(rx->subexps[14].value,"%d",&(fresh->StoreKey));
      fresh->AlbumName= formatting_process(rx->subexps[15].value);
      
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, type_57*, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_MoveAlbumGetQueue(df_connection *conn, int SearchNumber, void (*s_callback)(df_search*), void (*callback)(type_57*, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[MoveAlbumGetQueue %d]", SearchNumber);
}

