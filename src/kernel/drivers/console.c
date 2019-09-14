/* Console driver */
/* routines : print, get input(with echoing or not), basic commands (e.g. : man/help), scroll up / down */
#include "lib.h"
#include "string.h"
#include <stdarg.h>

void clear_buffer()
{
        tConsole.line_length = 0;
        tConsole.line[0] = 0;
}

/* */
void do_command()
{
        tolower(tConsole.line, tConsole.line);
        /* Parse commands */
        if(!strcmp(tConsole.line, "clear")) //if starts with 'clear'
        {
                console_init();
        }else if (!strcmp(tConsole.line, "uname"))
        {
                printf("\ncustom kernel v0.01");
        }else if(!strcmp(tConsole.line, "help"))
        {
                printf("\nList of all commands :\n");
                printf("CLEAR       Clears the console\n");
                printf("DUMP        Prints the value of all registers to the console\n");
                printf("HELP        Prints this help message\n");
                printf("SHUTDOWN    Shutdowns the computer\n");
                printf("UNAME       Prints the name of the system\n");
        }else if(!strcmp(tConsole.line, "shutdown"))
        {
                port_word_out(0x604, 0x2000); //Qemu-specific :-)
        }else if(!strcmp(tConsole.line, "dump"))
        {
                print_registers();
        }
        else
        {
                if(tConsole.line_length != 0)
                {
                        printf("\n");
                        printf(tConsole.line);
                        printf(" : command not found !");
                }
        }
        clear_buffer();
        printf("\n>");
}

void go_back()
{
        if(tConsole.curr_col > 1)
        {
                tConsole.line_length--; //Go back on console line buffer
                tConsole.line[tConsole.line_length] = 0;
                tConsole.curr_col--;
                update_cursor(tConsole.curr_col, tConsole.curr_row);
                write_char(' ', tConsole.curr_col, tConsole.curr_row);
        }
}


void console_init(){
        /* Init the console structure */
        tConsole.keyb = initKeyboard();
        tConsole.CONSOLE_WIDTH = VGA_WIDTH;
        tConsole.CONSOLE_WIDTH = VGA_HEIGHT;
        tConsole.curr_row = 0;
        tConsole.curr_col = 0;
        clear_buffer();
        tConsole.line_length = 0;
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

void do_keyboard_interrupt()
{
        char c = keyToAscii(abs(scan_keyboard()), &tConsole.keyb);
        if((c <= 392 || c >= 399) && !tConsole.keyb.special)
        {

                if(c == 8) //Delete last char
                {
                        go_back();
                }
                if(c >= 32 && c <= 126 && c != 94)
                {
                        printf("%c\0", c);
                        tConsole.line[tConsole.line_length] = c;
                        tConsole.line_length++;
                }
                else if(c == '\n')
                {
                        tConsole.line[tConsole.line_length] = 0;
                        do_command();
                }
        }else
        {
                printf("%d\n", c);
        }
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