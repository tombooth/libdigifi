/*
 *  commands.h
 *  libdigifi.new
 *
 *  Created by Tom Booth on 09/04/2010.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */


#ifndef COMMANDS_H
#define COMMANDS_H

#include "client.h"

typedef struct {
  out_socket *socket;
  int id;
  int count;
  char *name;
  
  void (*callback)(void);
  void *context;
} df_search;

int df_extract_from(df_search *, int start, int end);
void df_free_search(df_search *);

// Generated functions
//
<% function print_prototypes(c) { %>
/*!
  <%=c.description%>
*/
int df_<%= c.name %>(df_connection *conn, int TimeoutPerHost, void (*callback)(int, void*), void *context);
<%}%>

<% get_commands.forEach(print_prototypes); %>
<% set_commands.forEach(print_prototypes); %>
<% row_commands.forEach(print_prototypes); %>
