;---------boot1.asm-------------
;Second stage botloader
;This will manage all the steps that we could not do
;during the first stage until we are able to load the kernel (c code)
;Author : Pierre Engelstein
;-------------------------------
[bits 16]
[org 0x8000]
;Before we do anything, we setup the data segment, the extended segment and the stack
cli                            ;We are not safe to use interruptions here (old BIOSes)
;Setup the registers
xor ax, ax                     ;We want ax to be set to 0
mov ds, ax                     ;Set the data segment to 0, offset 0x8000
mov es, ax                     ;For the moment, DS = ES

;Setup the real-mode stack
mov bp, STACK_START_LOCATION   ;Setup the stack to start at 0x14FF
mov sp, bp                     ;Stack pointer to start of the stack
mov ss, ax

sti                            ;Now that we are safe, we can re-enable the interrupts

;Now that's done, we can do whatever we want to.
call clear_screen              ;We clear the screen from previous messages we did not needed
;Some messages...
mov bx, s_startupSecond
call print_str
mov bx, s_stage_start
call print_str
mov dx, $$
call print_hex
mov bx, s_stage_end
call print_str
mov dx, $$ + SECOND_STAGE_SIZE*512
call print_hex

call MainLoop

;Just for fun, a simple keyboard typer :)
MainLoop:
    mov ah, 00h    ;BIOS.GetKey
    int 16h
    cmp al, 27     ;Is it ESCAPE ?
    jne ProcessOtherKey
    cmp al, 8
    ;je ProcessBackKey
ProcessEscapeKey:
   jmp $$
ProcessOtherKey:
   mov ah, 0x0e
   int 0x10
   jmp MainLoop
ProcessBackKey:
   mov ah, 0x0e
   mov al, 32
   int 0x10
   jmp MainLoop



jmp $

;----------Includes needed----------
%include "src/arch_x86/print.asm"
%include "src/arch_x86/string_ctes.asm"
%include "src/arch_x86/ct.asm"
;-----------------------------------
;We make sure this file is exactly the size we want, given the size in ct.asm
times (SECOND_STAGE_SIZE * 512 - 2) - ($ - $$) db 0
dw 0xffff
