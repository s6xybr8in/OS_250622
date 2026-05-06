#include "pit.h"
#include "../include/asmb.h"
void init_PIT()
{
    outb(MODE_COMMAND_REG, 0b00110100);
    outb(CH0, 0);
    outb(CH0, 0);
}
