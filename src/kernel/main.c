// kernel.c
#include "../driver/serial.h"
#include <i386.h>
#include <kernel.h>

void init()
{
    init_serial();
    init_gdt();
    init_idt();
}

// 커널 메인 함수
void kmain()
{
    init();
    print("\n");
    volatile int a = 12;
    volatile int b = 0;
    a = a / b;
    char *p = "Hello World";
    printf("HI %s %d %x", p, b, a);
    print("\n");

    while (1)
        ; // 무한 루프
}