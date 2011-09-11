/*
 *	dfsearchpacket.h
 *	© 2009 DigiFi Limited
 *
 *	The definition for the search packet creator
 *
 */

#ifndef DFSEARCHPACKET_HEADER
#define DFSEARCHPACKET_HEADER

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdint.h>
#include <string.h>


// headers of the packet and fields
typedef struct {
	uint16_t type;
	uint8_t data_type;
	uint16_t length;
} df_searchfield_header;


typedef struct {
	char id[4];
	uint8_t field_count;
} df_searchpacket_header;

struct __df_searchfield {
	df_searchfield_header header;
	
	void *value;
	int int_value;
	
	struct __df_searchfield *next;
};

struct __df_searchpacket {
	df_searchpacket_header header;
	
	struct __df_searchfield *fields;
};

typedef struct __df_searchfield df_searchfield;
typedef struct __df_searchpacket df_searchpacket;




void* dfsearchpacket_create(int port, int* length);

df_searchpacket* dfsearchpacket_read(void *data, int length);

void dfsearchpacket_inspect(df_searchpacket *read);
	
#ifdef __cplusplus
}
#endif

#endif