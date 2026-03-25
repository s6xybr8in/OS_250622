# 1. 프로그램 및 경로 설정
AS      := nasm
CC      := gcc
QEMU    := qemu-system-i386
LD      := ld 

SRC_DIR := src
OBJ_DIR := build
BIN_DIR := bin
SCRIPT_DIR := scripts

# 최종 결과물 경로
DST     := $(BIN_DIR)/myos.bin
LINKER  := $(SCRIPT_DIR)/linker.ld

# 2. 모든 소스 파일 찾기 (하위 폴더 포함)
C_SRCS   := $(shell find $(SRC_DIR) -name "*.c")
ASM_SRCS := $(shell find $(SRC_DIR) -name "*.asm")

# 소스 경로를 build/ 경로의 .o 파일로 변환
OBJS     := $(C_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS     += $(ASM_SRCS:$(SRC_DIR)/%.asm=$(OBJ_DIR)/%.o)

# 3. 컴파일 및 링크 옵션
ASFLAGS  := -f elf32
CFLAGS   := -m32 -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I$(SRC_DIR)/include
# -T 옵션으로 스크립트 경로 지정, -m elf_i386으로 32비트 명시
LDFLAGS  := -T $(LINKER) -m elf_i386 -nostdlib

# ---------------------------------------------------------

.PHONY: all clean run debug prepare

all: prepare $(DST)

# 빌드 및 출력 디렉터리 생성 (구조 유지)
prepare:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)
	@find $(SRC_DIR) -type d | sed 's|^$(SRC_DIR)|$(OBJ_DIR)|' | xargs mkdir -p

# 최종 커널 바이너리 링크
$(DST): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(DST)
	@echo "Build Complete: $(DST)"

# C 파일 컴파일 규칙
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compiling C: $<"
	$(CC) $(CFLAGS) -c $< -o $@

# ASM 파일 컴파일 규칙
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.asm
	@echo "Assembling: $<"
	$(AS) $(ASFLAGS) $< -o $@

# ---------------------------------------------------------

# 실행 및 디버그
run: $(DST)
	$(QEMU) -kernel $(DST) -nographic -serial mon:stdio

debug: $(DST)
	$(QEMU) -kernel $(DST) -nographic -serial mon:stdio -s -S

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "Cleaned up."