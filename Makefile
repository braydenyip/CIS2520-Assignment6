CC = gcc
CFLAGS = -std=c99 -Wall -pedantic -g

all: build_idx

build_idx: build_idx.o hashfn.o util.o
	$(CC) $(CFLAGS) build_idx.o hashfn.o util.o -o build_idx

build_idx.o: build_idx.c assignment6.h
	$(CC) $(CFLAGS) build_idx.c -c


hashfn.o: hashfn.c hashfn.h
	$(CC) $(CFLAGS) hashfn.c -c

util.o: util.c util.h
	$(CC) $(CFLAGS) util.c -c


clean:
	rm *.o build_idx
