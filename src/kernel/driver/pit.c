#include "pit.h"

void init_PIT()
{
    outb(MODE_COMMAND_REG, 0b00110100);
    outb(CH0, 0xA9); // 1193 0b0100 10101001
    outb(CH0, 0x04);
}
