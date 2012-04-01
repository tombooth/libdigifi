
/*
 *  regex_list.c
 *  libdigifi.new
 *
 *  Created by Tom Booth on 09/04/2010.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

#include "../api/regex_list.h"

#include <string.h>

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

   <% get_commands.forEach(function get_regexps(c) { %>
   else if (strcmp(regex_name, "<%=c.name%>") == 0) {
      pattern = "<%=c.name%>[[:space:]+]<%= util.to_regexp(c.out_type)%>";
   }
   <% }); %>

   <% set_commands.forEach(function set_regexps(c) { %>
   else if (strcmp(regex_name, "<%=c.name%>") == 0) {
      pattern = "<%=c.name%><% if (c.out_type) { %>[[:space:]+]<%= util.to_regexp(c.out_type)%><% } %>";
   }
   <% }); %>

   <% row_commands.forEach(function row_regexps(c) { %>
   else if (strcmp(regex_name, "<%=c.name%>") == 0) {
      pattern = "Record[[:space:]+]<%= util.to_regexp(c.row_type)%>";
   }
   <% }); %>

   return pattern;

}
