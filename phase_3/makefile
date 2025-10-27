CC = gcc

main.img : boot.bin sector2.bin disk.img
	@cat boot.bin sector2.bin disk.img  >main.img

disk.img : kernel.img
	@objcopy -O binary kernel.img disk.img

kernel.img : kernel.o
	@ld -melf_i386 -Ttext 0x10200 -nostdlib kernel.o -o kernel.img

kernel.o : kernel.c
	@gcc -c -m32 -ffreestanding kernel.c -o kernel.o

boot.bin : boot.asm
	@nasm -f bin boot.asm -o boot.bin

sector2.bin : sector2.asm
	@nasm -f bin sector2.asm -o sector2.bin

run:
	qemu-system-x86_64 -drive format=raw,file=main.img

debug:
	qemu-system-x86_64 -drive format=raw,file=main.img -s -S & 

clean: 
	rm *.bin
	rm *.o
	rm *.img










