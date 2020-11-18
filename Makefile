CC = gcc
CFLAGS = -std=c99 -Wall -pedantic -g

all: buildidx key2val val2key

buildidx: buildidx.o hashfn.o util.o
	$(CC) $(CFLAGS) buildidx.o hashfn.o util.o  -o buildidx

buildidx.o: buildidx.c
	$(CC) $(CFLAGS) buildidx.c -c

key2val: key2val.o hashfn.o util.o
	$(CC) $(CFLAGS) key2val.o hashfn.o util.o  -o key2val

key2val.o: key2val.c
	$(CC) $(CFLAGS) key2val.c -c

val2key: val2key.o hashfn.o util.o
	$(CC) $(CFLAGS) val2key.o hashfn.o util.o  -o val2key

val2key.o: val2key.c
	$(CC) $(CFLAGS) val2key.c -c

actors: actors.o hashfn.o util.o
	$(CC) $(CFLAGS) actors.o hashfn.o util.o  -o actors

actors.o: actors.c
	$(CC) $(CFLAGS) actors.c -c

bacon1: bacon1.o hashfn.o util.o
	$(CC) $(CFLAGS) bacon1.o hashfn.o util.o  -o bacon1

bacon1.o: bacon1.c
	$(CC) $(CFLAGS) bacon1.c -c

hashfn.o: hashfn.c hashfn.h
	$(CC) $(CFLAGS) hashfn.c -c

util.o: util.c util.h
	$(CC) $(CFLAGS) util.c -c

clean:
	rm *.o buildidx key2val val2key
