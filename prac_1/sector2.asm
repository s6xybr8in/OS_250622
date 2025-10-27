BITS 16
ORG 0x10000

jmp 0x1000:start

start:
	mov ah,0x0e
	mov al,'h'
	int 0x10
	mov al,'i'
	int 0x10

jmp $

times 510 - ($ -$$) db 0
dw 0xAA55
