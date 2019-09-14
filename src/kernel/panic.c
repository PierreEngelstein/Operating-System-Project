#include "lib.h"

void kpanic(char *message)
{
    printf("[KERNEL PANIC] ");
    printf(message);
    for(;;){} //Stand by and do nothing else
}
