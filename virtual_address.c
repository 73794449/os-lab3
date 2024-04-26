#include <stdio.h>
#include "virtual_address.h"

void print_virt_addr(virt_addr* va)
{
    printf("%2llu..%4llu",va->segment_id,va->addr_in_seg);
}