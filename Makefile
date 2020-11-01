export PATH := Tools/bin:$(PATH)

CXX=g++ -g -W
ASM=nasm -f elf
NAME=RhysOS

main: gen run

gen: compile gen_iso clean

compile:
	${ASM} -o boot.o nasm/boot.s
	${ASM} -o gdt.o nasm/gdt.s
	${ASM} -o interrupts.o nasm/interrupts.s

	${CXX} boot.o gdt.o interrupts.o C/*.cpp -o ${NAME}.bin -T linker.ld -fno-stack-protector -fpermissive -nostdlib -m32 -std=c++11 -ffreestanding -IHeaders -IC -Wl,--build-id=none

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