;---------ct.asm-------------
;File containing all the values assigns (equ instruction)
;This file's only purpose is to make the code cleaner
;DO NOT PUT ACTUAL CODE IN HERE, IT COULD BREAK THE SYSTEM !
;Author : Pierre Engelstein
;-------------------------------------

;Second stage bootloader constants
SECOND_STAGE_LOCATION      equ   0x8000    ; Where to load the second stage bootloader
SECOND_STAGE_SIZE          equ   5         ; Second stage's size in sectors (1 sector = 512 bytes)
STACK_START_LOCATION       equ   0x7C00
PROTECTED_STACK_LOCATION   equ   0x90000

;Kernel constants
KERNEL_LOCATION            equ   0x9000    ; Where to load the kernel
KERNEL_SIZE                equ   41        ; Kernel's size in sectors
