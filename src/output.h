#ifndef __OUTPUT_H__
#define __OUTPUT_H__

#include "buffer.h"

// handle vertical and horizontal scrolling
// based on cursor position
void editorScroll();

// draw rows when opening editor
void editorDrawRows(struct abuf *ab);

// draw status bar at bottom of editor
void editorDrawStatusBar(struct abuf *ab);

// draw message bar below status bar
void editorDrawMessageBar(struct abuf *ab);

// refresh screen (redraw all rows and init)
void editorRefreshScreen();

// variadic function that can take any number of arguments
// va_arg helps get those arguments
void editorSetStatusMessage(const char *fmt, ...);

#endif