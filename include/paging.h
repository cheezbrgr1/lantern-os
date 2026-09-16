#ifndef LANTERN_PAGING_H
#define LANTERN_PAGING_H

#define PDE_COUNT 1024
#define PAGE_SIZE 0x1000
#define PTE_COUNT 4 // arbitrary

#define PAGE_PRESENT (1 << 0)
#define PAGE_RW      (1 << 1)
#define PAGE_USER    (1 << 2)

void initPaging(void);

#endif