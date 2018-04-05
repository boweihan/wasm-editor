#ifndef __FILETYPES_H__
#define __FILETYPES_H__

#include "structs.h"

// array of file extensions
extern char *C_HL_extensions[];

// array of keywords to highlight
extern char *C_HL_keywords[];

// struct to configure syntax highlighting rules
extern struct editorSyntax HLDB[];

// store the length of the HLDB array
extern unsigned int HLDB_ENTRIES;

#endif