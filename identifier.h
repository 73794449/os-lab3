#include <stdlib.h>
#include "virtual_address.h"
#ifndef IDENTIFIER_H
#define IDENTIFIER_H
struct Identifiers{
    char* name;
    size_t size; // 2, 4, 8, 2^n
    virt_addr addr;
};
typedef struct Identifiers ident;

#endif