#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include "cpu_stat_buffer.h"


#define BUFFER_SIZE 20

typedef struct Cpu_stat_buffer_node
{
    struct Cpu_stat_buffer_node* next;
    Cpu_stat_list* cpu_stat_list;

} Cpu_stat_buffer_node;

struct Cpu_stat_buffer
{
    Cpu_stat_buffer_node* head;
    Cpu_stat_buffer_node* tail; 
    int item_count;
    pthread_mutex_t mutex;
    pthread_cond_t can_get;
};

Cpu_stat_buffer* cpu_stat_buffer_create(void)
{
    Cpu_stat_buffer* buffer = calloc(1, sizeof(*buffer));
    if(buffer == NULL)
    {
        printf("buffer memory allocation error\n");
        return NULL;
    }
    Cpu_stat_buffer_node* first_node = calloc(1, sizeof(*first_node));
    if(first_node == NULL)
    {
        printf("buffer node memory allocation error\n");
        return NULL;
    }
    *buffer = (Cpu_stat_buffer)
    {
        .head = first_node,   
        .tail = first_node,
        .item_count = 0, 
        .mutex = PTHREAD_MUTEX_INITIALIZER,
        .can_get = PTHREAD_COND_INITIALIZER
    };

    Cpu_stat_buffer_node* temp = first_node;
    for(int i=0; i<BUFFER_SIZE-1; i++)
    {
        temp->cpu_stat_list = NULL;
        temp->next = calloc(1, sizeof(Cpu_stat_buffer_node));
        if(temp->next == NULL)
        {
            printf("buffer node memory allocation error\n");
            return NULL;
        }
        temp = temp->next;
    }
    temp->cpu_stat_list = NULL;
    temp->next = first_node;

    return buffer;
}

void cpu_stat_buffer_add_list(Cpu_stat_buffer* buffer, Cpu_stat_list* list)
{
    if(buffer == NULL) return;
    if(list == NULL) return;
    
    cpu_stat_list_delete(buffer->head->cpu_stat_list);
    buffer->head->cpu_stat_list = list;
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

Cpu_stat_list** cpu_stat_buffer_get_lists(Cpu_stat_buffer* buffer)
{
    Cpu_stat_list** list_array = malloc(2*sizeof(Cpu_stat_list*));
    list_array[0] = buffer->tail->cpu_stat_list;
    list_array[1] = buffer->tail->next->cpu_stat_list;
    buffer->tail->cpu_stat_list = NULL;
    buffer->tail = buffer->tail->next;
    buffer->item_count--;
    return list_array;
}

void cpu_stat_buffer_delete(Cpu_stat_buffer* buffer)
{
    if(buffer == NULL)
    {
        return;
    }
    Cpu_stat_buffer_node* curr = buffer->head;
    Cpu_stat_buffer_node* next = curr->next;
    curr->next = NULL;
    while (next != NULL)
    {
        curr = next;
        next = curr->next;
        cpu_stat_list_delete(curr->cpu_stat_list);
        free(curr);
    }
    pthread_mutex_destroy(&buffer->mutex);
    pthread_cond_destroy(&buffer->can_get);
    free(buffer);
}

bool cpu_stat_buffer_is_empty(Cpu_stat_buffer* buffer)
{
    return buffer->item_count<=1;
}



void cpu_stat_buffer_lock(Cpu_stat_buffer* buffer)
{
    pthread_mutex_lock(&buffer->mutex);
}

void cpu_stat_buffer_unlock(Cpu_stat_buffer* buffer)
{
    pthread_mutex_unlock(&buffer->mutex);
}

void cpu_stat_buffer_call_analyzer(Cpu_stat_buffer* buffer)
{
    if(buffer->item_count>=2)
        pthread_cond_signal(&buffer->can_get);
}

void cpu_stat_buffer_wait_for_reader(Cpu_stat_buffer* buffer)
{
    pthread_cond_wait(&buffer->can_get, &buffer->mutex);
}

void cpu_stat_buffer_print(Cpu_stat_buffer* buffer)
{
    // Cpu_stat_buffer_node* curr = buffer->tail;
    // while(curr->next != buffer->tail)
    // {
    //     if(curr==buffer->tail)
    //         printf("[T]");
    //     if(curr==buffer->head)
    //         printf("[H]");
    //     if(curr->cpu_stat_list != NULL)
    //         printf("X");
    //     else
    //         printf("_");
    //     curr = curr->next;
    // }
    //  if(curr==buffer->tail)
    //         printf("[T]");
    //     if(curr==buffer->head)
    //         printf("[H]");
    //     if(curr->cpu_stat_list != NULL)
    //         printf("X");
    //     else
    //         printf("_");
    //     curr = curr->next;
    // printf("\n");
    printf("cpu_stat_buffer: %d/%d\n", buffer->item_count, BUFFER_SIZE);

}