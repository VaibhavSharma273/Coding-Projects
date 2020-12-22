CC=gcc
CFLAGS = -std=c99 -pedantic -Wall -g3

all: Nine20

Deque.o:	Deque.h

Hash.o: 	Hash.h

Nine20: Nine20.o Deque.o Hash.o
	${CC} ${CFLAGS}	-o $@ $^

Nine20.o: Deque.h Hash.h

clean:
	rm -f Nine20 *.o
