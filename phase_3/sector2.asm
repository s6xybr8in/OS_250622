; Sector2.asm
CodeSeg equ 0x08
DataSeg equ 0x10

[org 0x10000]
BITS 32

init_protect:
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	mov edi, 0xB8020
	mov byte [edi], 'H'
	mov byte [edi+1], 0x10	
	mov byte [edi+2], 'I'
	mov byte [edi+3], 0x10	
	jmp dword CodeSeg:0x10200
	
times 512 -($ - $$) db 0
