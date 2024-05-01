#include <stdlib.h>
#ifndef VIRTUAL_ADDRESS_H
#define VIRTUAL_ADDRESS_H
struct VirtualAddress
{
    size_t segment_id;  // >= 0
    size_t addr_in_seg; // >= 0
};
typedef struct VirtualAddress virt_addr;

void print_virt_addr(virt_addr *va);
#endif