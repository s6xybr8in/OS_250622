// kernel.c
#include "init.h"
#include "print.h"
#include <stdint.h>
// 커널 메인 함수
void kmain()
{
    init();
    print("Hello, OS World! (Serial Console Ready)\n");
    uint8_t i;
    i = 1;
    while (1)
        ; // 무한 루프
}