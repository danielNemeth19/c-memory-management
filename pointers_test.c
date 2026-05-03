#include "pointers.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

static int float_equal(float a, float b) { return fabs(a - b) < 0.0001f; };
static int string_equal(const char *a, const char *b) {
    return strcmp(a, b) == 0;
};
static int int_equal(int a, int b) { return (a - b) == 0; };

void test_print_dump_graphics(void) {
    graphics_t graphics_array[10] = {
        {60, 1080, 1920},  {30, 720, 1280},  {144, 1440, 2560}, {75, 900, 1600},
        {120, 1080, 1920}, {60, 2160, 3840}, {240, 1080, 1920}, {60, 768, 1366},
        {165, 1440, 2560}, {90, 1200, 1920},
    };
    dump_graphics(graphics_array);
}

void test_change_filetype_cpp_to_python(void) {
    codefile_t original;
    original.lines = 100;
    original.filetype = 1;
    codefile_t result = change_filetype(&original, 2);
    assert(int_equal(result.filetype, 2));
    assert(int_equal(result.lines, 100));
}

void test_change_filetype_same_type(void) {
    codefile_t original;
    original.lines = 40;
    original.filetype = 3;
    codefile_t result = change_filetype(&original, 3);
    assert(int_equal(result.filetype, 3));
    assert(int_equal(result.lines, 40));
}

void test_change_filetype_no_mutation(void) {
    codefile_t original;
    original.lines = 40;
    original.filetype = 7;
    codefile_t result = change_filetype(&original, 8);
    assert(int_equal(result.filetype, 8));
    assert(int_equal(original.filetype, 7));
}

void test_get_match_stats(void) {
    int games_played = 0;
    int points = 0;

    get_match_stats(4, 2, 1, &games_played, &points);
    assert(int_equal(games_played, 7));
    assert(int_equal(points, 14));

    get_match_stats(2, 3, 0, &games_played, &points);
    assert(int_equal(games_played, 5));
    assert(int_equal(points, 9));
}

void test_concat_strings_empty_strings(void) {
    char str1[100] = "";
    char *str2 = "";
    concat_strings(str1, str2);
    assert(string_equal(str1, ""));
}

void test_concat_strings_empty_to_nonempty(void) {
    char str1[100] = "nonempty";
    char *str2 = "";
    concat_strings(str1, str2);
    assert(string_equal(str1, "nonempty"));
}

void test_concat_strings_nonempty_to_empty(void) {
    char str1[100] = "";
    char *str2 = "nonempty";
    concat_strings(str1, str2);
    assert(string_equal(str1, "nonempty"));
}

void test_concat_small_strings(void) {
    char mys[] = "abc";
    char mys2[] = "def";
    concat_strings(mys, mys2);
    assert(string_equal(mys, "abcdef"));
}

void test_concat_long_strings(void) {
    char str1[200] = "This is a longer string that ";
    char *str2 = "will be concatened with another long string.";
    concat_strings(str1, str2);
    assert(string_equal(str1, "This is a longer string that will be concatened "
                              "with another long string."));
}

void test_concat_null_terminator_explicit(void) {
    char str1[10];
    memset(str1, 'x', sizeof(str1));
    str1[0] = 'A';
    str1[1] = 'B';
    str1[2] = '\0';

    char *str2 = "CD";
    concat_strings(str1, str2);
    assert(string_equal(str1, "ABCD"));
    assert(str1[4] == '\0');
}

void test_smart_append_handles_null_inputs(void) {
    assert(float_equal(smart_append(NULL, NULL), 1));
    char *str = "ABC";
    assert(float_equal(smart_append(NULL, str), 1));
    TextBuffer tb = {.length = 0, .buffer = ""};
    assert(float_equal(smart_append(&tb, NULL), 1));
}

void test_smart_append_handles_append_if_slots_permit(void) {
    TextBuffer tb = {.length = 0, .buffer = ""};
    char *str = "Hello";
    assert(float_equal(smart_append(&tb, str), 0));
    assert(float_equal(tb.length, strlen(str)));
    assert(string_equal(tb.buffer, str));
}

void test_smart_append_exact_fit(void) {
    char buffer_sample[64];
    memset(buffer_sample, 'x', 60);
    TextBuffer tb = {.length = 60};
    memcpy(tb.buffer, buffer_sample, 60);

    char *str = "OKI";
    int r = smart_append(&tb, str);
    assert(float_equal(r, 0));
    assert(float_equal(tb.length, 63));
}

void test_smart_append_when_src_cannot_fit(void) {
    char buffer_sample[64];
    memset(buffer_sample, 'x', 60);
    TextBuffer tb = {.length = 60};
    memcpy(tb.buffer, buffer_sample, 60);
    char *str = "MYST";
    int r = smart_append(&tb, str);
    assert(float_equal(r, 1));
    assert(float_equal(tb.length, 63));
    assert(tb.buffer[60] == 'M');
    assert(tb.buffer[61] == 'Y');
    assert(tb.buffer[62] == 'S');
    assert(tb.buffer[63] == '\0');
}

void test_new_node_simple(void) {
    snekobject_t node = new_node("root");
    assert(string_equal(node.name, "root"));
    assert(node.child == NULL);
}

void test_new_node_empy_name(void) {
    snekobject_t node = new_node("");
    assert(string_equal(node.name, ""));
    assert(node.child == NULL);
}

void test_new_node_with_child(void) {
    snekobject_t child = new_node("child");
    snekobject_t parent = new_node("parent");
    parent.child = &child;

    assert(string_equal(child.name, "child"));
    assert(child.child == NULL);

    assert(string_equal(parent.name, "parent"));
    assert(parent.child != NULL);

    assert(string_equal(parent.child->name, "child"));
    assert(parent.child->child == NULL);
}

void test_new_node_nested_children(void) {
    snekobject_t grandchild = new_node("child");
    snekobject_t child = new_node("child");
    snekobject_t parent = new_node("parent");
    child.child = &grandchild;
    parent.child = &child;

    assert(string_equal(parent.name, "parent"));
    assert(parent.child->child != NULL);
    assert(string_equal(parent.child->child->name, "child"));
}

void test_assign_employee(void) {
    employee_t emp = create_employee(2, "CEO Karl");
    department_t dept = create_department("Finance");
    assign_employee(&emp, &dept);

    assert(string_equal(emp.name, "CEO Karl"));
    assert(string_equal(emp.department->name, "Finance"));
}

void test_assign_manager(void) {
    employee_t manager = create_employee(3, "Influencer Prime");
    department_t dept = create_department("Marketing");
    assign_manager(&dept, &manager);

    assert(int_equal(manager.id, 3));
    assert(string_equal(dept.name, "Marketing"));
    assert(string_equal(dept.manager->name, "Influencer Prime"));
}

int main(void) {
    test_print_dump_graphics();
    test_change_filetype_cpp_to_python();
    test_change_filetype_same_type();
    test_change_filetype_no_mutation();
    test_get_match_stats();
    test_concat_strings_empty_strings();
    test_concat_strings_empty_to_nonempty();
    test_concat_strings_nonempty_to_empty();
    test_concat_small_strings();
    test_concat_long_strings();
    test_concat_null_terminator_explicit();
    test_smart_append_handles_null_inputs();
    test_smart_append_handles_append_if_slots_permit();
    test_smart_append_exact_fit();
    test_smart_append_when_src_cannot_fit();
    test_new_node_simple();
    test_new_node_empy_name();
    test_new_node_with_child();
    test_new_node_nested_children();
    test_assign_employee();
    test_assign_manager();
    printf("All tests passed.\n");
    return 0;
}
