# This is a comment line
CC=g++
# CFLAGS will be the options passed to the compiler.
CFLAGS=-c –Wall
OBJECTS = space.o
SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system


all: space-app	
		
space-app: space.o Makefile
	$(CC) $(OBJECTS) -o space-app $(SFML_FLAGS)


%.o : %.cpp
	g++ -c $<

run :
	./space-app

clean :
	rm -f space.o space-app
       	

