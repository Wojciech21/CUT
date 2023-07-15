#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

#include "reader.h"
#include "cpu_stat_list.h"
#include "sigterm.h"

static pthread_t tid;

static void* read_file(void* arg)
{
    Cpu_stat_buffer* buffer = arg;
    FILE *file;
    char char_buffer[1024];
    long user, nice, system ,idle, iowait, irq, softirg, steal;
    while(!sigterm_is_done())
    {
        sleep(1);
        Cpu_stat_list* cpu_stat_list = cpu_stat_list_create();
        file = fopen("/proc/stat", "r");
        if (file == NULL)
        {
            printf("Failed to open the file.\n");
            kill(getpid(), SIGINT);
            return NULL;
        }

        int i=0;

        while(fgets(char_buffer, sizeof(char_buffer), file) && strncmp(char_buffer, "cpu", 3)==0)
        {
            int scanVal = sscanf(char_buffer, "%*s %ld %ld %ld %ld %ld %ld %ld %ld %*d %*d",
                &user, &nice, &system, &idle, &iowait, &irq, &softirg, &steal);
            if(scanVal<8)
            {
                printf("read file error\n");
                fclose(file);
                kill(getpid(), SIGINT);
                return NULL;
            }
            cpu_stat_list_add(cpu_stat_list, i, user, nice, system, idle, iowait, irq, softirg, steal);
            i++;
        }
        fclose(file);

        cpu_stat_buffer_lock(buffer);
        cpu_stat_buffer_add_list(buffer, cpu_stat_list);
        cpu_stat_buffer_call_analyzer(buffer);
        cpu_stat_buffer_unlock(buffer);
    }
    
    return NULL;
}

int reader_init(Cpu_stat_buffer* buffer)
{
    if(pthread_create(&tid, NULL, read_file, buffer) != 0) return -1;
    return 1;
}

int reader_join(void)
{
    if(pthread_join(tid, NULL) != 0) return -1;
    return 1;
}
