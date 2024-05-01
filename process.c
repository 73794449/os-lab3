#include "process.h"
#include <math.h>

size_t segs_num = 0;
proc *generate_procs(size_t count)
{
    proc *procs = malloc(count * sizeof(proc));
    for (size_t i = 0; i < count; i++)
    {
#ifndef NO_RANDOM
        size_t segments_count = (size_t)rand() % 5 + 1;
        size_t lifetime = (size_t)rand() % 10 + 1;
#endif
#ifdef NO_RANDOM
        size_t segments_count = 1;
        size_t lifetime = 1;
#endif
        procs[i].lifetime = lifetime;
        procs[i].segments_count = segments_count;
        procs[i].segments = malloc(segments_count * sizeof(seg));
        for (size_t k = 0; k < segments_count; k++)
        {
#ifndef NO_RANDOM
            size_t idents_count = (size_t)rand() % 3 + 1;
#endif
#ifdef NO_RANDOM
            size_t idents_count = 3;
#endif
            procs[i].segments[k].idents_count = idents_count;
            procs[i].segments[k].idents = malloc(idents_count * sizeof(ident));
            size_t size_of_segment = 0;
            procs[i].segments[k].id = segs_num++;
            for (size_t j = 0; j < idents_count; j++)
            {
                char *ident_names[10] = {"ident0", "ident1", "ident2", "ident3", "ident4", "ident5", "ident6", "ident7", "ident8", "ident9"};
#ifndef NO_RANDOM
                size_t size = (size_t)pow(2, rand() % 3 + 1);
                size_t name_id = (size_t)rand() % 9;
#endif
#ifdef NO_RANDOM
                size_t size = 4;
                size_t name_id = j;
#endif
                procs[i].segments[k].idents[j].name = ident_names[name_id];
                procs[i].segments[k].idents[j].size = size;
                procs[i].segments[k].idents[j].addr.segment_id = procs[i].segments[k].id;
                if (j == 0)
                    procs[i].segments[k].idents[j].addr.addr_in_seg = 0;
                else
                    procs[i].segments[k].idents[j].addr.addr_in_seg = procs[i].segments[k].idents[j - 1].size;

                size_of_segment += size;
            }
            procs[i].segments[k].size = size_of_segment;
        }
    }
    return procs;
}

size_t get_proc_size(proc *my_proc)
{
    size_t size = 0;
    for (size_t i = 0; i < my_proc->segments_count; i++)
        size += my_proc->segments[i].size;
    return size;
}