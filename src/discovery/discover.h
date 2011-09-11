/*
 *	dfsearchpacket.h
 *	© 2009 DigiFi Limited
 *
 *	The definition for the digifi discover code
 *
 */

#ifndef DFDISCOVER_HEADER
#define DFDISCOVER_HEADER

#ifdef __cplusplus
extern "C" {
#endif

	struct __df_server {
		char *name;
		char *version;
		char *address;
		
		struct __df_server *next;
	};
	
	typedef struct __df_server df_server;

	int df_discover(int wait_period, void (*callback)(df_server *, void*), void *context);
	
#ifdef __cplusplus
}
#endif

#endif