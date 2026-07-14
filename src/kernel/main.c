// kernel.c
#include "kernel.h"
#include "mem/paging.h"
#include <driver.h>
#include <i386.h>

extern uint32_t _kernel_start;
extern uint32_t _kernel_end;
extern uint32_t _start;
extern uint32_t *_memory_info;

void init()
{
    init_gdt();
    init_idt();
    init_com1();
    init_PIT();
    // init_paging();
}

void hlt()
{
    while (1) {
    }
}

// 커널 메인 함수
void kmain()
{
    init();
    print("\n");
    printf("Kernel Start : %x , End : %x\n", &_kernel_start, &_kernel_end);
    printf("Boot Start : %x\n", &_start);
    printf("Memory Info flag : %x mem_lower : %d mem_upper %d\n",
           (uint32_t)*_memory_info, (uint32_t) * (_memory_info + 1),
           (uint32_t) * (_memory_info + 2));

    hlt(); // 무한 루프
}