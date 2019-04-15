#include "lib.h"

#define PIC1 0x20
#define PIC2 0xA0
#define ICW1 0x11
#define ICW4 0x01

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

int main()
{
        init_pics(0x20, 0x27);
        /* Disable interrupts during initialisation */
        cli();
        idt_init();
        /* Initialize the console */
        console_init();
        printf("Starting OS ...\n");
        printf(">");
        /* Enable interrupts we want */
        enable_interrupt(INTERRUPT_KEYBOARD);
        for(;;){}
        return 0;
}
