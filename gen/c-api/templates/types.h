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

<% types.forEach(function(type) { %>
typedef struct {
   <% type.sub_types.forEach(function(subtype) { %>
   <%=subtype.type%> <%=subtype.name%>
   <% }); %>
} <%=type.name%>;

void <%=type.name%>_free(<%=type.name%>* ptr) {
   if (ptr == NULL) { return; }
   else {
      <% type.sub_types.forEach(function(subtype) { %>
      free(ptr-><%=subtype.name%>);
      <% }); %>
      free(ptr);
   }
}
<% }); %>

#endif
