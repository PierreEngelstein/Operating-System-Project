#include "lib.h"
#include "string.h"
#include "memory.h"

typedef struct //8 bytes length
{
        unsigned short int offset_lowerbits; //Offset bits 0..15
        unsigned short int selector; //A code segment selector in GDT or LDT
        unsigned char zero; //Unused
        unsigned char type_attr; //Type and attributes
        unsigned short int offset_higherbits; //Offset bits 16..31
}__attribute__((packed)) IDT_Entry;

IDT_Entry *IDT;

/* Some standard definitions */
#define PIC1 0x20
#define PIC2 0xA0
#define PIC1_COMM  PIC1
#define PIC1_DATA (PIC1 + 1)
#define PIC2_COMM  PIC2
#define PIC2_DATA (PIC2 + 1)
#define END_OF_INTERRUPT 0x20

typedef int (*irq)();

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

void cli()
{
        port_byte_out(PIC1_DATA,0xff); // 1111 1111 => no interrupt enabled on PIC1
        port_byte_out(PIC2_DATA,0xff); // 1111 1111 => no interrupt enabled on PIC2
}
void sei()
{
        port_byte_out(PIC1_DATA,0x00); // 0000 0000 => no interrupt enabled on PIC1
        port_byte_out(PIC2_DATA,0x00); // 0000 0000 => no interrupt enabled on PIC2
}

void enable_interrupt(uint8_t interrupt)
{
        int present = port_byte_in(PIC1_DATA);
        int mask = pow(2, interrupt) & 0xFF;
        port_byte_out(PIC1_DATA,present & ~mask);
        
        present = port_byte_in(PIC2_DATA);
        mask = (pow(2, interrupt) & 0xFF00) >> 8;
        port_byte_out(PIC2_DATA,present & ~mask);
        return;
}

extern int load_idt(IDT_Entry *entry);
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

/* Initializes the IDT */
int idt_init()
{
        IDT = (IDT_Entry *)0x4000; //For the moment mapped statically
        /* Clear out the entire IDT */
        for(int i = 0; i < 256 * sizeof(IDT_Entry); i++)
                createEmptyIDTEntry(&IDT[i]);

        irq irqs[17] =
        {
                &irq0,
                &irq1,
                &irq2,
                &irq3,
                &irq4,
                &irq4,
                &irq5,
                &irq6,
                &irq7,
                &irq8,
                &irq9,
                &irq10,
                &irq11,
                &irq12,
                &irq13,
                &irq14,
                &irq15
        };
        unsigned long idt_address = (unsigned long)IDT;
        unsigned long idt_ptr[2];  //Base address | Limit

        idt_ptr[0] = (sizeof (IDT_Entry) * 256) + ((idt_address & 0xffff) << 16);
        idt_ptr[1] = (idt_address) >> 16;
        /**
         * Remaps the PIC 
         **/
        /* ICW1 - Begin initialization */
        port_byte_out(PIC1_COMM, 0x11);
        port_byte_out(PIC2_COMM, 0x11);
        /* ICW2 - Remap offset address of IDT, where PIC1 is remapped at 32 (0x20) and PIC2 at 40 (0x28) */
        port_byte_out(PIC1_DATA, 0x20);
        port_byte_out(PIC2_DATA, 0x28);
        /* ICW3 - Setup cascading */
        port_byte_out(PIC1_DATA, 0x04);
        port_byte_out(PIC2_DATA, 0x02);
        /* ICW4 - Environment info */
        port_byte_out(PIC1_DATA, 0x01);
        port_byte_out(PIC2_DATA, 0x01);
        /* Mask every interrupt except for keyboard interrupt */
        cli();

        //IRQs (TODO : CPU exceptions and syscalls)
        for(int i = 0; i < 16; i++)
                createIDTEntry(&(IDT[i + 32]), (unsigned long)irqs[i]);
        load_idt(idt_ptr);
        return 0;
}

/* c-level irq handlers */

void irq0_handler(void) /* Timer interrupt */
{
        printf(".");
        port_byte_out(PIC1_COMM, END_OF_INTERRUPT);
}
void irq1_handler(void) /* Keyboard interrupt */
{
        do_keyboard_interrupt();
        // printf("%d", port_byte_in(KEYBOARD_SCAN_PORT));
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