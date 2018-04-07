;---------string_ctes.asm-------------
;File containing all the string constants to be printed on screen
;This file's only purpose is to make the code cleaner
;DO NOT PUT ACTUAL CODE IN HERE, IT COULD BREAK THE SYSTEM !
;Author : Pierre Engelstein
;-------------------------------------

;Second stage messages :
s_startupSecond    db "Started the second stage bootloader!",10 , 13, 0
s_stage_start      db "Second stage bootloader memory addresses : ", 10, 13, "Start : ", 0
s_stage_end        db "End   : ", 0
;-------------------------------------

;Error messages :
;-------------------------------------

;General messages :
s_hex_out          db '0x0000', 10, 13, 0
s_empty_line       db 10, 13, 0
;-------------------------------------
