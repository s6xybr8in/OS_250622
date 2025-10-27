BITS 16
ORG 0x7c00
CODE_SEG equ 0x08
DATA_SEG equ 0x10

mov ax, 0x1000
mov es, ax
mov bx, 0

mov ah, 0x02 ; read sector
mov al, 1 ; sector count
mov ch, 0 ; cylinder
mov cl, 2 ; sector
mov dh, 0 ; head
mov dl, 0x80 ; drive
int 0x13

cli
lgdt [gdt_descriptor]

mov eax, cr0
or eax, 1
mov cr0, eax
; cr0 on

jmp CODE_SEG:init_protect

gdt_descriptor:
	dw gdt_end - gdt_start - 1 ; size
	dd gdt_start
gdt_start:
	gdt_null: 
		dq 0x0000000000000000
	gdt_code: 
		dq 0x00CF9A000000FFFF
	gdt_data: 
		dq 0x00CF92000000FFFF
gdt_end: 

; protected mode

BITS 32
init_protect:
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov esp,0x90000

	mov edi, 0xB8000
	mov byte [edi], 'H'
	mov byte [edi+1], 0x07	
	mov byte [edi+2], 'I'
	mov byte [edi+3], 0x07	
	jmp dword 0x08:0x10000 


times 510-($-$$) db 0
dw 0xAA55
