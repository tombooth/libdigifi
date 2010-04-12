/*
 *  formatting.c
 *  libdigifi.new
 *
 *  Created by Tom Booth on 08/04/2010.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

#include "formatting.h"

#include "regex_wrapper.h"

#include "debugging.h"

#include <stdlib.h>
#include <string.h>

struct formatting_rule {
	regex_t *pattern;
	char *replacement;
};


static struct formatting_rule *rules;
static unsigned int num_rules;


static char* formatting_execute_rule(char *string, regex_t *rule, char *replacement);


void formatting_init() {
	rules = NULL;
	num_rules = 0;
}


void formatting_add_rule(char *pattern, char *replacement) {
	regex_t *regex;
	
	DFDEBUG("Adding pattern %s as a rule", pattern);
	
	regex = regex_compile(pattern);
	if (regex == NULL) { DFERROR("Failed to compile: %s", pattern, regex_get_error()); return; }
	
	num_rules++;
	rules = realloc(rules, sizeof(struct formatting_rule) * num_rules);
	rules[num_rules - 1].pattern = regex;
	rules[num_rules - 1].replacement = strdup(replacement);

}



char* formatting_process(char *input) {
	char *result, *holder;
	int i;
	
	result = strdup(input);
	for (i = 0; i < num_rules; i++) {
		holder = formatting_execute_rule(result, rules[i].pattern, rules[i].replacement);
		free(result);
		result = holder;
	}

	return result;
}


void formatting_destroy() {
	if (num_rules > 0) free(rules);
	num_rules = 0;
}


static char* formatting_execute_rule(char *string, regex_t *rule, char *replacement) {
	regex_result *rx;
	char *result, *holder;
	int length;

	result = strdup(string);
	while ((rx = regex_match(rule, result)) != NULL) {
		//DFDEBUG("Rule matched: %s", result);
		length = strlen(result);
		holder = (char *) malloc(length); // reduction by one inherant in the strlen missing out the null terminator
		strncpy(holder, result, rx->start);
		strncpy(holder + rx->start, result + rx->start + 1, length - (rx->start + 1));
		free(result);
		regex_free_result(rx);
		holder[length -1] = '\0';
		result = holder;
	}
	
	return result;
}




