#ifndef __INPUT_H__
#define __INPUT_H__

// prompt user in status message bar
char *editorPrompt(char *prompt, void (*callback)(char *, int));

// move cursor based on keypress and ensure cursor says within text
void editorMoveCursor(int key);

// process a user input keypress (raw mode)
void editorProcessKeypress();

#endif