#---------assemble.sh-----------
#Main bootloader assembler
#This script goes through the different bootloader's stages .asm files, assembling them
#and creating the main bootloader image.
#Author : Pierre Engelstein
#Version : 2.1.0
#Last modified : 06.04.2018
#-------------------------------

#!/bin/bash

echo "**********"
echo "Bootloader image complier. Made by Pierre Engelstein."
echo "**********"
echo "[0] Checking directories integrity and program presence ..."
mkdir -p bin/obj/
echo "[1] Compiling first stage bootloader ... nasm src/arch_x86/boot0.asm -f bin -o bin/boot0.bin"
nasm src/arch_x86/boot0.asm -f bin -o bin/boot0.bin
echo "[2] Compiling first stage bootloader ... nasm src/arch_x86/boot1.asm -f bin -o bin/boot1.bin"
nasm src/arch_x86/boot1.asm -f bin -o bin/boot1.bin
echo "[3] Creating hard drive image        ... cat bin/boot0.bin bin/boot1.bin > bin/boot.bin"
cat bin/boot0.bin bin/boot1.bin > bin/boot.bin
echo "**********"
