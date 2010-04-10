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


/*!
 List all defined rooms
 LocalOnly: If true then only return rooms local to the host running Sophia
 */
int df_GetRooms(df_connection *conn, int LocalOnly, void (*callback)(int, df_roomrow*, void*), void *context);






#endif




