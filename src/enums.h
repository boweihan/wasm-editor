#ifndef __ENUMS_H__
#define __ENUMS_H__

// Editor Key Constants (for inputs)
enum EDITOR_KEY {
	BACKSPACE = 127,
	ARROW_LEFT = 1000,
	ARROW_RIGHT,
	ARROW_UP,
	ARROW_DOWN,
	DEL_KEY,
	HOME_KEY,
	END_KEY,
	PAGE_UP,
	PAGE_DOWN
};

// Editor Highlight Constants (for syntax highlighting)
enum EDITOR_HIGHLIGHT {
	HL_NORMAL = 0,
	HL_COMMENT,
	HL_MLCOMMENT,
	HL_KEYWORD1,
	HL_KEYWORD2,
	HL_STRING,
	HL_NUMBER,
	HL_MATCH
};

extern enum EDITOR_KEY editorKey;
extern enum EDITOR_HIGHLIGHT editorHighlight;

#endif