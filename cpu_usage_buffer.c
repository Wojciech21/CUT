#include <stdlib.h>
#include <stdio.h>

#include <pthread.h>

#include "cpu_usage_buffer.h"


#define BUFFER_SIZE 20

typedef struct Cpu_usage_buffer_node
{
    struct Cpu_usage_buffer_node* next;
    Cpu_usage_list* cpu_usage_list;

} Cpu_usage_buffer_node;

struct Cpu_usage_buffer
{
    Cpu_usage_buffer_node* head;
    Cpu_usage_buffer_node* tail; 
    pthread_mutex_t mutex;
    pthread_cond_t can_get;
    int item_count;
    char paading[4];
};

Cpu_usage_buffer* cpu_usage_buffer_create(void)
{
    Cpu_usage_buffer* buffer = malloc(sizeof(*buffer));
    if(buffer == NULL)
    {
        printf("buffer memory allocation error\n");
        return NULL;
    }
    Cpu_usage_buffer_node* first_node = calloc(1, sizeof(*first_node));
    if(first_node == NULL)
    {
        printf("buffer node memory allocation error\n");
        return NULL;
    }
    *buffer = (Cpu_usage_buffer)
    {
        .head = first_node,   
        .tail = first_node,
        .item_count = 0, 
        .mutex = PTHREAD_MUTEX_INITIALIZER,
        .can_get = PTHREAD_COND_INITIALIZER
    };

    Cpu_usage_buffer_node* temp = first_node;
    for(int i=0; i<BUFFER_SIZE-1; i++)
    {
        temp->cpu_usage_list = NULL;
        temp->next = malloc(sizeof(Cpu_usage_buffer_node));
        if(temp->next == NULL)
        {
            printf("buffer node memory allocation error\n");
            return NULL;
        }
        temp = temp->next;
    }
    temp->cpu_usage_list = NULL;
    temp->next = first_node;

    return buffer;
}

void cpu_usage_buffer_add_list(Cpu_usage_buffer* buffer, Cpu_usage_list* list)
{
    if(buffer == NULL) return;
    if(list == NULL) return;

    cpu_usage_list_delete(buffer->head->cpu_usage_list);
    buffer->head->cpu_usage_list = list;
    buffer->head = buffer->head->next;
    if(buffer->item_count < BUFFER_SIZE)
    {
        buffer->item_count++;
    }
    else
    {
        buffer->tail = buffer->tail->next;
    }
}

Cpu_usage_list* cpu_usage_buffer_get_list(Cpu_usage_buffer* buffer)
{
    Cpu_usage_list* list = buffer->tail->cpu_usage_list;
    buffer->tail->cpu_usage_list = NULL;
    buffer->tail = buffer->tail->next;
    buffer->item_count--;
    return list;
}


void cpu_usage_buffer_delete(Cpu_usage_buffer* buffer)
{
    if(buffer == NULL)
    {
        return;
    }
    Cpu_usage_buffer_node* curr = buffer->head;
    Cpu_usage_buffer_node* next = curr->next;
    curr->next = NULL;
    while (next != NULL)
    {
        curr = next;
        next = curr->next;
        cpu_usage_list_delete(curr->cpu_usage_list);
        free(curr);
    }
    

    free(buffer);
}


bool cpu_usage_buffer_is_empty(Cpu_usage_buffer* buffer)
{
    return buffer->item_count == 0;
}



void cpu_usage_buffer_lock(Cpu_usage_buffer* buffer)
{
    pthread_mutex_lock(&buffer->mutex);
}

void cpu_usage_buffer_unlock(Cpu_usage_buffer* buffer)
{
    pthread_mutex_unlock(&buffer->mutex);
}

void cpu_usage_buffer_call_printer(Cpu_usage_buffer* buffer)
{
    pthread_cond_signal(&buffer->can_get);
}

void cpu_usage_buffer_wait_for_analyzer(Cpu_usage_buffer* buffer)
{
    pthread_cond_wait(&buffer->can_get, &buffer->mutex);
}

void cpu_usage_buffer_print(Cpu_usage_buffer* buffer)
{
    // Cpu_usage_buffer_node* curr = buffer->tail;
    // while(curr->next != buffer->tail)
    // {
    //     if(curr==buffer->tail)
    //         printf("[T]");
    //     if(curr==buffer->head)
    //         printf("[H]");
    //     if(curr->cpu_usage_list != NULL)
    //         printf("X");
    //     else
    //         printf("_");
    //     curr = curr->next;
    // }
    //  if(curr==buffer->tail)
    //         printf("[T]");
    //     if(curr==buffer->head)
    //         printf("[H]");
    //     if(curr->cpu_usage_list != NULL)
    //         printf("X");
    //     else
    //         printf("_");
    //     curr = curr->next;
    // printf("\n");
    printf("cpu_usage_buffer: %d/%d\n", buffer->item_count, BUFFER_SIZE);
}
