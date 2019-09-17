[bits 64]
extern main
global _start
; TODO : setup segments and stack

mov ebp, 0x3000     ;Setup the stack at the location we want
mov esp, ebp

_start:
   ; mov eax, 0x08
   ; mov rbx, 0x06
   ; push rbx
   ; push rax
   call main
   hlt