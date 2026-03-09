#include "exercise_1.h"
#include <assert.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

static int float_equal(float a, float b) { return fabs(a - b) < 0.0001f; };
static int string_equal(const char *a, const char *b) { return strcmp(a, b) == 0; };

static void test_get_average(void) {
  assert(float_equal(get_average(3, 4, 5), 4.0f));
  assert(float_equal(get_average(3, 3, 5), 11.0f / 3.0f));
  assert(float_equal(get_average(10, 10, 10), 10.0f));
  assert(float_equal(get_average(1050, 2050, 2075), 1725.0f));
}

static void test_snek_score(void) {
  assert(float_equal(snek_score(3, 4, 5, 0.1), 1.9));
  assert(float_equal(snek_score(10, 10, 10, 0.1), 11));
  assert(float_equal(snek_score(105, 205, 207, 0.1), 2194));
}

static void test_get_temperature_status(void) {
  char *t = get_temperature_status(50);
  assert(string_equal(get_temperature_status(50), "too cold"));
  assert(string_equal(get_temperature_status(100), "too hot"));
  assert(string_equal(get_temperature_status(70), "just right"));
  assert(string_equal(get_temperature_status(75), "just right"));
}

int main(void) {
  test_get_average();
  test_snek_score();
  test_get_temperature_status();
  printf("All tests passed.\n");
  return 0;
}
