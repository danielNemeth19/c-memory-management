#include <stddef.h>
#include <stdio.h>
#include <string.h>

int built_ins(void) {
    char src1[] = "Hello";
    char dest1[6];

    // Copies a string to another
    strcpy(dest1, src1);
    printf("copy result: %s\n", dest1);

    char src2[] = "Hello";
    char dest2[6];

    // Copies a specified number of chars from one string to another
    strncpy(dest2, src2, 3);
    // ensure null termination
    dest2[3] = '\0';
    printf("copy result: %s\n", dest2);

    // Concatenates one string to another
    char dest3[12] = "Hello";
    char src3[] = " World";
    strcat(dest3, src3);
    printf("concat result: %s\n", dest3);

    // Concatenates a specified number of chars from one string to another
    char dest4[12] = "Hello";
    char src4[] = " World";
    strncat(dest4, src4, 3); // Hello Wo
    printf("n concat result: %s\n", dest4);

    // strlen returns the length
    char str[] = "Hello";
    size_t len = strlen(str);
    printf("Len is %zu\n", len);

    // strcmp compares two strings lexicographically
    char str2[] = "Hello";
    char str3[] = "World";
    int result = strcmp(str2, str3);
    printf("result is negative if strings not equal: %d\n", result);

    int result2 = strcmp("same", "same");
    printf("result is negative if strings not equal: %d\n", result2);

    // strchr finds first occurence of a charachter in a string
    char str4[] = "Hello";
    char *pos = strchr(str4, 'l');
    // to print a char, the pointer DOES need to be dereferenced
    printf("pos points to: %c\n", *pos);

    // strstr finds the occurence of a substring in a string
    char str5[] = "Hello World";
    char *pos2 = strstr(str5, "World");
    // %s expects a pointer to the start of the string
    // so pos2 does NOT need to be dereferenced
    printf("pos2 points to: %s\n", pos2);
    return 0;
}

int main(void) {
    char str1[] = "Hi";
    char *str2 = "Snek";
    printf("%s %s\n", str1, str2);

    /* this reserves 50 char so after the null terminator it will have garbage
     * in memory */
    char first[50] = "Snek";
    char *second = "lang!";
    /* strcat knows that it needs to append after the null terminator */
    /* it doesn't know the length of the string but knows where it ends */
    strcat(first, second);
    printf("Hello %s\n", first);

    built_ins();
    return 0;
}
