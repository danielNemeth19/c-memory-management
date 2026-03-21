#include "coord.h"

coordinate_t new_coord(int x, int y, int z) {
    coordinate_t c = {.x = x, .y = y, .z = z};
    return c;
}

coordinate_t scale_coordinate(coordinate_t coord, int factor) {
    // compound assign operator
    coord.x *= factor;
    coord.y *= factor;
    coord.z *= factor;
    return coord;
}

void coordinate_update_x(coordinate_t coord, int new_x) { coord.x = new_x; }

coordinate_t coordinate_update_and_return_x(coordinate_t coord, int new_x) {
    coord.x = new_x;
    return coord;
}
