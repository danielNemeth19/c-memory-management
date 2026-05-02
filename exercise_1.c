#include "exercise_1.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

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

/* pointer is passed in so no automatic copy created automatically
   but still allocates a new struct, leaving the original untouched
   eventhough the pointer would allow us to modify the struct in place */
codefile_t change_filetype(codefile_t *f, int new_filetype) {
    codefile_t new_f = *f;
    new_f.filetype = new_filetype;
    return new_f;
}

void update_file(int filedata[200], int new_filetype, int new_num_lines) {
    for (int i = 0; i < 200; i++) {
        if (i == 1) {
            filedata[i] = new_num_lines;
        } else if (i == 2) {
            filedata[i] = new_filetype;
        } else if (i == 199) {
            filedata[i] = 0;
        }
    }
}

void get_match_stats(int wins, int draws, int losses, int *games_played,
                     int *points) {
    int p = wins * 3 + draws * 1;
    int g = wins + draws + losses;
    *points = p;
    *games_played = g;
};

void dump_graphics(graphics_t gsettings[10]) {
    int *ptr = (int *)gsettings;
    for (int i = 0; i < 30; i++) {
        printf("settings[i] is: %d\n", ptr[i]);
    };
};

void concat_strings(char *str1, char *str2) {
    /* let's use a while loop and pointer dereference to find the null
     * terminator */
    char terminator = '\0';
    int len_str1 = 0;
    while (*(str1 + len_str1) != terminator) {
        len_str1++;
    }
    int len_str2 = 0;
    while (*(str2 + len_str2) != terminator) {
        *(str1 + len_str1 + len_str2) = *(str2 + len_str2);
        len_str2++;
    }
    *(str1 + len_str1 + len_str2) = terminator;
}

int smart_append(TextBuffer *dest, const char *src) {
    if (dest == NULL || src == NULL) {
        return 1;
    }
    size_t buffer_len = sizeof(dest->buffer);
    size_t len_src = strlen(src);
    size_t free_slots = buffer_len - dest->length - 1;
    printf("free (%zu) - len of src (%zu) - %s\n", free_slots, len_src, src);
    if (free_slots >= len_src) {
        strcat(dest->buffer, src);
        dest->length += len_src;
        return 0;
    } else {
        strncat(dest->buffer, src, free_slots);
        dest->length = buffer_len - 1;
        return 1;
    }
}

snekobject_t new_node(char *name) {
    snekobject_t node = {
        .name = name,
        .child = NULL,
    };
    return node;
}

employee_t create_employee(int id, char *name) {
    employee_t emp = {.id = id, .name = name, .department = NULL};
    return emp;
}

department_t create_department(char *name) {
    department_t dept = {
        .name = name,
        .manager = NULL,
    };
    return dept;
}

void assign_employee(employee_t *emp, department_t *department) {
    emp->department = department;
}

void assign_manager(department_t *dept, employee_t *manager) {
    dept->manager = manager;
}
