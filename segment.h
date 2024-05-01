#include "identifier.h"
#ifndef SEGMENT_H
#define SEGMENT_H
struct Segment
{
    size_t id;           // >= 0
    ident *idents;       // Not NULL
    size_t idents_count; // >0
    size_t size;         // >0
};
typedef struct Segment seg;

virt_addr *get_virt_addr(char *name, seg my_seg);

#endif