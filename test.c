#include "exercise.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>

static int float_equal(float a, float b) {
    return fabs(a - b) < 0.0001f;
};

static void test_get_average(void) {
    assert(float_equal(get_average(3, 4, 5), 4.0f));
    assert(float_equal(get_average(3, 3, 5), 11.0f / 3.0f));
    assert(float_equal(get_average(10, 10, 10), 10.0f));
    assert(float_equal(get_average(1050, 2050, 2075), 1725.0f));
}

int main(void) {
    test_get_average();
    printf("All tests passed.\n");
    return 0;
}
