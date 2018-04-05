# GNU compiler collection (Unix)
CC = gcc

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
# -std=c99: use standard version C99 (released in 1999)
CFLAGS = -Wall -Werror -Wextra -std=c99

# Dependencies which trigger re-compilation via "make"
_DEPS = enums.h constants.h structs.h filetypes.h terminal.h
DEPS = $(patsubst %, $(SDIR)/%, $(_DEPS))

# Object files
_OBJ = editor.o filetypes.o terminal.o
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))

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

# prevent make from doing anything with files named "clean"
.PHONY: clean

# make clean will clean up source and object directories
clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~

