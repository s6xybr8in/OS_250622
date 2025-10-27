# Toolchain
CC = gcc
AS = nasm
LD = ld

# Directories
SRCDIR = .
BOOTDIR = $(SRCDIR)/boot
KERNELDIR = $(SRCDIR)/kernel
BINDIR = $(SRCDIR)/bin

# Files
BOOT_SRC = $(BOOTDIR)/boot.asm
SECTOR2_SRC = $(BOOTDIR)/sector2.asm

KERNEL_SRC = $(KERNELDIR)/kernel.c
FUNCTION_SRC = $(KERNELDIR)/function.c
INTERUPT_SRC = $(KERNELDIR)/interupt.c

BOOT_BIN = $(BINDIR)/boot.bin
SECTOR2_BIN = $(BINDIR)/sector2.bin

KERNEL_OBJ = $(BINDIR)/kernel.o
FUNCTION_OBJ = $(BINDIR)/function.o
INTERUPT_OBJ = $(BINDIR)/interupt.o

KERNEL_IMG = $(BINDIR)/kernel.img
DISK_IMG = $(BINDIR)/disk.img
MAIN_IMG = $(BINDIR)/main.img

# Flags
ASFLAGS = -f bin
CFLAGS = -c -masm=intel -m32 -ffreestanding
LDFLAGS = -melf_i386 -Ttext 0x10200 -nostdlib -e main

.PHONY: all run debug clean

all: $(MAIN_IMG)

$(MAIN_IMG): $(BOOT_BIN) $(SECTOR2_BIN) $(DISK_IMG)
	@cat $(BOOT_BIN) $(SECTOR2_BIN) $(DISK_IMG) > $(MAIN_IMG)

$(DISK_IMG): $(KERNEL_IMG)
	@objcopy -O binary $(KERNEL_IMG) $(DISK_IMG)

$(KERNEL_IMG): $(KERNEL_OBJ) $(FUNCTION_OBJ) $(INTERUPT_OBJ)
	@$(LD) $(LDFLAGS) $(KERNEL_OBJ) $(FUNCTION_OBJ) $(INTERUPT_OBJ) -o $(KERNEL_IMG)

$(KERNEL_OBJ): $(KERNEL_SRC)
	@mkdir -p $(BINDIR)
	@$(CC) $(CFLAGS) $(KERNEL_SRC) -o $(KERNEL_OBJ)

$(FUNCTION_OBJ): $(FUNCTION_SRC)
	@mkdir -p $(BINDIR)
	@$(CC) $(CFLAGS) $(FUNCTION_SRC) -o $(FUNCTION_OBJ)

$(INTERUPT_OBJ): $(INTERUPT_SRC)
	@mkdir -p $(BINDIR)
	@$(CC) $(CFLAGS) $(INTERUPT_SRC) -o $(INTERUPT_OBJ)

$(BOOT_BIN): $(BOOT_SRC)
	@mkdir -p $(BINDIR)
	@$(AS) $(ASFLAGS) $(BOOT_SRC) -o $(BOOT_BIN)

$(SECTOR2_BIN): $(SECTOR2_SRC)
	@mkdir -p $(BINDIR)
	@$(AS) $(ASFLAGS) $(SECTOR2_SRC) -o $(SECTOR2_BIN)

run: $(MAIN_IMG)
	@qemu-system-x86_64 -drive format=raw,file=$(MAIN_IMG)

debug: $(MAIN_IMG)
	@qemu-system-x86_64 -drive format=raw,file=$(MAIN_IMG) -s -S &

clean:
	@rm -rf $(BINDIR)