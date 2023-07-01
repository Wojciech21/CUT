#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "analyzer.h"
#include "cpu_list.h"
#include "sigterm.h"

static pthread_t tid;

void* analyze_data(void* param)
{
   Buffer* buffer = (Buffer*)param;

   while(!sigterm_is_done())
   {
        sleep(2);
        Cpu_list** cpu_lists = buffer_get_lists(buffer);
        Cpu_list* cpu_list_old = cpu_lists[0];
        // buffer_print(buffer);
        Cpu_list* cpu_list_new = cpu_lists[1];
        // buffer_print(buffer);
        free(cpu_lists);
        if(cpu_list_get_size(cpu_list_old)!=cpu_list_get_size(cpu_list_old)) return NULL;
        if(cpu_list_new == NULL || cpu_list_old == NULL)
            printf("empty\n");
        else
        {
            size_t size = cpu_list_get_size(cpu_list_old);
            for(size_t i=0; i<size; i++)
            {
                int cpu_num = cpu_list_get_cpu_num(cpu_list_old, i);
                long idle_old = cpu_list_get_idle(cpu_list_old, i) + cpu_list_get_iowait(cpu_list_old, i);
                long idle_new = cpu_list_get_idle(cpu_list_new, i) + cpu_list_get_iowait(cpu_list_new, i);
                long non_idle_old = cpu_list_get_user(cpu_list_old, i) + 
                cpu_list_get_nice(cpu_list_old, i) +
                cpu_list_get_system(cpu_list_old, i) +
                cpu_list_get_irq(cpu_list_old, i) +
                cpu_list_get_softirq(cpu_list_old, i) +
                cpu_list_get_steal(cpu_list_old, i);
                long non_idle_new = cpu_list_get_user(cpu_list_new, i) + 
                cpu_list_get_nice(cpu_list_new, i) +
                cpu_list_get_system(cpu_list_new, i) +
                cpu_list_get_irq(cpu_list_new, i) +
                cpu_list_get_softirq(cpu_list_new, i) +
                cpu_list_get_steal(cpu_list_new, i);


                long total_old = idle_old + non_idle_old;
                long total_new = idle_new + non_idle_new;

                long total_diff = total_new - total_old;
                long idle_diff = idle_new - idle_old;

                float CPU_usage = (total_diff - idle_diff)*100.0 / total_diff;

                printf("CPU %d usage: %.3f%%\n", cpu_num, CPU_usage);
            }
        }
   }
   return NULL;
}

void analyzer_init(Buffer* buffer)
{
    pthread_create(&tid, NULL, analyze_data, buffer);
}

void analyzer_join()
{
    pthread_join(tid, NULL);
}