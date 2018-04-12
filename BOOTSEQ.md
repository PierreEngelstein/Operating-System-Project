# Boot sequence #
Description of the boot sequence of this little project
<br>
*This will be completed as the project goes further*
<br>

## Booting
- [x] The first stage bootloader (`boot0.asm`) is loaded at `0x7c00` by the BIOS
  - [x] Sets up the data segment and the extra segment (code segment is already set up with the `org` instruction)
  - [x] Sets up the real-mode stack at `0x14FF` (arbitrary location between 0x500 & 0x1500)
  - [x] Resets the floppy disk controller via BIOS interrupt (`int 0x13, ah = 0`)
  - [x] Loads the second stage bootloader into memory at location `0x8000` (defined in `ct.asm`)  (*Could do it with reading a header at the start of the second stage*)
  - [x] Jumps to the second-stage bootloader

- [x] The second stage bootloader (`boot1.asm`) is started at `0x8000` by the first stage
  - [x] Sets up again the data segment and the extra segment with the new offset
  - [x] Sets up again the real mode stack at `0x14FF`
  - [x] Prints some information about this stage (where is it loaded and where does it stops)
  - [x] Gets the low-memory size via BIOS interrupt (`int 0x12`) and prints it
  - [x] Checks if the A20 gate is enabled. If it is not, we enable it via BIOS interrupt (`int 0x15, ax = 0x2401`). Otherwise, we continue.
  - [ ] Loads the kernel into memory (*To be coded*)
  - [x] Switches to protected mode
    - [x] Loads the Global Descriptor Table
    - [x] Changes the protected-mode bit indicator (`cr0`)
    - [x] Jumps to the protected-mode init code
  - [x] When in protected mode, setup (*again*) all the registers
  - [x] Setups the protected-mode stack location at `0x80000` (At the top of the bootloader free memory, to be sure we don't have any problems)
  - [x] Jumps to the core protected-mode code
  - [ ] Jumps where the kernel was loaded (*To be coded*)

## Some algorithms in this project :
###print_string routine
```python
function print_str(char *str)
{
  while(*str != 0)
  {
    al = *str;
    printchar(al);  #Interrupt 0x10 with ah = 0x0e
    al = al+1;
  }
}
```
####print_number routine
####disk_load routine
####GDT format
## Author
Made by Pierre Engelstein
