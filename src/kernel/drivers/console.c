/* Console driver */
/* routines : print, get input(with echoing or not), basic commands (e.g. : man/help), scroll up / down */
#include "stdlib.h"
#include <stdarg.h>

static Console tConsole;

void console_init(){
        /* Init the console structure */
        tConsole.keyb = initKeyboard();
        tConsole.CONSOLE_WIDTH = VGA_WIDTH;
        tConsole.CONSOLE_WIDTH = VGA_HEIGHT;
        tConsole.curr_row = 0;
        tConsole.curr_col = 0;
        tConsole.key = 0;
        tConsole.oldKey = 0;
        /* Clear the screen */
        console_clear();
}

void printf(const char *str, ...)
{
        va_list parameters;
        va_start(parameters, str);
        kprintf(str, parameters, &tConsole);
        va_end(parameters);
}
/* Processes the input by keyboard */
void scanf()
{
        tConsole.oldKey = tConsole.key;
        tConsole.key = scan_keyboard();
        if(!(tConsole.oldKey==tConsole.key)) {
                // printf("hexa=%x\n", abs(tConsole.key));
                char c = getLastChar();
                if((c <= 392 || c >= 399) && !tConsole.keyb.special)
                {
                        if(c >= 32 && c <= 126 && c != 94)
                                printf("%c\0", c);
                        else if(c == 13)
                                printf("\n");
                        else{
                        }
                }else
                {
                        printf("%d\n", c);
                }
        }
}

char getLastChar()
{
        return keyToAscii(abs(tConsole.key), &tConsole.keyb);
}

void scroll_up()
{

}
void pause() {}

/* Clears the screen */
void console_clear()
{
        int i;
        int j;
        for(i = 0; i < VGA_WIDTH; i++)
        {
                for(j = 0; j < VGA_HEIGHT; j++)
                {
                        write_char(' ', i, j);
                }
        }
}
