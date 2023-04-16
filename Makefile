CC = gcc
CFLAGS = -std=c11 -Wextra -Wpedantic -g3 -fsanitize=address
LDFLAGS = -lncurses -fsanitize=address
SRC = $(filter-out voorbeeld.c,$(wildcard *.c))
HEADERS = $(wildcard *.h)

.PHONY: tarball1 tarball2 clean

all: game

game: $(SRC)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

voorbeeld:
	$(CC) -o voorbeeld voorbeeld.c $(CFLAGS) $(LDFLAGS)

clean:
	rm -f *~ *.o voorbeeld game deel?.tar.gz
