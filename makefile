all: os-image

boot.bin: boot/boot.asm
	nasm -f bin boot/boot.asm -o bin/boot.bin

os-image: boot.bin
	cp bin/boot.bin bin/os-image.bin

run: os-image
	qemu-system-i386 -drive format=raw,file=bin/os-image.bin

clean:
	rm -f bin/*.bin
