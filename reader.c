#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

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
        // printf("1.\n");
        Cpu_stat_list* cpu_stat_list = cpu_stat_list_create();
        file = fopen("/proc/stat", "r");
        if (file == NULL)
        {
            printf("Failed to open the file.\n");
            break;
        }

        int i=0;

        // printf("2.\n");
        while(fgets(char_buffer, sizeof(char_buffer), file) && strncmp(char_buffer, "cpu", 3)==0)
        {
            // printf("%s", buffer);
            // printf("2.1\n");
            int scanVal = sscanf(char_buffer, "%*s %ld %ld %ld %ld %ld %ld %ld %ld %*d %*d",
                &user, &nice, &system, &idle, &iowait, &irq, &softirg, &steal);
            // printf("2.2\n");
            if(scanVal<8)
            {
                printf("read file error\n");
                break;
            }
            // printf("2.3\n");
            cpu_stat_list_add(cpu_stat_list, i, user, nice, system, idle, iowait, irq, softirg, steal);
            i++;
            // printf("2.4\n");
        }
        // printf("3.\n");
        fclose(file);

        // sleep(1);

        cpu_stat_buffer_lock(buffer);
        cpu_stat_buffer_add_list(buffer, cpu_stat_list);
        cpu_stat_buffer_call_analyzer(buffer);
        cpu_stat_buffer_unlock(buffer);

        // printf("4.\n");
        // printf("reader:\n");
        // cpu_stat_buffer_print(buffer);
        // printf("5.\n");
    }
    return NULL;
}

void reader_init(Cpu_stat_buffer* buffer)
{
    pthread_create(&tid, NULL, read_file, buffer);
}

void reader_join(void)
{
    pthread_join(tid, NULL);
}
