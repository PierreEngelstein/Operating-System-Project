#include "lib.h"
#include "string.h"
void kprintf(const char *string, va_list args, Console *tConsole)
{
        /* First step : get all the optional parameters (using stdarg header) */
        int i = 0;
        /* All type fields */
        int d;
        while(string[i] != 0) /* Write all string until end_of_string character '\0' */
        {
                if(string[i] == '\n') /* New line => increase current row position */
                {
                        tConsole->curr_row++;
                        tConsole->curr_col = 0;
                        i++;
                }else
                {
                        /* Parse type fields, TODO : Escape sequences */
                        if(string[i] == '%')
                        {
                                i += 2;
                                switch (string[i-1]) {
                                case 'd': /* Output an int */
                                        d=va_arg(args, signed int);
                                        char *buffd = NULL;
                                        itoa(d, buffd, 10);
                                        kprintf(buffd, args, tConsole);
                                        break;
                                case 'x': /* Output an hexadecimal */
                                        d=va_arg(args, signed int);
                                        char *buffx =NULL;
                                        itoa(d, buffx, 16);
                                        kprintf(buffx, args, tConsole);
                                        break;
                                case 'b':
                                        d=va_arg(args, signed int);
                                        char *buffb =NULL;
                                        itoa(d, buffb, 2);
                                        kprintf(buffb, args, tConsole);
                                        break;
                                case 'c': /* Output an hexadecimal */
                                        d = va_arg(args, int);
                                        write_char(d, tConsole->curr_col, tConsole->curr_row);
                                        i++;
                                        tConsole->curr_col++;
                                        break;
                                default:
                                        kprintf("$", args, tConsole);
                                        break;
                                }
                        }else
                        {
                                write_char(string[i], tConsole->curr_col, tConsole->curr_row);
                                i++;
                                tConsole->curr_col++;
                        }
                        if(tConsole->curr_col == VGA_WIDTH) /* If we are at the end of the line, we go to the next line */
                        {
                                tConsole->curr_col = 0;
                                tConsole->curr_row++;
                        }
                }
        }
        update_cursor(tConsole->curr_col, tConsole->curr_row);
}

void write_char(const char c, int col, int row)
{
        uint16_t index = (col + row * VGA_WIDTH) * 2; /* Transforms the (col, row) 2D coordinate to 1D index */
        char *video = (char*)(VGA_MEM);
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

int getCursorOffet()
{
        port_word_out(REG_SCREEN_CTRL, 14);
        int offset = port_word_in(REG_SCREEN_DATA) << 8; /* High byte: << 8 */
        port_word_out(REG_SCREEN_CTRL, 15);
        offset += port_word_in(REG_SCREEN_DATA);
        return offset * 2; /* Position * size of character cell */
}

int getOffsetRow(int offset)
{
        return offset / (2 * VGA_WIDTH);
}
int getOffsetCol(int offset)
{
        return (offset - (getOffsetRow(offset)*2*VGA_WIDTH))/2;
}
