#include "drivers/keyboard.h"
/* Console */
/* Console default size */
static const int VGA_WIDTH  = 80;
static const int VGA_HEIGHT = 25;
/* Video memory start address (NOT AN ARRAY)*/
static const int VGA_MEM = 0xb8000;
typedef struct
{
        kbd_t keyb;
        int CONSOLE_WIDTH;
        int CONSOLE_HEIGHT;
        int curr_row;
        int curr_col;
        int key;
        int oldKey;
}Console;
void console_init(); /* Main function */
void printf(const char *str, ...);  /* To print something on screen */
char scanf();   /* To get input from keyboard */
void scroll_up(); /* To scroll up what is written on the console */
void pause();   /* To pause the actual console */
void console_clear();
char getLastChar();