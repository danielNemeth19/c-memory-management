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

void test_http_switch_statement(void) {
    assert(string_equal(http_to_str(HTTP_BAD_REQUEST), "400 Bad Request"));
    assert(string_equal(http_to_str(HTTP_UNAUTHORIZED), "401 Unauthorized"));
    assert(string_equal(http_to_str(HTTP_NOT_FOUND), "404 Not Found"));
    assert(string_equal(http_to_str(HTTP_TEAPOT), "418 I AM A TEAPOT!"));
    assert(string_equal(http_to_str(HTTP_INTERNAL_SERVER_ERROR),
                        "500 Internal Server Error"));
    assert(string_equal(http_to_str(HTTP_BAD_REQUEST), "400 Bad Request"));

    assert(string_equal(http_to_str((http_error_code_t)999),
                        "Unknown HTTP status code"));
}

void test_packet_header_size(void) {
    assert(float_equal(sizeof(packet_header_t), 8));
}

int main(void) {
    test_color_enum1();
    test_color_enum2();
    test_colors_defined();
    test_colors_defined_correctly();
    test_http_switch_statement();
    printf("The size of BigNumbers is %zu bytes\n", sizeof(BigNumbers));
    printf("The size of HttpErrorCode is %zu bytes\n", sizeof(http_error_code_t));
    printf("All tests passed.\n");
    return 0;
}
