#include "isr.h"

void isr_handler(register_t *reg)
{
    if (reg->int_no < 32) {
        printf("Unknown Exception %d occured!, EIP :  %x\n", reg->int_no,
               reg->eip);
        cli();
        while (1)
            ;
    } else if (reg->int_no < 47) {
        printf("Keyboard Interupt %d occured!, EIP :  %x", reg->int_no,
               reg->eip);
        outb(PIC1_DATA, PIC_EOI);
        return;
    } else {
    }
}