#ifndef EXERCISE_1_H
#define EXERCISE_1_H

#include <string.h>

float get_average(int x, int y, int z);

float snek_score(int num_files, int num_contributors, int num_commits,
                 float avg_bug_criticality);

char *get_temperature_status(int temp);

int can_access_registry(int is_premium, int reputation, int has_2fa);

void print_numbers(int start, int end);

void print_numbers_reverse(int start, int end);
void print_numbers_reverse_do_while(int start, int end);

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

#endif
