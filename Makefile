export PATH := Tools/bin:$(PATH)

CXX=g++ -g -W
ASM=nasm -f elf
NAME=RhysOS

ASM_MAIN="nasm/boot.s"
MAIN=C/*.cpp

main: gen run

gen: compile gen_iso clean

compile:
	${ASM} -o Kernel.o ${ASM_MAIN} -Inasm &&\
	${CXX} Kernel.o ${MAIN} -o ${NAME}.bin -T linker.ld -fno-stack-protector -nostdlib -m32 -std=c++11 -ffreestanding -IHeaders -IC -Wl,--build-id=none

gen_iso:
	mv ${NAME}.bin ISO/boot/${NAME}.bin
	grub2-mkrescue -o RhysOS.iso ISO

run:
	qemu-system-i386 -boot d -cdrom ${NAME}.iso -m 64 -serial file:kernel.log

clean:
	rm Kernel.o
	rm ISO/boot/${NAME}.bin