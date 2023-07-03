#include <stdlib.h>
#include <stdio.h>

#include "buffer.h"


#define BUFFER_SIZE 20

typedef struct buffer_node
{
    struct buffer_node* next;
    Cpu_list* cpu_list;

} Buffer_node;

struct buffer
{
    Buffer_node* head;
    Buffer_node* tail; 
};

Buffer* buffer_create(void)
{
    Buffer* buffer = malloc(sizeof(*buffer));
    if(buffer == NULL)
    {
        printf("buffer memory allocation error\n");
        return NULL;
    }
    Buffer_node* first_node = malloc(sizeof(*first_node));
    if(first_node == NULL)
    {
        printf("buffer node memory allocation error\n");
        return NULL;
    }
    

    Buffer_node* temp = first_node;
    for(int i=0; i<BUFFER_SIZE-1; i++)
    {
        temp->cpu_list = NULL;
        temp->next = malloc(sizeof(Buffer_node));
        if(temp->next == NULL)
        {
            printf("buffer node memory allocation error\n");
            return NULL;
        }
        temp = temp->next;
    }
    temp->cpu_list = NULL;
    temp->next = first_node;

    buffer->tail = first_node;
    buffer->head = first_node;
    return buffer;
}

void buffer_add_list(Buffer* buffer, Cpu_list* list)
{
    if(buffer == NULL) return;
    if(list == NULL) return;

    cpu_list_delete(buffer->head->cpu_list);
    buffer->head->cpu_list = list;
    buffer->head = buffer->head->next;
    if(buffer->head == buffer->tail)
    {
        buffer->tail = buffer->tail->next;
    }
}

Cpu_list** buffer_get_lists(Buffer* buffer)
{
    Cpu_list** list_array = malloc(2*sizeof(Cpu_list*));
    list_array[0] = buffer->tail->cpu_list;
    list_array[1] = buffer->tail->next->cpu_list;
    buffer->tail->cpu_list = NULL;
    buffer->tail = buffer->tail->next;
    return list_array;
}

void buffer_print(Buffer* buffer)
{
    Buffer_node* curr = buffer->tail;
    while(curr->next != buffer->tail)
    {
        if(curr==buffer->tail)
            printf("[T]");
        if(curr==buffer->head)
            printf("[H]");
        if(curr->cpu_list != NULL)
            printf("X");
        else
            printf("_");
        curr = curr->next;
    }
     if(curr==buffer->tail)
            printf("[T]");
        if(curr==buffer->head)
            printf("[H]");
        if(curr->cpu_list != NULL)
            printf("X");
        else
            printf("_");
        curr = curr->next;
    printf("\n");
}

void buffer_delete(Buffer* buffer)
{
    if(buffer == NULL)
    {
        return;
    }
    Buffer_node* curr = buffer->head;
    Buffer_node* next = curr->next;
    curr->next = NULL;
    while (next != NULL)
    {
        curr = next;
        next = curr->next;
        cpu_list_delete(curr->cpu_list);
        free(curr);
    }
    

    free(buffer);
}