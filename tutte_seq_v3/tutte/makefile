# $@ : nom de la cible ;
# $< : première dépendance de la liste des dépendances ;
# $? : les dépendances plus récentes que la cible ;
# $^ : toutes les dépendances ;
# $* : correspond au ' * ' simple dans le shell, i.e. représente 
#      n'importe quel nom.

CC= g++
CXXFLAGS=-W -Wall -g
LDFLAGS=-lm
TULIP_CONFIG=`tulip-config --libs --cxxflags` -ldl

SRC= test_tutte.cpp 
OBJ= $(SRC:.cpp=.o)
EXE= $(OBJ:.o=)
STRUCTURE_DIR= ../structure/

all: $(EXE)

%o: %c


$(EXE) : $(OBJ) STRUCTURE toolkit.o
	$(CC) $(CXXFLAGS) $@.o $(STRUCTURE_DIR)MyGraph.o  toolkit.o -o $@ $(TULIP_CONFIG)

STRUCTURE : 
	make -C $(STRUCTURE_DIR) all

clean :
	rm -f *.o 
	make -C $(STRUCTURE_DIR) clean