#ifndef ANALYZER_H
#define ANALYZER_H


#include "cpu_stat_buffer.h"
#include "cpu_usage_buffer.h"

void analyzer_init(Cpu_stat_buffer* buffer1, Cpu_usage_buffer* buffer2);
void analyzer_join(void);
void analyze_data(Cpu_stat_buffer* buffer1, Cpu_usage_buffer* buffer2);

#endif
