
build:
	g++ -c main.cpp

run :
	g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
	./sfml-app
clean :
	rm -f main.o sfml-app
       	

