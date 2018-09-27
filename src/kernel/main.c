#include "../includes/console.h"
#include <stdarg.h>
/* Console default size */
static const int VGA_WIDTH = 80;
static const int VGA_HEIGHT = 25;
/* Video memory start address (NOT AN ARRAY)*/
static const int VGA_MEM = 0xb8000;
/* What is currently displayed on screen */
static char* buffer;
/* Current cursor position */
static int curr_row;
static int curr_col;
/* Current printing color */
static int color;

/** Clears the all screen **/
void clear()
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

void write_str(const char *string, ...)
{
    //First step : get all the optional parameters (using stdarg header)
    va_list parameters;
    va_start(parameters, string);
    int i = 0;
    while(string[i] != 0) //Write all string until end_of_string character '\0'
    {
        if(string[i] == '\n') //New line => increase current row position
        {
            curr_row++;
            curr_col = 0;
            i++;
        }else
        {
          //TODO : manage %c, %s, %d, ...
            if(string[i] == '%')
            {
            }else
            {
                  write_char(string[i], curr_col, curr_row);
                  i++;
                  curr_col++;
            }
            if(curr_col == VGA_WIDTH) //If we are at the end of the line, we go to the next line
            {
                curr_col = 0;
                curr_row++;
            }
        }
    }
}

void write_char(const char c, int col, int row)
{
    int index = (col + row * VGA_WIDTH) * 2; //Transforms the (col, row) 2D coordinate to 1D index
    char *video = (char*) VGA_MEM;
    video = video + index;
    *video = c;
    video++;
    *video = 0x0f;
}

/* Initializes the console */
void init_term()
{
    curr_row = 0;
    curr_col = 0;
    clear();
}

int main()
{
    char *video = (char*) 0xb8000;
    char *str = "hello";
    init_term();
    write_str(str);
    write_str(str);
    while(1){};
    return 1;
}
