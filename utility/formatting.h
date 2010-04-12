/*
 *  formatting.h
 *  libdigifi.new
 *
 *  Created by Tom Booth on 08/04/2010.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */


#ifndef FORMATTING_H
#define FORMATTING_H


void formatting_init();

void formatting_add_rule(char *pattern, char *replacement);

char* formatting_process(char *input);

void formatting_destroy();



#endif
