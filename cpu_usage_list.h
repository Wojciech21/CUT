#ifndef CPU_USAGE_LIST_H
#define CPU_USAGE_LIST_H

typedef struct Cpu_usage_list Cpu_usage_list;

Cpu_usage_list* cpu_usage_list_create(void);
void cpu_usage_list_add(Cpu_usage_list* const list, const int cpu_num, const double percent);
void cpu_usage_list_delete(Cpu_usage_list* list);
size_t cpu_usage_list_get_size(Cpu_usage_list* list);
int cpu_usage_list_get_cpu_num(Cpu_usage_list* list, size_t n);
double cpu_usage_list_get_percent(Cpu_usage_list* list, size_t n);

#endif
