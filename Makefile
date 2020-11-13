CC = gcc
CFLAGS = -std=c99 -Wall -pedantic -g

all: buildidx key2val

buildidx: buildidx.o hashfn.o util.o assignment6.o
	$(CC) $(CFLAGS) buildidx.o hashfn.o util.o assignment6.o -o buildidx

buildidx.o: buildidx.c assignment6.h
	$(CC) $(CFLAGS) buildidx.c -c

key2val: key2val.o hashfn.o util.o assignment6.o
	$(CC) $(CFLAGS) key2val.o hashfn.o util.o assignment6.o -o key2val

key2val.o: key2val.c assignment6.h
	$(CC) $(CFLAGS) key2val.c -c

val2key: val2key.o hashfn.o util.o assignment6.o
	$(CC) $(CFLAGS) val2key.o hashfn.o util.o assignment6.o -o val2key

val2key.o: val2key.c assignment6.h
	$(CC) $(CFLAGS) val2key.c -c

actors: actors.o hashfn.o util.o assignment6.o
	$(CC) $(CFLAGS) actors.o hashfn.o util.o assignment6.o -o actors

actors.o: actors.c assignment6.h
	$(CC) $(CFLAGS) actors.c -c

bacon1: bacon1.o hashfn.o util.o assignment6.o
	$(CC) $(CFLAGS) bacon1.o hashfn.o util.o assignment6.o -o bacon1

bacon1.o: bacon1.c assignment6.h
	$(CC) $(CFLAGS) bacon1.c -c

assignment6.o: assignment6.c assignment6.h
	$(CC) $(CFLAGS) assignment6.c -c

hashfn.o: hashfn.c hashfn.h
	$(CC) $(CFLAGS) hashfn.c -c

util.o: util.c util.h
	$(CC) $(CFLAGS) util.c -c

clean:
	rm *.o buildidx key2val
