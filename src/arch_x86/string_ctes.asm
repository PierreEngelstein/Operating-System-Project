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
s_stage_size       db "Total size : ", 0
s_lowmem_size      db "Low memory size : ", 0
s_a20_check        db "Checking A20 gate ...", 10, 13, 0
s_a20_enabled      db "A20 gate enabled !", 10, 13, 0
s_a20_disabled     db "A20 gate is disabled, jumping to enable it...", 10, 13, 0
;-------------------------------------

;Error messages :
s_a20error         db "Failed to enable A20 gate ! Error code is [ah] : ", 0
;-------------------------------------

;General messages :
s_bytes            db " bytes ", 0
s_KiB              db " KiB ", 0
s_MiB              db " MiB", 0
;-------------------------------------
