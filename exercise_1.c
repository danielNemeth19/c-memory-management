#include "exercise_1.h"

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
