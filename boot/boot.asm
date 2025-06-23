[ORG 0x7c00]      ; BIOS가 0x7C00에 부트로더를 로드함
[BITS 16]

start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7c00

    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    jmp 0x08:protected_mode_start

; GDT
align 8
gdt_start:
    dq 0x0000000000000000      ; null descriptor
    dq 0x00cf9a000000ffff      ; code segment descriptor
    dq 0x00cf92000000ffff      ; data segment descriptor
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start     ; GDT base address (linear)

[BITS 32]
protected_mode_start:
    mov ax, 0x10               ; data segment selector
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, 0x7c00

    mov esi, message
    mov edi, 0xb8000           ; VGA text mode memory
    mov ecx, message_len
.print_loop:
    lodsb
    test al, al
    jz .done
    mov ah, 0x0f               ; attribute: white on black
    stosw
    loop .print_loop

.done:

    hlt
    jmp .done

message:
 db 'Hello, PM!',0
message_len equ $-message

times 510-($-$$) db 0
dw 0xAA55         ; 부트 섹터 서명
