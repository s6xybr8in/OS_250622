// kernel.c
#include "../include/print.h"
#include "../include/init.h"

// 커널 메인 함수
void kmain() {
    init();
    print("Hello, OS World! (Serial Console Ready)\n");

    while(1); // 무한 루프
}