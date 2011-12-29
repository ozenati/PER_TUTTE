CC= g++
CXXFLAGS=-W -Wall
TULIP_CONFIG=`tulip-config --libs --cxxflags`

all: prog

prog: MyNode.o prog.o 
	$(CC) ${CXXFLAGS} ${TULIP_CONFIG} $^ -o $@

prog.o: MyNode.h

clean:
	rm -f *.o prog