#include "paging.h"
#include <stdint.h>
#define PTE_RW(x) ((x) | PAGE_PRESENT | PAGE_RW | PAGE_USER)

/*
PAGE FAULTS
US RW  P - Description
0  0  0 - Supervisory process tried to read a non-present page entry
0  0  1 - Supervisory process tried to read a page and caused a protection fault
0  1  0 - Supervisory process tried to write to a non-present page entry
0  1  1 - Supervisory process tried to write a page and caused a protection fault
1  0  0 - User process tried to read a non-present page entry
1  0  1 - User process tried to read a page and caused a protection fault
1  1  0 - User process tried to write to a non-present page entry
1  1  1 - User process tried to write a page and caused a protection fault
*/

uint32_t pageDirectory[PDE_COUNT] __attribute__((aligned(4096)));
static uint32_t pageTable[PTE_COUNT][1024] __attribute__((aligned(4096)));

extern void enablePaging(uint32_t dirAddr);

void initPaging(void) {
    for (int t = 0; t < PTE_COUNT; t++) {
        for (int i = 0; i < 1024; i++) {
            uint32_t physicalAddr = (t*1024 + i) * PAGE_SIZE;
            pageTable[t][i] = PTE_RW(physicalAddr);
        }
        pageDirectory[t] = PTE_RW((uint32_t)pageTable[t]);
    }
    for (int t = PTE_COUNT; t < PDE_COUNT; t++) {
        pageDirectory[t] = 0; // zero the rest out
    }
    enablePaging((uint32_t)&pageDirectory);
}
