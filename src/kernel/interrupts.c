#include "lib.h"
#include "string.h"
#include "memory.h"

#ifdef i386
/** 32-bit IDT entry structure. **/
typedef struct
{
        unsigned short int offset_lowerbits;    // Offset bits 0..15
        unsigned short int selector;            // A code segment selector in GDT or LDT
        unsigned char zero;                     // Unused
        unsigned char type_attr;                // Type and attributes
        unsigned short int offset_higherbits;   // Offset bits 16..31
}__attribute__((packed)) IDT_Entry;

#elif defined X86_64
/** 64-bit IDT entry structure. **/
typedef struct
{
        unsigned short int offset_lowerbits;    // Offset bits 0..15
        unsigned short int selector;            // A code segment selector in GDT or LDT
        unsigned char zero_1;                   // Unused
        unsigned char type_attr;                // Type and attributes
        unsigned short int offset_middlebits;   // Offset bits 16...32
        unsigned int offset_higherbits;         // Offset bits 32...64
        unsigned int zero_2;                    // Unused
} __attribute__((packed)) IDT_Entry;

/** 64-bit IDT descriptor. **/
typedef struct
{
        unsigned short int limit;
        unsigned long base;
}__attribute__((packed)) idtr;
#endif

/* IDT entry list. */
IDT_Entry *IDT;

/* Some standard definitions */
#define PIC1 0x20
#define PIC2 0xA0
#define PIC1_COMM  PIC1
#define PIC1_DATA (PIC1 + 1)
#define PIC2_COMM  PIC2
#define PIC2_DATA (PIC2 + 1)
#define END_OF_INTERRUPT 0x20
/** Gates values **/
#define GATE_INTERRUPT 0x0E
#define GATE_TRAP      0x0F
#define GATE_TASK      0x05
#define IDT_PRESENT    0x1
#define IDT_ABSENT     0x0

typedef int (*irq)();

/* Creates a new IDT Entry struct */
int createIDTEntry(IDT_Entry *entry, unsigned long irq_address, char gate)
{
        entry->offset_lowerbits = irq_address & 0xffff;
        entry->selector = 0x08; //Kernel code segment offset
        entry->type_attr = 0x80 | gate;
        #ifdef I386
        entry->offset_higherbits = (irq_address & 0xffff0000) >> 16;
        entry->zero = 0;
        #elif defined X86_64
        entry->offset_middlebits = (irq_address & 0xffff0000) >> 16;
        entry->offset_higherbits = (irq_address & 0xffff00000000) >> 32;
        entry->zero_1 = 0;
        entry->zero_2 = 0;
        #endif
        return 0;
}

int createEmptyIDTEntry(IDT_Entry *entry)
{
        entry->offset_lowerbits = 0;
        entry->offset_higherbits = 0;
        entry->selector = 0;
        entry->type_attr = 0;
        #ifdef I386
        entry->zero = 0;
        #elif defined X86_64
        entry->offset_middlebits = 0;
        entry->zero_1 = 0;
        entry->zero_2 = 0;
        #endif
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

#ifdef I386
extern int load_idt(IDT_Entry *entry);
#elif defined X86_64
extern int load_idt(idtr *entry);
#endif
extern int irq0(), irq1(), irq2(), irq3(), irq4(), irq5(), irq6(), irq7(), irq8(), irq9(), irq10(), irq11(), irq12(), irq13(), irq14(), irq15();

extern int err0(), err1(), err2(), err3(), err4(), err5(), err6(), err7(), err8(), err9(), err10(), err11(), err12(), err13(), err14(), err15(), err16();

extern int syscall_c();

/* Initializes the IDT */
int idt_init()
{
        #ifdef I386
        IDT = (IDT_Entry *)0x4000; //For the moment mapped statically
        #elif defined X86_64
        IDT = (IDT_Entry *)0x100000;
        #endif
        /* Clear out the entire IDT */
        for(int i = 0; i < 256 * sizeof(IDT_Entry); i++)
                createEmptyIDTEntry(&IDT[i]);
        /** Exceptions **/
        irq excepts[17] = 
        {
                &err0, &err1, &err2, &err3, &err4, &err5, &err6, &err7, &err8, &err9, &err10,
                &err11, &err12, &err13, &err14, &err15, &err16,
        };
        /** Hardware-generated interrupts **/
        irq irqs[17] =
        {
                &irq0, &irq1, &irq2, &irq3, &irq4, &irq4, &irq5, &irq6, &irq7, &irq8, &irq9, &irq10, 
                &irq11, &irq12, &irq13, &irq14, &irq15
        };
        
        /** Remaps the PIC **/
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
        /* Mask every interrupt */
        cli();

        // Exception handles
        for(int i = 0; i < 17; i++)
                createIDTEntry(&(IDT[i]), (unsigned long)excepts[i], GATE_INTERRUPT);
        // Interrupt handles
        for(int i = 0; i < 16; i++)
                createIDTEntry(&(IDT[i + 32]), (unsigned long)irqs[i], GATE_TRAP);
        createIDTEntry(&(IDT[0x80]), (unsigned long)&syscall_c, GATE_INTERRUPT);
        /* Load the IDT descriptor into memory. */
        unsigned long idt_address = (unsigned long)IDT;
        #ifdef I386
        unsigned long idt_ptr[2];
        idt_ptr[0] = (sizeof (IDT_Entry) * 256) + ((idt_address & 0xffff) << 16);
        idt_ptr[1] = (idt_address) >> 16;
        load_idt(idt_ptr);
        #elif defined X86_64
        idtr idt_desc;
        idt_desc.limit = sizeof(IDT_Entry) * 256 - 1;
        idt_desc.base = idt_address;
        load_idt(&idt_desc);
        #endif
        return 0;
}