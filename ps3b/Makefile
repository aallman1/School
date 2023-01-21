FLAGS= -Wall -Werror -pedantic --std=c++14

all: KGuitarSim test lint

lint:
	cpplint --filter=-runtime/references,-build/c++11 --root=. *

KGuitarSim: KGuitarSim.o StringSound.o SynthSound.o
	g++ ${FLAGS} KGuitarSim.o StringSound.o SynthSound.o -o KGuitarSim -lsfml-audio -lsfml-system -lsfml-window -lsfml-graphics
	
KGuitarSim.o: KGuitarSim.cpp KGuitarSim.hpp StringSound.hpp SynthSound.hpp
	g++ ${FLAGS} -c KGuitarSim.cpp 

StringSound.o: StringSound.cpp StringSound.hpp
	g++ ${FLAGS} -c StringSound.cpp

SynthSound.o: SynthSound.cpp
	g++ ${FLAGS} -c SynthSound.cpp

test: test.o StringSound.o SynthSound.o
	g++ ${FLAGS} test.o StringSound.o SynthSound.o -o test -lboost_unit_test_framework

test.o: test.cpp KGuitarSim.hpp sprites.hpp
	g++ ${FLAGS} -c test.cpp


clean:
	rm *.o 
	-rm test
	-rm KGuitarSim