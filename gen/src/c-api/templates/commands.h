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

#include "../api/client.h"

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
<% function print_prototypes(util, type_var, c) { 
   %>
/*!
  <%=c.description%>
  <% c.in && c.in.forEach(function(t) { %>
  <%= t.name%>: <%= t.description %><% }); %>
*/<%
   if (! ( c.row_type || c.out_type )) { %>
int df_<%=c.name%>(df_connection *conn);<%
   } else if (c.row_type) { %>
int df_<%=c.name%>(df_connection *conn, <%= c.c.in_arguments%>void (*s_callback)(df_search*), void (*callback)(<%= util.to_c_type(c.row_type)%>, void*), void *context); <%
   } else { %>
int df_<%=c.name%>(df_connection *conn, <%= c.c.in_arguments%>void (*callback)(<%= util.to_c_type(c.out_type)%>, void*), void *context); <%
   } %>
<%}%>

<% get_commands.forEach(print_prototypes); %>
<% set_commands.forEach(print_prototypes); %>
<% row_commands.forEach(print_prototypes); %>


#endif
