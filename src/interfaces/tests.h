/*
 *  tests.h
 *  libdigifi.new
 *
 *  Created by Tom Booth on 10/04/2010.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

#ifndef TESTS_H
#define TESTS_H

#include <pthread.h>
#include "DigiFi.h"


void main_conn_test(pthread_mutex_t *parent_lock);
void main_func_test(pthread_mutex_t *parent_lock);
void rget_test(pthread_mutex_t *parent_lock);
void misc_test(pthread_mutex_t *parent_lock);
void search_test(pthread_mutex_t *parent_lock);



#endif