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


<% function print_command(c) { %>
static void <%=c.name%>_handler(out_request *request, out_response *response, int num, void* context) {
	int tmp;
	regex_result *rx;
	struct call_holder *holder = context;


	if (response==0) { return; }


	rx = response->result->result;
		sscanf(rx->subexps[2].value,"%d",&(tmp));

	((void (*)(int, void*))(holder->callback))(tmp, holder->context);

}

int df_<%=c.name%>(df_connection *conn, <%= c.c.in_arguments%>void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "<%=c.name%>", 1, <%=c.name%>_handler, c, "[<%=c.name%><%=c.c.in_fmt_string%>]"<%=c.c.in_fmt_arguments%>);
}
<% } %>


<% function print_get_set_command(util, c) {
   if (c.out_type) {
%>static void <%=c.name%>_handler(out_request *request, out_response *response, int num, void* context) {
	struct call_holder *holder = context;
	<%=util.to_c_type(c.out_type)%> tmp;
	regex_result *rx;

	if (response==0) { return; }

	rx = response->result->result;

   <% if (c.out_type.type === 'Compound') { 
   %>tmp = malloc(sizeof(<%=c.out_type.name%>));
   memset(tmp, 0, sizeof(<%=c.out_type.name%>));<% 
   } %>

   <% c.out_type.sub_types.forEach(function(type, i) { 
   %><%=util.to_extraction("tmp", 2, c.out_type.type === 'Compound', type, i)%>
   <%
   }); %>
	((void (*)(<%= util.to_c_type(c.out_type)%>, void*))(holder->callback))(tmp, holder->context);
   free(holder);

} 

int df_<%=c.name%>(df_connection *conn, <%= c.c.in_arguments%>void (*callback)(<%= util.to_c_type(c.out_type)%>, void*), void *context) {
	struct call_holder *c;

	c = malloc(sizeof(struct call_holder)); c->callback = (void (*)(void))callback; c->context = context;

	return comm_send(conn, 0, "<%=c.name%>", 1, <%=c.name%>_handler, c, "[<%=c.name%><%=c.c.in_fmt_string%>]"<%=c.c.in_fmt_arguments%>);
}
<% } else { %>
int df_<%=c.name%>(df_connection *conn) {
	return comm_send(conn, 0, "void", 1, 0, 0, "[<%=c.name%>]");
}
<% } %>

<% } %>


<% get_commands.forEach(print_get_set_command.bind(this, util)); %>
<% set_commands.forEach(print_get_set_command.bind(this, util)); %>

<% row_commands.forEach(function print_command(c) { %>
static void <%=c.name%>_handler(out_request *request, out_response *response, int num, void* context) {
	<%=c.row_type.name%> *base = 0, *current = 0, *fresh = 0; 
	struct call_holder *holder = context;
	regex_result *rx;
   int i;

	if (response==0) { return; }

   for (i = 0; i < num; i++) {
      rx = response[i].result->result;

      fresh = malloc(sizeof(<%=c.row_type.name%>));
      memset(fresh, 0, sizeof(<%=c.row_type.name%>));

      <% c.row_type.sub_types.forEach(function(type, i) { 
      %><%=util.to_extraction("fresh", 2, c.row_type.type === 'Compound', type, i)%>
      <%
      }); %>
      fresh->next = 0;

      if (i==0) { base = current = fresh; }
		else { current->next = fresh; current = fresh; }
   }

   ((void (*)(int, <%= util.to_c_type(c.row_type)%>, void*))(holder->callback))(num, base, holder->context);
	free(holder);
}

int df_<%=c.name%>(df_connection *conn, <%= c.c.in_arguments%>void (*s_callback)(df_search*), void (*callback)(<%= util.to_c_type(c.row_type)%>, void*), void *context) {
   int search_num;
	struct search_call_holder *c;

   search_num = allocator_get();

	c = malloc(sizeof(struct search_call_holder)); c->callback = s_callback; c->call.context = context; c->call.callback = (void (*)(void))callback;

	return comm_send(conn, 0, "rowrequest", 1, create_search_struct, (void *)c, "[<%=c.name%><%=c.c.in_fmt_string%>]"<%=c.c.in_fmt_arguments%>);
}
<% }) %>
