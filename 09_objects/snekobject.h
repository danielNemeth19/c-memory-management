#include <stdlib.h>

typedef enum SneakObjectKind {
    INTEGER
} snek_object_kind_t;

typedef union SnekObjectData {
    int v_int;
} snek_object_data_t;

typedef struct SnekObject {
    snek_object_kind_t kind;
    snek_object_data_t data;
} snek_object_t;
