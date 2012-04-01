/*
 *  types.h
 *  libdigifi.new
 *
 *  Created by Tom Booth on 09/04/2010.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */
 
 
#ifndef TYPES_H
#define TYPES_H
 

#include <stdlib.h>
 
typedef enum {
    DF_STORAGE_UNKNOWN = 0,
    DF_STORAGE_SERVER = 1,
    DF_STORAGE_NETWORK = 2,
    DF_STORAGE_PORTABLE = 3
} df_storagetype;
 
 
typedef struct {
    unsigned int hours;
    unsigned int minutes;
    unsigned int seconds;
} df_time;
 
typedef struct {
    unsigned int year;
    unsigned int month;
    unsigned int day;
} df_date;

typedef struct {
	int key;
	char *name;
	int albumkey;
	char *albumname;
	int artistkey;
	char *artistname;
	int genrekey;
	char *genrename;
	df_time *length;
	int source;
	char *path;
    int capabilities;
    char *streamid;
} df_detailedtrack;

typedef struct {
	char *name;
	int source;
	char *path;
    int capabilities;
    char *streamid;
} df_trackname;

<% types.forEach(function(type) { %>

<% if (type.type === 'Compound') { %>

<% if (type.is_row) { %>

struct __<%=type.name%> {
   struct __<%=type.name%> *next;

   <% type.sub_types.forEach(function(subtype) { %>
      <%=util.to_c_type(subtype)%> <%=subtype.name%>;<% }); %>
};

typedef struct __<%=type.name%> <%=type.name%>;

<% } else { %>

typedef struct {
   <% type.sub_types.forEach(function(subtype) { %>
      <%=util.to_c_type(subtype)%> <%=subtype.name%>;<% }); %>
} <%=type.name%>;

<% } %>

<%
var types_to_free = type.sub_types.filter(function(s) { return (s.type === 'String'); });

if (types_to_free.length > 0) {

%>void <%=type.name%>_free(<%=type.name%>* ptr) {
   if (ptr == 0) { return; }
   else {
      <% types_to_free.forEach(function(subtype) { %>
      free(ptr-><%=subtype.name%>);<% }); %>
      free(ptr);
   }
}
<% } %>

<% } %>

<% }); %>

#endif
