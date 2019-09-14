#include <stdarg.h>
#include "io.h"
#include "maths.h"
#include "drivers/interrupts.h"

/** Some standard defines **/
#ifndef NULL
#define NULL 0
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

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

void kpanic(char *message);
#define assert(check, condition) do{ if ((check) != (condition)) kpanic();}while(0)

Console tConsole; /* The current console used */

/* Debug stuff */

uint8_t ah;
uint8_t al;
uint8_t bh;
uint8_t bl;
uint8_t ch;
uint8_t cl;
uint8_t dh;
uint8_t dl;

uint16_t ax;
uint16_t bx;
uint16_t cx;
uint16_t dx;

uint32_t eax;
uint32_t ebx;
uint32_t ecx;
uint32_t edx;
uint32_t esi;
uint32_t edi;
uint32_t esp;
uint32_t ebp;

/* Prints the value of all registers to screen (dump of registers is done inside) */
void print_registers();

