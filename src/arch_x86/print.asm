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

;Number printing routine
;Call with  :
;             bx = base i which it must be printed
;             dx = number to be printed
;return     :
;             nothing
;example : printing 0xdada in base 10 :
;          mov ax, 0xdada
;          mov cx, 10
;          call print_number
;
print_number:
   pusha
   mov bx, 0           ;Number of characters to be printed
   loop_number:
      xor dx, dx
      div cx
      push dx
      inc bx
      cmp ax, 0
      jne loop_number
      je loop_print
   loop_print:
      pop dx
      mov al, dl         ;We setup the number to be printed
      cmp al, 0xa
      jge loop_print_character
      jl loop_print_number
   loop_print_character:
      add al, 55
      jmp loop_print_continue
   loop_print_number:
      add al, '0'
      jmp loop_print_continue
   loop_print_continue:
      mov ah, 0x0e
      int 0x10
      dec bx
      cmp bx, 0
      jne loop_print
      je print_number_end
   print_number_end:
      ;We now print the base indicator if it is a binary, octal or hexadecimal
      cmp cx, 2
      je print_binary_indicator
      cmp cx, 8
      je print_octal_indicator
      cmp cx, 16
      je print_hexa_indicator
      jmp print_number_real_end
   print_binary_indicator:
      mov al, 'b'
      int 0x10
      jmp print_number_real_end
   print_octal_indicator:
      mov al, 'o'
      int 0x10
      jmp print_number_real_end
   print_hexa_indicator:
      mov al, 'h'
      int 0x10
   print_number_real_end:
      popa
      ret

;Clearing the screen
clear_screen:
   pusha
   mov ax, 0x3
   int 0x10
   popa
   ret

;Go to the next line
goToLine:
   pusha
   mov ah, 0x0e
   mov al, 10
   int 0x10
   mov al, 13
   int 0x10
   popa
   ret
