#ifndef __BUFFER_H__
#define __BUFFER_H__

// instead of calling write() directly, append strings to a buffer
// and write it out at the end
struct abuf {
	char *b;
	int len;
};

// constructor for abuf
#define ABUF_INIT { NULL, 0 }

// append to buffer
void abAppend(struct abuf *ab, const char *s, int len);

// free buffer
void abFree(struct abuf *ab);

#endif