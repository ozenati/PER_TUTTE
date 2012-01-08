# $@ : nom de la cible ;
# $< : première dépendance de la liste des dépendances ;
# $? : les dépendances plus récentes que la cible ;
# $^ : toutes les dépendances ;
# $* : correspond au ' * ' simple dans le shell, i.e. représente 
#      n'importe quel nom.

CC= g++
IFLAGS= -I../include/
CXXFLAGS=-W -Wall -g $(IFLAGS)
LDFLAGS= -ldl
TULIP_CONFIG=`tulip-config --libs --cxxflags`

SRC= main.cpp tutter.cpp
OBJ= $(SRC:.cpp=.o)
EXE= $(OBJ:.o=)

OBJDEP= MyNode.o toolkit.o tutte_parallel_asynchrone.o separator.o

all: $(EXE)

%o: %c

$(EXE): $(OBJ) $(OBJDEP) 
	$(CC) $(CXXFLAGS) $(IFLAGS) $(OBJDEP) $@.o $(TULIP_CONFIG) $(LDFLAGS) -fopenmp -o $@

# MyNode.o: MyNode.cpp
# 	$(CC) -g -c $(IFLAGS) MyNode.cpp

clean:
	rm -f *.o $(EXE)