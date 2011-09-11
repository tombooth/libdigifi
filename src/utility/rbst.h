//************************************************************************
//     rbst.h
//     2009 © Tom Booth
//
//     Definition for a generic random binary search tree
//     
//
//************************************************************************

#ifndef RBST_HEADER
#define RBST_HEADER

#ifdef __cplusplus
extern "C" {
#endif

// list of errors
#define RBST_ENOTFOUND			-1
#define RBST_EALREADYCACHED		-2
#define RBST_EADDFAILED			-3
#define RBST_ENOMEM				-10003

//#define RBST_DEBUG 0


int rbst_get(char* key, void** value);

int rbst_add(char* key, void* value);

void rbst_free(void);

void rbst_dump(void);

#ifdef __cplusplus
}
#endif
	

#endif