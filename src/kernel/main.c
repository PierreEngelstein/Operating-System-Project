#include "stdlib.h"
#include "io.h"
#include "console.h"

#define PIC1 0x20
#define PIC2 0xA0
#define ICW1 0x11
#define ICW4 0x01

void clear();
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

void init_pics(int pic1, int pic2)
{
    /* Send ICW1 */
    port_byte_out(PIC1, ICW1);
    port_byte_out(PIC2, ICW1);
    /* Send ICW2 */
    port_byte_out(PIC1 + 1, pic1);
    port_byte_out(PIC2 + 1, pic2);
    /* Send ICW3 */
    port_byte_out(PIC1 + 1, 4);
    port_byte_out(PIC2 + 1, 2);
    /* Send ICW4 */
    port_byte_out(PIC1 + 1, ICW4);
    port_byte_out(PIC2 + 1, ICW4);
    /* disable all irqs */
    port_byte_out(PIC1 + 1, 0xFF);
}

/* Initializes the console */
void init_term()
{
    curr_row = 0;
    curr_col = 0;
    //clear();
}

int main()
{
    init_pics(0x20, 0x28);
    clear();
    kprintf("Started Kernel ...\n");
    kprintf("Initialising Kernel ...");
    init_term();
    kprintf("Finished!\n");
    int a = 123;
    kprintf("a = %d\n", a);
    char oldkey;
char key;
for (;;) {
  oldkey=key;
  key=port_byte_in(0x60);
  if(!(oldkey==key)){
    kprintf(key);
  }
}
    while(1){};
    return 1;
}
