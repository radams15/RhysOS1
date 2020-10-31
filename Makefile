CXX=g++ -g -W
ASM=nasm -g
NAME=RhysOS

ASM_MAIN="nasm/Kernel.asm"
MAIN=C/*.cpp

main: gen run

gen: compile gen_iso clean

compile:
	${ASM} -f elf -o Kernel.o ${ASM_MAIN} -Inasm &&\
	${CXX} Kernel.o ${MAIN} -o ${NAME}.bin -T linker.ld -nostartfiles -nostdlib -m32 -std=c++11 -ffreestanding -IHeaders -IC -Wl,--build-id=none

gen_iso:
	mv ${NAME}.bin ISO/boot/${NAME}.bin
	grub2-mkrescue -o RhysOS.iso ISO

run:
	qemu-system-i386 -boot d -cdrom ${NAME}.iso -m 64 -serial file:kernel.log

clean:
	rm Kernel.o
	rm ISO/boot/${NAME}.bin