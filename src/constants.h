#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#define EDITOR_VERSION "0.0.1"

// size of tabs (in spaces)
#define EDITOR_TAB_STOP 8

// number of times to press ctrl-q before quitting if there are unsaved changes
#define EDITOR_QUIT_TIMES 3

// The CTRL_KEY macro bitwise-ANDs a character with the value 00011111
#define CTRL_KEY(k) ((k) & 0x1f)

// bit flag for highlighting numbers (0000 0001)
#define HL_HIGHLIGHT_NUMBERS (1<<0)

// bit flag for highlighting strings (0000 0010)
#define HL_HIGHLIGHT_STRINGS (1<<1)

#endif