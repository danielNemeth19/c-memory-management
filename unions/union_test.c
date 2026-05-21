#include "union.h"
#include <assert.h>
#include <limits.h>
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
    snek_object_t i = new_integer(5);
    format_object(i, buffer);
    assert(string_equal(buffer, "int:5"));
}

void test_format_objects_int2(void) {
    char buffer[100];
    snek_object_t i = new_integer(2014);
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

    assert(header.tcp_header.src_port == 0x1234);
    assert(header.tcp_header.dest_port == 0x5678);
    assert(header.tcp_header.seq_num == 0x9ABCDEF0);
}

void test_field_raw_size(void) {
    assert(sizeof(((packet_header_t *)0)->raw) == 8);
}

void test_field_to_raw_consistency(void) {
    packet_header_t header = {0};

    header.tcp_header.src_port = 0x1234;
    header.tcp_header.dest_port = 0x5678;
    header.tcp_header.seq_num = 0x9ABCDEF0;

    /*
    since packet_header_t` is a union, `header.tcp_header` and `header.raw`
    share the same memory. When tcp_header is set, those bytes are reflected in
    `raw` too.

    `src_port = 0x1234` (16 bits)
    `dest_port = 0x5678` (16 bits)
    `seq_num = 0x9ABCDEF0` (32 bits)

    **How are these stored in `raw`?**
    - On little-endian systems (like most Linux machines), the least significant
    byte comes first in memory.
    - So, for `src_port = 0x1234`:
      - `raw[0] = 0x34`
      - `raw[1] = 0x12`
    */

    assert(header.raw[0] == 0x34);
    assert(header.raw[1] == 0x12);
    assert(header.raw[2] == 0x78);
    assert(header.raw[3] == 0x56);
    assert(header.raw[4] == 0xF0);
    assert(header.raw[5] == 0xDE);
    assert(header.raw[6] == 0xBC);
    assert(header.raw[7] == 0x9A);
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
    test_field_raw_size();
    test_field_to_raw_consistency();
    printf("All tests passed.\n");
    return 0;
}
