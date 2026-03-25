# 1. 프로그램 및 경로 설정 (크로스 컴파일러로 변경)
AS      := nasm
CC      := i686-linux-gnu-gcc
LD      := i686-linux-gnu-ld
QEMU    := qemu-system-i386

# 만약 설치한 이름이 i686-linux-gnu-gcc라면 위 이름을 그에 맞게 수정하세요.
# 예: CC := i686-linux-gnu-gcc

SRC_DIR := src
OBJ_DIR := build
BIN_DIR := bin
SCRIPT_DIR := scripts

# 최종 결과물 경로
DST     := $(BIN_DIR)/myos.bin
LINKER  := $(SCRIPT_DIR)/linker.ld

# 2. 모든 소스 파일 찾기
C_SRCS   := $(shell find $(SRC_DIR) -name "*.c")
ASM_SRCS := $(shell find $(SRC_DIR) -name "*.asm")

OBJS     := $(C_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS     += $(ASM_SRCS:$(SRC_DIR)/%.asm=$(OBJ_DIR)/%.o)

# 3. 컴파일 및 링크 옵션
ASFLAGS  := -f elf32

# i686-elf-gcc는 기본이 32비트라 -m32가 필요 없습니다.
CFLAGS   := -std=gnu99 -ffreestanding -O2 -Wall -Wextra \
            -fno-stack-protector -fno-pie -fno-stack-check \
            -I$(SRC_DIR)/include

# i686-elf-ld 역시 기본이 elf_i386이라 -m 옵션이 생략 가능합니다.
LDFLAGS  := -T $(LINKER) -nostdlib

# ---------------------------------------------------------

.PHONY: all clean run debug prepare

all: prepare $(DST)

# 빌드 및 출력 디렉터리 생성
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