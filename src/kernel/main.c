// kernel.c
#include <driver.h>
#include <i386.h>
#include <kernel.h>

void init()
{
    init_gdt();
    init_idt();
    init_com1();
    init_PIT();
}

// 커널 메인 함수
void kmain()
{
    init();
    print("\n");
    char *p = "Hello World";
    printf("Hello WOrl0d\n");

    while (1)
        ; // 무한 루프
}