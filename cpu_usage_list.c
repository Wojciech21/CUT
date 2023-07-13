#include <stdio.h>
#include <stdlib.h>

#include "cpu_usage_list.h"

struct Cpu_usage_list
{
    struct Cpu_usage_node* head;
    size_t size;
};

typedef struct Cpu_usage_node
{
    struct Cpu_usage_node* next;
    double percent;
    int cpu_num;
    char padding[4];
} Cpu_usage_node;

Cpu_usage_list* cpu_usage_list_create(void)
{
    Cpu_usage_list* list = malloc(sizeof(Cpu_usage_list));
    if(list == NULL)
    {
        printf("memory allocation for list error");
        return NULL;
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

void cpu_usage_list_add(Cpu_usage_list* const list, const int cpu_num, const double percent)
{
    if(list == NULL)
    {
        printf("list is NULL\n");
        return;
    }
    
    Cpu_usage_node* node = calloc(1, sizeof(Cpu_usage_node));
    if(node == NULL)
    {
        printf("memory allocation for list node error");
        return;
    }
    *node = (Cpu_usage_node)
    {
        .cpu_num = cpu_num,
        .percent = percent,
        .next = NULL
    };
    list->size++;

    if(list->head == NULL)
    {
        list->head = node;
        return;
    }
    Cpu_usage_node* temp = list->head;
    while (temp->next!=NULL)
    {
        temp = temp->next;
    }
    temp->next = node;
}


void cpu_usage_list_delete(Cpu_usage_list* list)
{
    if(list == NULL)
    {
       return;
    }
    if(list->head != NULL)
    {
        while(list->head->next != NULL)
        {
            Cpu_usage_node* prev = NULL;
            Cpu_usage_node* node = list->head;
            while(node->next != NULL)
            {
                prev = node;
                node = node->next;
            }
            prev->next=NULL;
            free(node);
        }
    }
    free(list->head);
    free(list);
}

size_t cpu_usage_list_get_size(Cpu_usage_list* list)
{
    return list->size;
}

int cpu_usage_list_get_cpu_num(Cpu_usage_list* list, size_t n)
{
    if(n==0) return list->head->cpu_num;
    Cpu_usage_node* node = list->head;
    for(size_t i=0; i<n; i++)
    {
        if(node->next == NULL) return -1;
        node = node->next;
    }
    return node->cpu_num;
}

double cpu_usage_list_get_percent(Cpu_usage_list* list, size_t n)
{
    if(n==0) return list->head->percent;
    Cpu_usage_node* node = list->head;
    for(size_t i=0; i<n; i++)
    {
        if(node->next == NULL) return -1;
        node = node->next;
    }
    return node->percent;
}

void cpu_usage_list_print(Cpu_usage_list* list)
{
    Cpu_usage_node* node = list->head;
    while(node!=NULL)
    {
        printf("cpu %d: %.3f\n",
        node->cpu_num, 
        node->percent);
        node = node->next;
    }
}
