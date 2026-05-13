#include "stack_and_heap.h"
#include <stdio.h>

int main() {
    printMessageOne();
    printMessageTwo();
    printMessageThree();
    return 0;
}

/* __attribute__((noinline)) is a GCC and CLANG compiler
 * specific attribute that tells the compiler **not to inline**
 * the decorated function */
__attribute__((noinline)) void printMessageOne(void) {
    const char *message = "Dark mode?\n";
    printStackPointerDiff();
    printf("%s\n", message);
}

__attribute__((noinline)) void printMessageTwo(void) {
    const char *message = "More like...\n";
    printStackPointerDiff();
    printf("%s\n", message);
}

__attribute__((noinline)) void printMessageThree(void) {
    const char *message = "dark roast.\n";
    printStackPointerDiff();
    printf("%s\n", message);
}

/* The printout will be positive because the stack pointer decreases (moves to a
 * lower address) as we go deeper into function calls, so subtracting the new
 * (lower) address from the previous (higher) address yields a positive number.
 */
void printStackPointerDiff(void) {
    static void *last_sp = NULL;
    void *current_sp;
    current_sp = __builtin_frame_address(0);
    long diff;
    if (last_sp == NULL) {
        last_sp = current_sp;
        diff = 0;
    } else {
        diff = (char *)last_sp - (char *)current_sp;
    }
    printf("----------------------------------\n");
    printf("Stack pointer offset: %ld bytes\n", diff);
    printf("----------------------------------\n");
}
