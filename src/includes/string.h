#include "types.h"

/* Convert an integer to a string */
void itoa(int value, char* buffer, int base);
/* Reverses the string array given in argument */
char* reverse(char *buffer, int i, int j);
/* Swaps the two strings */
void swap(char *x, char *y);
/* Compares 2 strings */
int strcmp(const char* p1, const char* p2);
const char *strstr(const char *str1, const char *str2);

BOOL strstart(const char *str1, const char *str2);

/**
 * Copy a string.
 * @description
 * The strcpy() function copies the string pointed to by src (including the '\0' character)
 * to an array pointed to by dest. The strings may not overlap & the string dest must be large
 * enough to receive copy.
 * @return a pointer to the string dest.
 */
char *strcpy(char *dest, const char *src);

/**
 * Copy a string.
 * @description
 * The strncpy() is similar to the strcpy() except that no more than n bytes
 * of src are copyed. If there is no '\0' among the first n bytes of src, the
 * result will not be null-terminated.
 * @return a pointer to the string dest.
 */
char *strncpy(char *dest, const char *src, size_t len);

/**
 * Lowers a string.
 * @description
 * The tolower() function converts a string to lowercase.
 * It loops through all characters add 32 to all characters 
 * that are between 'A' and 'Z' (assuming we are in ascii).
 * @return a pointer to the modified string;
 */
char *tolower(char *dest, char *str);