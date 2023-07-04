#ifndef CPU_STAT_LIST_H
#define CPU_STAT_LIST_H

typedef struct Cpu_stat_list Cpu_stat_list;

Cpu_stat_list* cpu_stat_list_create(void);
void cpu_stat_list_add(Cpu_stat_list* const list,
    const unsigned int cpu_num,
    const unsigned long user,
    const unsigned long nice,
    const unsigned long system,
    const unsigned long idle,
    const unsigned long iowait,
    const unsigned long irq,
    const unsigned long softirq,
    const unsigned long steal);
void cpu_stat_list_delete(Cpu_stat_list* list);
size_t cpu_stat_list_get_size(Cpu_stat_list* list);
unsigned int cpu_stat_list_get_cpu_num(Cpu_stat_list* list, int n);
unsigned long cpu_stat_list_get_user(Cpu_stat_list* list, int n);
unsigned long cpu_stat_list_get_nice(Cpu_stat_list* list, int n);
unsigned long cpu_stat_list_get_system(Cpu_stat_list* list, int n);
unsigned long cpu_stat_list_get_idle(Cpu_stat_list* list, int n);
unsigned long cpu_stat_list_get_iowait(Cpu_stat_list* list, int n);
unsigned long cpu_stat_list_get_irq(Cpu_stat_list* list, int n);
unsigned long cpu_stat_list_get_softirq(Cpu_stat_list* list, int n);
unsigned long cpu_stat_list_get_steal(Cpu_stat_list* list, int n);

void cpu_stat_list_print(Cpu_stat_list* list);
#endif