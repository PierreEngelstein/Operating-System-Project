#include "k_memory.h"

void *memmove(void *dest, const void *src, unsigned long count)
{
        char *d = (char *)dest;
        const char *s = (const char *)src;
        int len;
        if(count == 0 || dest == src) /* If there is nothing to move or the source is identical to the destination */
                return dest;
        if((long)d < (long)s)
        {
                if(((long)d | (long)s) & lmask)
                {
                        /* if src and / or dest do not align on word boundary */
                        if((((long)d ^ (long)s) & lmask) || (count < lsize))
                                len = count; /* copy the rest with byte mover */
                        else
                                len = lsize - ((long)d & lmask); /* Move size up to word boundary */
                        count -= len;
                        for(; len > 0; len--)
                                *d++ = *s++;
                }
                for(len = count / lsize; len > 0; len--)
                {
                        *(word *)d = *(word *)s;
                        d += lsize;
                        s += lsize;
                }
                for(len = count & lmask; len > 0; len--)
                        *d++ = *s++;
        }else
        {
                d += count;
                s += count;
                if(((long)d | (long)s) & lmask)
                {
                        /* if src and / or dest do not align on word boundary */
                        if((((long)d ^ (long)s) & lmask) || (count <= lsize))
                                len = count; /* copy the rest with byte mover */
                        else
                                len =((long)d & lmask); /* Move size up to word boundary */
                        count -= len;
                        for(; len > 0; len--)
                                *d-- = *s--;
                }
                for(len = count / lsize; len > 0; len--)
                {
                        d -= lsize;
                        s -= lsize;
                        *(word *)d = *(word *)s;
                }
                for(len = count & lmask; len > 0; len--)
                        *d-- = *s--;
        }
        return dest;
}

void *memcpy(void *dest, const void *src, unsigned long count)
{
        char *d = (char *)dest;
        const char *s = (const char *)src;
        int len;
        if(count == 0 || dest == src) /* If there is nothing to copy or the source is identical to the destination */
                return dest;
        if(((long)d | (long)s) & lmask)
        {
                if((((long)d ^ (long)s) & lmask) || (count < lsize))
                        len = count;
                else
                        len = lsize - ((long)d & lmask);
                count -= len;
                for(; len > 0; len--)
                        *d++ = *s++;
        }
        for(len = count / lsize; len > 0; len--)
        {
                *(word *)d = *(word *)s;
                d += lsize;
                s += lsize;
        }
        for(len = count & lmask; len > 0; len--)
                *d++ = *s++;
        return dest;
}