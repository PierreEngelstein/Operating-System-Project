#include "lib.h"

void dump_register()
{
        __asm__( "mov %%ah, %0" : "=a" (ah) );
        __asm__( "mov %%al, %0" : "=a" (al) );
        __asm__( "mov %%bh, %0" : "=a" (bh) );
        __asm__( "mov %%bl, %0" : "=a" (bl) );
        __asm__( "mov %%ch, %0" : "=a" (bh) );
        __asm__( "mov %%cl, %0" : "=a" (bl) );
        __asm__( "mov %%dh, %0" : "=a" (dh) );
        __asm__( "mov %%dl, %0" : "=a" (dl) );

        __asm__( "mov %%ax, %0" : "=a" (ax) );
        __asm__( "mov %%bx, %0" : "=a" (bx) );
        __asm__( "mov %%cx, %0" : "=a" (cx) );
        __asm__( "mov %%dx, %0" : "=a" (dx) );

        __asm__( "mov %%eax, %0" : "=a" (eax) );
        __asm__( "mov %%ebx, %0" : "=a" (ebx) );
        __asm__( "mov %%ecx, %0" : "=a" (ecx) );
        __asm__( "mov %%edx, %0" : "=a" (edx) );
        __asm__( "mov %%esi, %0" : "=a" (esi) );
        __asm__( "mov %%edi, %0" : "=a" (edi) );
        __asm__( "mov %%esp, %0" : "=a" (esp) );
        __asm__( "mov %%ebp, %0" : "=a" (ebp) );
}

void print_registers()
{
        dump_register();
        printf("\nRegisters dump :\n");
        printf("ah = %x ; bh = %x ; ch = %x ; dh = %x\n", ah, bh, ch, dh);
        printf("al = %x ; bl = %x ; cl = %x ; dl = %x\n", al, bl, cl, dl);
        printf("ax = %x ; bx = %x ; cx = %x ; dx = %x\n", ax, bx, cx, dx);
        printf("eax = %x ; ebx = %x ; ecx = %x ; edx = %x\n", eax, ebx, ecx, edx);
        printf("esi = %x ; edi = %x ; esp = %x ; ebp = %x\n", esi, edi, esp, ebp);
}