CC = gcc
CFLAGS = -std=c11 -Wextra -Wpedantic -g3 -fsanitize=address
LDFLAGS = -lncurses -fsanitize=address
SRC = $(filter-out voorbeeld.c,$(wildcard *.c))
HEADERS = $(wildcard *.h)

.PHONY: tarball1 tarball2 clean

all: spel

spel: $(SRC)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

voorbeeld:
	$(CC) -o voorbeeld voorbeeld.c $(CFLAGS) $(LDFLAGS)

tarball1: deel1.tar.gz
tarball2: deel2.tar.gz

deel1.tar.gz: spel.c rooster.h rooster.c Makefile
	tar czf $@ $^

deel2.tar.gz: $(SRC) $(HEADERS) Makefile
	tar czf $@ $^ assets

clean:
	rm -f *~ *.o voorbeeld spel deel?.tar.gz
