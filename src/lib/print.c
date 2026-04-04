#include "print.h"
#include "asmb.h"
#include <stdbool.h>
#define PORT 0x3f8 // COM1 시리얼 포트 주소
#define BUF_MAX 16

// 전송 버퍼가 비었는지 확인
int is_transmit_empty()
{
    return inb(PORT + 5) & 0x20;
}

// 문자 하나 출력
void write_serial(char a)
{
    while (is_transmit_empty() == 0)
        ; // 비워질 때까지 대기
    outb(PORT, a);
}

// 문자열 출력
void print(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        write_serial(str[i]);
    }
}

void print_int(int32_t val)
{
    char buf[BUF_MAX];
    if (val == 0) {
        write_serial('0');
        return;
    }

    int i = 0;
    while (val > 0) {
        buf[i++] = (val % 10) + '0';
        val /= 10;
    }
    while (i--) {
        write_serial(buf[i]);
    }
}
void print_hex(int32_t val)
{
    if (val == 0) {
        write_serial('0');
        return;
    }
    char table[] = "0123456789ABCDEF";
    char buf[BUF_MAX];
    int i = 0;
    while (val > 0) {
        buf[i++] = table[(val % 16)];
        val /= 16;
    }
    while (i--) {
        write_serial(buf[i]);
    }
}

void printf(char *str, ...)
{
    bool flag = false;
    char *args = (char *)&str + sizeof(str);
    while (*str != 0) {
        if (flag) {
            switch (*str) {
            case 'd':
                int val = *(int *)args;
                print_int(val);
                args += sizeof(int *);
                break;
            case 'x':
                int val2 = *(int *)args;
                print_hex(val2);
                args += sizeof(int *);
                break;
            case 's':
                char *s = *(char **)args;
                print(s);
                args += sizeof(char **);
                break;
            }

            flag = false;
        } else if (*str == '%')
            flag = true;
        else
            write_serial(*str);
        str++;
    }
}