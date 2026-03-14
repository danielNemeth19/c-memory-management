.PHONY: build test build-test clean

build:
	gcc main.c -o main

test:
	gcc exercise_1.c coord.c test.c -o test_suite && ./test_suite

build-test:
	gcc exercise_1.c coord.c test.c -o test_suite

clean:
	rm -rf test_suite main *.o

