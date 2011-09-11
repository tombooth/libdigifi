/*
 *  debugging.h
 *  libdigifi.new
 *
 *  Created by Tom Booth on 10/04/2010.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */


#ifndef DEBUGGING_H
#define DEBUGGING_H


#include <stdio.h>
#include <errno.h>

// #define DEBUG

#ifdef DEBUG
#define DFDEBUG(...) { printf("%s:%d %s() ", __FILE__, __LINE__, __func__); printf(__VA_ARGS__); printf("\n"); }
//#define DFDEBUG(...) { FILE *fd = fopen("/tmp/df.log","at"); fprintf(fd, "%s:%d %s() ", __FILE__, __LINE__, __func__); fprintf(fd, __VA_ARGS__); fprintf(fd, "\n"); fclose(fd); }
//#define DFDEBUG(...) { FILE *fd = stdout; fprintf(fd, "%s:%d %s() ", __FILE__, __LINE__, __func__); fprintf(fd, __VA_ARGS__); fprintf(fd, "\n"); }
#define DFERROR(...) { printf("%s:%d %s() ERROR ", __FILE__, __LINE__, __func__); printf(__VA_ARGS__); printf("\n"); }
//#define DFERROR(...) { FILE *fd = fopen("/tmp/df.log","at"); fprintf(fd, "%s:%d %s() ERROR ", __FILE__, __LINE__, __func__); fprintf(fd, __VA_ARGS__); fprintf(fd, "\n"); fclose(fd); }
//#define DFERROR(...) { FILE *fd = stdout; fprintf(fd, "%s:%d %s() ERROR ", __FILE__, __LINE__, __func__); fprintf(fd, __VA_ARGS__); fprintf(fd, "\n"); }
#else
#define DFDEBUG(...) ;
#define DFERROR(...) ;
#endif


#endif