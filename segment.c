#include "segment.h"
#include <string.h>
#include <stdlib.h>

virt_addr* get_virt_addr(char* name, seg my_seg)
{
    for(size_t i = 0; i < my_seg.idents_count; i++)
    {
        if(strcmp(my_seg.idents->name, name) == 0)
            return &my_seg.idents->addr;
    }
    exit(EXIT_FAILURE);
}