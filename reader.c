#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "reader.h"
#include "cpu_stat_list.h"
#include "sigterm.h"

static pthread_t tid;

void* read_file(void* arg)
{
    Cpu_stat_buffer* buffer = arg;
    FILE *file;
    char char_buffer[1024];
    unsigned long user, nice, system ,idle, iowait, irq, softirg, steal;
    while(!sigterm_is_done())
    {
        Cpu_stat_list* cpu_stat_list = cpu_stat_list_create();
        file = fopen("/proc/stat", "r");
        if (file == NULL)
        {
            printf("Failed to open the file.\n");
            return NULL;
        }

        unsigned int i=0;

        while(fgets(char_buffer, sizeof(char_buffer), file) && strncmp(char_buffer, "cpu", 3)==0)
        {
            // printf("%s", buffer);
            int scanVal = sscanf(char_buffer, "%*s %lu %lu %lu %lu %lu %lu %lu %lu %*d %*d",
                &user, &nice, &system, &idle, &iowait, &irq, &softirg, &steal);
            if(scanVal<8)
            {
                printf("read file error\n");
                return NULL;
            }
            cpu_stat_list_add(cpu_stat_list, i, user, nice, system, idle, iowait, irq, softirg, steal);
            i++;
        }
        cpu_stat_buffer_add_list(buffer, cpu_stat_list);

        printf("reader:\n");
        cpu_stat_buffer_print(buffer);
        fclose(file);

        sleep(1);

    }
    return NULL;
}

void reader_init(Cpu_stat_buffer* buffer)
{
    pthread_create(&tid, NULL, read_file, buffer);
}

void reader_join()
{
    pthread_join(tid, NULL);
}