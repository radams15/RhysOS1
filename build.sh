#!/bin/bash

cxx=i686-elf-gcc

echo "NASM"
nasm -g -f elf -o Kernel.o "asm/Kernel.asm"

echo "GCC"
$cxx Kernel.o "C/main.cpp" -o Kernel.bin -T linker.ld -nostartfiles -nostdlib -fpermissive

echo "Moving"
mv Kernel.bin ISO/Kernel.bin

echo "Generate ISO"
mono "Tools/ISO9660Generator.exe" 4 "Kernel.iso" "ISO/isolinux-debug.bin" true "ISO"

echo "Cleaning"
rm Kernel.o
rm ISO/Kernel.bin
