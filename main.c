#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include "coord.h"
#include "exercise_1.h"

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
}
