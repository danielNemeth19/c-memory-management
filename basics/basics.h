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

void update_file(int filedata[200], int new_filetype, int new_num_lines);

unsigned long size_of_addr(long long i);

#endif
