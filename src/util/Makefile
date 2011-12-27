CC = gcc
IFLAG= -I../../include/util/

all: list.o cnode.o

list.o: list.c
	$(CC) -c $(IFLAG) list.c

cnode.o: cnode.c
	$(CC) -c $(IFLAG) cnode.c

clean:
	rm -f *.o *~