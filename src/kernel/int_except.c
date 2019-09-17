#define PIC1 0x20
#define PIC2 0xA0
#define PIC1_COMM  PIC1
#define PIC1_DATA (PIC1 + 1)
#define PIC2_COMM  PIC2
#define PIC2_DATA (PIC2 + 1)
#define END_OF_INTERRUPT 0x20
#include "lib.h"

void err0_handler(void) /* Divide by 0 exception */
{
        printf("divide by 0\n");
        while(1){}
}
void err1_handler(void) /* Debug exception */
{
        printf("debug exception\n");
}
void err2_handler(void)
{
        printf("non-maskable intrrupt\n");
}
void err3_handler(void) /* Breakpoint */
{
        printf("breakpoint\n");
        char c = ' ';
        while((c = keyToAscii(abs(scan_keyboard()), &tConsole.keyb)) != 'a'){}
}
void err4_handler(void) /* Overflow */
{
        printf("overflow\n");
}
void err5_handler(void) /* Bound range exceeded */
{
        printf("bound range exceeded\n");
}
void err6_handler(void) /* Invalid opcode */
{
        printf("invalid opcode\n");
}
void err7_handler(void) /* Device not available */
{
        printf("device not available\n");
}
void err8_handler(void) /* Double fault */
{
        printf("double fault\n");
}
void err9_handler(void) /* Coprocessor Segment Overrun */
{
        printf("coprocessor segment overrun\n");
}
void err10_handler(void) /* Invalid TSS */
{
        printf("invalid tss\n");
}
void err11_handler(void) /* Segment not present */
{
        printf("segment not present\n");
}
void err12_handler(void) /* Stack exception */
{
        printf("stack exception\n");
}
void err13_handler(void) /* General protection fault */
{
        printf("general protection fault\n");
}
void err14_handler(void) /* Page fault */
{
        printf("page fault\n");
}
void err15_handler(void) /* Coprocessor error */
{
        printf("coprocessor error\n");
}

void err16_handler(void) /* 2-byte SW interrupt */
{
        printf("2-byte sw interrupt\n");
}