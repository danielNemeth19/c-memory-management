#include "enums.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

static int float_equal(float a, float b) { return fabs(a - b) < 0.0001f; };
static int string_equal(const char *a, const char *b) {
    return strcmp(a, b) == 0;
};

void test_color_enum1(void) {
    assert(float_equal(RED_OLD, 0));
    assert(float_equal(GREEN_OLD, 1));
    assert(float_equal(BLUE_OLD, 2));
}

void test_color_enum2(void) {
    assert(RED_OLD != 2);
    assert(GREEN_OLD != 0);
    assert(BLUE_OLD != 5);
}

void test_colors_defined(void) {
    assert(float_equal(RED, 55));
    assert(float_equal(GREEN, 176));
    assert(float_equal(BLUE, 38));
}

void test_colors_defined_correctly(void) {
    assert(RED != 2);
    assert(GREEN != 0);
    assert(BLUE != 5);
}

int main(void) {
    test_color_enum1();
    test_color_enum2();
    test_colors_defined();
    test_colors_defined_correctly();
    printf("All tests passed.\n");
    return 0;
}
