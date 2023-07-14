#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "printer.h"
#include "cpu_usage_buffer.h"
#include "cpu_usage_list.h"
#include "sigterm.h"

static pthread_t tid;

static void* print_data(void* arg)
{
    Cpu_usage_buffer* buffer = arg;

    while(!sigterm_is_done())
    {
        cpu_usage_buffer_lock(buffer);
        if(cpu_usage_buffer_is_empty(buffer)) 
        {
            cpu_usage_buffer_wait_for_analyzer(buffer);
        }
        Cpu_usage_list* list = cpu_usage_buffer_get_list(buffer);

        size_t size = cpu_usage_list_get_size(list);
        for(size_t i=0; i<size; i++)
        {
            if(i==0)
                printf("%-4s %-4s %-5.3f %%\n", "CPU", "AVG", cpu_usage_list_get_percent(list, 0));
            else
                printf("%-4s %-4u %-5.3f %%\n", "CPU", cpu_usage_list_get_cpu_num(list, i), cpu_usage_list_get_percent(list, 0));
        }
        printf("--------------------\n");
        cpu_usage_list_delete(list);
        cpu_usage_buffer_unlock(buffer);
        sleep(1);
    }
    printf("\n");

    return NULL;
}

void printer_init(Cpu_usage_buffer* buffer)
{
    pthread_create(&tid, NULL, print_data, buffer);
}

void printer_join(void)
{
    pthread_join(tid, NULL);
}
