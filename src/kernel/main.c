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
    #define azerty
        init_pics(0x20, 0x27);
        clear();
        kprintf("Started Kernel ...\n");
        kprintf("Initialising Kernel ...");
        init_term();
        kprintf("Finished!\n");
        int a = 123;
        kprintf("a = %x\n", a);
        int *buffer = (int*)0x100000;
        int size = 10;
        kprintf("=====Circular Buffer Check====\n");
        cbuf_handle_t cbuf = circular_buff_init(buffer, size);
        kprintf("Buffer initialized. Full = %d, empty = %d, size = %d\n",
                circular_buff_full(cbuf),
                circular_buff_empty(cbuf),
                circular_buff_size(cbuf));
        kprintf("******\nAdding %d values\n", size - 1);
        for(int i = 0; i < (size - 1); i++)
        {
                circular_buff_put(cbuf, i);
                // kprintf("Added %d, size now : %d\n", i, circular_buff_size(cbuf));
        }
        kprintf("Full = %d, empty = %d, size = %d\n",
                circular_buff_full(cbuf),
                circular_buff_empty(cbuf),
                circular_buff_size(cbuf));
        kprintf("******\nReading back values:");
        while(!circular_buff_empty(cbuf))
        {
                int data;
                circular_buff_get(cbuf, &data);
                kprintf("%d ", data);
        }
        kprintf("\n");
        kprintf("******\nAdding %d values\n", size);
        for(int i = 0; i < (size); i++)
        {
                circular_buff_put(cbuf, i);
        }
        kprintf("Full = %d, empty = %d, size = %d\n",
                circular_buff_full(cbuf),
                circular_buff_empty(cbuf),
                circular_buff_size(cbuf));
        kprintf("******\nReading back values: ");
        while(!circular_buff_empty(cbuf))
        {
                int data;
                circular_buff_get(cbuf, &data);
                kprintf("%d ", data);
        }
        kprintf("\n");
        kprintf("******\nAdding %d values\n", size + 5);
        for(int i = 0; i < (size + 5); i++)
        {
                circular_buff_put(cbuf, i);
        }
        kprintf("Full = %d, empty = %d, size = %d\n",
                circular_buff_full(cbuf),
                circular_buff_empty(cbuf),
                circular_buff_size(cbuf));
        kprintf("******\nReading back values: ");
        while(!circular_buff_empty(cbuf))
        {
                int data;
                circular_buff_get(cbuf, &data);
                kprintf("%d ", data);
        }
        kprintf("\n******\nAdding %d values using non-overwrite version\n", size + 5);
        for(int i = 0; i < size + 5; i++)
        {
                circular_buff_put2(cbuf, i);
                // kprintf("Added %d, size now : %d\n", i, circular_buff_size(cbuf));
        }
        kprintf("Full = %d, empty = %d, size = %d\n",
                circular_buff_full(cbuf),
                circular_buff_empty(cbuf),
                circular_buff_size(cbuf));
        kprintf("******\nReading back values: ");
        while(!circular_buff_empty(cbuf))
        {
                int data;
                circular_buff_get(cbuf, &data);
                kprintf("%d ", data);
        }
        kprintf(" ... Check Finished");
        // int oldkey;
        // int key;
        // kbd_t keyb = initKeyboard();
        // /* prototype for inputing with keyboard */
        // for (;;)
        // {
        //         oldkey=key;
        //         key=kbd_interrupt(&keyb);
        //         // if((oldkey==key)) key = 0;
        //         if(!(oldkey==key)) {
        //                 // kprintf("hexa=%x\n", abs(key), abs(key));
        //                 printBuffer(&keyb);
        //                 // char c = keyToAscii(key, &keyb);
        //                 // if(c >= 32 && c <= 126 && c != 94)
        //                 //         kprintf("%c\0", c);
        //                 // else if(c == 13)
        //                 //         kprintf("\n");
        //         }
        // }
        while(1) {};
        return 1;
}
