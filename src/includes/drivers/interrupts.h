#include "types.h"

/* Initializes the interrupts */
int idt_init();
/* Disables all interrupts */
void cli();
/* Enables all interrupts */
void sei();
/* Enables a specific interrupt */
void enable_interrupt(uint8 interrupt);

/* Definition of all interrupts flags (use in enable_interrupt) */
#define INTERRUPT_TIMER         0
#define INTERRUPT_KEYBOARD      1
#define INTERRUPT_CASCADE       2
#define INTERRUPT_COM2          3
#define INTERRUPT_COM1          4
#define INTERRUPT_LPT2          5
#define INTERRUPT_FLOPPY        6
#define INTERRUPT_LPT1          7
#define INTERRUPT_RTCLOCK       8
#define INTERRUPT_PERIPH1       9
#define INTERRUPT_PERIPH2       10
#define INTERRUPT_PERIPH3       11
#define INTERRUPT_MOUSE         12
#define INTERRUPT_FPU           13
#define INTERRUPT_ATA1          14
#define INTERRUPT_ATA2          15
