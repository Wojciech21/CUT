#ifndef CPU_STAT_BUFFER_H
#define CPU_STAT_BUFFER_H

#include <stdbool.h>

#include "cpu_stat_list.h"

typedef struct Cpu_stat_buffer Cpu_stat_buffer;

Cpu_stat_buffer* cpu_stat_buffer_create(void);
void cpu_stat_buffer_delete(Cpu_stat_buffer* buffer);
void cpu_stat_buffer_add_list(Cpu_stat_buffer* buffer, Cpu_stat_list* list);
Cpu_stat_list** cpu_stat_buffer_get_lists(Cpu_stat_buffer* buffer);
bool cpu_stat_buffer_is_empty(Cpu_stat_buffer* buffer);

void cpu_stat_buffer_lock(Cpu_stat_buffer* buffer);
void cpu_stat_buffer_unlock(Cpu_stat_buffer* buffer);
void cpu_stat_buffer_call_analyzer(Cpu_stat_buffer* buffer);
void cpu_stat_buffer_wait_for_reader(Cpu_stat_buffer* buffer);

#endif
