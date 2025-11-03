# Copyright (C) 2025, Saqttra. All rights reserved.
#
# This file is part of Saqttra Eugenia
#
# This project's files are licensed under the MIT license
# found in the LICENSE file in the root directory.
#
# <https://github.com/saqttra/Eugenia>.

CC = gcc
CFLAGS = -std=c89 -pedantic -Wall -Wextra -Werror
LIBS = -lm
HEADERS = \
				src/errors.h src/cmds.h src/reader.h src/utils.h\
				src/typedefs.h src/utf8.h
SRC = \
		src/main.c src/errors.c src/cmds.c src/reader.c\
		src/utils.c src/utf8.c
EXEC = eugenia

all: $(EXEC)

$(EXEC): $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) -o $(EXEC) $(SRC) $(LIBS)

run: $(EXEC)
	./$(EXEC)

clean:
	rm -f $(EXEC)

# valgrind --leak-check=full --show-leak-kinds=all ./executable
