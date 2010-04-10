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

int df_init() {
	comm_start(3, process_incoming_rget);
	
	// setup formatting
	formatting_init();
	formatting_add_rule("\\\"", "\"");
	
	return 0;
}


df_connection * df_connect(char *ipaddress, int connections) {
	return comm_connect(ipaddress, connections);
}

void df_disconnect(df_connection *conn) {
	comm_disconnect(conn);
}


void df_destroy() {
	comm_stop();
	formatting_destroy();
}



