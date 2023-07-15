#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


#include "reader.h"
#include "analyzer.h"
#include "printer.h"
#include "cpu_stat_buffer.h"
#include "cpu_usage_buffer.h"
#include "sigterm.h"

int main(void)
{
    if(sigterm_init()==-1) return -1;
    Cpu_stat_buffer* cpu_stat_buffer = cpu_stat_buffer_create();
    if(cpu_stat_buffer == NULL) return -1;
    Cpu_usage_buffer* cpu_usage_buffer = cpu_usage_buffer_create();
    if(cpu_usage_buffer == NULL) goto cpu_usage_buffer_failed;

    if(reader_init(cpu_stat_buffer)==-1) goto thread_init_failed;
    if(analyzer_init(cpu_stat_buffer, cpu_usage_buffer)==-1) goto thread_init_failed;
    if(printer_init(cpu_usage_buffer)==-1) goto thread_init_failed;

thread_init_failed:
    if(printer_join()==-1) goto thread_join_failed;
    if(analyzer_join()==-1) goto thread_join_failed;
    if(reader_join()==-1) goto thread_join_failed;

thread_join_failed:
    cpu_usage_buffer_delete(cpu_usage_buffer);
cpu_usage_buffer_failed:
    cpu_stat_buffer_delete(cpu_stat_buffer);
    return 0;
}
