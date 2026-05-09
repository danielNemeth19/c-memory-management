#include "union.h"
#include <assert.h>
#include <math.h>
#include <limits.h>
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

void test_packet_header_size(void) {
    assert(float_equal(sizeof(packet_header_t), 8));
}

void test_packet_header_fields(void) {
    packet_header_t header;
    header.tcp_header.src_port = 0x1234;
    header.tcp_header.dest_port = 0x5678;
    header.tcp_header.seq_num = 0x9ABCDEF0;

    assert(float_equal(header.tcp_header.src_port, 0x1234));
    assert(float_equal(header.tcp_header.dest_port, 0x5678));
    assert(header.tcp_header.seq_num == 0x9ABCDEF0);
}

void test_field_raw_size(void) {
    assert(float_equal(sizeof(packet_header_t *)0) -> raw, 8)));
}

void test_sizes_of_union(void) {
    val_or_err_t val_set = {.value = -420};
    printf("value (set): %d\n", val_set.value);
    printf("err (unset): %u\n", val_set.err);

    val_or_err_t err_set = {.err = UINT_MAX};
    printf("value (unset): %d\n", err_set.value);
    printf("err (set): %u\n", err_set.err);
}

int main(void) {
    test_format_objects_int1();
    test_format_objects_int2();
    test_format_objects_str1();
    test_format_objects_str2();
    test_packet_header_size();
    test_sizes_of_union();
    test_packet_header_size();
    test_packet_header_fields();
    printf("All tests passed.\n");
    return 0;
}
