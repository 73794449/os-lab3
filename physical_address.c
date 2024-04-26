#include "physical_address.h"

void print_phys_addr(phys_addr* pa)
{
    printf("%2lux%4lu",pa->base,pa->offset);
}