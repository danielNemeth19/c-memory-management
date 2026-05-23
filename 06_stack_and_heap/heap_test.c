#include "heap.c"
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

bool is_on_stack(void *ptr) {
    void *stack_top = __builtin_frame_address(0);
    uintptr_t stack_top_addr = (uintptr_t)stack_top;
    uintptr_t ptr_addr = (uintptr_t)ptr;

    // check within a threshold in both directions
    uintptr_t threshold = 1024;
    return ptr_addr >= (stack_top_addr - threshold) &&
           ptr_addr <= (stack_top_addr + threshold);
}

static int string_equal(const char *a, const char *b) {
    return strcmp(a, b) == 0;
};

void test_basic_greeting_result_points_to_memory_on_the_heap(void) {
    char *result = get_full_greeting("Hello", "Alice", 20);
    assert(string_equal(result, "Hello Alice"));
    assert(is_on_stack(result) == false);
    free(result);
}

void test_result_itself_lives_on_the_stack(void) {
    char *result = get_full_greeting("Hey", "Bob", 4);
    assert(is_on_stack(&result) == true);
    free(result);
}

void test_short_buffer(void) {
    char *result = get_full_greeting("Hey", "Bob", 4);
    assert(string_equal(result, "Hey"));
    assert(is_on_stack(result) == false);
    free(result);
}


int main(void) {
    test_basic_greeting_result_points_to_memory_on_the_heap();
    test_result_itself_lives_on_the_stack();
    test_short_buffer();
    printf("All tests passed.\n");
    return 0;
}
