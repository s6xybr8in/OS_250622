; boot.s
MBOOT_PAGE_ALIGN    equ 1<<0
MBOOT_MEM_INFO      equ 1<<1
MBOOT_HEADER_MAGIC  equ 0x1BADB002
MBOOT_HEADER_FLAGS  equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO
MBOOT_CHECKSUM      equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

section .multiboot
align 4
    dd MBOOT_HEADER_MAGIC
    dd MBOOT_HEADER_FLAGS
    dd MBOOT_CHECKSUM

section .text
global _start
extern kmain

_start:
    ; 스택 설정 (esp 레지스터에 스택 끝 주소 할당)
    mov esp, stack_top

    ; C 언어 메인 함수 호출
    call kmain

; 혹시 kmain이 종료되면 무한 루프
jmp $

section .bss
align 16
stack_bottom:
    resb 16384 ; 16KB 스택 예약
stack_top: