#---------assemble.sh-----------
#Main bootloader assembler
#This script goes through the different bootloader's stages .asm files, assembling them
#and creating the main bootloader image.
#Author : Pierre Engelstein
#Version : 2.1.0
#Last modified : 06.04.2018
#-------------------------------

#!/bin/bash
clear
#Color codes
blue=`tput setaf 6`
green=`tput setaf 2`
yellow=`tput setaf 3`
reset=`tput sgr0`
echo "${reset}**********"
echo "Operating system image complier. Made by Pierre Engelstein."
echo "**********"
echo "${yellow}[0] ${green}Checking directories integrity and program presence${reset} ..."
mkdir -p bin/obj/
#First step, build the bootloader
echo "${yellow}[1] ${green}Compiling first stage bootloader${reset}                    ... ${blue}nasm src/arch_x86/boot0.asm -f bin -o bin/boot0.bin${reset}"
nasm src/arch_x86/boot0.asm -f bin -o bin/boot0.bin
echo "${yellow}[2] ${green}Compiling first stage bootloader${reset}                    ... ${blue}nasm src/arch_x86/boot1.asm -f bin -o bin/boot1.bin${reset}"
nasm src/arch_x86/boot1.asm -f bin -o bin/boot1.bin
echo "${yellow}[3] ${green}Compiling kernel entry file${reset}                         ... ${blue}nasm src/kernel/entry.asm -f elf64 -o bin/entry.bin${reset}"
nasm src/kernel/entry.asm -f elf32 -o bin/obj/entry.o
#Now it gets funny ... Compiling all the .c source code into .o obj file
echo "${yellow}[4] ${green}Compiling kernel source code${reset}"
declare -a FILELIST
declare -a OBJLIST
OBJLIST+=("bin/obj/entry.o")
OUTPUT_EXT=".o"
OBJ_FILE="bin/obj/"
for filename in src/kernel/*.c;
do
         #Construct the name of the output file : src/kernel/something.c converted into bin/obj/something.o
         FILELIST+=("$filename")
         FILE="${filename##*/}"
         FILE="${FILE%.*}"
         OBJ="$OBJ_FILE$FILE$OUTPUT_EXT"
         #Add this element into the list of object files
         OBJLIST+=("$OBJ")
         #And compile it
         echo "${blue}gcc -ffreestanding -Idirectory -Wall -c $filename -o $OBJ${reset}"
         gcc -ffreestanding -fno-pie -m32 -Idirectory -Wall -c $filename -o $OBJ
         #clang -S -O3 -fsyntax-only -ffreestanding -fsyntax-only -c $filename -o $OBJ
done

#And now we can create the full bin image of the kernel
echo "${yellow}[5] ${green}Creating kernel binary image${reset}"
echo "${blue}ld -Ttext 0x1000 ${OBJLIST[@]} -o bin/kernel.bin --oformat binary${reset}"
ld -Ttext 0x9000 ${OBJLIST[@]} -m elf_i386 -s -o bin/kernel.bin --oformat binary
echo "${yellow}[6] ${green}Creating hard drive image${reset}                           ... ${blue}cat bin/boot0.bin bin/boot1.bin bin/kernel.bin > bin/boot.bin${reset}"
cat bin/boot0.bin bin/boot1.bin bin/kernel.bin > bin/boot.bin
echo "**********"
