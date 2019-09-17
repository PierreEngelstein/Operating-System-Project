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

;--- Get and print low memory map
call GetLowMem
mov bx, s_lowmem_size         ;And print it
call print_str
mov cx, 10
call print_number
mov bx, s_KiB
call print_str
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
; call enableLongMode

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
  errorDiskLoad:
     mov bx, s_diskreadError
     call print_str
     ;print error code
     push ax
     mov al, ah
     and ax, 0x00FF
     mov cx, 16
     mov bx, s_diskCode
     call print_str
     call print_number
     call goToLine
     ;print number of sector already written
     pop ax
     and ax, 0x00FF
     mov cx, 10
     mov bx, s_sectRead
     call print_str
     call print_number
     call goToLine
     cli
     jmp $

fail:
   mov bx, s_ext_fail
   call print_str
   jmp $

;----------Includes needed----------
%include "src/includes/boot/print.asm"
%include "src/includes/boot/mem.asm"
%include "src/includes/boot/ct.asm"
%include "src/includes/boot/string_ctes.asm"
%include "src/includes/boot/switch_32.asm"
%include "src/arch/x86_64/boot/gdt.asm"
;-----------------------------------
;Protected mode code (Kernel loader)
[bits 32]
beginPM:
   ; Detect CPUID
   pushfd
   pop eax
   mov ecx, eax
   xor eax, 1 << 21
   push eax
   popfd
   pushfd
   pop eax
   push ecx
   popfd
   xor eax, ecx
   jz $
   ; If CPUID is okay, detect long mode
   mov eax, 0x80000000
   cpuid
   cmp eax, 0x80000001
   jb $
   mov eax, 0x80000001
   cpuid
   test edx, 1 << 29
   jz $
   ; If long mode is supported, enable it
   ; First disable paging
   mov eax, cr0
   and eax, 01111111111111111111111111111111b ; Clear bit 31 of cr0 (PG bit)
   mov cr0, eax
   ; Clear the tables
   mov edi, 0x1000
   mov cr3, edi
   xor eax, eax
   mov ecx, 4096
   rep stosd ; Clear memory
   mov edi, cr3
   ; Set Page-Map Level-4 table
   mov DWORD [edi], 0x2003
   add edi, 0x1000
   mov DWORD [edi], 0x3003
   add edi, 0x1000
   mov DWORD [edi], 0x4003
   add edi, 0x1000
   mov ebx, 0x00000003
   mov ecx, 512
SetEntry:
   mov DWORD[edi], ebx
   add ebx, 0x1000
   add edi, 8
   loop SetEntry
   ; Enable PAE-paging by setting PAE bit in cr4
   mov eax, cr4
   or eax, 1 << 5
   mov cr4, eax
   ; Set the Long-Mode bit
   mov ecx, 0xC0000080
   rdmsr
   or eax, 1 << 8
   wrmsr
   ; Re-enable paging by setting bit 31 of cr0
   mov eax, cr0
   or eax, 1 << 31
   mov cr0, eax
   lgdt [GDT64.Pointer]
   jmp GDT64.Code:BeginPM64
   hlt
   ; mov eax, [gdt_descriptor]
   ; push 0x16
   ; mov eax, 0x16
   mov eax, 0x1234
   cli
   call KERNEL_LOCATION
   hlt

[BITS 64]
BeginPM64:
   mov eax, DATA_SEG      ;Update the segment register
   mov ds, eax
   mov ss, eax
   mov es, eax
   mov fs, eax
   mov gs, eax

   mov ebp, PROTECTED_STACK_LOCATION     ;Setup the stack at the location we want
   mov esp, ebp
   ; cli
   mov eax, 0x1234
   call KERNEL_LOCATION
   hlt

;We make sure this file is exactly the size we want, given the size in ct.asm
times (SECOND_STAGE_SIZE * 512 - 2) - ($ - $$) db 0
dw 0xffff