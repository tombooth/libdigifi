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


struct call_holder {
	void (*callback)(void);
	void *context;
};


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




/*
 Handlers
 */


static void GetRooms_handler(out_request *request, out_response *response, int num, void *context) {
	df_roomrow *base, *current, *fresh;
	regex_result *rx;
	struct call_holder *holder = context;
	int i;
	
	for (i=0; i<num; i++) {
		rx = response[i].result->result;
		fresh = malloc(sizeof(df_roomrow));
		
		sscanf(rx->subexps[3].value,"%d",&(fresh->RoomKey));
		fresh->IPAddress = formatting_process(rx->subexps[4].value);
		sscanf(rx->subexps[5].value,"%d",&(fresh->Channel));
		fresh->Name = formatting_process(rx->subexps[6].value);
		fresh->ShortName = formatting_process(rx->subexps[7].value);
		sscanf(rx->subexps[8].value,"%d",&(fresh->IsMultiRoom));
		sscanf(rx->subexps[9].value,"%d",&(fresh->PlaybackCapability));
		sscanf(rx->subexps[10].value,"%d",&(fresh->RippingCapability));
		sscanf(rx->subexps[11].value,"%d",&(fresh->MusicManagementCapability));
		sscanf(rx->subexps[12].value,"%d",&(fresh->RoomID));
		fresh->HostName = formatting_process(rx->subexps[13].value);
		fresh->next = NULL;
		
		if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
	}
	
	((void (*)(int, df_roomrow*, void*))(holder->callback))(num, base, holder->context);
	
}



/*
 Core handler
 */

static void row_handler(out_request *request, out_response *response, int num, void *context) {
	if (strcmp(request->tag, "GetRooms") == 0) {
		GetRooms_handler(request, response, num, context);
	}
}










/*
 Front facing functions
 */

int df_GetRooms(df_connection *conn, int LocalOnly, void (*callback)(int, df_roomrow*, void*), void *context) {
	int search_num;
	struct call_holder *c;
	
	search_num = allocator_get();
	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;
	return comm_send(conn, 0, "rowrequest", 1, pull_rows, (void*)c, "[GetRooms %d %d]", search_num, LocalOnly);
}














