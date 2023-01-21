FLAGS= -Wall -pedantic -Werror --std=c++14

all: Sokoban

lint:
	cpplint --filter=-runtime/references,-build/c++11 --root=. *

Sokoban: main.o Sokoban.o Matrix.o 
	g++ ${FLAGS} main.o Sokoban.o Matrix.o -o Sokoban -lsfml-system -lsfml-window -lsfml-graphics

clean:
	rm *.o 
	-rm Sokoban