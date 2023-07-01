#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "reader.h"
#include "cpu_list.h"
#include "sigterm.h"

static pthread_t tid;

void* read_file(void* param)
{
    FILE *file;
    char buffer[1024];
    
    unsigned long user, nice, system ,idle, iowait, irq, softirg, steal;
    while(!sigterm_is_done())
    {
        Cpu_list* cpu_list = cpu_list_create();
        file = fopen("/proc/stat", "r");
        if (file == NULL)
        {
            printf("Failed to open the file.\n");
            return NULL;
        }

        unsigned int i=0;

        while(fgets(buffer, sizeof(buffer), file) && strncmp(buffer, "cpu", 3)==0)
        {
            // printf("%s", buffer);
            int scanVal = sscanf(buffer, "%*s %lu %lu %lu %lu %lu %lu %lu %lu %*d %*d",
                &user, &nice, &system, &idle, &iowait, &irq, &softirg, &steal);
            if(scanVal<8)
            {
                printf("read file error\n");
                return NULL;
            }
            cpu_list_add(cpu_list, i, user, nice, system, idle, iowait, irq, softirg, steal);
            i++;
        }
        buffer_add_list((Buffer*)param, cpu_list);
        // buffer_print((Buffer*)param);
        fclose(file);
        sleep(1);
    }
    return NULL;
}

void reader_init(Buffer* buffer)
{
    pthread_create(&tid, NULL, read_file, buffer);
}

void reader_join()
{
    pthread_join(tid, NULL);
}