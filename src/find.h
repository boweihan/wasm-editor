#ifndef __FIND_H__
#define __FIND_H__

// let user search forward and backwards through matched
// search terms using arrow keys
void editorFindCallback(char *query, int key);

// prompt user for search term and enter search mode
void editorFind();

#endif