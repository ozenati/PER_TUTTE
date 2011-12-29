# $@ : nom de la cible ;
# $< : première dépendance de la liste des dépendances ;
# $? : les dépendances plus récentes que la cible ;
# $^ : toutes les dépendances ;
# $* : correspond au ' * ' simple dans le shell, i.e. représente 
#      n'importe quel nom.

ROOT=/net/local/pvm3

CC= g++
CXXFLAGS=-W -Wall
LDFLAGS=-lm
TULIP_CONFIG=`tulip-config --libs --cxxflags`

SRC= main.cpp 
OBJ= $(SRC:.cpp=.o)
EXE= $(OBJ:.o=)
MYNODEDIR= mynode/

all: $(EXE)

%o: %c


$(EXE) : $(OBJ) MYNODE toolkit.o
	$(CC) $(TULIP_CONFIG) $(CXXFLAGS) $@.o $(MYNODEDIR)MyNode.o  toolkit.o -o $@

MYNODE : 
	make -C mynode all

clean :
	rm -f *.o 
	make -C mynode clean
