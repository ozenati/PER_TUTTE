CC= g++
LDFLAGS= -ldl
IFLAGS= -I../include/
TULIP_CONFIG=`tulip-config --libs --cxxflags`


all: separator

separator: separator.cpp MyNode.o
	$(CC) -g $(IFLAGS) separator.cpp MyNode.o $(TULIP_CONFIG) $(LDFLAGS) -o separator

MyNode.o: MyNode.cpp
	$(CC) -g -c $(IFLAGS) MyNode.cpp

clean:
	rm -f *.o separator