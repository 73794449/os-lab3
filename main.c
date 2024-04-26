#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include "config.h"
#include "memory_controller.h"
#include "physical_memory.h"
size_t current_proc = 0;
void print_phys_full(phys_mem *phys)
{
    printf("Output memory:\n");
    printf("RAM = %llu\n", phys->size);
    printf("Volume count = %llu\n", phys->volume_count);
    printf("Volume==================================\n");
    for (size_t i = 0; i < phys->volume_count; i++)
    {
        printf("Volume %llu\n", i);
        printf("Base: %llu\nSize: %llu\n", phys->volumes[i].base, phys->volumes[i].size);
        printf("Process count: %llu\n", phys->volumes[i].procs_count);
        printf("Process=================================\n");
        for (size_t k = 0; k < phys->volumes[i].procs_count; k++)
        {
            printf("Process %llu\n", k);
            printf("Physical address: ");
            phys_addr proc_phys = (get_phys_addr(phys->volumes[i].procs[k], &phys->volumes[i]));
            print_phys_addr(&proc_phys);
            printf("\n");
            printf("Lifetime: %llu\n", phys->volumes[i].procs[k]->lifetime);
            printf("Segments count: %llu\n", phys->volumes[i].procs[k]->segments_count);
            printf("Segment=================================\n");
            for (size_t j = 0; j < phys->volumes[i].procs[k]->segments_count; j++)
            {
                printf("Segment %llu\n", phys->volumes[i].procs[k]->segments[j].id);
                printf("Size: %llu\n", phys->volumes[i].procs[k]->segments[j].size);
                printf("Identifiers count: %llu\n", phys->volumes[i].procs[k]->segments[j].idents_count);
                printf("Identifier==============================\n");
                printf("Name      |Vseg|Voff|Size|Physical addr \n");
                printf("########################################\n");
                for (size_t a = 0; a < phys->volumes[i].procs[k]->segments[j].idents_count; a++)
                {
                    phys_addr ident_phys = (get_phys_addr_ident(phys->volumes[i].procs[k]->segments[j].idents[a].name,
                                                                &phys->volumes[i].procs[k]->segments[j], phys->volumes[i].procs[k], &phys->volumes[i]));
                    
                    printf("%10s|%4llu|%4llu|%4llu|", phys->volumes[i].procs[k]->segments[j].idents[a].name,
                           phys->volumes[i].procs[k]->segments[j].idents[a].addr.segment_id,
                           phys->volumes[i].procs[k]->segments[j].idents[a].addr.addr_in_seg,
                           phys->volumes[i].procs[k]->segments[j].idents[a].size);
                    print_phys_addr(&ident_phys);
                    printf("\n");
                }
            }
        }
    }
}

void load_proc_to_mem(mem_control *mem, phys_mem *phys)
{
    if (mem->procs_count > 0)
    {
        proc *my_proc = &mem->procs[current_proc];
        
        if (get_proc_size(my_proc) <= mem->free_memory)
        {


            bool status = create_volume(phys, my_proc);
            if (status){
                printf("Loaded\n");
                            mem->free_memory -= get_proc_size(my_proc);
            mem->used_memory += get_proc_size(my_proc);
            current_proc++;
            }
            else
                printf("Cannot load this proc\n");
        }
        else
        {
            printf("Sorry, unload some processses, not enough memory\n");
        }
    }
    else
    {
        printf("Sorry, restart program to generate new procs\n");
    }
}

void load_proc_to_spec_mem(mem_control *mem, phys_mem *phys)
{
    printf("Input volume id\n");
    size_t value;
    scanf("%llu", &value);
    if (value < phys->volume_count)
    {
        if (mem->procs_count > 0)
        {
            proc *my_proc = &mem->procs[current_proc];
            if (get_proc_size(my_proc) <= mem->free_memory)
            {


                bool status = add_to_volume(phys, my_proc, value);
                if (status){
                    printf("Loaded\n");
                                    mem->free_memory -= get_proc_size(my_proc);
                mem->used_memory += get_proc_size(my_proc);
                current_proc++;
                }
                else
                    printf("Cannot load this proc\n");
            }
            else
            {
                printf("Sorry, unload some processses, not enough memory\n");
            }
        }
        else
        {
            printf("Sorry, restart program to generate new procs\n");
        }
    }
    else
    {
        printf("This volume id does not exist");
    }
}

void proc_tick(mem_control *mem, phys_mem *phys, size_t tick)
{
    for (size_t i = 0; i < phys->volume_count; i++)
    {
        for (size_t k = 0; k < phys->volumes[i].procs_count; k++)
        {
            phys->volumes[i].procs[k]->lifetime--;
            if (phys->volumes[i].procs[k]->lifetime == 0){
                mem->free_memory+=get_proc_size(phys->volumes[i].procs[k]);
                mem->used_memory-=get_proc_size(phys->volumes[i].procs[k]);
                delete_proc_from_volume(phys, phys->volumes[i].procs[k], i);
                mem->procs_count--;         
                if(phys->volume_count == 0)
                    break;
            }

        }
    }
    printf("Tick %llu\n", tick);
}

void unload_proc(mem_control *mem, phys_mem *phys)
{
    printf("Enter volume id: ");
    size_t volume_id = SIZE_MAX;
    scanf("%llu", &volume_id);
    if (volume_id < phys->volume_count)
    {
        printf("Enter proc id: ");
        size_t proc_id = SIZE_MAX;
        scanf("%llu", &proc_id);
        if (proc_id < phys->volumes[volume_id].procs_count)
        {
                            mem->free_memory+=get_proc_size(phys->volumes[volume_id].procs[proc_id]);
                mem->used_memory-=get_proc_size(phys->volumes[volume_id].procs[proc_id]);
                mem->procs_count--;  
            delete_proc_from_volume(phys, phys->volumes[volume_id].procs[proc_id], volume_id);
            printf("Success\n");
        }
    }
}

void menu()
{
    printf("MENU\n");
    printf("a. Print memory\n");
    printf("b. Load one random proc to memory\n");
    printf("c. Load one random proc to specified volume\n");
    printf("d. Processor tick\n");
    printf("e. Force unload proc from memory\n");
    printf("q. Exit\n");
}

int main()
{
    srand((unsigned int)time(NULL));
    size_t procs_count = 10;
    proc *procs = generate_procs(procs_count);
    mem_control mem = {.max_size = RAM_SIZE,
                       .procs = procs,
                       .procs_count = procs_count,
                       .used_memory = 0,
                       .free_memory = RAM_SIZE};
    phys_mem physical = {.size = RAM_SIZE,
                         .volume_count = 0,
                         .volumes = NULL};
    size_t cpu_tick = 0;
    char c = '\n';
    do
    {
            switch (c)
            {
            case 'a':
                print_phys_full(&physical);
                break;
            case 'b':
                load_proc_to_mem(&mem, &physical);
                break;
            case 'c':
                load_proc_to_spec_mem(&mem, &physical);
                break;
            case 'd':
                proc_tick(&mem, &physical, cpu_tick);
                cpu_tick++;
                break;
            case 'e':
                unload_proc(&mem, &physical);
                break;
            default:
            menu();
                break;
            };
        c = (char)getchar();
    } while (c != 'q');
    return 0;
}