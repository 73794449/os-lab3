#include "process.h"
#ifndef MEMORY_CONTROLLER_H
#define MEMORY_CONTROLLER_H
struct MemoryController
{
    size_t max_size;
    size_t used_memory;
    size_t free_memory;
    size_t procs_count;
    proc *procs;
};
typedef struct MemoryController mem_control;

#endif