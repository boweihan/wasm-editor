/*** feature test macros for code portability ***/
#define _DEFAULT_SOURCE // asprintf() for linux
#define _BSD_SOURCE // gettimeofday() for linux
#define _GNU_SOURCE // modern glibc will complain about the above without this

/*** standard libraries ***/
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <unistd.h>

/*** custom dependencies ***/

#include "constants.h"
#include "enums.h"
#include "structs.h"
#include "filetypes.h"
#include "terminal.h"
#include "highlight.h"
#include "row.h"
#include "editor.h"
#include "fileio.h"
#include "find.h"
#include "input.h"
#include "output.h"

struct editorConfig E;

/*** Init ***/

void initEditor() {
	E.cx = 0;
	E.cy = 0;
	E.rx = 0;
	E.rowoff = 0;
	E.coloff = 0;
	E.numrows = 0;
	E.row = NULL;
	E.dirty = 0;
	E.filename = NULL;
	E.statusmsg[0] = '\0';
	E.statusmsg_time = 0;
	E.syntax = NULL;

	if (getWindowSize(&E.screenrows, &E.screencols) == -1) die("getWindowSize");
	E.screenrows -= 2;
}

int main(int argc, char *argv[]) {
	enableRawMode();
	initEditor();
	if (argc >= 2) {
		editorOpen(argv[1]);
	}
	editorSetStatusMessage("HELP: Ctrl-S = save | Ctrl-Q = quit | Ctrl-F = find");
	while (1) {
		editorRefreshScreen();
		editorProcessKeypress();
	};
	return 0;
}
