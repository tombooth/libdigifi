/*
 *  extraction.c
 *  libdigifi.new
 *
 *  Created by Tom Booth on 08/04/2010.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

#include "extraction.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "debugging.h"

#define READ_AMMOUNT 64


static extraction_result* extraction_check_buffer(cbuf *buffer, regex_t *regex, regex_t *error_regex);


extraction_result* extraction_run(int fd, cbuf *buffer, regex_t *regex, regex_t *error_regex, timing_obj *tmr) {
	extraction_result *result;
	void *byte_buffer;
	int bytes_read;
	
	// check whether there is a match in the buffer as is
	result = extraction_check_buffer(buffer, regex, error_regex);
	
	byte_buffer = malloc(READ_AMMOUNT);
	
	while (result == NULL) {
		// set buffer to null
		memset((void*)byte_buffer, 0, READ_AMMOUNT);
		
		// read from the file descriptor into the buffer
		bytes_read = read(fd, byte_buffer, READ_AMMOUNT);
		if (bytes_read <= 0) {
			if (errno == EAGAIN) {			// ignore a non-blocking return error as we can expect this occasionally or when somethings screwed up
				usleep(NON_BLOCKING_READ_WAIT);
			} else {
				// an error has occurred
				DFERROR("An error occured will trying to read from fd:%d [%d] %s", fd, errno, debugging_get_error_string(errno));
			}
		}
		else {
			cbuf_append(buffer, byte_buffer, bytes_read);
		
			// check the buffer now
			result = extraction_check_buffer(buffer, regex, error_regex);
		}
		
		if (tmr!=NULL && timing_has_elapsed(tmr)) break;
	}
	
	free(byte_buffer);
	
	return result;
}


void extraction_free_result(extraction_result *result) {
	if (result == NULL) return;
	regex_free_result(result->result);
	free(result);
}





static extraction_result* extraction_check_buffer(cbuf *buffer, regex_t *regex, regex_t *error_regex) {
	extraction_result *result;
	regex_result *rx_result;
	char *temp;
	int is_error = 0;
	
	rx_result = regex_match(regex, buffer->data);
	if (rx_result == NULL && error_regex != NULL) {
		is_error = 1;
		rx_result = regex_match(error_regex, buffer->data);
	}
	
	result = NULL;
	if (rx_result != NULL) {
		result = malloc(sizeof(extraction_result));
		result->is_error = is_error;
		result->result = rx_result;
		
		temp = cbuf_extract(buffer, rx_result->start, rx_result->length);
		if (temp != NULL) free(temp);
	}
	
	
	return result;
}






