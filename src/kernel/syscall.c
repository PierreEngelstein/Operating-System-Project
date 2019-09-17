#define SYSCALLS_START() switch(index){
#define SYSCALLS_END() }
#define SYSCALL_REGISTER(index, function) case index: function();break;
#include "io.h"
#include "drivers/keyboard.h"

int KnSyscall(int syscall_index)
{
        asm( "movl %0, %%eax" : : "b" (syscall_index) : "eax");
        __asm__("int $0x80");
        return 0;
}

int KnShutdown()
{
        KnSyscall(1);
        return 0;
}

int KnKeyboard()
{
        KnSyscall(2);
        return 0;
}

void syscall_handler(int index)
{
        SYSCALLS_START()
                SYSCALL_REGISTER(1, syscall_knshutdown)
                SYSCALL_REGISTER(2, syscall_keyboard)
        SYSCALLS_END()
}

int syscall_knshutdown()
{
        port_word_out(0x604, 0x2000); // Qemu-specific
        return 0;
}

int syscall_keyboard()
{
        printf("Hello World\n");
        return 0;
}