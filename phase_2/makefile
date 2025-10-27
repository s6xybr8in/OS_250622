
main.img : boot.bin sector2.bin
	@cat ./bin/boot.bin ./bin/sector2.bin  >./bin/main.img

boot.bin : boot.asm
	@nasm -f bin boot.asm -o ./bin/boot.bin

sector2.bin : sector2.asm
	@nasm -f bin sector2.asm -o ./bin/sector2.bin

sector:
	qemu-system-x86_64 -drive format=raw,file=./bin/sector2.bin
boot:
	qemu-system-x86_64 -drive format=raw,file=./bin/boot.bin
run:
	qemu-system-x86_64 -drive format=raw,file=./bin/main.img
