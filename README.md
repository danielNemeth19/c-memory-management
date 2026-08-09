# Learning memory management in C

## Basics
### C Program Structure
In C, the entry point for every program is the `main` functions, unlike Python, which begins execution at the top of the file.
The simplest C program includes an `int main` function that returns an interger exit code,
with `0` indicating successful execution. C enforces strict syntax rules, such as using semicolon to terminate statements and
curly braces `{}` to define the body of functions. However, C ignores whitespace.

Printing in C requires using the `printf` function from the `stdio.h` library. This function allows formatted output,
and explict newlines must be added to strings to achieve line breaks, contrary to Python's `print()` function, which automatically
appends a newline.

#### Examples
```c
#include <stdio.h>

int main() {
    printf("Program in C!\n");
    return 0;
}
```
### C is compiled
C is a compiled language, meaning the source code is transformed into machine code by a compiler before it can be executed.
This process catches certain errors at compile time, preventing the program from running if there are issues like syntax errors
or undeclared functions. Unlike interpreted laguanges, where code execution happens line-by-line, C's compilation process ensures
that the entire program is free of basic errors before it even starts running. This can help catch mistakes early in the development
pUsing the ternary operator to find the maximum of two numbers:rocess, although runtime errors and logical errors still need to be managed.

### Comments in C
C supports two types of comments:
* single-line comments: Use `//` to comment out a single line.
* multi-line comments: Use `/*` to start a comment and `*/` to end it. All text between `/*` and `*/` will be ignored, allowing
for comments spanning multiple lines.

### Basic types
C provides several basic data types to work with numerical and character data. The primary types are include:
* `int`: Represents integer values typically used for counting and indexing
* `float`: Represents floating-point numbers for decimal values and is useful in calculations requiring precision.
* `char`: Represents a single character and typically uses single quotes, e.g. `'a'`.
* `char *`: Represents a pointer to a character array, often used to handle strings although C
does not have a dedicated sting type.

#### Examples
```c
int age = 23;
float salary = 234.34;
char grade = 'A';
char *name = 'John Doe';

printf("Age: %s\n", age);
printf("Salary: %.2f\n", salary);
printf("Grade: %c\n", grade);
printf("Name: %s\n", name);
```

### Strings in C
In C, strings are implemented as arrays of characters, terminated with a null character (`\0`). There is no dedicated `string`
type. Instead, you use a pointer to a `char` to represent strings. This is denoted as `char *`. String literals must be enclosed
in double quotes (`"`), whereas single quotes (`'`) are used for individual characters.

#### Examples
```c
char *name = "John Doe";
printf("Name: %s\n", name);
```
In this code `name` is a pointer to the first character of the string `"John Doe"`.

### Printing in C
In C, the `printf` function is used for formatted output, allowing to print variables by specifying their types with format specifiers.
Unlike Python's f-strings, C requires explicit format specifiers such as `%d` for integers, `%c` for characters, `%f` for
floating-point numbers, and `%s` for strings. Each format specifier must match the corresponding variable type being printed.
Additionally, C does not automatically add a newline character to output, so you must manually include `\n` to print stdout.

| Specifier | Used For                                         |
|-----------|--------------------------------------------------|
| %c        | a single character                               |
| %s        | a string                                         |
| %hi       | short (signed)                                   |
| %hu       | short (unsigned)                                 |
| %Lf       | long double                                      |
| %n        | prints nothing                                   |
| %d        | a decimal integer (assumes base 10)              |
| %i        | a decimal integer (detects the base automatically)|
| %o        | an octal (base 8) integer                        |
| %x        | a hexadecimal (base 16) integer                  |
| %p        | an address (or pointer)                          |
| %f        | a floating point number for floats               |
| %u        | int unsigned decimal                             |
| %e        | a floating point number in scientific notation   |
| %E        | a floating point number in scientific notation   |
| %%        | the % symbol                                     |

#### Examples
```c
int age = 23;
float height = 5.9;
char grade = 'A';
char *name = 'John Doe';

printf("Age: %s\n", age);
printf("Height: %.1f\n", height);
printf("Grade: %c\n", grade);
printf("Name: %s\n", name);
```

### Compilation and Types in C
In C, variables types are explicit and immutable once declared. Unlike Python, where a variable's type can be changed dynamically,
C requires the type to be defined at declaration and does not allow it to change. This ensures type safety and consistency.
Attempts to assign a value of a different type to an existing variable will result in a compilation error.


