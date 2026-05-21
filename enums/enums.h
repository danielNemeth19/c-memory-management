#ifndef ENUMS_H
#define ENUMS_H

typedef enum Color_old {
    RED_OLD,
    GREEN_OLD,
    BLUE_OLD
} color_old_t;

typedef enum Color {
    RED = 55,
    GREEN = 176,
    BLUE = 38
} color_t;

typedef enum {
    HTTP_BAD_REQUEST = 400,
    HTTP_UNAUTHORIZED = 401,
    HTTP_NOT_FOUND = 404,
    HTTP_TEAPOT = 418,
    HTTP_INTERNAL_SERVER_ERROR = 500,
} http_error_code_t;

char *http_to_str(http_error_code_t code);

typedef enum {
    BIG = 123412341234,
    BIGGER,
    BIGGEST
} BigNumbers;

#endif

