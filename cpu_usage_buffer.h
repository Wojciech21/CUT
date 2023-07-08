#ifndef CPU_USAGE_BUFFER_H
#define CPU_USAGE_BUFFER_H

#include <stdbool.h>

#include "cpu_usage_list.h"

typedef struct Cpu_usage_buffer Cpu_usage_buffer;

Cpu_usage_buffer* cpu_usage_buffer_create(void);
void cpu_usage_buffer_delete(Cpu_usage_buffer* buffer);
void cpu_usage_buffer_add_list(Cpu_usage_buffer* buffer, Cpu_usage_list* list);
Cpu_usage_list* cpu_usage_buffer_get_list(Cpu_usage_buffer* buffer);
bool cpu_usage_buffer_is_empty(Cpu_usage_buffer* buffer);

void cpu_usage_buffer_lock(Cpu_usage_buffer* buffer);
void cpu_usage_buffer_unlock(Cpu_usage_buffer* buffer);
void cpu_usage_buffer_call_printer(Cpu_usage_buffer* buffer);
void cpu_usage_buffer_wait_for_analyzer(Cpu_usage_buffer* buffer);

void cpu_usage_buffer_print(Cpu_usage_buffer* buffer);

#endif