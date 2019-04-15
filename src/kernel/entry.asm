[bits 32]
[extern main]
[global _start]
; TODO : setup segments and stack
mov eax, 0x9000      ;Update the segment register
; mov ds, eax
; mov ss, eax
; mov es, eax
; mov fs, eax
; mov gs, eax

mov ebp, 0x80000     ;Setup the stack at the location we want
mov esp, ebp

_start:
   call main
   hlt

; The IDT handler
global load_idt

global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15

global irq0_handler
global irq1_handler
global irq2_handler
global irq3_handler
global irq4_handler
global irq5_handler
global irq6_handler
global irq7_handler
global irq8_handler
global irq9_handler
global irq10_handler
global irq11_handler
global irq12_handler
global irq13_handler
global irq14_handler
global irq15_handler

extern irq0_handler
extern irq1_handler
extern irq2_handler
extern irq3_handler
extern irq4_handler
extern irq5_handler
extern irq6_handler
extern irq7_handler
extern irq8_handler
extern irq9_handler
extern irq10_handler
extern irq11_handler
extern irq12_handler
extern irq13_handler
extern irq14_handler
extern irq15_handler

load_idt:
   mov edx, [esp + 4]
   lidt [edx]
   sti
   ret

irq0:
   pusha
   call irq0_handler
   popa
   ret
irq1:
   pusha
   call irq1_handler
   popa
   ret
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