#include "physical_address.h"
#include <stdio.h>

void print_phys_addr(phys_addr *pa)
{
    printf("%2llux%4llu", pa->base, pa->offset);
}