CC=gcc
CFLAGS=-Wall -Wextra -pedantic -ansi
DEBUG=-g -ggdb -O0 -march=native

build: Palindrom

Palindrom: Palindrom.o Dequeue_unlinked.o LinkedList.o
	$(CC) $(CFLAGS) $(DEBUG) Palindrom.o Dequeue_unlinked.o LinkedList.o -o Palindrom

Dequeue_unlinked.o: Dequeue.h Dequeue.c
	$(CC) $(CFLAGS) $(DEBUG) Dequeue.c -c -o Dequeue_unlinked.o

LinkedList.o: LinkedList.h LinkedList.c
	$(CC) $(CFLAGS) $(DEBUG) LinkedList.c -c -o LinkedList.o

Palindrom.o: Palindrom.c
	$(CC) $(CFLAGS) $(DEBUG) Palindrom.c -c -o Palindrom.o

clean:
	rm *.o
	rm Palindrom
