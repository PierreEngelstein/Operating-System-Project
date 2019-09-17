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
s_highmem_size     db "High memory size : ", 0
s_ext1_16          db "Extended memory between 1 MB and 16 MB : ", 0
s_ext16            db "Extended memory above 16 MB : ", 0
s_ext16_mult       db " * 64 KB", 0
s_ext_fail         db "Failed to get extended memory !", 10, 13, 0

s_a20_check        db "Checking A20 gate ...", 10, 13, 0
s_a20_enabled      db "A20 gate enabled !", 10, 13, 0
s_a20_disabled     db "A20 gate is disabled, jumping to enable it...", 10, 13, 0
s_kernel_read      db "Reading kernel sectors ...", 10, 13, 0
s_kernel_endread   db "Written kernel sectors at ", 0
s_kernel_long_ok   db "Long mode is okay", 0
s_kernel_long_no   db "Long mode is not available", 0
s_kernel_cpuid_no  db "CPUID is not available", 10, 13, 0
;-------------------------------------

;Error messages :
s_a20error         db "Failed to enable A20 gate ! Error code is [ah] : ", 0
s_diskreadError    db "Failed to read kernel sectors !", 10, 13, 0
s_diskCode         db "     => Error code : ", 0
s_sectRead         db "     => Disk sector already written : ", 0
;-------------------------------------

;General messages :
s_bytes            db " bytes ", 0
s_KiB              db " KiB ", 0
s_MiB              db " MiB", 0
s_hex              db "0x", 0
s_separator        db "*******************************************************************************", 10, 13, 0
;-------------------------------------