#### Examples
```c
#include <stdio.h>

int main() {
    char *max_threads = "5";
    // Illegal type change
    // max_threads = 5; // This will raise compilation error
}
Correct usage with consistent types:
```c
#include <stdio.h>

int main() {
    int max_threads = 5;
    printf("Max threads: %d\n", max_threads);

    char *max_threads_str = "5";
    printf("Max threads: %s\n", max_threads_str);
}
```

### Variables
In C each variable must be declared with a specific data type. The data type of a variable cannot be changed after it is declared.
However, the value of the a variable can be updated multiple times as long as the new value is the same type.

When updating the value of a variable, there is no need to specify the data type again; doing so will result in compilation error.

#### Examples
Incorrect variable redeclaration:
```c
int main() {
    int y = 5;
    float y = 3.14; // compilation error: redeclaration of `y` with a different type
}
```

Correct variable value update:
```c
int main() {
    int y = 5;
    y = 10; // valid update of variable `y`
    y = 20; 
```

### Constants
In C, variables can be declared as constants using the `const` qualifier. A constant variable's value cannot
be altered after its initial assignment. This feature is useful for values that should remain unchanged
throughout the program, ensuring data integrity and clarity in code.

Attempting to modify a constant variable will result in a compilation error.

#### Examples
Declaring and using a constant:
```c
int main() {
    const int maxSpeed = 120;

    // Attempting to modify maxSpeed will cause a compilation error
    maxSpeed = 180; // -> error
    return 0;
}

```

### Functions in C
In C, functions define the types for their arguments and return values, making the type enforcement 
a key feature. The syntax for defining a function includes specifying the return type, function name,
and the types of its parameters. Casting is the process of converting one data type to another,
and it is explicitly used in C by placing the type in parentheses before the value to be converted.

#### Examples
Defining and using a function in C:
```c
int multiply(int x, int y) {
    return x * y;
}

int main() {
    int product = multiply(5, 3);
    printf("Product: %d\n", product);
    // Product: 15
    return 0;
}
```
Function with casting:
```c
float divide(int numerator, int denominator) {
    return (float)numerator / denominator;
}

int main() {
    float result = divide(10, 3);
    printf("Quotient: %f\n", result);
    // Quotient: 3.33333
    return 0;
}
```

### Using Void in C
In C, `void` is used to define functions that either do not return a value or do not take any arguments.
When a function is declared with a `void` return type, it indicates that the function does not return a value.
Conversely, using `void` as a parameter in a function signature specifies that the function does not accept
any arguments. Unlike Python's `None`, `void` cannot be used as a value or assigned to a variable.

#### Examples
Function with a void parameter:
```c
int get_integer(void) {
    return 42;
}
```
Function with a void return type:
```c
int print_integer(int x) {
    printf("this is an int: %d\n", x);
}
```

### Math Operators in C
C provides a variety of arithmetic operators for performing mathematical operations: addition (`+`),
subtraction (`-`), multiplication (`*`), and division (`/`). Compound assignment operators such as
`+=`, `-=`, `*=`, `/=` are also supported for updating and assigning values in a single step.

C also introduces increment (`++`) and decrement (`--`) operators, which can be used in postfix (e.g. `x++`)
and prefix (e.g. `++x`) forms. Postfix increments or decrements the value after it is used in an expression,
whereas prefix does it before its used in an expression.

#### Examples
Using arithmetic operators:
```c
int a = 10, b = 5;
int sum = a + b; // 15
int difference = a - b; // 5
int product = a * b; // 50
int quotient = a / b; // 2
```
Postfix vs Prefix
```c
int x = 5;
int y = x++; // y becomes 5, then x becomes 6

int a = 5;
int b = ++a; // a becomes 6, then b becomes 6
```
Casting an integer to a float:
```c
int num = 10;
float floatNum = (float)num; // floatNum is 10.0
```

### Conditional statements
If statements provide basic control flow in C, allowing you to execute code based on conditions.
An if statement evaluates a condition and executes a block of code if the condition is true.
You can extend it with `else if` and `else` to handle multiple conditions.

The syntax for an if statement requires braces `{}` around the code block, but they can be omitted for
a single statement. However, omitting the braces can lead to errors and is generally discouraged for
readability.

#### Examples
Basic if statement:
```c
int temperature = 75;

if (temperature) {
    printf("too hot\n");
} else if (temperature < 70) {
    printf("too cold\n");
} else {
    printf("just right\n");
}
```

### Logical operators
Logical operators in C allow you to combine multiple conditions. The AND operator (`&&`) returs true
only if both operands are true. The OR operator (`||`) returns true if at least one operand is true.
The NOT operator (`!`) inverts a boolean value.

C uses short-circuit evaluation: with `&&`, if the left operand is false, the right operand is never
evaluated. With `||`, if the left operand is true, the right operand is never evaluated. This behavior
is useful for preventing errors and improving performance.

#### Example
Using logical AND:
```c
int age = 25;
int has_license = 1;

if (age >= 18 && has_license) {
    printf("Can drive legally\n");
}

```

Using logical OR:
```c
int is_weekend = 0;
int is_holiday = 1;
if (is_weekend || is_holiday) {
    printf("No work today!\n");
```

Using logical NOT:
```c
int is_raining = 0;
if (!is_raining) {
    printf("Good weather for a walk\n");
```

Combining multiple operators:
```c
int reputation = 150;
int has_2fa = 1;
int is_banned = 0;

if ((reputation >= 100 && has_2fa) || !is_banned) {
    printf("Access granted!\n");
}
```

### Ternary operators
The ternary operator in C is a concise way to perform conditional operations. It evaluates a condition
and selects one of two values based on the result of the evaluation. The ternary syntax is structured
as follows:
* `condition ? value_if_true : value_if_false`

The expression evaluates to `value_if_true` if the condition is true, and `value_if_false` if the condition
is false. It is often used for simple conditional assignments where an `if-else` statement would be
unnecessarily verbose.

#### Example
Using the ternary operator to find the maximum of two numbers:
```c
int score1 = 90;
int score2 = 94;
int highest_score = score1 > score2 ? score1 : score2;
printf("Highest score is: %d\n", highest_score);
```
Assigning a status based on age:
```c
int age = 20;
const char *status = age >= 18 ? "Adult" : "Minor";
printf("Status: %s\n", status);
```

### Type sizes in C
In C, the size of the data type in memory is not consistent across all systems. The architecture of the
system, such as whether it is 32-bit or 64-bit, affects type sizes. For instance, an `int`, might
be 4 bytes on a 32-bit system but 8 bytes on a 64-bit system. The `sizeof` operator can be used to
determine the exact size of a type on a specific platform. Some data types have consistent sizes, like
`char`, which is always 1 byte. The basic C data types include:

* `char`: Always 1 byte, represents a single character, and can be signed or unsigned.
* `float`: Typically 4 bytes, represents a single-precision floating-point number.
* `double`: Typically 8 bytes, represents a double-precision floating-point number.

#### Example
Determining type size with `sizeof`:
```c
#include <stdio.h>
int main () {
    printf("Size of char: %zu byte\n", sizeof(char));
    printf("Size of float: %zu byte\n", sizeof(float));
    printf("Size of double: %zu byte\n", sizeof(double));

    return 0;
}
```

### For loop in C
A `for` loop in C is used to execute a block of code repeatedly. It consists of three main components:
initialization, condition, and final-expression. This control flow structure allows iteration over
a range of values, executing a specified block of code for each iteration. Unlike Python, C does not
have a direct "for each" loop, so you must use indices when iterating over arrays or lists.

#### Examples
Basic `for` loop iterating over indices:
```c
#include <stdio.h>

int main() {
    for (int i = 0; i < 3; i++) {
        printf("Index %d\n", i);
    }
    return 0;
}
```

Iterating over an array using a `for` loop:
```c
#include <stdio.h>

int main() {
    int numbers[] = {10, 20, 30};
    int size = sizeof(numbers) / sizeof(numbers[0]);

    for (int i = 0; i < size; i++) {
        printf("Number: %d\n", numbers[i]);
    }
    return 0;
}
// Output:
// Number: 10
// Number: 20
// Number: 30
```

### While loops in C
A `while` loop in C is used to repeatedly execute a block of code as long as a specified condition
is true. The loop checks the condition before each iteration, and if the condition is false initially
or becomes false during execution, the loop terminates. If the condition remains true indefinitely,
the loop may result in an infinite execution.

#### Examples
Basic example of a `while` loop:
```c
#include <stdio.h>

int main() {
    int count = 3;
    while (count) {
        printf("Countdown: %d\n", count);
        count--;
    }
    return 0;
}
```

### Do while loop in C
A `do while` loop in C is a control flow statement that allows code to be executed repeatedly based on
a given boolean condition, ensuring that the loop body executes at least once. The condition is evaluated
after the execution of the loop body. This makes the `do while` loop distinct from the `while` loop,
which evaluates the condition before the loop body executes.

#### Examples
Basic `do while` loop:
```c
int i = 0;
do {
    printf("i = %d\n", i);
    i++;
} while (i < 3);
// Output:
// i = 0
// i = 1
// i = 2
```
Single execution of loop body when condition is initially false:
```c
int i = 10;
do {
    printf("i = %d\n", i);
    i++;
} while (i < 5);
// Output:
// i = 10
```

### Pragma Once and Header Guards in C
In C, multiple inclusions of the same header file can lead to redefinition errors. Two methods to prevent
this are `#pragma once` and header guards.

`#pragma once` is a preprocessor directive included at the top of a header file to ensure the file is
only included once. It's a modern and less error-prone solution that works with most compilers.

Header guards are another approach using preprocessor directives. They involve defining a unique macro
at the top of the file, and wrapping the file's contents within `#ifndef`, `#define`, and `#endif`
directives. If the macro is already defined (i.e. the file has been included), the guard prevents
reprocessing.

While both methods are effective, `#pragma once` is preferred for its simplicity.

#### Examples
Using `#pragma once`:
```c
// coordinates.h
#pragma once

struct Point {
    int x;
    int y;
};
```

Using header guards:
```c
// coordinates.h
#ifndef COORDINATES_H
#define COORDINATES_H

struct Point {
    int x;
    int y;
};
#endif
```

## Pointers
### Memory and Variable Addresses in C
In computing, an address refers to a specific location in memory, which can be thought of as an array of bytes.
Each byte in memory has a unique address represented as a number. These addresses are frequently displayed in a Hexadecimal format
(base 16) rather than decimal (base 10) because it is more compact and easier to work with in the context of memory management.
For example 0xfff8 in Hexadecimal corresponds to `65,528` in decimal.

In C, variables are human-readable names that reference data stored in memory.
Memory can be visualized as a large array of bytesm where each piece of data is stored at a specific index or address.
The address-of-operator (`&`) is used to retrieve the memory address of a variable. Memory addresses are crucial for understanding pointers and memory management.

Understanding memory addresses is crucial for working with pointers and managing memory in laguanges like C.


### Virtual Memory
Virtual memory is an abstraction layer provided by the operating systems that makes it appear as though a program has direct access
to the entire memory space of a machine. In reality, the operating system manages this access, enabling several advantages.

Key Concepts
- **Physical Memory**: The actual RAM hardware in a computer
- **Operating System**: Manages access to physical memory and provides virtual memory to processess
- **Process**: A running instance of a program that is given access to a segment of virtual memory
- **Virtual Memory**: An abstraction that enables processess to operate as if they have continuous access to a large block of memory

Benefits
1. **Isolation**: Processess are isolated from each other, preventing unauthorized memory access
2. **Security**: Systems can restrict access to certain memory areas, enhancing security
3. **Simplicity**: Developers don't need to manage physical memory directly
4. **Performance**: Memory access is optimized, with data being efficiently moved between RAM and storage as needed.

Overall, virtual memory simplifies programming and enhances system stability and performance by managing how processes interact with memory

### Understanding pointers in C
Pointers in C are variables that store memory addresses, effectively "pointing" to the location of another variable's data.
They are declared with an asterix (`*`) after the type, indicating the variable is a pointer of that type. The address-of-operator (`&`)
is used to obtain the memory address of a variable, which can be then stored in a pointer.

#### Examples
```c
int age = 37;
int *ptr_to_age = &age;
int value_at_prt = *ptr_to_age;
```
Printing the address of a variable:
```c
#include <stdio.h>

int main() {
    int wizardLevel = 5;
    printf("Address of wizardLevel is: %p\n", &wizardLevel);
    // Possible output: Address of wizardLevel is: 0xfff8
    return 0;
}
```

### Pointer dereferencing
Dereferencing a pointer accesses the value stored at the memory address it points to, using the `*` operator. This operator is used
both to declare pointer types and to access the data being pointed to, which can cause confusion.

#### Examples
Declaring and using pointers:
```c
int meaining_of_life = 42;
int *ptr_to_mol = &meaining_of_life;
int value_at_pointer = *ptr_to_mol; // Dereference to get value at the pointer
printf("value_at_pointer: %d\n", value_at_pointer);  // 42
```

Changing a value with pointers:
```c
int speed = 60;
int *pointer_to_speed = &speed;  
*pointer_to_speed = 100;  // Dereferencing to update value stored in speed
```

### Why pointers in C?
Pointers in C are crucial for manipulating data structures like structs. When structs are passed to functions, they are passed by value,
meaming a copy is created, and modifications do not affect the original data unless the struct is returned or pointers are used.
Using pointers allows you to modifiy the original data without creating a copy, makeing functions more efficient by directly manipulating the memory address of the data.

#### Examples
In Python, objects like class instances are inherently passed by reference, allowing modifications within functions to affect the original object:
```python
class Coordinate:
    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z


def update_coordinate(coord, new_x):
    coord.x = new_x


c = Coordinate(1, 2, 3)
update_coordinate(c, 4)
print(c.x)  # 4
```
C Example: Passing by value
In C, structs are passed by value, requiring the struct to be returned *or* pointers to be used for modifications to persist:
```c
struct Coordinate {
    int x, y, z;
};

struct Coordinate coordinate_update_and_return(struct Coordinate coord, int new_x) {
    coord.x = new_x;
    return coord;
}

struct Coordinate c = {1, 2, 3};
c = coordinate_update_and_return(c, 4);
printf("%d\n", c.x);  // 4
```

### Arrow Operator
In C, when you have a struct, fields are accessed using the dot (`.`). However, if you have a pointer to a struct, the arrow (`->`)
operator is used to access the fields. This operator combines dereferencing the pointer and accessing the field in one step, leading to
more concise and readable code compared to using the dereference (`*`) and dot (`.`) operators separately.

The precedence of the `.` operator is higher than the `*` operator, so parentheses are necessary when using `*` to dereference before accessing a member with `.`.

Which explains why the arrow operator is so much more common.

#### Examples
Accessing struct members with a pointer using the arrow operator:
```c
typedef struct {
    int x;
    int y;
    int z;
} coordinate_t,

coordinate_t point = {10, 20, 30};
coordinate_t *ptrToPoint = &point;
printf("X: %d\n", ptrToPoint->x);  // Outputs: X: 10
```

Accessing struct member with a pointer using dereference and dot operators:
```c
printf("X: %d\n", (*ptrToPoint).x);  // Outputs: X: 10
```

### C Arrays
In C, arrays are a fixed-size, ordered collection of elements of the same type, stored in contiguous memory. Arrays are indexed starting from zero,
similar to python lists, but cannot be resized dynamically. Due to their fixed size, they can be more memory efficient and faster for accessing elements
compared to dynamic data structures.

Iterating over arrays in C requires using a loop with an index variable since there's no built-in syntax for iterating directly
over the array elements. You can update array values using the index and assignment syntax `arr[index] = value`.

#### Examples
Declaring and initializing an integer array:
```c
int number[3] = {10, 20, 30};
```
Iterating
```c
#include <stdio.h>

int main() {
    int numbers[3] = {10, 20, 30};

    for (int i=0; i < 3; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
    return 0;
}
```

NOTE: C does **not** provide a built-in `length` attibute for arrays. Size needs to be tracked separately.

### Pointer Arithmetic
In C, the name of an array **acts as a pointer to its first element**, making arrays and pointers closely related. This allows array indexing
and pointer arithmetic to be used interchangeably to access elements. When you add an integer to a pointer, it calculates the offset
based on the size of the data type, allowing direct access to specific array elements.

### Examples
Declare an array and access elements using indexing and pointers:
```c
int numbers[5] = {1, 2, 3, 4, 5};

// Access using index arraying
int valueWithIndex = numbers[2];

// Access using pointer arithmetic
int valueWithPointer = *(numbers + 2);

// Both valueWithIndex and valueWithPointer will be 3
```
Pointer arithmetic
```c
int numbers[5] = {1, 2, 3, 4, 5};
int *ptr = numbers;

// Pointer initially points to the first element
printf("%d\n", *ptr);  // Output: 1

// Move pointer two positions forward
ptr += 2;
printf("%d\n", *ptr);  // Output: 3
```

In these examples, the pointer manipulation demonstatrates how you can traverse an array using pointer arithmetic, achieving the same results
as with traditional array indexing.


## Enums

### Summary

Enums in C allow you to create a set of named integer constants. They are defined using the `enum` keyword and can be made easier to use
with `typedef`. Enums are not collections but rather a way to define a custom type that can have one of the specified named values.
Each name in an enum corresponds to an integer, starting from zero by default.

### Examples

```c
typedef enum Colors {
    RED,
    GREEN,
    BLUE
} color_t;

typedef enum Car {
    char *model;
    color_t color;
} car_t;

car_t myCar;
myCar.model = "Falcon X";
myCar.color = RED;
```

### Non-default Values in C Enums
In C, enums (enumerations) are used to define a set of named integer constants. By default, the first name in an enum is assinged the 
integer value 0, and each subsequent name is assigned an incremented integer value. However, it is possible to assign specific integer values
to enum numbers. This can be useful when the specific number representation of a constant is important, such as defining program exit status codes.

#### Examples
Defining specific values for enum members:
```c
typedef enum {
    RED = 55,
    GREEN = 176,
    BLUE = 38
} Color;
```

Mixing specific and default values:
```c
typedef enum {
    START = 10,
    MIDDLE, // 11
    END // 12
} Progress;
```
### Enumns and Switch Statements in C
In C, enums can be effectively used with switch statements to manage control flow based on named constants, avoiding the use of
"magic numbers" and increasing code readability. Enums provide clear, descriptive names for values, making code easier to understand and maintain.
Switch statements evaluate a variable against a list of cases, executing the block of code corresponding to the matching case.

Each case in a switch statement typically ends with a `break` to prevent fallthrough, where control passes into the next case. However,
deliberate fallthrough is possible by omitting `break`, allowing multiple cases to execute the same block of code.

#### Examples
Basic switch statement with an enum:
```c
enum LogLevel {
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR
}

void logMessage(enum LogLevel level) {
    switch (level) {
        case LOG_DEBUG:
            printf("Debug logging enabled\n");
            break;
        case LOG_INFO:
            printf("Info logging enabled\n");
            break;
        case LOG_WARN:
            printf("Warning logging enabled\n");
            break;
        case LOG_ERROR:
            printf("Error logging enabled\n");
            break;
        default:
            printf("Unknown log level\n");
    }
}
```
Switch statement with intentional fallthrough:
```c
void handleError(int errorCode) {
    switch (errorCode) {
        case 1:
        case 2:
        case 3:
            printf("Minor error occured. Please try again.\n");
            break;
        case 4:
        case 5:
            printf("Major error occured. Restart required.\n");
            break;
        default:
            printf("Unknown error.\n");
    }
}
```
### Size of Enum in C
In C, the `sizeof` operator can be used on enums to determine their size in memory. Typically, enums are stored as integers (`int`),
but if an enums's value exceeds the range of an `int`, a larger integer type like `unsigned int` or `long` may be used by the compiler.
This ensures that all possible enum values can be stored. Enums represent a set of named constants and, from the compiler's perspective,
they are simply integers with  a more readable name.

#### Examples
Defining and using enums with sizeof:
```c
#include <stdio.h>

enum Size {
    SMALL,
    MEDIUM,
    LARGE,
    EXTRA_LARGE
};

int main() {
    printf("Size of Size enum: %zu bytes\n", sizeof(enum Size));
    return 0;
}
```
Enum with large values and checking size:
```c
#include <stdio.h>

enum BigNumbers {
    HUGE = 21474836448, // Larger than typical `int` range
    GIANT,
    COLOSSAL
};

int main() {
    printf("Size of BigNumbers enum: %zu bytes\n", sizeof(enum BigNumbers));
    return 0;
}
```

## Unions

### Summary

Unions in C allow a single variable to store one of several types, but only one type at a time. Unlike structs,
which allocate memory for each field, a union shares the same memory for all of its fields, and only enough space is reserved
to store the largest member. This means writing to one field will overwrite the others, and you should only access the field that
you most recently set. The C compiler uses the list of possible types in a union to determine the maximum memory required.
This feature is useful for memory-efficient data storage when you know only one of the fields will be used at any time.

#### Examples

```c
typedef union {
    int age;
    char *name;
} AgeOrName;

AgeOrName person;
person.age = 30;
printf("Age: %d\n", person.age); // Age: 30

// Accessing a non-set field results in undefined behavior
printf("Name: %s\n", person.name); // Undefined behavior
```

### Union size in C
Unions in C allow for different data types to be stored in the same memory location. The size of a union is determined by the
size of its largest member. This can lead to inefficient memory use if the union frequently stores smaller data types. For example,
a union with an `int` and a `char` array of 256 bytes will always allocate enough memory to accomodate the `char` array, even if
only `int` is used most of the time.

#### Examples
Union with different field sizes:
```c
// This union will always allocate 256 bytes, the size of the largest type
typedef union IntOrErrMessage {
    int data;
    char err[256];
} int_or_err_message_t;

```

### Helper Fields in C Unions
In C, unions allow you to store different data types in the same memory location. A unique use of unions is to create "helper"
fields that provide multiple ways to access the same piece of memory. For example, you can define a union with a struct and a
primitive data type that both occupy the same memory space. This enables reading and writing to the memory via different views:
one offering invidual component access and the other providing access to the whole data at once.

In the example given a union named `Color` has both a `struct` representing RGBA components and a `uint32_t` representation for
the full color. This is efficient as it uses only 4 bytes for both fields, allowing either method to access or modify the color
data depending on your needs.

#### Example
Defining a union with a struct and a full data representation:
```c
typedef union {
    struct {
        uint8_t red;
        uint8_t green;
        uint8_t blue;
        uint8_t alpha;
    } components;
    uint32_t rgba;
} ColorUnion;

ColorUnion color;
color.rgba = 0xFF00FF00; // set color using rgba
printf("Red: %d\n", color.components.red); // access red component
// Red: 0
// accessing `red` is possible because both fields in the union is exactly 32 bytes
```

## Stack and Heap

### Summary
In C programming, memory is divided into the **stack** and the **heap**.

- The **stack** is where local variables are stored.
- Each time a function is called, a new stack frame is created to hold the function's local variables and parameters.
- When the function completes, its stack frame is removed ("popped") from the stack.
- A stack frame consists of:
- Return address (where to continue execution after the function call)
    - Function arguments
    - Local variables
    - The stack operates as a **Last In, First Out (LIFO)** structure: the most recently added stack frame is the first to be removed.

### Why use the stack?

    Allocating memory on the stack is preferred when possible because the stack is faster and simpler than the heap.

    - **Efficient Pointer Management**
    - Stack allocation is just a quick increment or decrement of the stack pointer (extremely fast).
    - Heap allocations require more complex bookkeeping.
- **Cache-Friendly Memory Access**
    - Stack memory is stored in contiguous blocks, enhancing cache performance due to spatial locality.
    - Related values live next to each other in memory, so the CPU can load and access them more quickly.
- **Automatic Memory Management**
    - Stack memory is managed automatically as functions are called and return.
- **Inherent Thread Safety**
    - Each thread has its own stack.
    - Heap allocations require synchronization mechanisms when used concurrently, potentially introducing overhead.

> **Note:**  
> - One reason Go programs are efficient is that Go uses stack allocation for variables when possible (like C).
> - The Go compiler performs escape analysis to decide whether a variable can be allocated on the stack.
> - For example, Python allocates most objects on the heap, which can impact performance.

## Big Endian and  Little Endian
Endiannes is the order in which bytes are stored in memory.
The two most common formats are big endian and little endian.

### Big Endian
In a big-endian system, the most significant byte is stored firs, at the lowest memory address.

Taking `0x123456578` as example. The most significant byte is 0x12 -> this will be stored at the lowest memory address.

### Little Endian
In a little-endian system, the least significant byte is stored firs, at the lowest memory address.

Taking `0x123456578` as example. The least significant byte is 0x78 -> this will be stored at the lowest memory address.

This is the format used by most modern computers.

### Interpreting and Converting Hexadecimal Values

- **Hexadecimal (base 16)** uses digits 0–9 and letters A–F (or a–f) to represent values 0–15.
- Each hex digit represents 4 bits (half a byte). Two hex digits = 1 byte (8 bits).
- To convert a hex number (e.g., `0x12345678`) to decimal:
    - Break it into bytes: `0x12`, `0x34`, `0x56`, `0x78`
    - Each byte’s position represents a power of 256 (since 1 byte = 256 values):
        - `0x12` × 256³
        - `0x34` × 256²
        - `0x56` × 256¹
        - `0x78` × 256⁰
    - Add the results to get the decimal value.
- **Example:**
    - `0x12345678` = (0x12 × 16,777,216) + (0x34 × 65,536) + (0x56 × 256) + (0x78 × 1) = 305,419,896
- **Most significant byte (MSB):** The leftmost byte (highest place value).
- **Least significant byte (LSB):** The rightmost byte (lowest place value).

#### How to Convert a Hexadecimal Byte to Decimal

- Each hex digit represents a power of 16.
- For example, `0x12`:
    - Left digit (`1`): 1 × 16¹ = 16
    - Right digit (`2`): 2 × 16⁰ = 2
    - Add them: 16 + 2 = **18**
- General formula:  
    - For `0xAB`, decimal value = (A × 16) + (B × 1)


## Advanced Pointers
### Pointer-to-Pointer in C
In C, a pointer-to-pointer is a variable that stores the address of another pointer. This allows for the creation of complex data
structures and enables indirect modifications of pointers. The syntax for declaring a pointer-to-pointer involves using double asterisks (**).

Pointer-to-pointer variables are useful for working with mult-level data structures, such as arrays of pointers or when dynamically
allocating memory for complex objects. They enable a chain of dereferences to reach the final value, similar to following a series of linked addresses.

#### Examples
Declare a pointer-to-pointer:
```c
int value = 42;
int  *single_pointer = &value;
int **double_pointer = &single_pointer;

// Dereferencing to access `value`
printf("%d\n", **double_pointer); // 42

```

Modify value using a pointer-to-pointer:
```c
int number = 10;
int  *ptr = &number;
int **ptr_ptr = &ptr;

**ptr_ptr = 20;

printf("%d\n", **ptr_ptr); // 20 

```
After above change, consider below diagramm:
```
Assume:
number  at address 0x100
ptr     at address 0x200
ptr_ptr at address 0x300

Variable   | Address  | Value
-----------|----------|-----------------
number     | 0x100    | 20
ptr        | 0x200    | 0x100 (address of number)
ptr_ptr    | 0x300    | 0x200 (address of ptr)

So:
*ptr      == 20
*ptr_ptr  == 0x100 (address of number)
**ptr_ptr == 20
```

### Array of Pointers in C
In C, array of pointers can be created, which are especially useful for handling strings. An array of pointers can be dynamically allocated
on the heap using the `malloc` function. This allows storing addresses of dynamically allocated memory, faciliating complex data structures
like arrays of strings or arrays of structs.

#### Examples
Creating an array of integer pointers:
```c
int **int_pointer_array = malloc(sizeof(int *) * 3);
int_pointer_array[0] = malloc(sizeof(int));
*int_pointer_array[0] = 10;
int_pointer_array[1] = malloc(sizeof(int));
*int_pointer_array[1] = 20;
int_pointer_array[2] = malloc(sizeof(int));
*int_pointer_array[2] = 30;
```
Creating an array of string pointers:
```c
char **string_array = malloc(sizeof(char *) * 3);
string_array[0] = strdup("apple");
string_array[1] = strdup("banana");
string_array[2] = strdup("cherry");
```

### Void Pointers in C
In C, a `void *` or "void pointer" is a pointer that can hold the address of any data type. This makes void pointers versatile for generic
programming, but they cannot be dereferenced without explicitly casting them to another pointer type. A void pointer must be cast back to its
original type before performing operations like dereferencing.

Casting to void pointers is unique - no type information is preserved when casting a specific type to a void pointer. To utilize the data,
you must cast the void pointer back to the appropriate type.

#### Examples
Basic example showing casting and dereferencing:
```c
int number = 42;
void *generic_ptr = &number;

// Cast to appropriate type before dereferencing
printf("Value of number: %d\n", *(int *)generic_ptr);
```
Example of using void pointers with type information:
```c
typedef enum DATA_TYPE {
    INT,
    FLOAT
} data_type_t;

void printValue(void *ptr, data_type_t type) {
    if (type == INT) {
        printf("Value: %d\n", *(int*)ptr);
    } else if (type == FLOAT) {
        printf("Value: %d\n", *(float*)ptr);
    }
}

int number = 42;
printValue(&number, INT);

float decimal = 3.14;
printValue(&decimal, FLOAT);
```

### Swapping Integers Using pointers in C
In C, swapping two integers using pointers involves accessing the memory loactions directly through their pointers.
The technique requires a temporary variable to store the value of one integer temporarily while the values are swapped.
By manipulating pointers, you can efficiently swap the values stored at two distinct memory addresses without returning them from a function.

#### Examples
Swapping two integers with pointers:
```c
void swap_ints(int *a, int *b) {
    int temp = *a; // Store the value pointed to by `a`
    *a = *b;  // Assign the value pointed to by `b` to the location pointed to by `a`
    *b = temp; // Assign the stored value to the location pointed to by `b`
}

// Usage
int main() {
    int number1 = 10;
    int number2 = 20;
    swap_ints(number1, number2);
    // number1 is now  20
    // number2 is now 10
}
```
### Generic swap (Using memcpy in C)
to be added
