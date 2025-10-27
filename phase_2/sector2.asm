; Sector2.asm
CodeSegment equ 0x08
DataSegment equ 0x10

[org 0x10000]
[bits 32]

mov ax, 0x10
mov es, ax
mov ds, ax
mov ss, ax
mov edi, 0xB8000
mov byte[edi+0x08], 'P'
mov byte[edi+0x09], 0x09

jmp $

