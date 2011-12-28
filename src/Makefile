CC= g++
OPTION= -Wno-deprecated
LFLAG= -ltulip -ldl
IFLAG= -I../include/
OBJ= util/*.o

all: separator

separator: separator.cpp Per_node.o
	$(CC) $(OPTION) $(IFLAG) separator.cpp Per_node.o $(LFLAG) -o separator

Per_node.o: Per_node.cpp
	$(CC) -c $(IFLAG) Per_node.cpp

clean:
	rm -f *.o separator