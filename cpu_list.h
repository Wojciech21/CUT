#ifndef CPULIST_H
#define CPULIST_H

typedef struct cpu_list Cpu_list;

Cpu_list* create_list(void);
void add_to_list(Cpu_list* const list,
    const unsigned int cpu_num,
    const unsigned long user,
    const unsigned long nice,
    const unsigned long system,
    const unsigned long idle,
    const unsigned long iowait,
    const unsigned long irq,
    const unsigned long softirg,
    const unsigned long steal);
void print_list(Cpu_list* list);
void delete_list(Cpu_list* list);

#endif