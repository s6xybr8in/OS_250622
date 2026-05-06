#include "isr.h"
#define IRQ0 32
void isr_handler(register_t *reg)
{
    if (reg->int_no < 32) {
        printf("Unknown Exception %d occured!, EIP :  %x\n", reg->int_no,
               reg->eip);
        cli();
        while (1)
            ;
    } else if (reg->int_no < 47) {
        // uint8_t a = inb(0x60);
        // printf("IRQ Interupt %d occured!, EIP :  %d\n", reg->int_no);
        if (reg->int_no == IRQ0) { // timer
            timer_handler();
        }
        if (reg->int_no == IRQ0 + 4) { // COM1
            com1_handler();
        }

        outb(PIC1_COMMAND, PIC_EOI);
        return;
    } else {
    }
}
bool flag = false;
void com1_handler()
{
    uint8_t iir = inb(0x3F8 + 2);
    uint8_t buf = inb(0x3f8);
    if (iir == 0xc2) {
        if (flag)
            return;
        flag = true;
    }

    // printf("COM1 Interupt IIR -> %x\n", iir);
    if (buf) {
        printf("%s", &buf);
    }
}

void timer_handler()
{
    printf("Timer Interupt! %d\n", timer_count++);
}