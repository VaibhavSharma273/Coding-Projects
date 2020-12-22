CC=gcc
CFLAGS= -std=c99 -pedantic -Wall -g3

all: Linesort

#####
# Instructions to make Linesort
#####

Linesort: Linesort.o Deque.o
	${CC} ${CFLAGS} -o $@ $^

Linesort.o: Deque.h

clean:
	rm -f Linesort *.o
