CC = gcc
CFLAGS = -Wall

.PHONY:
all:	treap
	
run:	treap
	./treap

treap:	src/main.c src/treap.c
	$(CC) $(CFLAGS) -o $@ $^ -g

.PHONY:
clean:
	-rm treap
