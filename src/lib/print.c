#include "print.h"
#include "asmb.h"

#define PORT 0x3f8          // COM1 시리얼 포트 주소

// 시리얼 포트 초기화 (속도 및 데이터 형식 설정)

// 전송 버퍼가 비었는지 확인
int is_transmit_empty() {
    return inb(PORT + 5) & 0x20;
}

// 문자 하나 출력
void write_serial(char a) {
    while (is_transmit_empty() == 0); // 비워질 때까지 대기
    outb(PORT, a);
}

// 문자열 출력
void print(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        write_serial(str[i]);
    }
}
