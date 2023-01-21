FLAGS= -Wall -Werror -pedantic --std=c++14 

all: PS7

lint:
	cpplint --filter=-runtime/references,-build/c++11 --root=. *

PS7: main.o BootSequence.o Service.o
	g++ ${FLAGS} main.o BootSequence.o Service.o -o PS7 -lboost_regex

clean:
	-rm PS7
	-rm *.o 
