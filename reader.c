#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "reader.h"
#include "cpu_list.h"


void* read_file(void* param)
{
    FILE *file;
    char buffer[1024];
    
    unsigned long user, nice, system ,idle, iowait, irq, softirg, steal;
    for(int idk=0; idk<20; idk++)
    {
        Cpu_list* cpu_list = create_list();
        file = fopen("/proc/stat", "r");
        if (file == NULL)
        {
            printf("Failed to open the file.\n");
            return NULL;
        }

        unsigned int i=0;

        while(fgets(buffer, sizeof(buffer), file) && strncmp(buffer, "cpu", 3)==0)
        {
            int scanVal = sscanf(buffer, "%*s %lu %lu %lu %lu %lu %lu %lu %lu %*d %*d",
                &user, &nice, &system, &idle, &iowait, &irq, &softirg, &steal);
            if(scanVal<8)
            {
                printf("read file error\n");
                return NULL;
            }
            add_to_list(cpu_list, i, user, nice, system, idle, iowait, irq, softirg, steal);
            i++;
        }
        buffer_add_list((Buffer*)param, cpu_list);
        buffer_print((Buffer*)param);
        fclose(file);
    }
    return NULL;
}

void reader_init(Buffer* buffer)
{
    pthread_t tid;
    // read_file(buffer);
    pthread_create(&tid, NULL, read_file, buffer);
    pthread_join(tid, NULL);
}