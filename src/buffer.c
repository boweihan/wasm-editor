#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct abuf {
	char *b;
	int len;
};

void abAppend(struct abuf *ab, const char *s, int len) {
	// allocate a block of memory
	char *new = realloc(ab->b, ab->len + len);
	if (new == NULL) return;
	memcpy(&new[ab->len], s, len);
	ab->b = new;
	ab-> len += len;
}

void abFree(struct abuf *ab) {
	// deallocate the dynamic memory used by abuf
	free(ab->b);
}