#ifndef __EDITOR_H__
#define __EDITOR_H__

// insert a character at cursor position
// uses editorRowInsertChar under the hood with cursor position
void editorInsertChar(int c);

// insert a new line at cursor position
void editorInsertNewline();

// delete a character at cursor position
void editorDelChar();

#endif