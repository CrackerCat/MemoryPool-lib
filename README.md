# MemoryPool

[Memory pools](https://en.wikipedia.org/wiki/Memory_pool), also called fixed-size blocks allocation, is the use of pools for memory management that allows dynamic memory allocation comparable to malloc or C++'s operator new. As those implementations suffer from fragmentation because of variable block sizes, it is not recommendable to use them in a real time system due to performance. A more efficient solution is preallocating a number of memory blocks with the same size called the memory pool. The application can allocate, access, and free blocks represented by handles at run time.

## Example Usage Library 

```C
int main()
{
    Pool(2, sizeof(char)); // Create Pool

    char *a = p_new(); // get 1 block
    char *b = p_new(); // get 2 block
    
    // Set values
    *a = 'a';
    *b = 'b'; 
    
    // Print values
    puts(a); 
    puts(b);

    // Free pointer block
    p_free(a);  
    p_free(b);  
    
    // Delete Pool
    p_dell();

    return 0;
}
```

## Help

Compiler library 

`gcc -c MemPool-lib/pool.c -I MemPool-lib/ -o MemPool-lib/objs/pool.o`

Usage `#include "MemPool-lib/pool.h"` pass `pool.o` in front of the main



> Notes: Simple Memory Pool, I will add new features : )