#include "lib.h"

void kpanic(char *message)
{
    printf(message);
    for(;;){} //Stand by and do nothing else
}
