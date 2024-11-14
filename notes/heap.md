# HEAP

```c
// important functions (90%+)
malloc() // gives a pointer
free() // use pointer from malloc
=====
aligned_alloc()
calloc() // allocates an array
realloc() // deallocates old object pointed to by ptr
```
- free()
    - De-allocates memory
    - Only pass pointers that are from malloc
    - Only free things one time
        - Will crash if more than once
        - Crashes later
- aligned_alloc()
    - 
- calloc(): multiples together
    - nmemb number of elemnts in array
    - size: size of individual element

## Heap Related Problems
- Memory Leaks: Failure to free memory when it is no longer needed
    - Similar to heart disease, memory grows and grows
- Dangling References: Pointers still exist to memory that was freed
    - Points to something that is no longer valid
    - Just because you have freed something, doesnt mean the pointer is no longer around
    - If you use a pointer, might be benign, memory untouched
    - Memory can be marked as inaccesible leading to a segmentation violation
- Double Free: Attempting to dellocate memory that has already been deallocated

## Management of heap

### Goals
- Maximize Throughput: Performance Matters
- Maximize Memory Utilization: Size Matters

### Constraints
- Arbitrary Request Sequences
- Immediate Response to requests (cannot reorder the requests)
- The only memory available to use is the heap
- Cannot move or modify allocated blocks

## Other
- Once you have allocated, cannot take it back until applciation frees it
- sbrk() allocates more memory

## Design Decisions
- How are free blocks managed
- How to satisfy a request?
    - First fit?
    - Best fit?
    - Others?
- Error dectections to support?

## GCC Heap Properties
- mmap for very large requests (>=128K)
- Best fit allocator for larger requests (>=512 bytes)
- Caching allocator that maintains pools of quickly recycled chunks for small requests(<=64 bytes>)
- Hybrid approach for requests between 64 and 512 bytes
- Minimum overhead allocated chunk: 8 bytes
- Minimum allocated size: 32 bytes (including 8 byte overhead)

## Application Design Decision
- Will dynamic memory allication onlu occur during initialization
- Real time or safety critical applicaiton coding standard may require this
    - Real Time
        - Time matters in applications
        - Right answer late is wrong
        - i.e. games
    - Safety Crical Applications
        - Failure can cost lives or property damage
        - i.e. Flight control system
    - Avionics are a mix of both
- Why?

### How to Prevent Memory Leaks
- A memory leak is when memory is allocated and never deallocated
- Tools
    - Static analysis tools (fortify)
    - Dynamic analysis tools (valgrind)
- Coding Style
    - Single exit from each function. Clean up allocated memory before exit

## Garbage Collection
- Form of automatic memory management
- Programmer is no longer responsible for freeing objects that are no longer used
- i.e. Java, Javascript, Python, and other functional languages