# Operating System project #

Main project on creating a bootloader & kernel using assembly and C.
<br>
Last modified : 04.08.2018

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
- Run `~/.assemble.sh`.
- Run `qemu-system-i386 -hda bin/boot.bin` to run the bootloader.

## Project Roadmap
- [x] First stage Bootloader
  - [x] Setup segments and stack
  - [x] Read hard drive for second-stage Bootloader sectors
  - [x] Jump to the second stage
- [ ] Second stage bootloader
  - [x] Setup segments and stack
  - [ ] Read hard drive for Kernel sectors
  - [ ] Enable A20 gate
  - [ ] load GDT
  - [ ] begin Kernel execution
- [ ] Kernel (*To be defined*)

## Author
Made by Pierre Engelstein
