BITS 16
ORG 0x7c00

cli ; deactivate interupt

lgdt [gdt_descriptor]

mov eax, cr0
or eax, 1
mov cr0, eax
; cr0 on

jmp CODE_SEG:init_protected

gdt_start:
	gdt_null: dq 0x0000000000000000
	gdt_code: dq 0x00CF9A000000FFFF
	gdt_data: dq 0x00CF92000000FFFF
gdt_end: 

gdt_descriptor:
	dw gdt_end - gdt_start - 1
	dd gdt_start
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

; protected mode
BITS 32
init_protected:
	mov ax, DATA_SEG
	mov ds, ax
	mov ss, ax
	mov es,ax
	mov esp,0x90000

	;call kernel_main
times 510-($-$$) db 0
dw 0xAA55
