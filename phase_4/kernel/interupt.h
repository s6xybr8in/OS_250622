#pragma once
void init_interupt();
void idt_ignore();
void idt_timer();
void idt_keyboard();

struct IDT{
    unsigned short offsetl;
    unsigned short selector;
    unsigned short type;
    unsigned short offseth;
}__attribute__((packed)); // block the padding bit

struct IDTR{
    unsigned short size;
    unsigned int addr;
}__attribute__((packed));

