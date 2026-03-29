#include <stdint.h>

void set_gdt(int i, uint32_t base, uint32_t limit, uint8_t access,
             uint8_t flag);

void init_gdt();
