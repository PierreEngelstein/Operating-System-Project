[bits 16]
switch_to_pm:
   cli                    ;Avoid bugs : disable interrupts
   lgdt [gdt_descriptor]  ;Loads the Global Descriptor Table
   mov eax, cr0           ;Changes the protected-mode bit indicator (cr0)
   or eax, 0x1
   mov cr0, eax
   ; jmp $
   jmp CODE_SEG:init_pm   ;Jumps to the protected-mode code

[bits 32]
init_pm:
   mov ax, DATA_SEG      ;Update the segment register
   mov ds, ax
   mov ss, ax
   mov es, ax
   mov fs, ax
   mov gs, ax

   mov ebp, PROTECTED_STACK_LOCATION     ;Setup the stack at the location we want
   mov esp, ebp
   call beginPM                          ;Jumps to the core code of the protected mode
