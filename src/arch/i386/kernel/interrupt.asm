;--------------------------------------------------
; ASM-level interrupt operations.
; Handles IDT creation and hardware interrupts
;--------------------------------------------------
[bits 32]

global load_idt ; The main IDT loading procedure

; ASM irqs
global irq0, irq1, irq2, irq3, irq4, irq5, irq6, irq7, irq8, irq9, irq10, irq11, irq12, irq13, irq14, irq15, syscall_c
; Reference to c-level irqs
global irq0_handler, irq1_handler, irq2_handler, irq3_handler, irq4_handler, irq5_handler, irq6_handler, irq7_handler, irq8_handler, irq9_handler
global irq10_handler, irq11_handler, irq12_handler, irq13_handler, irq14_handler, irq15_handler, syscall_handler

extern irq0_handler, irq1_handler, irq2_handler, irq3_handler, irq4_handler, irq5_handler, irq6_handler, irq7_handler, irq8_handler, irq9_handler
extern irq10_handler, irq11_handler, irq12_handler, irq13_handler, irq14_handler, irq15_handler, syscall_handler

load_idt:
   mov edx, [esp + 4]
   lidt [edx]
   sti
   ret

syscall_c:
   push eax
   call syscall_handler
   pop eax
   iret
irq0:
   pusha
   call irq0_handler
   popa
   iret
irq1:
   pusha
   call irq1_handler
   popa
   iret
irq2:
   pusha
   call irq2_handler
   popa
   ret
irq3:
   pusha
   call irq3_handler
   popa
   ret
irq4:
   pusha
   call irq4_handler
   popa
   ret
irq5:
   pusha
   call irq5_handler
   popa
   ret
irq6:
   pusha
   call irq6_handler
   popa
   ret
irq7:
   pusha
   call irq7_handler
   popa
   ret
irq8:
   pusha
   call irq8_handler
   popa
   ret
irq9:
   pusha
   call irq9_handler
   popa
   ret
irq10:
   pusha
   call irq10_handler
   popa
   ret
irq11:
   pusha
   call irq11_handler
   popa
   ret
irq12:
   pusha
   call irq12_handler
   popa
   ret
irq13:
   pusha
   call irq13_handler
   popa
   ret
irq14:
   pusha
   call irq14_handler
   popa
   ret
irq15:
   pusha
   call irq15_handler
   popa
   ret