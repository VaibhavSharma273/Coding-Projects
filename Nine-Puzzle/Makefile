CC=gcc
CFLAGS = -std=c99 -pedantic -Wall -g3

HWK4= /c/cs223/Hwk4
HWK5= /c/cs223/Hwk5

all: Nine20

Deque.o:	$(HWK4)/Deque.h

Hash.o: 	Hash.h

Nine20: Nine20.o $(HWK5)/Deque.o Hash.o
	${CC} ${CFLAGS}	-o $@ $^

Nine20.o: $(HWK4)/Deque.h Hash.h

clean:
	rm -f Nine20 *.o
## Name : Vaibhav Sharma
## NetID: vs432