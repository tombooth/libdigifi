/*
 *	dfsearchpacket.c
 *	© 2009 DigiFi Limited
 *
 *	The creator and reader of df_searchpackets
 *
 */

#include "searchpacket.h"
#include <stdio.h>

typedef enum {
	fieldtype_servicename = 0,
	fieldtype_packettype = 1,
	fieldtype_filename = 2,
	fieldtype_filesize = 3,
	fieldtype_hostaddress = 4,
	fieldtype_subnetmask = 5,
	fieldtype_defaultgateway = 6,
	fieldtype_dnsserver = 7,
	fieldtype_streamname = 8,
	fieldtype_portnumber = 9,
	fieldtype_version = 10,
	fieldtype_hostname = 11,
	fieldtype_message = 12,
	fieldtype_messagesource = 13,
	fieldtype_iserror = 14
} df_fieldtype;

typedef enum {
	datatype_integer = 0,
	datatype_string = 1,
	datatype_ip = 2,
	datatype_short = 3
	
} df_datatype;

typedef enum  {
	packettype_sophiapublicrequest = 0x00050001,
	packettype_sophiapublicresponse = 0x00050002,
	packettype_httpserverstartfile = 0x00070001,
	packettype_httpserverendfile = 0x00070002,
	packettype_upgraderstatusmessage = 0x00080001
} df_packettype;

struct packetfield {
	df_fieldtype type;
	df_datatype data_type;
	int length;
	
	char *string_value;
	int int_value;
	
	struct packetfield *next;
} ;

static void dfsearchpacket_addpackettype(df_searchpacket *packet, df_packettype packet_type);
static void dfsearchpacket_addstring(df_searchpacket *packet, char *data, df_fieldtype type);
static void dfsearchpacket_addint(df_searchpacket *packet, int data, df_fieldtype type);
static void dfsearchpacket_addgeneric(df_searchpacket *packet, void *data, df_fieldtype type, df_datatype data_type, int length);

static void* dfsearchpacket_flatten(df_searchpacket *packet, int *length);
static df_searchpacket* dfsearchpacket_structure(void* data, int length);

//static void print_bytes(uint8_t *bytes, int length);




void* dfsearchpacket_create(int port, int *length) {
	df_searchpacket *packet;
	char *service_name;
	
	packet = malloc(sizeof(df_searchpacket));
	strcpy(packet->header.id, "DSP1");
	packet->header.field_count = 0;	//will be incrememented
	packet->fields = NULL;
	
	service_name = malloc(21*sizeof(char));
	strcpy(service_name, "DigiFi.Client.Sophia");
	
	dfsearchpacket_addstring(packet, service_name, fieldtype_servicename);
	dfsearchpacket_addpackettype(packet, packettype_sophiapublicrequest);
	dfsearchpacket_addint(packet, port, fieldtype_portnumber);
	
	return dfsearchpacket_flatten(packet, length);
}



df_searchpacket* dfsearchpacket_read(void *data, int length) {
	
	
	return dfsearchpacket_structure(data,length);
}

void dfsearchpacket_inspect(df_searchpacket *read) {
	df_searchfield *current;
	
	printf("Packet header\n--------------------\n");
	printf("id: %s\n", read->header.id);
	printf("field_count: %d\n", read->header.field_count);
	
	current = read->fields;
	
	while (current!=NULL && current->header.length!=0) {
		printf("\nFields\n--------------------\n");
		printf("type: %d\n", current->header.type);
		printf("data_type: %d\n", current->header.data_type);
		printf("length: %d\n", current->header.length);
		printf("pointer: %p\n", current->value);
		
		if (current->header.data_type == datatype_integer) {
			printf("int: %x\n", current->int_value);
		}
		else if (current->header.data_type == datatype_string) {
			printf("string: %s\n", (char*)current->value);
		}
		
		
		printf("\n");
		
		current = current->next;
	}
}



static void dfsearchpacket_addpackettype(df_searchpacket *packet, df_packettype packet_type){
	dfsearchpacket_addint(packet, (int) packet_type, fieldtype_packettype);
}


static void dfsearchpacket_addstring(df_searchpacket *packet, char *data, df_fieldtype type) {
	dfsearchpacket_addgeneric(packet, (void *)data, type, datatype_string, strlen(data) + 1);
}


