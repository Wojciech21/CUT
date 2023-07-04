#ifndef CPU_USAGE_LIST_H
#define CPU_USAGE_LIST_H

typedef struct Cpu_usage_list Cpu_usage_list;

Cpu_usage_list* cpu_usage_list_create(void);
void cpu_usage_list_add(Cpu_usage_list* const list, const unsigned int cpu_num, const float percent);
void cpu_usage_list_delete(Cpu_usage_list* list);
size_t cpu_usage_list_get_size(Cpu_usage_list* list);
unsigned int cpu_usage_list_get_cpu_num(Cpu_usage_list* list, int n);
float cpu_usage_list_get_percent(Cpu_usage_list* list, int n);


void cpu_usage_list_print(Cpu_usage_list* list);
#endif