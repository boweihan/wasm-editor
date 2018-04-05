#ifndef __TERMINAL_H__
#define __TERMINAL_H__

// kill the program / clear the screen on exit
void die(const char *s);

// disable raw mode on exit
void disableRawMode();

// enable raw modes, so we can react to keystrokes without enter
void enableRawMode();

// read and return the next key stroke
int editorReadKey();

// get and return the current cursor position
int getCursorPosition(int *rows, int *cols);

// get and return the current window size
int getWindowSize(int *rows, int *cols);

#endif