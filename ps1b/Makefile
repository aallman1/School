FLAGS= -Wall -Werror -pedantic --std=c++14
all: PhotoMagic test

PhotoMagic: PhotoMagic.o FibLFSR.o
	g++ ${FLAGS} PhotoMagic.o FibLFSR.o -o PhotoMagic -lsfml-graphics -lsfml-window -lsfml-system

PhotoMagic.o: PhotoMagic.cpp FibLFSR.cpp
	g++ ${FLAGS} -c PhotoMagic.cpp

FibLFSR.o: FibLFSR.cpp FibLFSR.hpp
	g++ ${FLAGS} -c FibLFSR.cpp

test: test.o FibLFSR.o
	g++ ${FLAGS} test.o FibLFSR.o -o test -lboost_unit_test_framework

test.o: test.cpp FibLFSR.hpp
	g++ ${FLAGS} -c test.cpp
clean:
	rm *.o 
	-rm PhotoMagic
	-rm test
