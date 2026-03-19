#pragma once

typedef struct Coordinate {
    int x;
    int y;
    int z;
} coordinate_t;

coordinate_t new_coord(int x, int y, int z);

coordinate_t scale_coordinate(coordinate_t coord, int factor);

void coordinate_update_x(coordinate_t coord, int new_x);

coordinate_t coordinate_update_and_return_x(coordinate_t coord, int new_x);