static void dfsearchpacket_addint(df_searchpacket *packet, int data, df_fieldtype type) {
	df_searchfield* current;
	
	packet->header.field_count++;
	
	// find the place to add the new
	current = packet->fields;
	if (current==NULL) {
		packet->fields = malloc(sizeof(df_searchfield));
		current = packet->fields;
	}
	else {
		while (current->next !=NULL) { current = current->next; }
		current->next = malloc(sizeof(df_searchfield));
		current = current->next;
	}
	
	current->header.type = type;
	current->header.data_type = datatype_integer;
	current->header.length = 4;
	
	current->int_value = data;
	current->value=NULL;
	
	current->next = NULL;
}


static void dfsearchpacket_addgeneric(df_searchpacket *packet, void *data, df_fieldtype type, df_datatype data_type, int length) {
	df_searchfield* current;
	
	packet->header.field_count++;
	
	// find the place to add the new
	current = packet->fields;
	if (current==NULL) {
		packet->fields = malloc(sizeof(df_searchfield));
		current = packet->fields;
	}
	else {
		while (current->next !=NULL) { current = current->next; }
		current->next = malloc(sizeof(df_searchfield));
		current = current->next;
	}
	
	current->header.type = type;
	current->header.data_type = data_type;
	current->header.length = length;
	
	current->value = data;
	
	current->next = NULL;
}


static df_searchpacket* dfsearchpacket_structure(void* data, int length) {
	df_searchpacket *ret;
	df_searchpacket_header *packet_header;
	df_searchfield *current;
	int i, offset;
	
	ret = malloc(sizeof(df_searchpacket));
	
	packet_header = (df_searchpacket_header *)data;
	
	// copy over the header info
	memcpy(&(ret->header), packet_header, sizeof(df_searchpacket_header));
	
	offset = 5;
	ret->fields = malloc(sizeof(df_searchfield));
	current = ret->fields;
	
	// run through all the fields
	for (i=0; i<ret->header.field_count; i++) {
		memcpy(&(current->header.type), data+offset, 2);
		current->header.type = ntohs(current->header.type);
		offset+=2;
		memcpy(&(current->header.data_type), data+offset, 1);
		offset+=1;
		memcpy(&(current->header.length), data+offset, 2);
		current->header.length = ntohs(current->header.length);
		offset+=2;
		
		// set the pointer to the data
		
		if (current->header.data_type == datatype_integer) {
			current->int_value = *((int*)(data+offset));
			current->int_value = ntohl(current->int_value);
		}
		else { current->value = data+offset; }
		
		offset+= current->header.length;
		
		current->next = malloc(sizeof(df_searchfield));
		current = current->next;
		current->next = NULL;
	}
	
	//memset(current,'\0',sizeof(df_searchfield));
	//free(current);
	
	return ret;
}


static void* dfsearchpacket_flatten(df_searchpacket *packet, int* length) {
	int size, offset, holder;
	df_searchfield *current;
	void *ret;
	uint16_t net_conv;
	
	// calculate size to allocate
	size = 5;	// size of the packet header
	current = packet->fields;
	
	while (current!=NULL) {
		size += 5;		// size of the field header
		size +=	current->header.length;	// size of the held value
		
		current = current->next;
	}
	
	*length = size;
	
	ret = malloc(size);
	offset = 0;
	
	// move the header
	memcpy(ret + offset, &packet->header.id, sizeof(packet->header.id));
	offset += sizeof(packet->header.id);
	memcpy(ret + offset, &packet->header.field_count, 1);
	offset += 1;
	
	// move the fields
	current = packet->fields;
	
	while (current != NULL) {		
		// more the field header
		net_conv = htons(current->header.type);
		memcpy(ret + offset, &net_conv, 2);
		offset += 2;
		net_conv = current->header.data_type;
		memcpy(ret + offset, &net_conv, 1);
		offset += 1;
		net_conv = htons(current->header.length);
		memcpy(ret + offset, &net_conv, 2);
		offset += 2;

		
		// move the body
		if (current->header.data_type == datatype_integer) {
			holder = htonl(current->int_value);
			memcpy(ret + offset, &holder, current->header.length);
		}
		else { memcpy(ret + offset, current->value, current->header.length); }
		offset += current->header.length;
		
		current = current->next;
	}
	
	
	return ret;
}











/*static void print_bytes(uint8_t *bytes, int length) {
	int i;
	
	for (i=0; i<length; i++) {
		fprintf(stdout, "%d ", bytes[i]);
	}
	
	fprintf(stdout, "\n");
}*/

