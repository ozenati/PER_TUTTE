CC= g++
OPTION= -Wno-deprecated
LFLAG= -ltulip -ldl
IFLAG= -I../include/util/
OBJ= util/*.o

all: objet separator

separator: separator.cpp
	$(CC) $(OPTION) $(IFLAG) separator.cpp $(OBJ) $(LFLAG) -o separator

objet:
	make -C util