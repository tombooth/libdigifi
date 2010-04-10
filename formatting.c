/*
 *  formatting.c
 *  libdigifi.new
 *
 *  Created by Tom Booth on 08/04/2010.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

#include "formatting.h"

#include <stdlib.h>
#include <string.h>

struct formatting_rule {
	char *pattern;
	char *replacement;
};


static struct formatting_rule *rules;
static unsigned int num_rules;


static char* formatting_replace(char* string, char* sub_string, char* replacement);



void formatting_init() {
	rules = NULL;
	num_rules = 0;
}


void formatting_add_rule(char *pattern, char *replacement) {
	num_rules++;
	rules = realloc(rules, sizeof(struct formatting_rule) * num_rules);
	rules[num_rules - 1].pattern = strdup(pattern);
	rules[num_rules - 1].replacement = strdup(replacement);

}



char* formatting_process(char *input) {
	/*int i;
	char *in, *out;
	
	in = input;
	for (i = 0; i < num_rules; i++) {
		out = formatting_replace(in, rules[i].pattern, rules[i].replacement);
		
		if (i > 0) free(in);
		in = out;
	}
	
	return out;*/
	return strdup(input);
}


void formatting_destroy() {
	if (num_rules > 0) free(rules);
	num_rules = 0;
}





static char* formatting_replace(char* string, char* sub_string, char* replacement) {
	char* tmp_string;
	int p_len;
	int altered = 0;
	
	char* out = malloc(0);
	while((tmp_string = strstr(string,sub_string))){
		altered = 1;
		
		p_len = strlen(out);
		out = realloc(out, p_len + tmp_string-string + strlen(replacement) + 1);
		out[strlen(out)] = '\0';
		strncpy(out+p_len,string,tmp_string-string);
		strcat(out,replacement);
		tmp_string+=strlen(sub_string);
		string=tmp_string;
	}
	
	return (altered == 0) ? strdup(string) : (string == NULL) ? out : strcat(out,string);
}


