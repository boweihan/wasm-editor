/*** Dependencies ***/

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

/*** Constant/Macro Definitions ***/

#define EDITOR_VERSION "0.0.1"
#define CTRL_KEY(k) ((k) & 0x1f)

/*** Data ***/

struct editorConfig {
	int cx, cy;
	int screenrows;
	int screencols;
	struct termios orig_termios;
};

struct editorConfig E;

/*** Terminal ***/

void die(const char *s) {
	// clear the screen on exit
	write(STDOUT_FILENO, "\x1b[2J", 4);
	write(STDOUT_FILENO, "\x1b[H", 3);
	perror(s);
	exit(1);
}

void disableRawMode() {
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &E.orig_termios) == -1)
		die("tcsetattr");
}

void enableRawMode() {
	if (tcgetattr(STDIN_FILENO, &E.orig_termios) == -1)
		die("tcgetattr");
	atexit(disableRawMode);
	struct termios raw = E.orig_termios;
	raw.c_iflag &= ~(BRKINT | ICRNL | IXON | INPCK | ISTRIP);
	raw.c_oflag &= ~(OPOST);
	raw.c_cflag |= (CS8);
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
		die("tcgetattr");
}

char editorReadKey() {
	int nread;
	char c;
	while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
		if (nread == -1 && errno != EAGAIN) die("read");
	}
	return c;
}

int getCursorPosition(int *rows, int *cols) {
	char buf[32];
	unsigned int i = 0;

	if (write(STDOUT_FILENO, "\x1b[6n", 4) != 4) return -1;

	printf("\r\n");

	while (i < sizeof(buf) - 1) {
		if (read(STDIN_FILENO, &buf[i], 1) != 1) break;
		if (buf[i] == 'R') break;
		i++;
	}
	buf[i] = '\0';
	if (buf[0] != '\x1b' || buf[1] != '[') return -1;
  if (sscanf(&buf[2], "%d;%d", rows, cols) != 2) return -1;
  return 0;
}

int getWindowSize(int *rows, int *cols) {
	// it's common to pass int references in C
	// you can now use the return value for the code
	struct winsize ws;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
		// move cursor to bottom right of screen (using large values ie 999)
		if (write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12) return -1;
		// use cursor position to determine how many rows and cols we have as a fallback
		return getCursorPosition(rows, cols);
	} else {
		*cols = ws.ws_col;
		*rows = ws.ws_row;
		return 0;
	}
}

/*** Append Buffer ***/

// instead of calling write() directly, append strings to a buffer
// and write it out at the end
struct abuf {
	char *b;
	int len;
};

// constructor for abuf
#define ABUF_INIT { NULL, 0 }

void abAppend(struct abuf *ab, const char *s, int len) {
	// allocate a block of memory
	char *new = realloc(ab->b, ab->len + len);
	if (new == NULL) return;
	memcpy(&new[ab->len], s, len);
	ab->b = new;
	ab-> len += len;
}

void abFree(struct abuf *ab) {
	// deallocate the dynamic memory used by abuf
	free(ab->b);
}

/*** Input ***/

void editorMoveCursor(char key) {
	switch (key) {
		case 'a':
			E.cx--;
			break;
		case 'd':
			E.cx++;
			break;
		case 'w':
			E.cy--;
			break;
		case 's':
			E.cy++;
			break;
	}
}

void editorProcessKeypress() {
	char c = editorReadKey();
	switch (c) {
		case CTRL_KEY('q'):
			// clear the screen on exit
			write(STDOUT_FILENO, "\x1b[2J", 4);
			write(STDOUT_FILENO, "\x1b[H", 3);
			exit(0);
			break;
		case 'w':
		case 's':
		case 'a':
		case 'd':
			editorMoveCursor(c);
			break;
	}
}

/*** Output ***/

void editorDrawRows(struct abuf *ab) {
	int y;
	for (y = 0; y < E.screenrows; y++) {
		if (y == E.screenrows / 3) {
			char welcome[80];
			int welcomelen = snprintf(welcome, sizeof(welcome),
				"wasm-editor -- version %s", EDITOR_VERSION);
			if (welcomelen > E.screencols) welcomelen = E.screencols;
			int padding = (E.screencols - welcomelen) / 2;
			if (padding) {
				abAppend(ab, "~", 1);
				padding--;
			}
			while (padding--) abAppend(ab, " ", 1);
			abAppend(ab, welcome, welcomelen);
		} else {
			abAppend(ab, "~", 1);
		}
		// clear each line as we redraw instead of clearing entire screen
		abAppend(ab, "\x1b[K", 3);
		if (y < E.screenrows - 1) {
			// don't print a carriage return on the last line so the terminal
			// doesn't scroll
			abAppend(ab, "\r\n", 2);
		}
	}
}

void editorRefreshScreen() {
	struct abuf ab = ABUF_INIT;
	// write escape sequence to terminal
	// 2J clears the entire screen - 1J up to cursor, 0J after cursor
	// (commented because we're clearing each line instead)
	// abAppend(&ab, "\x1b[2J", 4);
	// 3 byte escape sequence to reposition cursor to 1:1 (same as \x1b[1;1H)
	abAppend(&ab, "\x1b[?25l", 6);
	abAppend(&ab, "\x1b[H", 3);
	// draw tildes to start each row
	editorDrawRows(&ab);

	// move the cursor to the correct position after refresh
	char buf[32];
	snprintf(buf, sizeof(buf), "\x1b[%d;%dH", E.cy + 1, E.cx + 1);
	abAppend(&ab, buf, strlen(buf));

	// reposition cursor
	abAppend(&ab, "\x1b[?25h", 6);
	write(STDOUT_FILENO, ab.b, ab.len);
	abFree(&ab);
}

/*** Init ***/

void initEditor() {
	E.cx = 0;
	E.cy = 0;
	if (getWindowSize(&E.screenrows, &E.screencols) == -1) die("getWindowSize");
}

int main() {
	enableRawMode();
	initEditor();
	while (1) {
		editorRefreshScreen();
		editorProcessKeypress();
	};
	return 0;
}
