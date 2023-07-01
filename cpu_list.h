#ifndef CPULIST_H
#define CPULIST_H

typedef struct cpu_list Cpu_list;

Cpu_list* cpu_list_create(void);
void cpu_list_add(Cpu_list* const list,
    const unsigned int cpu_num,
    const unsigned long user,
    const unsigned long nice,
    const unsigned long system,
    const unsigned long idle,
    const unsigned long iowait,
    const unsigned long irq,
    const unsigned long softirq,
    const unsigned long steal);
void cpu_list_delete(Cpu_list* list);
size_t cpu_list_get_size(Cpu_list* list);
unsigned int cpu_list_get_cpu_num(Cpu_list* list, int n);
unsigned long cpu_list_get_user(Cpu_list* list, int n);
unsigned long cpu_list_get_nice(Cpu_list* list, int n);
unsigned long cpu_list_get_system(Cpu_list* list, int n);
unsigned long cpu_list_get_idle(Cpu_list* list, int n);
unsigned long cpu_list_get_iowait(Cpu_list* list, int n);
unsigned long cpu_list_get_irq(Cpu_list* list, int n);
unsigned long cpu_list_get_softirq(Cpu_list* list, int n);
unsigned long cpu_list_get_steal(Cpu_list* list, int n);

void cpu_list_print(Cpu_list* list);
#endif