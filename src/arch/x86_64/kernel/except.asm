;------------------------------
;ASM-level exception handling.
;------------------------------

[bits 64]

global err0, err1, err2, err3, err4, err5, err6, err7, err8, err9, err10, err11, err12, err13, err14, err15, err16

global err0_handler, err1_handler, err2_handler, err3_handler, err4_handler, err5_handler, err6_handler, err7_handler, err8_handler, err9_handler
global err10_handler, err11_handler, err12_handler, err13_handler, err14_handler, err15_handler, err16_handler

extern err0_handler, err1_handler, err2_handler, err3_handler, err4_handler, err5_handler, err6_handler, err7_handler, err8_handler, err9_handler
extern err10_handler, err11_handler, err12_handler, err13_handler, err14_handler, err15_handler, err16_handler

err0:
   push rax
   push rcx
   push rdx
   push r8
   push r9
   push r10
   push r11
   call err0_handler
   pop r11
   pop r10
   pop r9
   pop r8
   pop rdx
   pop rcx
   pop rax
   iretq
err1:
   push rax
   push rcx
   push rdx
   push r8
   push r9
   push r10
   push r11
   call err1_handler
   pop r11
   pop r10
   pop r9
   pop r8
   pop rdx
   pop rcx
   pop rax
   iretq
err2:
   push rax
   push rcx
   push rdx
   push r8
   push r9
   push r10
   push r11
   call err2_handler
   pop r11
   pop r10
   pop r9
   pop r8
   pop rdx
   pop rcx
   pop rax
   iretq
err3:
   push rax
   push rcx
   push rdx
   push r8
   push r9
   push r10
   push r11
   call err3_handler
   pop r11
   pop r10
   pop r9
   pop r8
   pop rdx
   pop rcx
   pop rax
   iretq
err4:
   push rax
   push rcx
   push rdx
   push r8
   push r9
   push r10
   push r11
   call err4_handler
   pop r11
   pop r10
   pop r9
   pop r8
   pop rdx
   pop rcx
   pop rax
   iretq
err5:
   push rax
   push rcx
   push rdx
   push r8
   push r9
   push r10
   push r11
   call err5_handler
   pop r11
   pop r10
   pop r9
   pop r8
   pop rdx
   pop rcx
   pop rax
   iretq
err6:
   push rax
   push rcx
   push rdx
   push r8
   push r9
   push r10
   push r11
   call err6_handler
   pop r11
   pop r10
   pop r9
   pop r8
   pop rdx
   pop rcx
   pop rax
   iretq
err7:
   push rax
   push rcx
   push rdx
   push r8
   push r9
   push r10
   push r11
   call err7_handler
   pop r11
   pop r10
   pop r9
   pop r8
   pop rdx
   pop rcx
   pop rax
   iretq
err8:
   push rax
   push rcx
   push rdx
   push r8
   push r9
   push r10
   push r11
   call err8_handler
   pop r11
   pop r10
   pop r9
   pop r8
   pop rdx
   pop rcx
   pop rax
   iretq
err9:
   push rax
   push rcx
   push rdx
   push r8
   push r9
   push r10
   push r11
   call err9_handler
   pop r11
   pop r10
   pop r9
   pop r8
   pop rdx
   pop rcx
   pop rax
   iretq
err10:
   push rax
   push rcx
   push rdx
   push r8
   push r9
   push r10
   push r11
   call err10_handler
   pop r11
   pop r10
   pop r9
   pop r8
   pop rdx
   pop rcx
   pop rax
   iretq
err11:
   push rax
   push rcx
   push rdx
   push r8
   push r9
   push r10
   push r11
   call err11_handler
   pop r11
   pop r10
   pop r9
   pop r8
   pop rdx
   pop rcx
   pop rax
   iretq
err12:
   push rax
   push rcx
   push rdx
   push r8
   push r9
   push r10
   push r11
   call err12_handler
   pop r11
   pop r10
   pop r9
   pop r8
   pop rdx
   pop rcx
   pop rax
   iretq
err13:
   push rax
   push rcx
   push rdx
   push r8
   push r9
   push r10
   push r11
   call err13_handler
   pop r11
   pop r10
   pop r9
   pop r8
   pop rdx
   pop rcx
   pop rax
   iretq
err14:
   push rax
   push rcx
   push rdx
   push r8
   push r9
   push r10
   push r11
   call err14_handler
   pop r11
   pop r10
   pop r9
   pop r8
   pop rdx
   pop rcx
   pop rax
   iretq
err15:
   push rax
   push rcx
   push rdx
   push r8
   push r9
   push r10
   push r11
   call err15_handler
   pop r11
   pop r10
   pop r9
   pop r8
   pop rdx
   pop rcx
   pop rax
   iretq
err16:
   push rax
   push rcx
   push rdx
   push r8
   push r9
   push r10
   push r11
   call err16_handler
   pop r11
   pop r10
   pop r9
   pop r8
   pop rdx
   pop rcx
   pop rax
   iretq