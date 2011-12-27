CC = g++
FLAGS = -Wno-deprecated 
LIB = -ltulip -ldl
# `tulip-config --libs --cxxflas`

all: test tuto

tuto: tuto.cc
	$(CC) $(FLAGS) tuto.cc $(LIB) -o tuto

test: test.cc
	$(CC) $(FLAGS) test.cc $(LIB) -o test