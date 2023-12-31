#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

#include "analyzer.h"
#include "cpu_stat_list.h"
#include "cpu_usage_list.h"
#include "sigterm.h"

static pthread_t tid;

struct Buffers
{
    Cpu_stat_buffer* buffer1;
    Cpu_usage_buffer* buffer2;
};

static void* thread_loop(void* arg)
{
    Cpu_stat_buffer* buffer1 = ((struct Buffers*)arg)->buffer1;
    Cpu_usage_buffer* buffer2 = ((struct Buffers*)arg)->buffer2;
    free(arg);

   while(!sigterm_is_done())
   {
        if(analyze_data(buffer1, buffer2)==-1) 
        {
            kill(getpid(), SIGINT);
            return NULL;
        }
   }

   return NULL;
}

int analyze_data(Cpu_stat_buffer* buffer1, Cpu_usage_buffer* buffer2)
{
    cpu_stat_buffer_lock(buffer1);
    if(cpu_stat_buffer_is_empty(buffer1)) 
    {
        cpu_stat_buffer_wait_for_reader(buffer1);
    }

    Cpu_stat_list** cpu_stat_lists = cpu_stat_buffer_get_lists(buffer1);
    Cpu_stat_list* cpu_stat_list_old = cpu_stat_lists[0];
    if(cpu_stat_list_old==NULL) 
    {
        printf("empty old list\n");
        cpu_stat_buffer_unlock(buffer1);
        free(cpu_stat_lists);
        return -1;
    }
    Cpu_stat_list* cpu_stat_list_new = cpu_stat_lists[1];
    if(cpu_stat_list_new==NULL) 
    {
        printf("empty new list\n");
        cpu_stat_buffer_unlock(buffer1);
        free(cpu_stat_lists);
        return -1;
    }
    free(cpu_stat_lists);

    size_t size = cpu_stat_list_get_size(cpu_stat_list_old);
    if(size!=cpu_stat_list_get_size(cpu_stat_list_old)) 
    {
        printf("size changed\n");
        cpu_stat_buffer_unlock(buffer1);
        return -1;
    }
    
    Cpu_usage_list* cpu_usage_list = cpu_usage_list_create();
    for(size_t i=0; i<size; i++)
    {
        int cpu_num = cpu_stat_list_get_cpu_num(cpu_stat_list_old, i);
        long idle_old = cpu_stat_list_get_idle(cpu_stat_list_old, i) + cpu_stat_list_get_iowait(cpu_stat_list_old, i);
        long idle_new = cpu_stat_list_get_idle(cpu_stat_list_new, i) + cpu_stat_list_get_iowait(cpu_stat_list_new, i);
        long non_idle_old = cpu_stat_list_get_user(cpu_stat_list_old, i) + 
        cpu_stat_list_get_nice(cpu_stat_list_old, i) +
        cpu_stat_list_get_system(cpu_stat_list_old, i) +
        cpu_stat_list_get_irq(cpu_stat_list_old, i) +
        cpu_stat_list_get_softirq(cpu_stat_list_old, i) +
        cpu_stat_list_get_steal(cpu_stat_list_old, i);
        long non_idle_new = cpu_stat_list_get_user(cpu_stat_list_new, i) + 
        cpu_stat_list_get_nice(cpu_stat_list_new, i) +
        cpu_stat_list_get_system(cpu_stat_list_new, i) +
        cpu_stat_list_get_irq(cpu_stat_list_new, i) +
        cpu_stat_list_get_softirq(cpu_stat_list_new, i) +
        cpu_stat_list_get_steal(cpu_stat_list_new, i);


        long total_old = idle_old + non_idle_old;
        long total_new = idle_new + non_idle_new;

        long total_diff = total_new - total_old;
        long idle_diff = idle_new - idle_old;

        double CPU_usage;
        CPU_usage = total_diff==0 ? 0 : (double)(total_diff - idle_diff)*100.0 / (double)total_diff;

        cpu_usage_list_add(cpu_usage_list, cpu_num, CPU_usage);
        
    }
    cpu_stat_list_delete(cpu_stat_list_old); 
    cpu_stat_buffer_unlock(buffer1);
    
    cpu_usage_buffer_lock(buffer2);
    cpu_usage_buffer_add_list(buffer2, cpu_usage_list);
    cpu_usage_buffer_call_printer(buffer2);
    cpu_usage_buffer_unlock(buffer2);
    return 1;
}

int analyzer_init(Cpu_stat_buffer* buffer1, Cpu_usage_buffer* buffer2)
{
    if(buffer1 == NULL) return -1;
    if(buffer2 == NULL) return -1;

    struct Buffers* buffers = calloc(1, sizeof(*buffers));
    if(buffers == NULL) return -1;
    *buffers = (struct Buffers)
    {
        .buffer1 = buffer1,
        .buffer2 = buffer2
    };
    if(pthread_create(&tid, NULL, thread_loop, buffers) != 0) return -1;
    return 1;
}

int analyzer_join(void)
{
    if(pthread_join(tid, NULL)!=0) return -1;
    return 1;
}
