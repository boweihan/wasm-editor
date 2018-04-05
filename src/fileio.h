#ifndef __FILEIO_H__
#define __FILEIO_H__

// convert all rows to a string ready to be written to a file
void *editorRowsToString(int *buflen);

// open a file for reading
void editorOpen(char *filename);

// write a string to disk
void editorSave();

#endif