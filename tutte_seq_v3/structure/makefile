CC= g++
CXXFLAGS=-W -Wall
TULIP_CONFIG=`tulip-config --libs --cxxflags` -ldl

all: test_structure

test_structure: MyGraph.o test_structure.o 
	$(CC) ${CXXFLAGS} $^ -o $@ ${TULIP_CONFIG}

test_structure.o: MyGraph.h

clean:
	rm -f *.o test_structure