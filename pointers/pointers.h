#ifndef POINTERS_1_H
#define POINTERS_1_H

#include <string.h>

typedef struct SneklangVar {
    double weight;
    int value;
    int scope_level;
    char *name;
    char type;
    char is_constant;
} sneklang_var_t;

typedef struct CodeFile {
    int lines;
    int filetype;
} codefile_t;

codefile_t change_filetype(codefile_t *f, int new_filetype);

void update_file(int filedata[200], int new_filetype, int new_num_lines);

void get_match_stats(int wins, int draws, int losses, int *games_played,
                     int *points);

typedef struct Graphics {
    int fps;
    int height;
    int width;
} graphics_t;

void dump_graphics(graphics_t gsettings[10]);

void concat_strings(char *str1, char *str2);

typedef struct {
    size_t length;
    char buffer[64];
} TextBuffer;

int smart_append(TextBuffer *dest, const char *src);

typedef struct SnekObject snekobject_t;

typedef struct SnekObject {
    char *name;
    snekobject_t *child;
} snekobject_t;

snekobject_t new_node(char *name);

typedef struct Department department_t;
typedef struct Employee employee_t;

typedef struct Employee {
    int id;
    char *name;
    department_t *department;
} employee_t;

typedef struct Department {
    char *name;
    employee_t *manager;
} computer_t;

employee_t create_employee(int id, char *name);
department_t create_department(char *name);

void assign_employee(employee_t *emp, department_t *department);
void assign_manager(department_t *department, employee_t *manager);

#endif
