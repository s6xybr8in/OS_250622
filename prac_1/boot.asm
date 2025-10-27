BITS 16
ORG 0

jmp 0x07c0:start


start:
	mov ah,0x0e
	mov al, 'i'
	int 0x10	
	mov al, 'm'
	int 0x10
	mov al, 'C'
	int 0x10
	mov al, 'h'
	int 0x10
	mov al, 'u'
	int 0x10
	mov al,0x0d 
	int 0x10
	mov al, 0x0A
	int 0x10

load_sector:
	mov ax, 0x1000
	mov es,ax
	mov bx,0
	
	mov ah,2
	mov al,1
	mov ch,0
	mov cl,2
	mov dh,0
	mov dl,0x80
	int 13h

	jc load_sector

jmp 0x1000:0

msg db 'Hello World',0x0d,0x0a, 0
times 510 - ($ - $$) db 0
dw 0xAA55 
