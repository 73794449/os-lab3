#include "volume.h"
#include <stdbool.h>
#ifndef PHYSICAL_MEMORY
#define PHYSICAL_MEMORY

struct PhysicalMemory
{
    size_t size;
    size_t volume_count;
    volume *volumes;
};
typedef struct PhysicalMemory phys_mem;

size_t compress(phys_mem *memory);
bool give_me_space_after(phys_mem *memory, size_t size, size_t volume_id);
bool add_to_volume(phys_mem *memory, proc *my_proc, size_t volume_id);
bool create_volume(phys_mem *memory, proc *my_proc);
void delete_proc_from_volume(phys_mem *memory, proc *my_proc, size_t volume_id);
void delete_volume(phys_mem *memory, size_t volume_id);

#endif