#include "stdlib.h"
#include "console.h"
#include "io.h"
#include <stdarg.h>

void kprintf(const char *string, ...)
{
    /* First step : get all the optional parameters (using stdarg header) */
    va_list parameters;
    va_start(parameters, string);
    int i = 0;
    /* All type fields */
    int d;
    char c;
    while(string[i] != 0) /* Write all string until end_of_string character '\0' */
    {
        if(string[i] == '\n') /* New line => increase current row position */
        {
            curr_row++;
            curr_col = 0;
            i++;
        }else
        {
            /* Parse type fields, TODO : Escape sequences */
            if(string[i] == '%')
            {
                i += 2;
                switch (string[i-1]) {
                  case 'd':       /* Output an int */
                    d=va_arg(parameters, signed int);
                    char *buff;
                    itoa(d, buff, 10);
                    kprintf(buff);
                    break;
                  default:
                    kprintf("%?");
                    break;
                }
            }else
            {
                  write_char(string[i], curr_col, curr_row);
                  i++;
                  curr_col++;
            }
            if(curr_col == VGA_WIDTH) /* If we are at the end of the line, we go to the next line */
            {
                curr_col = 0;
                curr_row++;
            }
        }
    }
    update_cursor(curr_col, curr_row);
    va_end(parameters);
}

void write_char(const char c, int col, int row)
{
    uint16_t index = (col + row * VGA_WIDTH) * 2; /* Transforms the (col, row) 2D coordinate to 1D index */
    char *video = (char*) VGA_MEM;
    video = video + index;
    *video = c;
    video++;
    *video = 0x0f;
}

void update_cursor(int col, int row)
{
    uint16_t pos = row * VGA_WIDTH + col;
    port_byte_out(REG_SCREEN_CTRL, 0x0F);
    port_byte_out(REG_SCREEN_DATA, (uint8_t)(pos & 0xFF));
    port_byte_out(REG_SCREEN_CTRL, 0x0E);
    port_byte_out(REG_SCREEN_DATA, (uint8_t)((pos >> 8) & 0xFF));
}
