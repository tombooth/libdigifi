/*
 *  regex_wrapper.c
 *  libdigifi.new
 *
 *  Created by Tom Booth on 08/04/2010.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

#include "regex_wrapper.h"

#include <stdlib.h>
#include <string.h>

#define LAST_ERROR_LENGTH 50
static char last_error[LAST_ERROR_LENGTH];


void regex_init() {
	
}



regex_t* regex_get_compiled(char *name) {
	regex_t *rx_compiled;
	int err;
	char *regex;
	
	if (rbst_get(name, (void**)&rx_compiled) < 0) {
		if ((rx_compiled = malloc(sizeof(regex_t))) == NULL) { return NULL;}
		
		regex = regex_list_get(name);
		if (regex== NULL) { free(rx_compiled);  return NULL; }
		
		
		err = regcomp(rx_compiled, regex, REG_EXTENDED);
		if (err!=0) { 
			regerror(err, rx_compiled, last_error, LAST_ERROR_LENGTH); 
			free(rx_compiled); 
			return NULL;
		}
		
		rbst_add(name, rx_compiled);
		
	}
	
	return rx_compiled;
}



regex_result* regex_match(regex_t *regex, char *string) {
	regmatch_t *match;
	regex_result *result;
	int err;
	unsigned int i;
	
	result = NULL;
	
	// setup match to hold as many sub exps as there are
	if ((match = calloc(regex->re_nsub+1, sizeof(regmatch_t))) == NULL) { return NULL; }
	
	err = regexec(regex, string, regex->re_nsub+1, match, 0);
	
	if (err != 0) {
		regerror(err, regex, last_error, LAST_ERROR_LENGTH);
		free(match);
		
		return NULL;
	}
	
	if ((result = malloc(sizeof(regex_result))) == NULL) { return NULL; }
	
	result->start = match[0].rm_so;
	result->length = match[0].rm_eo - match[0].rm_so;
	
	if ((result->value = malloc((result->length+1) * sizeof(char))) == NULL) { return NULL; }
	strncpy(result->value, string+(result->start*sizeof(char)), (size_t)result->length);
	result->value[result->length] = '\0';
	
	result->num_subexps = regex->re_nsub+1;
	if ((result->subexps = malloc(sizeof(regex_subexpression) * (regex->re_nsub+1))) == NULL) { return NULL; }
	
	
	for (i=0; i<(regex->re_nsub+1); i++) {
		result->subexps[i].start = match[i].rm_so;
		result->subexps[i].length = match[i].rm_eo - match[i].rm_so;
		
		if ((result->subexps[i].value = malloc((result->subexps[i].length+1) * sizeof(char))) == NULL) { return NULL; }
		strncpy(result->subexps[i].value, string+(result->subexps[i].start*sizeof(char)), result->subexps[i].length);
		result->subexps[i].value[result->subexps[i].length] = '\0';
	}
	
	free(match);
	
	return result;
}



void regex_free_result(regex_result* result) {
	unsigned int i;
	
	if (result == NULL) return;
	
	for (i=0; i<result->num_subexps; i++) {
		free(result->subexps[i].value);
	}
	
	free(result->value);
	free(result->subexps);
	free(result);
}



void regex_destroy() {
	
}





