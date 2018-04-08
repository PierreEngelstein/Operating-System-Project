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
      xor dx, dx               ;The number read is dx:ax, but we don't need dx (we are still in 16 bit), so dx = 0
      div cx                   ;(dx:ax)/cx
      push dx                  ;Push the result so we are able to print it in order later
      inc bx                   ;Increment the character counter
      cmp ax, 0                ;If the quotient is 0, then we have finished to compute our number in base n
      jne loop_number          ;Else, we continue the division
      je loop_print            ;Then we can print the number
   loop_print:
      pop dx                   ;Get the number to be printed
      mov al, dl               ;We setup the number to be printed
      cmp al, 0xa              ;If the number to be printed is not in [0-9], then we print a letter
      jge loop_print_character ;Jump to print a character
      jl loop_print_number     ;Jump to print a number
   loop_print_character:
      add al, 55               ;Add the printable ascci 'a'
      jmp loop_print_continue  ;Continue over printing
   loop_print_number:
      add al, '0'              ;Add the printable ascci '0'
      jmp loop_print_continue  ;Continue over printing
   loop_print_continue:
      mov ah, 0x0e             ;Interrupt 10h, function 02h
      int 0x10
      dec bx                   ;We have printed our character, so we decrease the number counter
      cmp bx, 0                ;If we have no number left, we can end this task
      jne loop_print           ;Otherwise, we go to the next number
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
