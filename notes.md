# Unions

## Summary

Unions in C allow a single variable to store one of several types, but only one type at a time.

Unlike structs, which allocate memory for each field,
- a union shares the same memory for all of its fields
- only enough space is reserved to store the largest member
- writing to one field will overwrite the others -> only recently set field should be accessed
- the C compiler uses the list of possible types in a union to determine the maximum memory required
- this makes unions memory-efficient data storage when we know that only one field will be used at any time

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

