FLAGS= -g -Wall -Werror -pedantic --std=c++14

all: TextWriter

lint:
	cpplint --filter=-runtime/references,-build/c++11 --root=. *

TextWriter: TextWriter.o RandWriter.o
	g++ ${FLAGS} TextWriter.o RandWriter.o -o TextWriter

test: test.o RandWriter.o
	g++ ${FLAGS} test.o RandWriter.o -o test -lboost_unit_test_framework

clean:
	-rm Main
	-rm test
	-rm *.o