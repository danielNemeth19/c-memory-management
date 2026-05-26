#include <stdio.h>
#include <stdlib.h>

void allocate_int(int **pointer_pointer, int value);

typedef struct Token {
    char *literal;
    int line;
    int column;
} token_t;

token_t **create_token_pointer_array(token_t *tokens, size_t count);


typedef enum SkekObjectKind {
    INTEGER,
    FLOAT,
    BOOL,
} snek_object_kind_t;


typedef struct SneakInt {
    char *name;
    int value;
} snek_int_t;


typedef struct SneakFloat {
    char *name;
    long _pad;
    float value;
} snek_float_t;


typedef struct SneakBool {
    char *name;
    long _pad;
    unsigned int value;
} snek_bool_t;


void snek_zero_out(void *ptr, snek_object_kind_t kind);
