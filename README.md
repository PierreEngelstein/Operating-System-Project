## Operating System project ##

Main assembly + c project on creating a small kernel

## Setting up the environment
This project uses some external tools to be build up. Please install the following tools in order to compile & run the code :
- nasm
  - Linux Debian : `apt-get install nasm`
  - Linux Fedora : `dnf install nasm`
- qemu
  - Linux Debian : `apt-get install qemu`
  - Linux Fedora : `dnf install qemu`

## Compiling the source
- Clone the repository on a location of your choice : `git clone https://github.com/PierreEngelstein/Operating-System-Project.git`
- Run `~/.assemble.sh` (if the script can't run, make sure you have the permission to run it, otherwise do : `chmod +x ~/assemble.sh`).
- Run `qemu-system-i386 -hda bin/boot.bin` to run the bootloader.

**NOTE**: The script is made with bash, so you can't run it with windows. If you want to build this project in Windows, you will have to execute each command by yourself, or code a windows-compatible script.

## Project Road Map
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
