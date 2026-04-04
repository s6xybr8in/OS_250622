#ifndef IDT_H
#define IDT_H
#define MAX 47
#define KERNEL_CODE_SELECTOR 0x08
#include <kernel.h>
struct idt_entry {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t reserve;
    uint8_t access;
    uint16_t offset_high;
} __attribute__((packed));

struct idtr {
    uint16_t size;
    uint32_t base;
} __attribute((packed));

void init_idt();
void set_idt_gate(uint32_t num, uint32_t offset, uint8_t access,
                  uint16_t selector);

#endif