CXX=g++
ASM=nasm
ISO_NAME=RhysOS
MAIN=C/main.cpp

main: gen run

gen: compile geniso clean

compile:
	${ASM} -g -f elf -o Kernel.o "asm/Kernel.asm" &&\
	${CXX} Kernel.o ${MAIN} -o Kernel.bin -T linker.ld -nostartfiles -nostdlib -m32 -IHeaders

geniso:
	mv Kernel.bin ISO/Kernel.bin
	mono "Tools/ISO9660Generator.exe" 4 "${ISO_NAME}.iso" "ISO/isolinux-debug.bin" true "ISO"
	#genisoimage --input-charset utf-8 -o ${ISO_NAME}.iso -b ISO/isolinux.bin -no-emul-boot -boot-load-size 4 -boot-info-table ISO

run:
	qemu-system-i386 -boot d -cdrom ${ISO_NAME}.iso -m 512

clean:
	rm Kernel.o
	rm ISO/Kernel.bin