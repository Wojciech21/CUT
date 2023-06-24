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
    const unsigned long softirq,
    const unsigned long steal);
void print_list(Cpu_list* list);
void delete_list(Cpu_list* list);
long cpu_list_get_user(Cpu_list* list);
long cpu_list_get_nice(Cpu_list* list);
long cpu_list_get_system(Cpu_list* list);
long cpu_list_get_idle(Cpu_list* list);
long cpu_list_get_iowait(Cpu_list* list);
long cpu_list_get_irq(Cpu_list* list);
long cpu_list_get_softirq(Cpu_list* list);
long cpu_list_get_steal(Cpu_list* list);


#endif