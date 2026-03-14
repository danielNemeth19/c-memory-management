#include "exercise_1.h"
#include <stdio.h>

float get_average(int x, int y, int z) {
    int sum = x + y + z;
    float avg = sum / 3.0f;
    return avg;
}

float snek_score(int num_files, int num_contributors, int num_commits,
                 float avg_bug_criticality) {
    int size_factor = num_files * num_commits;
    int complexity_factor = size_factor + num_contributors;
    float snek_score = complexity_factor * avg_bug_criticality;
    return snek_score;
}

char *get_temperature_status(int temp) {
    if (temp < 51) {
        return "too cold";
    }
    if (temp > 99) {
        return "too hot";
    }
    return "just right";
}

/* ---- Operator Precedence ----
| Operator | Description   | Precedence |
|----------|--------------|------------|
| `!`      | NOT           | Highest    |
| `&&`     | AND           | Middle     |
| `||`     | OR            | Lowest     |

Logical NOT (!) is a unary operator, so naturally has higher precedence
Logical AND (&&) is more binding than OR as both sides must be true
Logical OR (||) is the less binding, hence lowest precedence

To state the obvious: below function doesn't use logical NOT and applies
parentheses too

*/
int can_access_registry(int is_premium, int reputation, int has_2fa) {
    int verdict = is_premium || (reputation >= 100 && has_2fa);
    return verdict;
}

void print_numbers(int start, int end) {
    for (int i = start; i < end + 1; i++) {
        printf("current number is: %d\n", i);
    }
}

void print_numbers_reverse(int start, int end) {
    int i = start;
    while (i >= end) {
        printf("current number is: %d\n", i);
        i--;
    }
}

void print_numbers_reverse_do_while(int start, int end) {
    int i = start;
    do {
        printf("current number is: %d\n", i);
        i--;
    } while (i >= end);
}
