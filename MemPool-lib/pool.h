#pragma once

#include <stdlib.h>
#include <stddef.h>

typedef void* byte;

// hearder block structures
struct BlkHeader
{
    size_t size;
    __uint8_t index;
};

// Enumerate memory free errors
enum FREE
{
    FAIL_FREE = -1,
    SUCESS_FREE
};

long HeadSize;
size_t BlkSize; // size of each block
size_t BlkCount; // block quantities
size_t TotalSize; // Total allocated in Arena

byte *Memory; // pointing to the beginning of memory
byte *Head;   // pointer memory free not allocated

void Pool(size_t __block_c, size_t  __block_s);

void *p_new(); // create new block
__uint8_t p_free(void *__ptr); // dealoc pointer 
__uint8_t p_dell(); // delete arena
