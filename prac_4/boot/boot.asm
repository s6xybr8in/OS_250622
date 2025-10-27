BITS 16
ORG 0x7c00
CODE_SEG equ 0x08
DATA_SEG equ 0x10
load:
	mov ax, 0x1000
	mov es, ax
	mov bx, 0

	mov ah, 0x02 ; read sector
	mov al, 20 ; sector count
	mov ch, 0 ; cylinder
	mov cl, 0x02 ; sector
	mov dh, 0 ; head
	mov dl, 0x80 ; drive
	int 0x13
	jc load

PIC:
	; master PIC I/O : 0x20/0x21
	; slave PIC I/O : 0xA0/0xA1

	; master PIC IRQ
	; IRQ0 timer
	; IRQ1 keyboard
	; IRQ2 slave pic
	; IRQ3 com2
	; IRQ4 com1
	; IRQ5 printer port2 
	; IRQ6 floppy disk controller 
	; IRQ7 printer port1
	
	; slave PIC IRQ
	; IRQ8 RTC
	; IRQ12 PS/2 mouse
	; IRQ13 Coprocessor
	; IRQ14 harddisk 1
	; IRQ15 harddisk 2

	; ICW1 on IC4, initial bit
	mov al, 0x11 ; 0b00010001
	out 0x20, al ; master PIC
	dw 0x00eb, 0x00eb
	out 0xA0, al ; slave PIC
	dw 0x00eb, 0x00eb

	; ICW2 
	mov al, 0x20 ; master PIC interupt begin points 00100000
	out 0x21, al
	dw 0x00eb, 0x00eb
	mov al, 0x28 ; slave PIC interupt begin point 00101000
	out 0xA1, al
	dw 0x00eb, 0x00eb
	
	; ICW3 master and slave connect
	mov al, 0x04 ; master PIC IRQ 2
	out 0x21, al ; slave PIC connect
	dw 0x00eb, 0x00eb ; jmp $+2, jmp $+2
	mov al,0x02 ; slave PIC, master PIC
	out 0xA1, al ; IRQ 2 connected
	dw 0x00eb, 0x00eb

	mov al,0x01 ; 8086
	out 0x21, al
	dw 0x00eb, 0x00eb
	out 0xA1, al
	dw 0x00eb, 0x00eb

	mov al, 0xFF ; block all interupts of slave PIC
	out 0xA1, al
	dw 0x00eb, 0x00eb
	mov al, 0xFF ; ; block all interupts of master PIC witout IRQ 2
	out 0x21, al
cli
lgdt [gdt_descriptor]

mov eax, cr0
or eax, 1
mov cr0, eax
; cr0 on

jmp dword CODE_SEG:0x10000

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


times 510-($-$$) db 0
dw 0xAA55
