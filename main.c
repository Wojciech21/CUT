#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "reader.h"
#include "analyzer.h"
#include "cpu_stat_buffer.h"
#include "cpu_usage_buffer.h"
#include "sigterm.h"

int main(void)
{
    sigterm_init();
    
    Cpu_stat_buffer* buffer1 = cpu_stat_buffer_create();
    Cpu_usage_buffer* buffer2 = cpu_usage_buffer_create();

    reader_init(buffer1);
    analyzer_init(buffer1, buffer2);

    reader_join();
    analyzer_join();

    cpu_stat_buffer_delete(buffer1);
    cpu_usage_buffer_delete(buffer2);

    return 0;
}