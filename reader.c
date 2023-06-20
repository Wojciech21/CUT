#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "reader.h"
#include "cpu_list.h"

// void reader_createThread(void)
// {
//     pthread_t tid;
//     pthread_create(&tid, NULL, read, NULL);

//     pthread_exit(NULL);
// }

void* reader_read(void* param)
{
    FILE *file;
    char buffer[1024];
    Cpu_list* cpu_list = create_list();
    unsigned long user, nice, system ,idle, iowait, irq, softirg, steal;
    // while(1)
    {   
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
        print_list(cpu_list);
        sleep(1);
    }

    delete_list(cpu_list);
    fclose(file);
    return NULL;
}