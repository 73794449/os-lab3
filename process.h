#include "segment.h"
#ifndef PROCESS_H
#define PROCESS_H

struct Process
{
    seg *segments;         // Not NULL
    size_t segments_count; // >0
    size_t lifetime;       // >0
};
typedef struct Process proc;

proc *generate_procs(size_t count);

size_t get_proc_size(proc *my_proc);

#endif