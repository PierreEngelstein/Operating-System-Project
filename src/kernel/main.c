#include "lib.h"
#include "string.h"
#include "k_memory.h"
#include "syscall.h"
#define PIC1 0x20
#define PIC2 0xA0
#define ICW1 0x11
#define ICW4 0x01

// extern int gdt_descriptor;

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

typedef struct gdt
{
        uint16 limit;
        uint16 baseLo;
        uint8  baseMid;
        uint8 access;
        uint8 granularity;
        uint8  baseHi;
}gdt;

typedef struct gdtr
{
        uint16 m_limit;
        uint32 m_base;
}gdtr __attribute__((packed));

// #define MAX_DESCRIPTORS 6

// static struct gdt  *_gdt;
// struct gdtr * _gdtr;

// void *memset(void *dst, int c, size_t n)
// {
//         if(n)
//         {
//                 char *d = dst;
//                 do
//                 {
//                         *d++ = c;
//                 }while(--n);
//         }
//         return dst;
// }

// void printData(void *dst, size_t n)
// {
//         if(n)
//         {
//                 char *d = dst;
//                 do
//                 {
//                         printf("%d;", *d);
//                         *d++;
//                 }while(--n);
//                 printf("\n");
//         }
// }

// extern void gdt_install();

// void gdt_set_descriptor(uint32 i, uint64 base, uint64 limit, uint8 access, uint8 grand)
// {
//         if(i > MAX_DESCRIPTORS)
//                 return;
        
//         memset((void *) &_gdt[i], 0, sizeof(gdt));

//         /* Set limit and base addresses */
//         _gdt[i].baseLo  = base & 0xffff;
//         _gdt[i].baseMid = (base >> 16) & 0xff;
//         _gdt[i].baseHi  = (base >> 24) & 0xff;
//         _gdt[i].limit   = limit & 0xffff;

//         /* Set flags and grandularity bytes */
//         _gdt[i].access = access;
//         _gdt[i].granularity = ((limit >> 16) & 0x0f);
//         _gdt[i].granularity |= grand & 0xf0;
// }

// int gdt_init()
// {
//         _gdtr = (struct _gdtr *)_k_malloc(sizeof(struct gdtr));
//         _gdt = (gdt *)_k_malloc(MAX_DESCRIPTORS * sizeof(gdt));
        
//         _gdtr->m_limit = (sizeof(struct gdt) * MAX_DESCRIPTORS) - 1;
//         _gdtr->m_base  = (uint32) &_gdt[0];

//         gdt_set_descriptor(0, 0, 0, 0, 0);
//         gdt_set_descriptor(1, 0, 0xffffffff, 0x9A, 0xCF);
//         printData((void *)&_gdt[1], sizeof(gdt));
//         printf("\n%x %x\n", _gdt, _gdtr);
//         printf("sizeof(gdt) = %d\n", sizeof(gdt));
//         gdt_set_descriptor(2, 0, 0xffffffff, 0x92, 0xCF);
//         gdt_set_descriptor(3, 0, 0xffffffff, 0xFA, 0xCF);
//         gdt_set_descriptor(4, 0, 0xffffffff, 0xF2, 0xCF);

//         gdt_install();
//         return 0;
// }

int main(int a)
{
        struct gdtr *test = (struct gdtr *)a;

        struct gdt *test_gdt = (test->m_base + test->m_limit);
        
        init_pics(0x20, 0x27);
        cli();
        _k_init_mem();
        idt_init();
        
        /* Initialize the console */
        console_init();
        
        // gdt_init();
        // int *array = _k_malloc(sizeof(int) * 256);
        // printf("array at %x. Memory at %x\n", array, a);

        // unsigned short total;
        // unsigned char lowmem, highmem;
        
        // port_byte_out(0x70, 0x30);
        // lowmem = port_byte_in(0x71);
        // port_byte_out(0x70, 0x31);
        // highmem = port_byte_in(0x71);

        // total = lowmem | highmem << 8;
        // printf("low = %d, high = %d, total = %d\n", lowmem, highmem, total);
        // printf("args = [a:%x; b:%x]\n", a, b);
        // printf("gdtr = [base:%x; limit:%x]\n", a->m_base, a->m_limit);
        // printf("gdt = [limit:%x baseLo:%x; baseMid:%x; access:%x; granularity:%x; baseHi:%x]\n", test_gdt->limit, test_gdt->baseLo, test_gdt->baseMid, test_gdt->access, test_gdt->granularity, test_gdt->baseHi);
        printf("Starting OS ... %x (%d, %d)\n", a, test->m_base, test->m_limit);
        // printf("%x\n", test_gdt->granularity);
        #ifdef I386
        printf("32 bit system !\n");
        #elif defined X86_64
        printf("64 bit system !\n");
        #endif
        printf("sizeof(long) = %d\n", sizeof(long));
        printf(">");
        // /* Enable interrupts we want */
        enable_interrupt(INTERRUPT_KEYBOARD);
        // enable_interrupt(INTERRUPT_TIMER);
        // printf("%d\n", 3/0);
        // __asm__("movl $1, %eax");
        int c = KnKeyboard();

        for(;;){}
        return 0;
}
