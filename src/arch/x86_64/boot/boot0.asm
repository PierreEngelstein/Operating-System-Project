;---------boot0.asm-------------
;First stage botloader
;This stage will only setup the real-mode stack and load the second stage bootloader.
;To optimize place token, I won't use the string_ctes.asm file, or other files.
;I will see later on to optimize speed (maybe)
;For the moment, I probably won't have to touch again to this file.
;Author : Pierre Engelstein
;-------------------------------
[bits 16]
[org 0x7c00]
cli                          ;We are not safe to use interruptions here (old BIOSes)
;Setup the registers
xor ax, ax                   ;We want ax to be set to 0
mov ds, ax                   ;Set the data segment to 0, offset 0x7c00
mov es, ax                   ;For the moment, DS = ES

;Setup the real-mode stack
mov bp, STACK_START_LOCATION ;Setup the stack to start at 0x14FF
mov sp, bp                   ;Stack pointer to start of the stack
mov ss, ax

sti                          ;Now that we are safe, we can re-enable the interrupts

;clear the screen
mov ax, 0x3
int 0x10
;Reset the floppy disk controller (interrupt 0x13, function 0x00)
mov bx, s_floppyreset
call print_str
xor ax, ax             ;Function flag (0x00 for reseting floppy disk)
mov dl, 0x80           ;We reset drive 0
int 0x13
jc errorFloppy         ;Stop the program if there is an error (carry flag set)

mov bx, s_bootRead
call print_str

;Load the bootloader into memory at address 0x8000
mov bx, SECOND_STAGE_LOCATION
mov dh, SECOND_STAGE_SIZE  ;We read 2 sectors (corresponding to the padding indicated in boot1.asm)
mov cl, 0x02               ;We start reading after this first sector
call disk_load

mov dx, bx
mov bx, s_endRead
call print_str
call print_hex

;Jump to the second stage bootloader
jmp 0x000:SECOND_STAGE_LOCATION

jmp $

;----------Routines-----------------
;String printing routine
;Call with  :
;             bx = string to be printed
;return     :
;             nothing
print_str:
   pusha
   loop_str:
      mov al, [bx]    ;**We move the current character to be printed to the al register where 0x10 can print it
      cmp al, 0       ;**We compare the current character to 0, and if it is, we end the printing
      jne print_char  ;**we jump to the end of the function
      popa
      ret
   print_char:
      mov ah, 0x0e
      int 0x10
      add bx, 1
      jmp loop_str
;Hexadecimal printing routine
;Call with  :
;             dx = hexadecimal number to be printed
;return     :
;             nothing
print_hex:
   pusha
   mov cx, 4                  ;**we want it printed 4 times
   loop_hex:
      dec cx                  ;**We decrement cx each time
      mov ax, dx              ;**We move the value we want to print into the ax register
      shr dx, 4               ;**shift bx 4 bits to the right
      and ax, 0xf             ;**We mask ah to get the last 4 bits
      mov bx, s_hex_out         ;**Moving the base hex to bx
      add bx, 2               ;**We add 2 to bx : we don't want to touch to '0x'
      add bx, cx              ;**And we go where we are working now
      cmp ax, 0xa             ;**Check if the current character is a letter or a character
      jl print_hex_letter     ;**If it is a number (ascii value lower than 0xa) we go setting the value
      add byte [bx], 7        ;**Otherwise we add 7 to the current byte
      jl print_hex_letter     ;**And we go setting the value
      print_hex_letter:
         add byte [bx], al    ;**We add the value of the byte to the char at bx
         cmp cx, 0            ;**We check if it is the end of the string to be printed
         je print_hex_end     ;**If so, we jump to the end of the function
         jmp loop_hex         ;**Otherwise, we loop again to the next number
      print_hex_end:
         mov bx, s_hex_out      ;**Setting the hex string to be printed
         call print_str       ;**Printing it
         call hexout_reset
         popa
         ret
         hexout_reset:
            pusha
            mov bx, s_hex_out
            mov cx, 5
            add bx, 2                ;We don't want to change '0x'
            hexout_reset_loop:
               dec cx
               cmp cx, 0      ;While the character is not '0', we put '0' in it
               jne hexout_set
               jmp hexout_end
            hexout_set:
               mov byte [bx], 0x30   ;We put '0' in bx (ASCII 0x30 = d.48)
               inc bx                ;We move to the next character to reset
               jmp hexout_reset_loop
            hexout_end:
               popa
               ret
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
   ;dl = 0x00 if floppy disk 1, 0x01 if floppy disk 2, 0x80 if hdd 1, 0x81 if hdd2
   mov ch, 0x00      ;cylinder number [0x000 -> 0x3FF]
   int 0x13
   jc errorDiskLoad  ;Stop the program if there is an error (carry flag set)
   pop dx
   cmp al, dh
   jne errorDiskLoad ;We want to be sure that we read all the sectors we wanted
   popa
   ret
;Floppy reset error
errorFloppy:
   mov bx, s_floppyresestFail
   call print_str
   mov dx, ax
   call print_hex
   cli
   jmp $
;Disk load error
errorDiskLoad:
   mov bx, s_diskreadError
   call print_str
   mov dx, ax
   call print_hex
   cli
   jmp $

;----------Constants----------------
s_floppyreset      db "Reseting floppy disk controller...", 10, 13, 0
s_bootRead         db "Reading the second stage bootloader ...", 10, 13, 0
s_endRead          db "Written the bootloader at ", 0

s_floppyresestFail db "Failed to reset disk controller !", 10, 13, "Error code : ax = ", 0
s_diskreadError    db "Failed to read second stage bootloader", 10, 13, "  => [al = nb sectors read, ah = error code] : ", 0

s_hex_out          db '0x0000', 10, 13, 0

%include "src/includes/boot/ct.asm"

;Magic signature
times 510 - ($ - $$) db 0
dw 0xaa55
