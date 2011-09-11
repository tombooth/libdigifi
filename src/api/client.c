/*
 *  client.c
 *  libdigifi.new
 *
 *  Created by Tom Booth on 09/04/2010.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

#include "client.h"
#include "rgets.h"
#include "formatting.h"
#include "debugging.h"

int df_init() {
	
	DFDEBUG("Starting init");
	
	comm_start(2, process_incoming_rget);
	
	// setup formatting
	formatting_init();
	formatting_add_rule("\\\\[\\[\\]\"]", "\"");
	
	DFDEBUG("Finished init");
	
	return 0;
}


df_connection * df_connect(char *ipaddress, int connections) {
	DFDEBUG("Connection to %s", ipaddress);
	return comm_connect(ipaddress, connections);
}

void df_disconnect(df_connection *conn) {
	DFDEBUG("Disconnecting from %s", conn->label);
	comm_disconnect(conn);
}


void df_destroy() {
	DFDEBUG("called");
	comm_stop();
	formatting_destroy();
}


void dferrors_register_errorcallback(void (*callback)(int, char*)) {
	DFDEBUG("called");
}

void dferrors_register_debugcallback(void (*callback)(char*)) {
	DFDEBUG("called");
}
