#include "coord.h"
#include "exercise_1.h"
#include "snek.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

static int float_equal(float a, float b) { return fabs(a - b) < 0.0001f; };
static int string_equal(const char *a, const char *b) {
    return strcmp(a, b) == 0;
};
static int int_equal(int a, int b) { return (a - b) == 0; };

static void test_get_average(void) {
    assert(float_equal(get_average(3, 4, 5), 4.0f));
    assert(float_equal(get_average(3, 3, 5), 11.0f / 3.0f));
    assert(float_equal(get_average(10, 10, 10), 10.0f));
    assert(float_equal(get_average(1050, 2050, 2075), 1725.0f));
}

static void test_snek_score(void) {
    assert(float_equal(snek_score(3, 4, 5, 0.1), 1.9));
    assert(float_equal(snek_score(10, 10, 10, 0.1), 11));
    assert(float_equal(snek_score(105, 205, 207, 0.1), 2194));
}

static void test_get_temperature_status(void) {
    assert(string_equal(get_temperature_status(50), "too cold"));
    assert(string_equal(get_temperature_status(100), "too hot"));
    assert(string_equal(get_temperature_status(70), "just right"));
    assert(string_equal(get_temperature_status(75), "just right"));
}

static void test_can_access_registry(void) {
    assert(int_equal(can_access_registry(1, 120, 1), 1));
    assert(int_equal(can_access_registry(1, 0, 0), 1));
    assert(int_equal(can_access_registry(0, 100, 1), 1));
    assert(int_equal(can_access_registry(0, 150, 0), 0));
    assert(int_equal(can_access_registry(0, 50, 1), 0));
    assert(int_equal(can_access_registry(1, 50, 1), 1));
    assert(int_equal(can_access_registry(0, 20, 0), 0));
}

static void test_coord_struct(void) {
    coordinate_t cord = new_coord(10, 20, 30);
    assert(int_equal(cord.x, 10));
    assert(int_equal(cord.y, 20));
    assert(int_equal(cord.z, 30));
}

static void test_coord_scale(void) {
    coordinate_t cord = new_coord(10, 20, 30);
    cord = scale_coordinate(cord, 2);
    assert(int_equal(cord.x, 20));
    assert(int_equal(cord.y, 40));
    assert(int_equal(cord.z, 60));
}

static void test_size_of_addr(void) {
    unsigned long size_1 = size_of_addr(16);
    assert(int_equal(size_1, 4));

    unsigned long size_2 = size_of_addr(32);
    assert(int_equal(size_2, 4));

    unsigned long size_3 = size_of_addr(64);
    assert(int_equal(size_3, 4));

    unsigned long size_4 = size_of_addr(128);
    assert(int_equal(size_4, 4));
}

void test_print(int start, int end) {
    printf("Printing from %d to %d:\n", start, end);
    print_numbers(start, end);
    printf("=====================\n");
}

void test_print_reverse(int start, int end) {
    printf("Printing from %d to %d:\n", start, end);
    print_numbers_reverse(start, end);
    printf("=====================\n");
}

void test_print_reverse_do_while(int start, int end) {
    printf("Printing from %d to %d:\n", start, end);
    print_numbers_reverse_do_while(start, end);
    printf("=====================\n");
}

int main(void) {
    test_print(42, 69);
    test_print_reverse(10, 5);
    test_print_reverse_do_while(0, 5);
    test_get_average();
    test_snek_score();
    test_get_temperature_status();
    test_can_access_registry();
    test_coord_struct();
    test_coord_scale();
    printf("All tests passed.\n");
    return 0;
}
