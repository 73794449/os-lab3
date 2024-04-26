#include "process.h"
#include "physical_address.h"
#ifndef VOLUME_H
#define VOLUME_H
struct Volume{
    size_t base;
    size_t size;
    proc** procs;
    size_t procs_count;
};
typedef struct Volume volume;

phys_addr get_phys_addr(proc* proc, volume* volume);

phys_addr get_phys_addr_ident(char* name, seg* segment, proc* proc,volume* volume);

size_t whoami_physically(proc* proc, volume* volume);

void delete_proc_from_volume_by_id(size_t id_proc, volume* volume);

void add_proc_to_volume(proc* proc, volume* volume);

#endif