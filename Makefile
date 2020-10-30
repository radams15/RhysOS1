CXX=g++
ASM=nasm
ISO_NAME=RhysOS

ASM_MAIN="nasm/Kernel.asm"
MAIN=C/main.cpp

main: gen run

gen: compile geniso clean

compile:
	${ASM} -g -f elf -o Kernel.o ${ASM_MAIN} &&\
	${CXX} Kernel.o ${MAIN} -o Kernel.bin -T linker.ld -nostartfiles -nostdlib -m32 -IHeaders -IC

geniso:
	mv Kernel.bin ISO/Kernel.bin
	mono "Tools/ISO9660Generator.exe" 4 "${ISO_NAME}.iso" "ISO/isolinux-debug.bin" true "ISO"

run:
	qemu-system-i386 -boot d -cdrom ${ISO_NAME}.iso -m 64 -serial file:kernel.log

clean:
	rm Kernel.o
	rm ISO/Kernel.bin