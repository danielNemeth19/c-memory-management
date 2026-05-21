#include "coord.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

static int float_equal(float a, float b) { return fabs(a - b) < 0.0001f; };
static int string_equal(const char *a, const char *b) {
    return strcmp(a, b) == 0;
};
static int int_equal(int a, int b) { return (a - b) == 0; };

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

void test_coordinate_update(void) {
    coordinate_t c1 = new_coord(1, 2, 3);
    coordinate_update_x(c1, 5);
    assert(int_equal(c1.x, 1));

    coordinate_t c2 = new_coord(1, 2, 3);
    coordinate_t c3 = coordinate_update_and_return_x(c2, 10);
    assert(int_equal(c2.x, 1));
    assert(int_equal(c3.x, 10));
    // Addresses are not the same
    assert(&c2 != &c3);
}

int main(void) {
    test_coord_struct();
    test_coord_scale();
    test_coordinate_update();
    printf("All tests passed.\n");
    return 0;
}
