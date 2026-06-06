# Learning memory management in C

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
Virtual memory is an abstraction layer providede by the operating systems that makes it appear as though a program has direct access
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

## Unions

### Summary

Unions in C allow a single variable to store one of several types, but only one type at a time.

Unlike structs, which allocate memory for each field,
- a union shares the same memory for all of its fields
- only enough space is reserved to store the largest member
- writing to one field will overwrite the others -> only recently set field should be accessed
- the C compiler uses the list of possible types in a union to determine the maximum memory required
- this makes unions memory-efficient data storage when we know that only one field will be used at any time

### Examples

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
