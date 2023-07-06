#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "printer.h"
#include "cpu_usage_buffer.h"
#include "cpu_usage_list.h"
#include "sigterm.h"

static pthread_t tid;

void* print_data(void* arg)
{
    Cpu_usage_buffer* buffer = arg;

    while(!sigterm_is_done())
    {
        sleep(5);
            
        Cpu_usage_list* list = cpu_usage_buffer_get_list(buffer);

        for(size_t i=0; i<cpu_usage_list_get_size(list); i++)
        {
            if(i==0)
                printf("CPU AVG USAGE %.3f%%\n", cpu_usage_list_get_percent(list, 0));
            else
                printf("CPU %u. USAGE %.3f%%\n", cpu_usage_list_get_cpu_num(list, i), cpu_usage_list_get_percent(list, i));
        }
        cpu_usage_list_delete(list);
        printf("printer:\n");
        cpu_usage_buffer_print(buffer);
    }
    return NULL;
}

void printer_init(Cpu_usage_buffer* buffer)
{
    pthread_create(&tid, NULL, print_data, buffer);
}

void printer_join()
{
    pthread_join(tid, NULL);
}