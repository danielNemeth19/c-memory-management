#include "coord.h"
#include <signal.h>
#include <stdio.h>

/* Example memory layout */
/* Address 	Element 	    Value 	Offset (bytes) */
/* 0x2000 	points[0].x 	1 	    0 */
/* 0x2004 	points[0].y 	2 	    4 */
/* 0x2008 	points[0].z 	3 	    8 */
/* 0x200C 	points[1].x 	4 	    12 */
/* 0x2010 	points[1].y 	5 	    16 */
/* 0x2014 	points[1].z 	6 	    20 */
/* 0x2018 	points[2].x 	7 	    24 */
/* 0x201C 	points[2].y 	8 	    28 */
/* 0x2020 	points[2].z 	9 	    32 */

int multibyte_arrays(void) {
    coordinate_t points[3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
    };
    printf("points[1].x = %d , points[1].y = %d, points[1].z = %d\n",
           points[1].x, points[1].y, points[1].z);

    coordinate_t *ptr = points;
    printf("ptr[1].x = %d , ptr[1].y = %d, ptr[1].z = %d\n", (ptr + 1)->x,
           (ptr + 1)->y, (ptr + 1)->z);
    return 0;
}

int array_casting(void) {
    coordinate_t points[3] = {
        {5, 4, 1},
        {7, 3, 2},
        {9, 6, 8},
    };
    int *points_start = (int *)points;
    for (int x = 0; x < 9; x++) {
        printf("x here is %d\n", points_start[x]);
    };
    return 0;
}

void core_utils_func(int core_utilization[]) {
    printf("sizeof core_utilization in core_utils_func: %zu\n",
           sizeof(core_utilization));
}

void passed_array_decays_to_pointer_test(void) {
    int core_utilization[] = {34, 35, 456, 34, 67, 23, 87, 44};
    int len = sizeof(core_utilization) / sizeof(core_utilization[0]);
    printf("sizeof core_utilization in main %zu\n", sizeof(core_utilization));
    printf("len of core_utilization: %d\n", len);
    core_utils_func(core_utilization);
}

int main(void) {
    multibyte_arrays();
    array_casting();
    passed_array_decays_to_pointer_test();
    return 0;
}
