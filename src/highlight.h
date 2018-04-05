#ifndef __HIGHLIGHT_H__
#define __HIGHLIGHT_H__

#include "structs.h" 

// check if a character is a separator character (ie space)
int is_separator(int c);

// update a row of characters with proper highlighting
void editorUpdateSyntax(erow *row);

// return appropriate highlight color
int editorSyntaxToColor(int hl);

// set syntax highlighting rules based on filetype
void editorSelectSyntaxHighlight();

#endif