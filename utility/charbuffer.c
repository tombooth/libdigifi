

#include "charbuffer.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define INITAL_SIZE 512
#define INCREMENTAL_SIZE 256


struct cbuf_chunk {
	int offset;
	int length;
	
	struct cbuf_chunk *next;
};

static void cbuf_chunk_free(struct cbuf_chunk *ptr);


cbuf* cbuf_new(void) {
	
	cbuf *buffer = malloc(sizeof(cbuf));
	
	buffer->length = 0;
	buffer->size = INITAL_SIZE;
	buffer->data = malloc(INITAL_SIZE);
	memset(buffer->data, 0, INITAL_SIZE);
	
	
	return buffer;
}


void cbuf_free(cbuf* buffer) {
	free(buffer->data);
	free(buffer);
}


void cbuf_extend(cbuf* buffer, int length) {
	int increments_required = 0;
	
	if ((buffer->length + length) >= buffer->size) {
		// we need to resize as we dont have enough room left
		increments_required = (((buffer->length + length) - buffer->size) / INCREMENTAL_SIZE) + 1;
		
		buffer->size += (increments_required * INCREMENTAL_SIZE);
		buffer->data = realloc(buffer->data, buffer->size);
		
		memset(buffer->data + buffer->length, 0, buffer->size - buffer->length);
	}
}


void cbuf_append(cbuf *buffer, char *data, int length) {
	// extend out if needs be
	int new_length = length;
	cbuf_extend(buffer, new_length);
	
	memcpy(buffer->data + buffer->length, data, new_length);
	buffer->length += new_length;
	
	//buffer->data[buffer->length - 1] = '\0';
}



char* cbuf_extract(cbuf *buffer, int offset, int length) {	
	
	if (buffer == NULL ||
		offset < 0 ||
		length == 0) { return ""; }
	
	char *ret = malloc(length + 1);
	
	memcpy(ret, buffer->data + offset, length);
	
	/*	memmove(buffer->data + offset, buffer->data + offset + length, buffer->length - (offset + length));
		buffer->length -= length;
		
		memset(buffer->data + buffer->length, 0, buffer->size - buffer->length);*/
	
	memmove(buffer->data, buffer->data + offset + length, buffer->length - (offset + length));
	buffer->length -= (offset + length);
	
	memset(buffer->data + buffer->length, 0, buffer->size - buffer->length);
	
	ret[length] = '\0';
	
	return ret;
}

char* cbuf_extract_to(cbuf *buffer, char *end, int min_length) {

	if (buffer == NULL ||
		end == NULL) { return ""; }
	
	// char *ret;
	// int end_length = strlen(end);
	
	// TODO: Not sure if needed
	
	return "";
	
}

void cbuf_shrink(cbuf *buffer) {
	struct cbuf_chunk *chunks, *latest_chunk, *new_chunk;
	int i, offset, new_size, increments_required;
	
	//fprintf(stdout, "Shrinking from %d:%d\n", buffer->length, buffer->size);
	
	chunks = malloc(sizeof(struct cbuf_chunk));
	chunks->length = 0;
	chunks->offset = 0;
	chunks->next = NULL;
	
	latest_chunk = chunks;
	new_chunk = NULL;
	
	for (i=0; i<buffer->length; i++) {
		if (buffer->data[i] == '\r' || buffer->data[i] == '\n' || buffer->data[i] == '\0') {
			if (new_chunk != NULL) {
				latest_chunk->next = new_chunk;
				latest_chunk = new_chunk;
				new_chunk = NULL;
			}
		}
		else {
			if (new_chunk == NULL) {
				new_chunk = malloc(sizeof(struct cbuf_chunk));
				new_chunk->length = 1;
				new_chunk->offset = i;
				new_chunk->next = NULL;
			}
			else { new_chunk->length++; }
		}
	}
	
	if (new_chunk != NULL) { latest_chunk->next = new_chunk; }
	
	offset = 0;
	latest_chunk = chunks;
	
	while (latest_chunk != NULL) {
	
		memmove(buffer->data + offset, buffer->data + latest_chunk->offset, latest_chunk->length);
		
		offset += latest_chunk->length;
		latest_chunk = latest_chunk->next;
	}
	
	cbuf_chunk_free(chunks);
	
	// offset is now the total ammount of data we have
	if (offset < INITAL_SIZE) { new_size = INITAL_SIZE; }
	else {
		increments_required = ((offset-INITAL_SIZE) / INCREMENTAL_SIZE) + 1;
		new_size = INITAL_SIZE + (increments_required * INCREMENTAL_SIZE);
	}
	
	buffer->data = realloc(buffer->data, new_size);
	buffer->size = new_size;
	buffer->length = offset;
	
	//fprintf(stdout, "Shrunk to %d:%d\n", buffer->length, buffer->size);

}

static void cbuf_chunk_free(struct cbuf_chunk *ptr) {
	if (ptr==NULL) { return; }
	else if (ptr->next != NULL) { cbuf_chunk_free(ptr->next); }
	
	free(ptr);
}







