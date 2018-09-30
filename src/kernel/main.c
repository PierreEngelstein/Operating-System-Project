#include "stdlib.h"
#include "io.h"
#include "console.h"
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


/* Initializes the console */
void init_term()
{
    curr_row = 0;
    curr_col = 0;
}

int main()
{
    clear();
    kprintf("Started Kernel ...\n");
    kprintf("Initialising Kernel ...");
    init_term();
    kprintf("Finished!\n");
    int a = 123;
    kprintf("a = %d\n", a);
    int b = port_byte_in(10);
    kprintf("port 10 = %d", b);
    while(1){};
    return 1;
}
