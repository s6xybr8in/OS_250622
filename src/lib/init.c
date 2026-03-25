#include "../include/init.h"
#include "../include/asmb.h"

#define PORT 0x3f8          // COM1 시리얼 포트 주소


void init_serial() {
    outb(PORT + 1, 0x00);    // 인터럽트 비활성화
    outb(PORT + 3, 0x80);    // DLAB 활성화 (속도 설정 모드)
    outb(PORT + 0, 0x03);    // 속도 설정 (38400 baud, 하위 바이트)
    outb(PORT + 1, 0x00);    // (상위 바이트)
    outb(PORT + 3, 0x03);    // 8비트, 패리티 없음, 1비트 정지 (8N1)
    outb(PORT + 2, 0xC7);    // FIFO 활성화
    outb(PORT + 4, 0x0B);    // IRQs 활성화, RTS/DSR 활성화
}

void init(){
    init_serial();
}