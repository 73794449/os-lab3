#include "volume.h"
#include <stdio.h>
#include <string.h>

void add_proc_to_volume(proc *my_proc, volume *my_volume)
{
    my_volume->procs_count++;
    my_volume->procs = realloc(my_volume->procs, my_volume->procs_count * sizeof(proc *));
    my_volume->procs[my_volume->procs_count - 1] = my_proc;
    my_volume->size += get_proc_size(my_proc);
}
void delete_proc_from_volume_by_id(size_t id_proc, volume *my_volume)
{
    my_volume->procs_count--;
    my_volume->size -= get_proc_size(my_volume->procs[id_proc]);
    for (size_t i = id_proc; i < my_volume->procs_count; i++)
    {
        my_volume->procs[i] = my_volume->procs[i + 1];
    }
    my_volume->procs = realloc(my_volume->procs, my_volume->procs_count * (sizeof(proc)));
}
size_t whoami_physically(proc *my_proc, volume *my_volume)
{
    for (size_t i = 0; i < my_volume->procs_count; i++)
    {
        if (my_volume->procs[i] == my_proc)
            return i;
    }
    printf("Tried to access to proc from another volume\n");
    exit(EXIT_FAILURE);
}
phys_addr get_phys_addr(proc *my_proc, volume *my_volume)
{
    size_t id = whoami_physically(my_proc, my_volume);
    size_t offset = 0;
    for (size_t i = 0; i < id; i++)
    {
        offset += get_proc_size(my_volume->procs[i]);
    }
    phys_addr phys = {.base = my_volume->base,
                      .offset = offset};
    return phys;
}

phys_addr get_phys_addr_ident(char *name, seg *segment, proc *my_proc, volume *my_volume)
{
    phys_addr procs_one = get_phys_addr(my_proc, my_volume);
    procs_one.offset = 0;
    size_t offset = 0;
    for (size_t i = 0; i < my_proc->segments_count; i++)
    {
        offset += my_proc->segments[i].size;
        if (my_proc->segments[i].id == segment->id)
        {
            for (size_t k = 0; k < my_proc->segments[i].idents_count; k++)
            {
                if (strcmp(my_proc->segments[i].idents[k].name, name) == 0)
                {
                    procs_one.offset += offset;
                    return procs_one;
                }
                offset += my_proc->segments[i].idents[k].size;
            }
        }
    }
    printf("ERROR: cannot find specified name or segment or proc or volume or etc\n");
    exit(EXIT_FAILURE);
}