[bits 32]
[extern main]
[global _start]
;TODO : setup segments and stack
; mov eax, 0x9000      ;Update the segment register
; mov ds, eax
; mov ss, eax
; mov es, eax
; mov fs, eax
; mov gs, eax
;
; mov ebp, 0x80000     ;Setup the stack at the location we want
; mov esp, ebp
_start:
   call main
   hlt
