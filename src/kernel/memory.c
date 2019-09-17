#include "k_memory.h"
#include "const.h"
#include "drivers/console.h"

BOOL _k_mem_CheckIndex(int i);
BOOL _k_mem_GetFree(int i);
VOID _k_mem_SetFree(int i);
VOID _k_mem_SetOccupied(int i);
VOID *_k_mem_GetFirstFreeBlock();
VOID *_k_mem_GetNFreeBlocks(size_t n);

#define MEMSIZE 4096  //Only 4KB for the moment, will extend this maybe one day

int _k_mem_start = 0x100000; // Where the heap starts

MEMBLK data[MEMSIZE]; // The array of block descriptors, for the moment as char but later as a full structure.

VOID _k_init_mem()
{
        for(int i = 0; i < MEMSIZE; i++)
                data[i] = 0xFF;
}

void *_k_malloc(size_t _size)
{
        void *k = _k_mem_GetNFreeBlocks(_size);
        MEMBLK diff = (int *)k - _k_mem_start;
        if(k)
                for(int i = diff; i < diff + _size; i++)
                        _k_mem_SetOccupied(i);
        return k;
}

/**
 * This section is only internal function that are not intended to be used outside of here (that's why they are not on the memory header).
 * Globally, they handle low-level memory block state management.
 */

/** Returns true if the given index is correct. */
BOOL _k_mem_CheckIndex(int i)
{
        if(i / (sizeof(MEMBLK) * 8) < 0) return FALSE;
        if(i / (sizeof(MEMBLK) * 8) > MEMSIZE) return FALSE;
        return TRUE;
}

/** Returns TRUE if the block is free. */
BOOL _k_mem_GetFree(int i)
{
        if(!_k_mem_CheckIndex(i))
                kpanic("_k_mem_GetFree error : wrong index !");
        int _data_idx = i/(sizeof(MEMBLK) * 8);   // Index in data[] array
        int _data_loc = i % (sizeof(MEMBLK) * 8); // Index in a local 8 bits number
        int _mask = 0x1 << _data_loc;
        int val = (data[_data_idx] & _mask) >> _data_loc;
        if(val)
                return TRUE;
        return FALSE;
}

/** Sets the block as free */
VOID _k_mem_SetFree(int i)
{
        if(!_k_mem_CheckIndex(i))
                kpanic("_k_mem_SetFree error : wrong index !");
        int _data_idx = i/(sizeof(MEMBLK) * 8);   // Index in data[] array
        int _data_loc = i % (sizeof(MEMBLK) * 8); // Index in a local 8 bits number
        int _mask = 0x1 << _data_loc;
        data[_data_idx] |= _mask;
}

/** Set the block as occupied. */
VOID _k_mem_SetOccupied(int i)
{
        if(!_k_mem_CheckIndex(i))
                kpanic("_k_mem_SetOccupied error : wrong index !");
        int _data_idx = i/(sizeof(MEMBLK) * 8);
        int _data_loc = i % (sizeof(MEMBLK) * 8);
        int _mask = ~(0x1 << _data_loc);
        data[_data_idx] &= _mask;
}

/** Gets the first free block on memory. */
VOID *_k_mem_GetFirstFreeBlock()
{
        for(int i = 0; i < sizeof(MEMBLK) * 8 * MEMSIZE; i++)
        {
                if(_k_mem_GetFree(i) == TRUE)
                        return (void *)(_k_mem_start + i);
        }
        return (void *)0;
}

/** Gets the first free N adjacent blocks on memory */
VOID *_k_mem_GetNFreeBlocks(size_t n)
{
        int i = 0;
        void *tmp = 0;
        while(i < sizeof(MEMBLK) * 8 * MEMSIZE - n)
        {
                if(_k_mem_GetFree(i))
                {
                        int j = 1;
                        for(j = 0; j < n; j++)
                        {
                                if(!_k_mem_GetFree(i + j))
                                {
                                        i += j;
                                        break;
                                }
                        }
                        if(j == n)
                        {
                                return (void *)(_k_mem_start + i);
                        }
                }
                i++;
        }
        return (void *)0;
}