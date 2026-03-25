#include "asmb.h"
#include <stdint.h>

struct gdtr {
    uint16_t size;
    uint32_t base;
} __attribute__((packed)) my_gdtr;

struct gdt_entry // 8byte
{
    uint16_t limit_low;  // 세그먼트 크기 하위 16비트
    uint16_t base_low;   // 시작 주소 하위 16비트
    uint8_t base_middle; // 시작 주소 중간 8비트
    uint8_t access;      // 권한 설정 (P, DPL, S, Type 등)
    uint8_t granularity; // 크기 단위 및 나머지 비트들
    uint8_t base_high;   // 시작 주소 상위 8비트
} __attribute__((packed));


