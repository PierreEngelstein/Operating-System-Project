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
mov cx, 16
mov bx, s_startupSecond
call print_str
mov bx, s_stage_start
call print_str
mov ax, $$
call print_number
call goToLine
mov bx, s_stage_end
call print_str
mov ax, $$ + SECOND_STAGE_SIZE*512
call print_number
call goToLine
mov cx, 10
mov bx, s_stage_size
call print_str
sub ax, $$
call print_number
mov bx, s_bytes
call print_str
call goToLine


jmp $

;----------Includes needed----------
%include "src/arch_x86/print.asm"
%include "src/arch_x86/string_ctes.asm"
%include "src/arch_x86/ct.asm"
;-----------------------------------
;We make sure this file is exactly the size we want, given the size in ct.asm
times (SECOND_STAGE_SIZE * 512 - 2) - ($ - $$) db 0
dw 0xffff
