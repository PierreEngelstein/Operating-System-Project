;---------gdt.asm-------------
;Global Descriptor Table loader
;Necessary code to enter 32-bit protected mode
;Author : Pierre Engelstein
;-------------------------------

gdt_start:      ; Mandatory null Descriptor
   dd 0x0
   dd 0x0
gdt_code:       ; Code segment descriptor
   ; base = 0x0, limit = 0xfffff
   ; 1st flag : (present)1 (privilege)00 (descriptor type)1 ->1001b
   ; type flag : (code)1 (conforming)0 (readable)1 (accessed)0 ->1010b
   ; 2nd flag : (granularity)1 (32-bit default)1 (64-bit seg)0 (AVL)0 ->1100b
   dw 0xffff    ; Segment limit (bits 0 - 15)
   dw 0x0       ; Segment base (bits 0 -15)
   db 0x0       ; Segment base (bits 16 - 23)
   db 10011010b ; 1st flag, Type flag
   db 11001111b ; 2nd flag, Segment limit (b$its 16-19)
   db 0x0       ; Segment base (bits 24 - 31)
gdt_data:       ; Data segment descriptor
   ; Same as code segment except for the type flags:
   ; type flags : (code)0 (expand down)0 (writable)1 (accessed)0 -> 0010b
   dw 0xffff    ; Segment limit (bits 0 - 15)
   dw 0x0       ; Segment base (bits 0 -15)
   db 0x0       ; Segment base (bits 16 - 23)
   db 10010010b ; 1st flag, Type flag
   db 11001111b ; 2nd flag, Segment limit (bits 16-19)
   db 0x0       ; Segment base (bits 24 - 31)
gdt_end:        ; Put a label here at the end of the gdt so we can have the assembler
                ; calculate the size of the GDT Descriptor Table (see below)

;GDT Descriptor
gdt_descriptor:
   dw gdt_end - gdt_start - 1 ; Size of out GDT (less one of the true size)
   dd gdt_start               ; Start address of our GDT

; Define some constants for the GDT Segment Descriptor offsets, which
; are what segment registers must contain when in protected mode.
; When we set DS = 0x10 in PM, the CPU knows we mean it to  use the
; segment described at offset 0x10 (16 bytes) in our GDT, which in
; ou case is the DATA segment (0x0 -> null, 0x08 -> CODE, 0x10 -> DATA)

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

; 64 bit mode GDT
GDT64:
   .Null: equ $ - GDT64    ; Null descriptor
   dw 0xffff               ; Limit (Low)
   dw 0                    ; Base (low)
   db 0                    ; Base (middle)
   db 0                    ; Access
   db 1                    ; Granularity
   db 0                    ; Base (High)
   .Code: equ $ - GDT64    ; Code descriptor
   dw 0                    ; Limit (low)
   dw 0                    ; Base (low)
   db 0                    ; Base (middle)
   db 10011010b            ; Access (exec / read)
   db 10101111b            ; Granularity, 64 bits flag, limit19:16
   db 0                    ; Base (high)
   .Data: equ $ - GDT64    ; Data descriptor
   dw 0                    ; Limit (low)
   dw 0                    ; Base(low)
   db 0                    ; Base (middle)
   db 10010010b            ; Access (read/write)
   db 00000000b            ; Granularity
   db 0                    ; Base (high)
   .Pointer:               ; The GDT-pointer
   dw $ - GDT64 - 1
   dq GDT64