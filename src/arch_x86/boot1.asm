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
;call clear_screen              ;We clear the screen from previous messages we did not needed
;call goToLine
mov bx, s_separator
call print_str
;Some messages indicating information
mov cx, 16
mov bx, s_startupSecond
call print_str
call goToLine
mov bx, s_stage_start
call print_str
mov ax, $$
push $$
call print_number
call goToLine
mov bx, s_stage_end
call print_str
mov ax, $$ + SECOND_STAGE_SIZE*512
push $$ + SECOND_STAGE_SIZE*512
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
call goToLine
;Load kernel into memory
mov bx, s_kernel_read
call print_str
mov bx, KERNEL_LOCATION    ;Load the Kernel at 0x9000
mov dh, KERNEL_SIZE        ;Read 2 sectors (for the moment it is static, will work to make it dynamic later)
mov cl, 0x02               ;Start reading after this sector
add cl, SECOND_STAGE_SIZE
call disk_load

mov bx, s_kernel_endread
call print_str
mov ax, KERNEL_LOCATION
mov cx, 16
call print_number

;Switch to protected mode
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

;Disk load routine
;Call with :
;              bx = Where to store the sectors read
;              dh = How much sectors to read
;              cl = From which sector we read [0x01 -> 0x11]
;Return :
; If error, ah = error code
;           al = number of sector that have been already read
;TODO : manage multiple head/cylinder if we want to load more than 128 sectors (which could be a good idea...)
disk_load:
  pusha
  push dx
  mov ah, 0x02      ;Interrupt 13h, function 02h
  mov al, dh        ;How much sectors do we read [0x01 -> 0x80]
  mov dh, 0x00      ;Head number
  mov dl, 0x80      ;dl = 0x00 if floppy disk 1, 0x01 if floppy disk 2, 0x80 if hdd 1, 0x81 if hdd2
  mov ch, 0x00      ;cylinder number [0x000 -> 0x3FF]
  int 0x13
  jc errorDiskLoad  ;Stop the program if there is an error (carry flag set)
  pop dx
  cmp al, dh
  jne errorDiskLoad ;We want to be sure that we read all the sectors we wanted
  popa
  ret
;Disk load error
errorDiskLoad:
   mov bx, s_diskreadError
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

;Protected mode code (Kernel loader)
[bits 64]
beginPM:
   jmp $

;We make sure this file is exactly the size we want, given the size in ct.asm
times (SECOND_STAGE_SIZE * 512 - 2) - ($ - $$) db 0
dw 0xffff
