export PATH := Tools/bin:$(PATH)

CXX=g++ -g -m32
ASM=nasm -f elf
NAME=RhysOS

main: gen run

gen: compile gen_iso clean

compile:
	${ASM} -o boot.o nasm/boot.s
	${ASM} -o gdt.o nasm/gdt.s
	${ASM} -o interrupts.o nasm/interrupts.s

	${CXX} boot.o gdt.o interrupts.o CPP/*.cpp CPP/Cpu/*.cpp C_Interop/*.c -o ${NAME}.bin -T linker.ld -fno-stack-protector -fpermissive -nostdlib -std=c++11 -ffreestanding -IHeaders -IC_Interop -IC -Wl,--build-id=none

gen_iso:
	mv ${NAME}.bin ISO/boot/${NAME}.bin
	grub2-mkrescue -o RhysOS.iso ISO

run:
	qemu-system-i386 -boot d -cdrom ${NAME}.iso -m 64 -serial file:kernel_log.txt

clean:
	rm boot.o
	rm gdt.o
	rm interrupts.o
	rm ISO/boot/${NAME}.bin