# GNU compiler collection (Unix)
CC = gcc

# Emscripten compiler (for web assembly)
ECC = emcc

# Source directory
SDIR = src

# Object directory
ODIR = obj

# Extra flags to give to the compiler
# -Wall: enable all warnings that are easy to avoid / questionable
# -Werror: make all warnings into errors
# -Wextra: enable extra warning flags not implied by -Wall
# -Wmissing-prototypes: warn if a global function is defined
# 	without previous prototype declaration
# -std=c99: use standard version C99 (released in 1999) with GNU extensions
CFLAGS = -Wall -Werror -Wextra -std=gnu99

# Dependencies which trigger re-compilation via "make"
_DEPS = enums.h constants.h structs.h
_DEPS += editor.h filetypes.h terminal.h highlight.h
_DEPS += row.h fileio.h input.h output.h
_DEPS += find.h buffer.h
DEPS = $(patsubst %, $(SDIR)/%, $(_DEPS))

# Object files
_OBJ = main.o editor.o filetypes.o terminal.o
_OBJ += highlight.o row.o fileio.o input.o
_OBJ += output.o find.o buffer.o
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))

# C files
_SRC += filetypes.c terminal.c highlight.c
_SRC += row.c input.c output.c
_SRC += find.c buffer.c fileio.c
_SRC += editor.c main.c
SRC = $(patsubst %, $(SDIR)/%, $(_SRC))

# Rule states that .o file depends on the .c version
# of the file and the .h files included in the DEPS macro
# $@ - special macro - name of file to be made
# $< - special macro - name of the related file that caused the action
# $^ - special macro - include list of all files that caused the action
$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# "make" will compile the editor as default
# $^ - special macro - include list of all files that caused the action
editor: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

wasm: $(SRC)
	$(ECC) -o $@ $^ $(CFLAGS) -s WASM=1 -o dist/editor.html

# prevent make from doing anything with files named "clean"
.PHONY: clean

# make clean will clean up source and object directories
clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~

