#include "pointers.h"

#include <stdio.h>

void get_match_stats(int wins, int draws, int losses, int *games_played,
                     int *points) {
    int p = wins * 3 + draws * 1;
    int g = wins + draws + losses;
    *points = p;
    *games_played = g;
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

/* pointer is passed in so no automatic copy created automatically
   but still allocates a new struct, leaving the original untouched
   eventhough the pointer would allow us to modify the struct in place */
codefile_t change_filetype(codefile_t *f, int new_filetype) {
    codefile_t new_f = *f;
    new_f.filetype = new_filetype;
    return new_f;
}

void dump_graphics(graphics_t gsettings[10]) {
    int *ptr = (int *)gsettings;
    for (int i = 0; i < 30; i++) {
        printf("settings[i] is: %d\n", ptr[i]);
    };
};

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
