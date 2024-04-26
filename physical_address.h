#include <stdlib.h>
#ifndef PHYSICAL_ADDRESS_H
#define PHYSICAL_ADDRESS_H
struct PhysicalAddress
{
    size_t base;
    size_t offset;
};
typedef struct PhysicalAddress phys_addr;

void print_phys_addr(phys_addr* pa);
#endif