// kernel.c
#include "../driver/serial.h"
#include "i386/gdt.h"
#include "print.h"
#include <stdint.h>

void init()
{
    init_serial();
    init_gdt();
}

// 커널 메인 함수
void kmain()
{
    init();
    // print("Hello, OS World! (Serial Console Ready)\n");
    print("\n");
    printf("한글도 될까요? %d %x %s", 1234, 15, "메롱");
    while (1)
        ; // 무한 루프
}