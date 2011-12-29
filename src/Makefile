CC= g++
LDFLAGS= -ldl
IFLAGS= -I../include/
TULIP_CONFIG=`tulip-config --libs --cxxflags`


all: separator

separator: separator.cpp MyNode.o
	$(CC) $(IFLAGS) separator.cpp MyNode.o $(TULIP_CONFIG) $(LDFLAGS) -o separator

MyNode.o: MyNode.cpp
	$(CC) -c $(IFLAGS) MyNode.cpp

clean:
	rm -f *.o separator