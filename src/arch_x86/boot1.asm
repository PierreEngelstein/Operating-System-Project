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
;Some messages indicating information
mov cx, 16
mov bx, s_startupSecond
call print_str
call goToLine
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

int 0x12                      ;Get the low-memory size (KiB) with interrupt 12h (result saved in ax)
mov bx, s_lowmem_size         ;And print it
call print_str
mov cx, 10
mov dx, ax
call print_number
mov bx, s_KiB
call print_str
call goToLine
call goToLine

;Enable the A20 gate via BIOS's interrupts (will do other methods later on...)
mov bx, s_a20_check
call print_str
mov ax, 0x2402              ;Interrupt 15h, function 2402h : query A20 gate status
int 0x15
cmp al, 0                  ;Result stored in AL : AL=0 => gate disabled ; AL=1 => gate enabled
jne skipa20                ;If the gate is enabled, we skip the enabling of the gate (to avoid errors)

mov bx, s_a20_disabled
call print_str
mov ax, 0x2401             ;Interrupt 15h, function 2401 : enable A20
int 0x15
jc errora20                ;Stop the program if there is an error (carry flag set)
skipa20:                   ;Else, we continue the road
mov bx, s_a20_enabled
call print_str

call switch_to_pm

jmp $

errora20:
   mov bx, s_a20error
   call print_str
   mov dx, ax
   mov cx, 16
   call print_number
   cli
   jmp $

;----------Includes needed----------
%include "src/arch_x86/print.asm"
%include "src/arch_x86/string_ctes.asm"
%include "src/arch_x86/ct.asm"
%include "src/arch_x86/gdt.asm"
%include "src/arch_x86/switch_32.asm"
;-----------------------------------

;Protected mode code
[bits 64]
beginPM:
   jmp $

;We make sure this file is exactly the size we want, given the size in ct.asm
times (SECOND_STAGE_SIZE * 512 - 2) - ($ - $$) db 0
dw 0xffff
