;------------------------------
;ASM-level exception handling.
;------------------------------

[bits 32]

global err0, err1, err2, err3, err4, err5, err6, err7, err8, err9, err10, err11, err12, err13, err14, err15, err16

global err0_handler, err1_handler, err2_handler, err3_handler, err4_handler, err5_handler, err6_handler, err7_handler, err8_handler, err9_handler
global err10_handler, err11_handler, err12_handler, err13_handler, err14_handler, err15_handler, err16_handler

extern err0_handler, err1_handler, err2_handler, err3_handler, err4_handler, err5_handler, err6_handler, err7_handler, err8_handler, err9_handler
extern err10_handler, err11_handler, err12_handler, err13_handler, err14_handler, err15_handler, err16_handler

err0:
   pusha
   call err0_handler
   popa
   iret
err1:
   pusha
   call err1_handler
   popa
   iret
err2:
   pusha
   call err2_handler
   popa
   iret
err3:
   pusha
   call err3_handler
   popa
   iret
err4:
   pusha
   call err4_handler
   popa
   iret
err5:
   pusha
   call err5_handler
   popa
   iret
err6:
   pusha
   call err6_handler
   popa
   iret
err7:
   pusha
   call err7_handler
   popa
   iret
err8:
   pusha
   call err8_handler
   popa
   iret
err9:
   pusha
   call err9_handler
   popa
   iret
err10:
   pusha
   call err10_handler
   popa
   iret
err11:
   pusha
   call err11_handler
   popa
   iret
err12:
   pusha
   call err12_handler
   popa
   iret
err13:
   pusha
   call err13_handler
   popa
   iret
err14:
   pusha
   call err14_handler
   popa
   iret
err15:
   pusha
   call err15_handler
   popa
   iret
err16:
   pusha
   call err16_handler
   popa
   iret