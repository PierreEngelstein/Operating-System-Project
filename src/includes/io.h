#include <stdint.h>
#include "const.h"
#include "keyboard.h"
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5
/* Reads an unsigned byte from the specified port */
unsigned char port_byte_in(uint8_t port);
/* Writes an unsigned byte into the specified port */
void port_byte_out(uint16_t port, uint8_t data);
/* Reads an unsigned short from the specified port */
unsigned short port_word_in(uint16_t port);
/* Writes an unsigned short into the specified port  */
void port_word_out(uint16_t port, uint16_t data);

/* Keyboard */
typedef struct Keyboard
{
    int *buffer;
    unsigned int buf_size;
    char *map;
    /* Booleans => keyboard status */
    int shift;
    int cpslock;
    int alt;
    int ctrl;
    int numlock;
    int special;
    int nbSpecial;
}kbd_t;
int scan_keyboard();
void kbd_interrupt(kbd_t * keyboard);
void printBuffer(kbd_t * keyboard);
int keyToAscii(int scancode, kbd_t * keyboard);
struct Keyboard initKeyboard();

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
void scanf();   /* To get input from keyboard */
void scroll_up(); /* To scroll up what is written on the console */
void pause();   /* To pause the actual console */
void console_clear();
char getLastChar();
