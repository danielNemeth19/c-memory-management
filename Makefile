.PHONY: build-basics test-basics test-structs test-pointers test-enums test-unions test-adv-pointers test-stack test-objects

build-basics:
	gcc basics/main.c -o main.o

test-basics:
	gcc basics/basics.c basics/basics_test.c -o test_suite.o && ./test_suite.o

test-structs:
	gcc structs/coord.c structs/coord_test.c -o test_suite.o && ./test_suite.o

test-pointers:
	gcc pointers/pointers.c pointers/pointers_test.c -o test_suite.o && ./test_suite.o

test-enums:
	gcc enums/enums.c enums/enums_test.c -o test_suite.o && ./test_suite.o

test-unions:
	gcc unions/union.c unions/union_test.c -o test_suite.o && ./test_suite.o

test-adv-pointers:
	gcc 07_advanced_pointers/advanced_pointers.c 07_advanced_pointers/advanced_pointers_test.c -o test_suite.o && ./test_suite.o

test-stack:
	gcc 08_stack_data_structures/snekstack.c 08_stack_data_structures/snekstack_test.c -o test_suite.o && ./test_suite.o

test-objects:
	gcc 09_objects/snekobject.c 09_objects/snekobject_test.c -o test_suite.o && ./test_suite.o

clean:
	rm -rf *.o *.out

