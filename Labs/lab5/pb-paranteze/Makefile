CC=gcc
CFLAGS=-Wall -Wextra -pedantic -ansi
DEBUG=-g -ggdb -O0 -march=native

build: Paranteze

Paranteze: Paranteze.o Stack_unlinked.o LinkedList.o
	$(CC) $(CFLAGS) $(DEBUG) Paranteze.o Stack_unlinked.o LinkedList.o -o Paranteze

Stack_unlinked.o: Stack.h Stack.c
	$(CC) $(CFLAGS) $(DEBUG) Stack.c -c -o Stack_unlinked.o

LinkedList.o: LinkedList.h LinkedList.c
	$(CC) $(CFLAGS) $(DEBUG) LinkedList.c -c -o LinkedList.o

Paranteze.o: Paranteze.c
	$(CC) $(CFLAGS) $(DEBUG) Paranteze.c -c -o Paranteze.o

clean:
	rm *.o
	rm Paranteze


