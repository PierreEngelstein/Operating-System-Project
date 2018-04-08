## Operating System project ##

Main assembly + c project on creating a small kernel

## Setting up the environment
This project uses some external tools to be build up. Please install the following tools in order to compile & run the code :
1. nasm (Linux Debian : 'apt-get install nasm' ; Linux Fedora : 'dnf install nasm')
2. qemu (Linux Debian : 'apt-get install qemu' ; Linux Fedora : 'dnf install qemu')

## Compiling the source
1. Clone the repository on a location of your choice : 'git clone https://github.com/PierreEngelstein/Operating-System-Project.git'
2. Run '~/.assemble.sh' (if the script can't run, make sure you have the permission to run it, otherwise do : 'chmod +x ~/assemble.sh').
3. Run 'qemu-system-i386 -hda bin/boot.bin' to run the bootloader.
<p>
**NOTE**: The script is made with bash, so you can't run it with windows. If you want to build this project in Windows, you will have to execute each command by yourself, or code a windows-compatible script.
</p>

## Author
Made by Pierre Engelstein
