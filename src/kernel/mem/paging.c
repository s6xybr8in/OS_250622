#include "paging.h"

struct page_directory page_dir __attribute__((aligned(4096)));
struct page_table kernel_page_table __attribute__((aligned(4096)));

void set_pde()
{
    // page_dir.entry[i].present = 1;
    // page_dir.entry[i].read_write = 1;
    // page_dir.entry[i].user_priv = 0;
    // page_dir.entry[i].reserved = 0;
    // page_dir.entry[i].frame_addr = i;
}
void set_pte(pte_t *pte, int i, uint32_t addr)
{
    pte->frame_addr = (addr >> 12) + i;
    pte->present = 1;
    pte->read_write = 1;
    pte->user_priv = 0;
    pte->reserved = 0;
}
void init_paging()
{
    cli();
    for (int i = 0; i < 1024; i++) {
        page_dir.entry[i] = 0;
    }

    for (int i = 0; i < 1024; i++) {
        set_pte(kernel_page_table.entry + i, i, 0);
    }
    page_dir.entry[0] = (uint32_t)(&kernel_page_table) | 3;
    paging_flush((uint32_t)&page_dir);
    sti();
}