#include "physical_memory.h"
bool create_volume(phys_mem *memory, proc *my_proc)
{
    size_t curr_offset = 0;
    if (memory->volume_count != 0)
        curr_offset = memory->volumes[memory->volume_count - 1].base + memory->volumes[memory->volume_count - 1].size;
    if (get_proc_size(my_proc) + curr_offset > memory->size)
    {
        curr_offset = compress(memory);
        if (get_proc_size(my_proc) + curr_offset > memory->size)
        {
            return false;
        }
    }
    memory->volume_count++;
    memory->volumes = realloc(memory->volumes, memory->volume_count * (sizeof(volume)));
    memory->volumes[memory->volume_count - 1].base = curr_offset;
    memory->volumes[memory->volume_count - 1].procs_count = 0;
    memory->volumes[memory->volume_count - 1].procs = malloc(memory->volumes[memory->volume_count - 1].procs_count * sizeof(proc *));
    memory->volumes[memory->volume_count - 1].size = 0;
    add_proc_to_volume(my_proc, &memory->volumes[memory->volume_count - 1]);
    return true;
}

bool add_to_volume(phys_mem *memory, proc *my_proc, size_t volume_id)
{
    if (volume_id < memory->volume_count)
    {
        if (volume_id + 1 < memory->volume_count)
        {
            if (get_proc_size(my_proc) + memory->volumes[volume_id].base + memory->volumes[volume_id].size <= memory->volumes[volume_id + 1].base)
            {
                add_proc_to_volume(my_proc, &memory->volumes[volume_id]);
            }
            else
            {
                compress(memory);
                if (give_me_space_after(memory, get_proc_size(my_proc), volume_id))
                {
                    add_proc_to_volume(my_proc, &memory->volumes[volume_id]);
                }
                else
                {
                    return false;
                }
            }
        }
        else
        {
            if (get_proc_size(my_proc) + memory->volumes[volume_id].base + memory->volumes[volume_id].size <= memory->size)
            {
                add_proc_to_volume(my_proc, &memory->volumes[volume_id]);
            }
            else
            {
                size_t offset = compress(memory);
                if (offset + get_proc_size(my_proc) <= memory->size)
                {
                    add_proc_to_volume(my_proc, &memory->volumes[volume_id]);
                }
                else
                {
                    return false;
                }
            }
        }
    }
    else
    {
        return false;
    }
    return true;
}

bool give_me_space_after(phys_mem *memory, size_t size, size_t volume_id)
{
    if (memory->volumes[memory->volume_count - 1].base + memory->volumes[memory->volume_count - 1].size + size <= memory->size)
    {
        for (size_t i = volume_id + 1; i < memory->volume_count; i++)
        {
            memory->volumes[i].base += size;
            memory->volumes[i].size += size;
        }
        return true;
    }
    return false;
}

size_t compress(phys_mem *memory)
{
    for (size_t i = 1; i < memory->volume_count; i++)
    {
        if (memory->volumes[i].base > (memory->volumes[i - 1].base + memory->volumes[i - 1].size))
        {
            size_t diff = memory->volumes[i].base - (memory->volumes[i - 1].base + memory->volumes[i - 1].size);
            memory->volumes[i].base -= diff;
        }
    }
    size_t curr_offset = memory->volumes[memory->volume_count - 1].base + memory->volumes[memory->volume_count - 1].size;
    return curr_offset;
}

void delete_proc_from_volume(phys_mem *memory, proc *my_proc, size_t volume_id)
{
    for (size_t i = 0; i < memory->volumes[volume_id].procs_count; i++)
    {
        if (memory->volumes[volume_id].procs[i] == my_proc)
        {
            if (memory->volumes[volume_id].procs_count == 1)
            {
                delete_volume(memory, volume_id);
                break;
            }
            else
            {
                memory->volumes[volume_id].procs_count--;
                for (size_t k = i; k < memory->volumes[volume_id].procs_count; k++)
                {
                    memory->volumes[volume_id].procs[k] = memory->volumes[volume_id].procs[k + 1];
                }
                memory->volumes[volume_id].procs = realloc(memory->volumes[volume_id].procs, memory->volumes[volume_id].procs_count * sizeof(proc));
            }
        }
    }
}

void delete_volume(phys_mem *memory, size_t volume_id)
{
    memory->volume_count--;
    for (size_t i = volume_id; i < memory->volume_count; i++)
    {
        memory->volumes[i] = memory->volumes[i + 1];
    }
    memory->volumes = realloc(memory->volumes, memory->volume_count * sizeof(volume));
}