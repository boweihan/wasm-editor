#ifndef __INPUT_H__
#define __INPUT_H__

char *editorPrompt(char *prompt, void (*callback)(char *, int));

void editorMoveCursor(int key);

void editorProcessKeypress();

#endif