#include <stdio.h>
#include <sys/mman.h>
#include <string.h>

#include "pool.h"

/**
 * @brief create arena
 *
 * @param __block_c number of blocks
 * @param __block_s block size
 */
void Pool(size_t __block_c, size_t __block_s)
{
    HeadSize = sizeof(byte *);
    BlkCount = __block_c;
    BlkSize = HeadSize + __block_s;
    TotalSize = BlkCount * HeadSize;

    Memory = mmap(NULL, TotalSize, PROT_WRITE | PROT_READ, MAP_PRIVATE | MAP_ANON, -1, 0);
    if (Memory == MAP_FAILED)
    {
        Memory = NULL;
        fprintf(stderr, "Error Not allocated Memory %ld\n", TotalSize);
        exit(EXIT_FAILURE);
    }

    Head = Memory;
    byte *ptr_h = Head;
    byte **ptr;

    for (size_t i = 0; i < BlkCount - 1; i++)
    {
        byte *p_next = ptr_h + HeadSize;

        ptr = (byte **)ptr_h;
        *ptr = p_next;

        ptr_h = p_next;
    }

    ptr = (byte **)ptr_h;
    *ptr = NULL;
}

/**
 * @brief return 1 block allocated
 *
 * @return void*
 */
void *p_new()
{
    byte *blk;

    if (Head == NULL)
    {
        fprintf(stderr, "Out of memory, cry a new Pool\n");
        blk = NULL;
    }
    else
    {
        blk = HeadSize + Head;

        byte **ptr = (byte **)Head;
        Head = *ptr;
    }

    memset(blk, 0, BlkSize);

    return blk;
}

/**
 * @brief release a block passing a pointer as a parameter
 *
 * @param __ptr pointer for dealoc block
 * @return __uint8_t
 */
__uint8_t p_free(void *__ptr)
{
    __uint8_t status_exit = SUCESS_FREE;

    if (__ptr == NULL)
    {
        status_exit = FAIL_FREE;
        fprintf(stderr, "Error invalid pointer\n");
        exit(EXIT_FAILURE + 1);
    }
    else
    {
        byte **Ptr = __ptr;
        *Ptr = Head;

        Head = __ptr;
    }

    return status_exit;
}

/**
 * @brief will delete your arena, the last allocated arena
 *
 * @return __uint8_t
 */
__uint8_t p_dell()
{
    __uint8_t status_exit = SUCESS_FREE;

    if (Memory == NULL)
    {
        status_exit = FAIL_FREE;
        fprintf(stderr, "Noting Arena\n verify allocation Pool\n");
        exit(EXIT_FAILURE + 2);
    }
    else
        munmap(Memory, TotalSize);

    return status_exit;
}