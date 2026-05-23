#include "../structs/coord.h"
#include "../pointers/pointers.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

int main() {
    printf("sizeof(char) = %zu\n", sizeof(char));
    printf("sizeof(bool) = %zu\n", sizeof(bool));
    printf("sizeof(int) = %zu\n", sizeof(int));
    printf("sizeof(float) = %zu\n", sizeof(float));
    printf("sizeof(long) = %zu\n", sizeof(long));
    printf("sizeof(double) = %zu\n", sizeof(double));
    printf("sizeof(size_t) = %zu\n", sizeof(size_t));
    printf("sizeof(coordinate_t) = %zu\n", sizeof(coordinate_t));
    printf("sizeof(sneklang_var_t) = %zu\n", sizeof(sneklang_var_t));

    int n = 15;
    int *pointer_to_n = &n;
    printf("address stored in pointer_to_n is %p\n", pointer_to_n);
    printf("value of pointer: %d\n", *pointer_to_n);

    char k = 'k';
    char *pointer_to_k = &k;
    printf("address stored in pointer_to_k is %p\n", pointer_to_k);
    printf("value of pointer: %c\n", *pointer_to_k);

    /* Initializing struct based on position is also possible
     designated initalization would be: coordinate_t c = {.x = x, .y = y, .z = z};
     */
    coordinate_t point = {10, 20, 30};
    printf("X: %d\n", point.x);

    coordinate_t *ptr_point = &point;
    /*  the arrow syntax dereferences the pointer and access the field in one step*/
    printf("X: %d as dereferenced pointer\n", ptr_point -> x);
    /* the more verbose syntax - note that `.` has higher priority than `*`
       which is why the parentheses are needed
    */
    printf("X: %d dereferencing pointer first, then accessing the field\n", (*ptr_point).x);

    printf("Arrays as pointers\n");
    int numbers[5] = {1, 2, 3, 4, 5};
    int *ptr = numbers;
    printf("The name `numbers` act as a pointer to the first element of the array: %p\n", ptr);
    printf("numbers[2] = %d\n", numbers[2]);
    printf("*(numbers + 2) =  %d\n", *(numbers + 2));

    ptr += 2;
    printf("Pointer arithmetic: ptr points now to numbers[2]: %d\n", *ptr);

    int *intPrt;
    char *charPtr;
    double *doublePtr;

    printf("Size of int pointer: %zu bytes\n", sizeof(intPrt));
    printf("Size of char pointer: %zu bytes\n", sizeof(charPtr));
    printf("Size of double pointer: %zu bytes\n", sizeof(doublePtr));

    int intArray[10];
    char charArray[10];
    double doubleArray[10];

    printf("Size of int array: %zu bytes\n", sizeof(intArray));
    printf("Size of char array: %zu bytes\n", sizeof(charArray));
    printf("Size of double array: %zu bytes\n", sizeof(doubleArray));
}
