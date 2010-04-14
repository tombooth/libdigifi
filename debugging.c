/*
 *  debugging.c
 *  libdigifi.new
 *
 *  Created by Tom Booth on 14/04/2010.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */


#include "debugging.h"

char *debugging_get_error_string(int err) {
	char *error_string;
	switch (errno) {
		case EAGAIN:
			error_string = "[EAGAIN] No data was avaliable for reading";
			break;
		case EBADF:
			error_string = "[EBADF] Not a valid file descriptor";
			break;
		case EFAULT:
			error_string = "[EFAULT] Buffer is outside accessible address space";
			break;
		case EIO:
			error_string = "[EIO] IO Error";
			break;
		case EINTR:
			error_string = "[EINTR] Interrupted by signal";
			break;
		case EINVAL:
			error_string = "[EINVAL] File descriptor unsuitable for reading";
			break;
		case EISDIR:
			error_string = "[EISDIR] File descriptor is a directory";
			break;
		default:
			error_string = "Unknown error";
			break;
	}
	return error_string;
}