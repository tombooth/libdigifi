

#ifndef CHARBUF_HEADER
#define CHARBUF_HEADER

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	char *data;
	unsigned int length;
	unsigned int size;
} cbuf;



cbuf* cbuf_new(void);
void cbuf_free(cbuf* buffer);
void cbuf_extend(cbuf* buffer, int length);
void cbuf_append(cbuf *buffer, char *data, int length);
char* cbuf_extract(cbuf *buffer, int offset, int length);
char* cbuf_extract_to(cbuf *buffer, char *end, int min_length);
void cbuf_shrink(cbuf *buffer);

	
#ifdef __cplusplus
}
#endif

#endif