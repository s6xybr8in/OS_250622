#ifndef PAGING_H
#define PAGING_H
#include "../kernel.h"

/*

https://wiki.osdev.org/Paging

Page Directory
The topmost paging structure is the page directory. It is essentially an array
of page directory entries that take the following form.

P : Present 
R/W : Read/Write(1) , Read(0)
U/S : User/Supervisor
RSVD : reserved
I/D : Instruction/Data (1 = instruction fetch, 0 = data access)
PK : protection-key violation
SS : shadow-stack access fault
AVL : avalable 
D : Dirty
A : Accessed
PS : 1 = 4Mib , 0 = 4Kib
G : Global 



uint32_t eax = 0;
uint32_t ebx = 0x100000;

for(uint16_t eax=0; eax < 1024; eax++){
    uint32_t ecx = ebx | 3;
    *(uint32_t *)(table_768 + eax * 4) = ecx;
    ebx += 4096;
}

paging -> 맨아래로 옮기기
physical address 관리 

*/

extern void paging_flush(uint32_t page_dir);
extern struct page_directory page_dir __attribute__((aligned(4096)));
extern struct page_table kernel_page_table __attribute__((aligned(4096)));

typedef struct {
    uint32_t present : 1; // 메모리에 있는지 여부 (1=있음, 0=없음)
    uint32_t read_write : 1; // 0=읽기전용, 1=읽기/쓰기
    uint32_t user_priv : 1;  // 0=커널 전용, 1=사용자 가능
    uint32_t reserved : 9;   // 기타 제어 비트 (Dirty, Accessed 등)
    uint32_t frame_addr : 20; // 실제 물리 프레임 주소의 상위 20비트
} __attribute__((packed)) pte_t;

struct page_directory {
    /*
    PDE
    |        31 ~ 22      |  21   |        20~13        |  12 | 11~9 | 8 |   7   | 6 | 5 |  4  |  3  |  2  |  1  | 0 |
    |Bits 31~22 of address|RSVD(0)|Bits 39~32 of address| PAT | AVL  | G | PS(1) | D | A | PCD | PWT | U/S | R/W | P | 

    |         31~12            | 11 ~ 8 |    7  | 6   | 5 | 4   | 3   | 2   | 1   | 0 |
    | Bits of 31~12 of address |   AVL  | PS(0) | AVL | A | PCD | PWT | U/S | R/W | P |

    */

    uint32_t entry[1024] __attribute__((aligned(4096)));
};

struct page_table { // 4KB offset
    /*
    PTE
    |         31~12            | 11 ~ 9 | 8 |  7  | 6 | 5 |  4  | 3   |  2  |  1  | 0 |
    | Bits of 31~12 of address |   AVL  | G | PAT | D | A | PCD | PWT | U/S | R/W | P |    
    
    */
    pte_t entry[1024] __attribute__((aligned(4096)));
};

// extern struct page_directory page_dir;

void init_paging();
void set_pte(pte_t *pte, int i, uint32_t addr);
void set_pde();

#endif