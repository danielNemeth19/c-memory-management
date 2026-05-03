.PHONY: build test-exercise test-pointers build-test clean

build:
	gcc main.c -o main.o

test-exercise:
	gcc exercise_1.c coord.c snek.c test.c -o test_suite.o && ./test_suite.o

test-pointers:
	gcc pointers.c pointers_test.c -o pointers_test.o && ./pointers_test.o

build-test:
	gcc exercise_1.c coord.c snek.c test.c -o test_suite.o

clean:
	rm -rf *.o *.out

