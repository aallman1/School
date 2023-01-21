FLAGS= -Wall -Werror -pedantic --std=c++14

all: test lint

lint:
	cpplint --filter=-runtime/references,-build/c++11 --root=. *
	
test: test.o 
	g++ ${FLAGS} test.o -o test -lboost_unit_test_framework

test.o: test.cpp CircularBuffer.hpp
	g++ ${FLAGS} -c test.cpp


clean:
	rm *.o 
	-rm test