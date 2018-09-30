#include "stdlib.h"

void itoa(int input, char* buffer, int base)
{
    /* Incorrect base : print '?' */
    if(base < 2 || base > 32)
    {
        buffer[0]='?';
        buffer[1]='\0';
        return;
    }

    int i = 0;
    int isNegative = 0;
    /* Explicitely handle 0, otherwise it returns an empty string */
    if(input == 0)
    {
        buffer[i++] = '0';
        buffer[i] = '\0';
    }
    /* We consider that only base 10 numbers can be negative, otherwise they are unsigned */
    if(input < 0 && base == 10)
    {
        isNegative = 1;
        input = -input;
    }
    /* Process individual digits */
    while(input != 0)
    {
        int rem = input % base;
        buffer[i++] = (rem > 9)? (rem - 10) + 'A' : rem + '0';
        input = input / base;
    }
    if(isNegative)
      buffer[i++] = '-';
    buffer[i] = '\0';
    reverse(buffer, 0, i - 1);
}

char* reverse(char *buffer, int i, int j)
{
	while (i < j)
		swap(&buffer[i++], &buffer[j--]);
	return buffer;
}

inline void swap(char *x, char *y)
{
    char t = *x;
    *x = *y;
    *y = t;
}
