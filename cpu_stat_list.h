#ifndef CPU_STAT_LIST_H
#define CPU_STAT_LIST_H

typedef struct Cpu_stat_list Cpu_stat_list;

Cpu_stat_list* cpu_stat_list_create(void);
void cpu_stat_list_add(Cpu_stat_list* const list,
    const int cpu_num,
    const long user,
    const long nice,
    const long system,
    const long idle,
    const long iowait,
    const long irq,
    const long softirq,
    const long steal);
void cpu_stat_list_delete(Cpu_stat_list* list);
size_t cpu_stat_list_get_size(Cpu_stat_list* list);
int cpu_stat_list_get_cpu_num(Cpu_stat_list* list, size_t n);
long cpu_stat_list_get_user(Cpu_stat_list* list, size_t n);
long cpu_stat_list_get_nice(Cpu_stat_list* list, size_t n);
long cpu_stat_list_get_system(Cpu_stat_list* list, size_t n);
long cpu_stat_list_get_idle(Cpu_stat_list* list, size_t n);
long cpu_stat_list_get_iowait(Cpu_stat_list* list, size_t n);
long cpu_stat_list_get_irq(Cpu_stat_list* list, size_t n);
long cpu_stat_list_get_softirq(Cpu_stat_list* list, size_t n);
long cpu_stat_list_get_steal(Cpu_stat_list* list, size_t n);

#endif
