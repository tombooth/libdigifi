/*
 *  regex_wrapper.h
 *  libdigifi.new
 *
 *  Created by Tom Booth on 08/04/2010.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */


#ifndef REGEXWRAPPER_H
#define REGEXWRAPPER_H

//#include <regex.h>
#include "../../ext/pcre/pcreposix.h"
#include "rbst.h"
#include "../api/regex_list.h"

typedef struct {
	unsigned int start;
	unsigned int length;
	
	char *value;
} regex_subexpression;

typedef struct {
	unsigned int start;
	unsigned int length;
	
	char *value;
	
	unsigned int num_subexps;
	regex_subexpression* subexps;
} regex_result;




void regex_init();

char *regex_get_error();

regex_t* regex_get_compiled(char *name);

regex_t* regex_compile(char *pattern);

regex_result* regex_match(regex_t *regex, char *string);

void regex_free_result(regex_result* result);

void regex_destroy();



#endif
