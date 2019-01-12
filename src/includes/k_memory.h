typedef long word;

#define lsize sizeof(word)
#define lmask (lsize - 1)

void *memmove(void *dest, const void *src, unsigned long count);
void *memcpy(void *dest, const void *src, unsigned long count);