#include "lib.h"

IDT_Entry *IDT;

/* Some standard definitions */
#define PIC1 0x20
#define PIC2 0xA0
#define PIC1_COMM  PIC1
#define PIC1_DATA (PIC1 + 1)
#define PIC2_COMM  PIC2
#define PIC2_DATA (PIC2 + 1)
#define END_OF_INTERRUPT 0x20

/* Creates a new IDT Entry struct */
int createIDTEntry(IDT_Entry *entry, unsigned long irq_address)
{
        entry->offset_lowerbits = irq_address & 0xffff;
        entry->offset_higherbits = (irq_address & 0xffff0000) >> 16;
        entry->selector = 0x08; //Kernel code segment offset
        entry->type_attr = 0x8f; //Interrupt gate
        entry->zero = 0;
        return 0;
}

int createEmptyIDTEntry(IDT_Entry *entry)
{
        entry->offset_lowerbits = 0;
        entry->offset_higherbits = 0;
        entry->selector = 0;
        entry->type_attr = 0;
        entry->zero = 0;
        return 0;
}

/* Initializes the IDT */
int idt_init()
{
        /* Clear out the entire IDT */
        for(int i = 0; i < 256 * sizeof(IDT_Entry); i++)
                createEmptyIDTEntry(&IDT[i]);
        IDT = 0x6000; //For the moment mapped statically
        extern int load_idt();
        extern int irq0();
        extern int irq1();
        extern int irq2();
        extern int irq3();
        extern int irq4();
        extern int irq5();
        extern int irq6();
        extern int irq7();
        extern int irq8();
        extern int irq9();
        extern int irq10();
        extern int irq11();
        extern int irq12();
        extern int irq13();
        extern int irq14();
        extern int irq15();

        unsigned long irq0_address = (unsigned long)irq0;
        unsigned long irq1_address = (unsigned long)irq1;
        unsigned long irq2_address = (unsigned long)irq2;
        unsigned long irq3_address = (unsigned long)irq3;
        unsigned long irq4_address = (unsigned long)irq4;
        unsigned long irq5_address = (unsigned long)irq5;
        unsigned long irq6_address = (unsigned long)irq6;
        unsigned long irq7_address = (unsigned long)irq7;
        unsigned long irq8_address = (unsigned long)irq8;
        unsigned long irq9_address = (unsigned long)irq9;
        unsigned long irq10_address = (unsigned long)irq10;
        unsigned long irq11_address = (unsigned long)irq11;
        unsigned long irq12_address = (unsigned long)irq12;
        unsigned long irq13_address = (unsigned long)irq13;
        unsigned long irq14_address = (unsigned long)irq14;
        unsigned long irq15_address = (unsigned long)irq15;
        unsigned long idt_address = (unsigned long)IDT;
        unsigned long idt_ptr[2];

        idt_ptr[0] = (sizeof (IDT_Entry) * 256) + ((idt_address & 0xffff) << 16);
        idt_ptr[1] = idt_address >> 16;
        /**
         * Remaps the PIC 
         **/
        /* ICW1 - Begin initialization */
        port_byte_out(PIC1_COMM, 0x11);
        port_byte_out(PIC2_COMM, 0x11);
        /* ICW2 - Remap offset address of IDT */
        port_byte_out(PIC1_DATA, 0x20);
        port_byte_out(PIC2_DATA, 0x28);
        /* ICW3 - Setup cascading */
        port_byte_out(PIC1_DATA, 0x04);
        port_byte_out(PIC2_DATA, 0x02);
        /* ICW4 - Environment info */
        port_byte_out(PIC1_DATA, 0x01);
        port_byte_out(PIC2_DATA, 0x01);
        /* Mask every interrupt except for keyboard interrupt */
        port_byte_out(PIC1_DATA,0xfd);
        port_byte_out(PIC2_DATA,0xff);

        //IRQs (TODO : CPU exceptions and syscalls)
        createIDTEntry(&(IDT[32]), irq0_address);
        createIDTEntry(&(IDT[33]), irq1_address);
        createIDTEntry(&(IDT[34]), irq2_address);
        createIDTEntry(&(IDT[35]), irq3_address);
        createIDTEntry(&(IDT[36]), irq4_address);
        createIDTEntry(&(IDT[37]), irq5_address);
        createIDTEntry(&(IDT[38]), irq6_address);
        createIDTEntry(&(IDT[39]), irq7_address);
        createIDTEntry(&(IDT[40]), irq8_address);
        createIDTEntry(&(IDT[41]), irq9_address);
        createIDTEntry(&(IDT[42]), irq10_address);
        createIDTEntry(&(IDT[43]), irq11_address);
        createIDTEntry(&(IDT[44]), irq12_address);
        createIDTEntry(&(IDT[45]), irq13_address);
        createIDTEntry(&(IDT[46]), irq14_address);
        createIDTEntry(&(IDT[47]), irq15_address);

        load_idt(idt_ptr);
        return 0;
}

/* c-level irq handlers */

void irq0_handler(void) /* Timer interrupt */
{
        port_byte_out(PIC1_COMM, END_OF_INTERRUPT);
}
void irq1_handler(void) /* Keyboard interrupt */
{
        printf("%d", port_byte_in(KEYBOARD_SCAN_PORT));
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
        printf("Mouse !");
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