#include <stdio.h>
#include <string.h>

int main(void) {
    char str1[] = "Hi";
    char *str2 = "Snek";
    printf("%s %s\n", str1, str2);

    /* this reserves 50 char so after the null terminator it will have garbage in memory */
    char first[50] = "Snek";
    char *second = "lang!";
    /* strcat knows that it needs to append after the null terminator */
    /* it doesn't know the length of the string but knows where it ends */
    strcat(first, second);
    printf("Hello %s\n", first);
    return 0;
}
