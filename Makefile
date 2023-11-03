CC = gcc
CFLAGS = -std=c11 -Wextra -Wpedantic -g3 -fsanitize=address
LDFLAGS = -lncurses -fsanitize=address
SRC = $(filter-out src/voorbeeld.c,$(wildcard src/*.c))
HEADERS = $(wildcard src/*.h)

.PHONY: tarball1 tarball2 clean

all: game

game: $(SRC)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

voorbeeld:
	$(CC) -o voorbeeld src/voorbeeld.c $(CFLAGS) $(LDFLAGS)

clean:
	rm -f *~ *.o voorbeeld game deel?.tar.gz

