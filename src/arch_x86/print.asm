;---------print.asm-------------
;Printing to screen routines
;Only works for 16-bit real mode (bootloader-purpose only)
;Author : Pierre Engelstein
;-------------------------------

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

;Clearing the screen
clear_screen:
   pusha
   mov ax, 0x3
   int 0x10
   popa
   ret
