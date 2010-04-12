/*
 *  extraction.h
 *  libdigifi.new
 *
 *  Created by Tom Booth on 08/04/2010.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */




#ifndef EXTRACTION_H
#define EXTRACTION_H


#include "regex_wrapper.h"
#include "charbuffer.h"


typedef struct {
	int is_error;
	regex_result *result;
} extraction_result;



extraction_result* extraction_run(int fd, cbuf *buffer, regex_t *regex, regex_t *error_regex);

void extraction_free_result(extraction_result *result);




#endif