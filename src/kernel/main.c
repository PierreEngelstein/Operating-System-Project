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

char *fgets(char *dest, int max)
{
        int c;
        char *p;
        for(p = dest, max--; max > 0; max--)
        {
                c = scanf(); /* Process the input */
                // c = getLastChar(); /* And get the last typed character */
                if(c == '\n')
                        break;
                *p++ = c;
        }
        *p = '\0';
        if(p == dest)
                return NULL;
        return (p);
}

int main()
{
        //init_pics(0x20, 0x27);
        idt_init();
        /* Initialize the console */
        console_init();
        /* Print some random thing on screen to test */
        printf("Started Kernel ...\n");
        printf("Testing number %d\n", 123);

        printf("Start inputing things on keyboard :\n");
        
        // IDT_Entry *IDT;
        // printf("\nsizeof(IDT_Entry) = %d\n", sizeof(unsigned char));
        // IDT = 0x7000;
        // extern int irq0();
        // extern int irq2();
        // unsigned long irq0_address = (unsigned long)irq0;
        // unsigned long irq2_address = (unsigned long)irq2;
        // createIDTEntry(&(IDT[47]), irq2_address);
        // printf("address of IDT[0] : %x\n", &(IDT[47]));
        // printf("IDT[0].offset_higherbits = %x\n", IDT[47].offset_higherbits);
        // printf("IDT[0].offset_lowerbits = %x\n", IDT[47].offset_lowerbits);
        // printf("IDT[0].selector = %x\n", IDT[47].selector);
        // printf("IDT[0].type_attr = %x", IDT[47].type_attr);

        /* Test the keyboard input */
        // int lgMax = 128;
        // char cmd[lgMax];
        // cmd[0] = '\0';
        // for(;;)
        // {
        //         fgets(cmd, lgMax);
        // }
        // printf("Hello World !");
        for(;;){}
        return 0;
}
