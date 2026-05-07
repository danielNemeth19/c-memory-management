#include "union.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

static int float_equal(float a, float b) { return fabs(a - b) < 0.0001f; };
static int string_equal(const char *a, const char *b) {
    return strcmp(a, b) == 0;
};
static int int_equal(int a, int b) { return (a - b) == 0; };

void test_format_objects_int1(void) {
    char buffer[100];
    snek_object_t i =new_integer(5);
    format_object(i, buffer);
    assert(string_equal(buffer, "int:5"));
}

void test_format_objects_int2(void) {
    char buffer[100];
    snek_object_t i =new_integer(2014);
    format_object(i, buffer);
    assert(string_equal(buffer, "int:2014"));
}

void test_format_objects_str1(void) {
    char buffer[100];
    snek_object_t i = new_string("test");
    format_object(i, buffer);
    assert(string_equal(buffer, "string:test"));
}

void test_format_objects_str2(void) {
    char buffer[100];
    snek_object_t i = new_string("nvim btw");
    format_object(i, buffer);
    printf("got: %s\n", buffer);
    assert(string_equal(buffer, "string:nvim btw"));
}

int main(void) {
    test_format_objects_int1();
    test_format_objects_int2();
    test_format_objects_str1();
    test_format_objects_str2();
    printf("All tests passed.\n");
    return 0;
}
