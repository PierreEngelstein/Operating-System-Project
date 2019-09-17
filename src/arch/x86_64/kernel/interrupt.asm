;--------------------------------------------------
; ASM-level interrupt operations.
; Handles IDT creation and hardware interrupts
;--------------------------------------------------
[bits 64]

global load_idt ; The main IDT loading procedure

; ASM irqs
global irq0, irq1, irq2, irq3, irq4, irq5, irq6, irq7, irq8, irq9, irq10, irq11, irq12, irq13, irq14, irq15, syscall_c
; Reference to c-level irqs
global irq0_handler, irq1_handler, irq2_handler, irq3_handler, irq4_handler, irq5_handler, irq6_handler, irq7_handler, irq8_handler, irq9_handler
global irq10_handler, irq11_handler, irq12_handler, irq13_handler, irq14_handler, irq15_handler, syscall_handler

extern irq0_handler, irq1_handler, irq2_handler, irq3_handler, irq4_handler, irq5_handler, irq6_handler, irq7_handler, irq8_handler, irq9_handler
extern irq10_handler, irq11_handler, irq12_handler, irq13_handler, irq14_handler, irq15_handler, syscall_handler

syscall_c:
   push rax
   call syscall_handler
   pop rax
   iretq

load_idt:
   lidt [rdi]
   sti
   ret

irq0:
   push rax
   push rcx
   push rdx
   push r8
   push r9
   push r10
   push r11
   call irq0_handler
   pop r11
   pop r10
   pop r9
   pop r8
   pop rdx
   pop rcx
   pop rax
   iretq
irq1:
   push rax
   push rcx
   push rdx
   push r8
   push r9
   push r10
   push r11
   call irq1_handler
   pop r11
   pop r10
   pop r9
   pop r8
   pop rdx
   pop rcx
   pop rax
   iretq
irq2:
   push rax
   push rcx
   push rdx
   push r8
   push r9
   push r10
   push r11
   call irq2_handler
   pop r11
   pop r10
   pop r9
   pop r8
   pop rdx
   pop rcx
   pop rax
   iretq
irq3:
   push rax
   push rcx
   push rdx
   push r8
   push r9
   push r10
   push r11
   call irq3_handler
   pop r11
   pop r10
   pop r9
   pop r8
   pop rdx
   pop rcx
   pop rax
   iretq
irq4:
   push rax
   push rcx
   push rdx
   push r8
   push r9
   push r10
   push r11
   call irq4_handler
   pop r11
   pop r10
   pop r9
   pop r8
   pop rdx
   pop rcx
   pop rax
   iretq
irq5:
   push rax
   push rcx
   push rdx
   push r8
   push r9
   push r10
   push r11
   call irq5_handler
   pop r11
   pop r10
   pop r9
   pop r8
   pop rdx
   pop rcx
   pop rax
   iretq
irq6:
   push rax
   push rcx
   push rdx
   push r8
   push r9
   push r10
   push r11
   call irq6_handler
   pop r11
   pop r10
   pop r9
   pop r8
   pop rdx
   pop rcx
   pop rax
   iretq
irq7:
   push rax
   push rcx
   push rdx
   push r8
   push r9
   push r10
   push r11
   call irq7_handler
   pop r11
   pop r10
   pop r9
   pop r8
   pop rdx
   pop rcx
   pop rax
   iretq
irq8:
   push rax
   push rcx
   push rdx
   push r8
   push r9
   push r10
   push r11
   call irq8_handler
   pop r11
   pop r10
   pop r9
   pop r8
   pop rdx
   pop rcx
   pop rax
   iretq
irq9:
   push rax
   push rcx
   push rdx
   push r8
   push r9
   push r10
   push r11
   call irq9_handler
   pop r11
   pop r10
   pop r9
   pop r8
   pop rdx
   pop rcx
   pop rax
   iretq
irq10:
   push rax
   push rcx
   push rdx
   push r8
   push r9
   push r10
   push r11
   call irq10_handler
   pop r11
   pop r10
   pop r9
   pop r8
   pop rdx
   pop rcx
   pop rax
   iretq
irq11:
   push rax
   push rcx
   push rdx
   push r8
   push r9
   push r10
   push r11
   call irq11_handler
   pop r11
   pop r10
   pop r9
   pop r8
   pop rdx
   pop rcx
   pop rax
   iretq
irq12:
   push rax
   push rcx
   push rdx
   push r8
   push r9
   push r10
   push r11
   call irq12_handler
   pop r11
   pop r10
   pop r9
   pop r8
   pop rdx
   pop rcx
   pop rax
   iretq
irq13:
   push rax
   push rcx
   push rdx
   push r8
   push r9
   push r10
   push r11
   call irq13_handler
   pop r11
   pop r10
   pop r9
   pop r8
   pop rdx
   pop rcx
   pop rax
   iretq
irq14:
   push rax
   push rcx
   push rdx
   push r8
   push r9
   push r10
   push r11
   call irq14_handler
   pop r11
   pop r10
   pop r9
   pop r8
   pop rdx
   pop rcx
   pop rax
   iretq
irq15:
   push rax
   push rcx
   push rdx
   push r8
   push r9
   push r10
   push r11
   call irq15_handler
   pop r11
   pop r10
   pop r9
   pop r8
   pop rdx
   pop rcx
   pop rax
   iretq