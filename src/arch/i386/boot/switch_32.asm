[bits 16]
switch_to_pm:
   cli                    ;Avoid bugs : disable interrupts
   lgdt [gdt_descriptor]  ;Loads the Global Descriptor Table
   mov eax, cr0           ;Changes the protected-mode bit indicator (cr0)
   or eax, 0x1
   mov cr0, eax
   jmp CODE_SEG:init_pm   ;Jumps to the protected-mode code

[bits 32]
init_pm:
   mov eax, DATA_SEG      ;Update the segment register
   mov ds, eax
   mov ss, eax
   mov es, eax
   mov fs, eax
   mov gs, eax

   mov ebp, PROTECTED_STACK_LOCATION     ;Setup the stack at the location we want
   mov esp, ebp
   call beginPM                          ;Jumps to the core code of the protected mode
