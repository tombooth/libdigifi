/*
 *  client.h
 *  libdigifi.new
 *
 *  Created by Tom Booth on 09/04/2010.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */


#ifndef CLIENT_H
#define CLIENT_H

#include "../api-impl/types.h"
#include "../comms/comm_manager.h"

typedef connection df_connection;


int df_init();


df_connection * df_connect(char *ipaddress, int connections);

void df_disconnect(df_connection *conn);


void df_destroy();

void dferrors_register_errorcallback(void (*callback)(int, char*));

void dferrors_register_debugcallback(void (*callback)(char*));


#endif
