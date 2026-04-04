#ifndef ASMB_H
#define ASMB_H
#include <stdint.h>

extern void gdt_flush(uint32_t gdtr_ptr);
extern void idt_flush(uint32_t idtr_ptr);

static inline void cli()
{
    asm volatile("cli");
}

static inline void sti()
{
    asm volatile("sti");
}

static inline void outb(unsigned short port, unsigned char val)
{
    asm volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

// x86 I/O 포트에서 데이터를 읽는 함수
static inline unsigned char inb(unsigned short port)
{
    unsigned char ret;
    asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

static inline void io_wait(void)
{
    asm volatile("outb %%al, $0x80" : : "a"(0));
}

#endif