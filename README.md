# Learning memory management in C

# Unions

## Summary

Unions in C allow a single variable to store one of several types, but only one type at a time.

Unlike structs, which allocate memory for each field,
- a union shares the same memory for all of its fields
- only enough space is reserved to store the largest member
- writing to one field will overwrite the others -> only recently set field should be accessed
- the C compiler uses the list of possible types in a union to determine the maximum memory required
- this makes unions memory-efficient data storage when we know that only one field will be used at any time

## Examples

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

# Stack and Heap

## Summary
In C programming, memory is divided into the **stack** and the **heap**.

- The **stack** is where local variables are stored.
    - Each time a function is called, a new stack frame is created to hold the function's local variables and parameters.
    - When the function completes, its stack frame is removed ("popped") from the stack.
    - A stack frame consists of:
        - Return address (where to continue execution after the function call)
        - Function arguments
        - Local variables
    - The stack operates as a **Last In, First Out (LIFO)** structure: the most recently added stack frame is the first to be removed.

## Why use the stack?

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


