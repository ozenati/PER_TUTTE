# $@ : nom de la cible ;
# $< : première dépendance de la liste des dépendances ;
# $? : les dépendances plus récentes que la cible ;
# $^ : toutes les dépendances ;
# $* : correspond au ' * ' simple dans le shell, i.e. représente 
#      n'importe quel nom.

CC= g++
IFLAGS= -I../include/ 
CXXFLAGS=-W -Wall -fopenmp $(IFLAGS) -DNDEBUG  \
	-funroll-all-loops -O3 -mtune=native
LDFLAGS= -ldl -lgomp
TULIP_CONFIG=`tulip-config --libs --cxxflags`

SRC= main.cpp tutter.cpp benchmark.cpp
OBJ= $(SRC:.cpp=.o)
EXE= $(OBJ:.o=)

OBJDEP= myNode.o toolkit.o tutte_sequentiel_asynchrone.o separator.o \
	 tutte_parallel_synchrone.o tutte_parallel_asynchrone.o 

all: $(EXE)

%o: %c

$(EXE): $(OBJ) $(OBJDEP) 
	$(CC) $(CXXFLAGS) $(IFLAGS) $(OBJDEP) $@.o $(TULIP_CONFIG) $(LDFLAGS) -o $@

clean:
	rm -f *.o $(EXE)