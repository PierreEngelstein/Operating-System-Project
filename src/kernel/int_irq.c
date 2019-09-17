#define PIC1 0x20
#define PIC2 0xA0
#define PIC1_COMM  PIC1
#define PIC1_DATA (PIC1 + 1)
#define PIC2_COMM  PIC2
#define PIC2_DATA (PIC2 + 1)
#define END_OF_INTERRUPT 0x20
#include "drivers/console.h"

void irq0_handler(void) /* Timer interrupt */
{
        printf(".");
        port_byte_out(PIC1_COMM, END_OF_INTERRUPT);
}
void irq1_handler(void) /* Keyboard interrupt */
{
        do_keyboard_interrupt();
        port_byte_out(PIC1_COMM, END_OF_INTERRUPT);
}
void irq2_handler(void) /* Cascade (never raised) */
{
        port_byte_out(PIC1_COMM, END_OF_INTERRUPT); 
}
void irq3_handler(void) /* COM2 if enabled */
{
        port_byte_out(PIC1_COMM, END_OF_INTERRUPT); 
}
void irq4_handler(void) /* COM1 if enabled */
{
        port_byte_out(PIC1_COMM, END_OF_INTERRUPT); 
}
void irq5_handler(void) /* LPT2 if enabled */
{
        port_byte_out(PIC1_COMM, END_OF_INTERRUPT); 
}
void irq6_handler(void) /* Floppy disk */
{
        port_byte_out(PIC1_COMM, END_OF_INTERRUPT); 
}
void irq7_handler(void) /* LPT1 */
{
        port_byte_out(PIC1_COMM, END_OF_INTERRUPT); 
}
void irq8_handler(void) /* CMOS real-time clock */
{
        port_byte_out(PIC2_COMM, END_OF_INTERRUPT);
        port_byte_out(PIC1_COMM, END_OF_INTERRUPT); 
}
void irq9_handler(void) /* Free for peripherals / legacy SCSI / NIC */
{
        port_byte_out(PIC2_COMM, END_OF_INTERRUPT);
        port_byte_out(PIC1_COMM, END_OF_INTERRUPT); 
}
void irq10_handler(void) /* Free for peripherals / SCSI / NIC */
{
        port_byte_out(PIC2_COMM, END_OF_INTERRUPT);
        port_byte_out(PIC1_COMM, END_OF_INTERRUPT); 
}
void irq11_handler(void) /* Free for peripherals / SCSI / NIC */
{
        port_byte_out(PIC2_COMM, END_OF_INTERRUPT);
        port_byte_out(PIC1_COMM, END_OF_INTERRUPT); 
}
void irq12_handler(void) /* PS2 Mouse */
{
        // printf("Mouse !");
        port_byte_out(PIC2_COMM, END_OF_INTERRUPT);
        port_byte_out(PIC1_COMM, END_OF_INTERRUPT);
}
void irq13_handler(void) /* FPU / Coprocessor / Inter-processor */
{
        port_byte_out(PIC2_COMM, END_OF_INTERRUPT);
        port_byte_out(PIC1_COMM, END_OF_INTERRUPT); 
}
void irq14_handler(void) /* Primary ATA Hard-disk */
{
        port_byte_out(PIC2_COMM, END_OF_INTERRUPT);
        port_byte_out(PIC1_COMM, END_OF_INTERRUPT); 
}
void irq15_handler(void) /* Secondary ATA Hard-disk */
{
        port_byte_out(PIC2_COMM, END_OF_INTERRUPT);
        port_byte_out(PIC1_COMM, END_OF_INTERRUPT); 
}