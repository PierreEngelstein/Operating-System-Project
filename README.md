# Operating System project #

Main project on creating a bootloader & kernel using assembly and C.
<br>

## Setting up the environment
Install the following tools in order to compile & run the code :
- nasm
  - Linux Debian : `apt-get install nasm`
  - Linux Fedora : `dnf install nasm`
- qemu
  - Linux Debian : `apt-get install qemu`
  - Linux Fedora : `dnf install qemu`

## Compiling the source
- Clone the repository on a location of your choice : `git clone https://github.com/PierreEngelstein/Operating-System-Project.git`
- Chose the prossessor architecure you want to build your kernel on:
   - i386 for 32-bit intel processor
        - Compile using `./assemble.sh i386`
        - Run using `./run.sh i386`
   - x86_64 for 64-bit intel processor
        - Compile using `./assemble.sh x86_64`
        - Run using `./run.sh x86_64`

## Project Roadmap
- [x] First stage Bootloader
  - [x] Setup segments and stack
  - [x] Read hard drive for second-stage Bootloader sectors
  - [x] Jump to the second stage
- [x] Second stage bootloader
  - [x] Setup segments and stack
  - [x] Read hard drive for Kernel sectors
  - [x] Enable A20 gate
  - [x] load GDT
  - [x] Switch to 32-bit protected mode
  - [x] begin Kernel execution
- [ ] Kernel (*To be defined*)
  - [x] Load IDT
  - [x] Keyboard driver
  - [ ] Shell
  - [ ] Memory management
    - [x] Basic memory management
    - [ ] Advanced memory management

## Author
Made by Pierre Engelstein
