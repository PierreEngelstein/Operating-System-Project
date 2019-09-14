typedef char MEMBLK;
#include "types.h"

/** Initializes the memory. */
VOID _k_init_mem();

/** Allocates size bytes on the heap. Returns a pointer to the base of the block allocated */
void *_k_malloc(size_t size);