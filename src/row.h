#ifndef __ROW_H__
#define __ROW_H__

#include "structs.h"

// convert chars index to render index to render tabs
int editorRowCxToRx(erow *row, int cx);

// convert render index to char index to process rows with tabs
int editorRowRxToCx(erow *row, int rx);

// use chars string of erow to fill in render string
void editorUpdateRow(erow *row);

// insert a row at specified index
void editorInsertRow(int at, char *s, size_t len);

// free the memory owned by a row (when deleting for ex.)
void editorFreeRow(erow *row);

// delete row (with memmove)
void editorDelRow(int at);

// insert a char into a row at a specific position
void editorRowInsertChar(erow *row, int at, int c);

// append row to end of string (i.e. when pressing delete on the first
// character in a row)
void editorRowAppendString(erow *row, char *s, size_t len);

// delete a character in an erow at a specified index
void editorRowDelChar(erow *row, int at);

#endif