FLAGS=  -g -Wall -Werror -pedantic --std=c++14 

all: EDistance

lint:
	cpplint --filter=-runtime/references,-build/c++11 --root=. *

EDistance: main.o EDistance.o Matrix.o 
	g++ ${FLAGS} main.o EDistance.o Matrix.o -o EDistance -lsfml-system


clean:
	rm *.o 
	-rm EDistance