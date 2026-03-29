#include "gdt.h"
#include "asmb.h"
#include <stdint.h>

struct gdtr {
    uint16_t size;
    uint32_t base;
} __attribute__((packed)) my_gdtr;

typedef struct gdt_entry // 8byte
{
    uint16_t limit_low;  // 세그먼트 크기 하위 16비트
    uint16_t base_low;   // 시작 주소 하위 16비트
    uint8_t base_middle; // 시작 주소 중간 8비트
    uint8_t access;      // 권한 설정 (P, DPL, S, Type 등)
    uint8_t granularity; // 크기 단위 및 나머지 비트들
    uint8_t base_high;   // 시작 주소 상위 8비트
} __attribute__((packed)) gdt;

gdt gdts[5];

void set_gdt(int i, uint32_t base, uint32_t limit, uint8_t access, uint8_t flag)
{
    gdts[i].base_low = (base & 0xFFFF);
    gdts[i].base_middle = (base >> 16) & 0xFF;
    gdts[i].base_high = (base >> 24) & 0xff;
    gdts[i].access = access;

    gdts[i].granularity = flag & 0xf0;
    gdts[i].granularity |= (limit >> 16) & 0x0f;

    gdts[i].limit_low = limit & 0xffff;
}

void init_gdt()
{
    my_gdtr.base = (uint32_t)gdts;
    my_gdtr.size = sizeof(gdts) - 1;
    set_gdt(0, 0, 0, 0, 0);
    set_gdt(1, 0, 0xFFFFF, 0x9A, 0xCF);
    set_gdt(2, 0, 0xFFFFF, 0x92, 0xCF);
    set_gdt(3, 0, 0xFFFFF, 0xFA, 0xCF);
    set_gdt(4, 0, 0xFFFFF, 0xF2, 0xCF);
    // set_gdt(5,&tss,sizeof(tss)-1,0x89,0) // Task Sate Segment

    gdt_flush((uint32_t)&my_gdtr);
}
