/*
 *  comm_manager.h
 *  libdigifi.new
 *
 *  Created by Tom Booth on 09/04/2010.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */



#ifndef COMMMANAGER_H
#define COMMMANAGER_H


#include "comm_in.h"
#include "comm_out.h"



#define SOPHIA_PORT 2921
#define RGET_PORT_BASE 27374


typedef struct {
	char *label;
	int connected;
	
	out_socket *sockets;
	int num_sockets;
	
	in_settings rget_settings;
	
} connection;




void comm_start(int outgoing_threads, void (*rget_callback)(in_settings*, char*, char*));

connection *comm_connect(char *ipaddress, int connections);

int comm_send(connection *conn, int rget, char *tag, int count, void (*callback)(out_request*, out_response*, int, void*), void *context, char *message, ...);
int comm_send_via_socket(out_socket *socket, char *tag, int count, void (*callback)(out_request*, out_response*, int, void*), void *context, char *message, ...);

void comm_disconnect(connection *conn);

void comm_stop();








#endif



