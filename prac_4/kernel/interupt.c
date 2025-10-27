#include "interupt.h"
#include "function.h"

struct IDT idt[256];
struct IDTR idtr = {256 * 8 -1 , 0};
unsigned char key[2] = {'A' , 0};
unsigned char keyt[2] = {'A' , 0};

static inline void setup_idt_entry(struct IDT* idt,unsigned int ptr){
        idt->selector = (unsigned short)0x08; // code segment
        idt->type = (unsigned short)0x8E00;
        idt->offsetl = (unsigned short)(ptr & 0xFFFF);
        idt->offseth = (unsigned short)(ptr >> 16);
}


void init_interupt(){
    int i,j;
    idtr.addr = (unsigned int)idt;

    for(i=0;i<256;i++){
        setup_idt_entry(&idt[i], (unsigned int)idt_ignore);
    }

    __asm__ __volatile__("lidt %0"::"m"(idtr));
    __asm__ __volatile__("mov al, 0xFC");
    __asm__ __volatile__("out 0x21,al");
    __asm__ __volatile__("sti");
    char str[24] = "Hello IDT in C!";
    Print(str,8,0x09);
}
__attribute__((naked))
void idt_ignore(){
    Print("Hello ignore",12,0x09);
     asm volatile(
        "pusha\n\t"
        "push ds\n\t"
        "push es\n\t"
        "push fs\n\t"
        "push gs\n\t"

        "mov ax, 0x10\n\t"      // DATA_SEG selector
        "mov ds, ax\n\t"
        "mov es, ax\n\t"

        // send EOI to master PIC
        "mov al, 0x20\n\t"
        "out 0x20, al\n\t"

        "pop gs\n\t"
        "pop fs\n\t"
        "pop es\n\t"
        "pop ds\n\t"
        "popa\n\t"
        "iret\n\t"
    );
}
void idt_timer(){
    __asm__ __volatile__("iret");
}
void idt_keyboard(){
    __asm__ __volatile__("iret");
}
