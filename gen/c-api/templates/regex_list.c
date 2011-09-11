
/*
 *  regex_list.c
 *  libdigifi.new
 *
 *  Created by Tom Booth on 09/04/2010.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

#include "regex_list.h"

#include "string.h"

char* regex_list_get(char *regex_name) {
	char *pattern;

	if (strcmp(regex_name, "void") == 0) {
		pattern="\\[(.+)\\]";
	}
	else if (strcmp(regex_name, "error") == 0) {
		pattern = "\\[ERR (.+)\\]";
	}
	else if (strcmp(regex_name, "findname") == 0) {
		pattern = "\\[([^[:space:]]+)[[:space:]+](.+)[^\\\\]\\]";
	}
	else if (strcmp(regex_name, "rowrequest") == 0) {
		pattern = "\\[ACK[[:space:]+]([^[:space:]]+)[[:space:]+]([0-9]+)[[:space:]+]\"([0-9]+)\"\\]";
	}
	else if (strcmp(regex_name, "rowrequestroom") == 0) {
		pattern = "\\[ACK[[:space:]+]([^[:space:]]+)[[:space:]+]([0-9]+)[[:space:]+]([0-9]+)[[:space:]+]\"([0-9]+)\"\\]";
	}

   <% get_commands.forEach(function(c) { %>
   else if (strcmp(regex_name, "<%=c.name%>") == 0) {
      pattern = "<%=c.name%>";
   }
   <% }); %>

   <% set_commands.forEach(function(c) { %>
   else if (strcmp(regex_name, "<%=c.name%>") == 0) {
      pattern = "<%=c.name%>";
   }
   <% }); %>

   <% row_commands.forEach(function(c) { %>
   else if (strcmp(regex_name, "<%=c.name%>") == 0) {
      pattern = "Record";
   }
   <% }); %>

   return pattern;

}