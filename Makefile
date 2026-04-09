.PHONY: build test build-test clean

build:
	gcc main.c -o main.o

test:
	gcc exercise_1.c coord.c snek.c test.c -o test_suite.o && ./test_suite.o

build-test:
	gcc exercise_1.c coord.c snek.c test.c -o test_suite.o

clean:
	rm -rf *.o

