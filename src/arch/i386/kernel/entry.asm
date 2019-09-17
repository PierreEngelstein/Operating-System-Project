[bits 32]
extern main
global _start
; TODO : setup segments and stack
mov eax, 0x9000

mov ebp, 0x80000     ;Setup the stack at the location we want
mov esp, ebp

_start:
   push edx
   call main
   hlt