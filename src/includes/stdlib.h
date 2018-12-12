#include <stdarg.h>
#include "io.h"
/**
    String routines
**/
/* Convert an integer to a string */
void itoa(int value, char* buffer, int base);
/* Reverses the string array given in argument */
char* reverse(char *buffer, int i, int j);
/* Swaps the two strings */
void swap(char *x, char *y);
int abs(int n);

/**
    Print routines
**/
/* Prints a string and type fields */
void kprintf(const char *string, va_list args, Console *tConsole);
/* Prints the character at the given coordinates */
void write_char(const char c, int col, int row);
/* Updates the cursor to the given coordinates */
void update_cursor(int col, int row);
int getCursorOffet();
int getOffsetRow(int offset);
int getOffsetCol(int offset);

// #define sizeof(x) ((&x + 1) - &x)

void kpanic(char *message);
#define assert(check, condition) do{ if ((check) != (condition)) kpanic();}while(0)
