#include <stdio.h>
#include <stdlib.h>

#include "cpu_list.h"

struct cpu_list
{
    struct cpu_node* head;
};

typedef struct cpu_node
{
    unsigned int cpu_num;
    unsigned long user;
    unsigned long nice;
    unsigned long system;
    unsigned long idle;
    unsigned long iowait;
    unsigned long irq;
    unsigned long softirg;
    unsigned long steal;
    struct cpu_node* next;
} Cpu_node;

Cpu_list* create_list(void)
{
    Cpu_list* list = malloc(sizeof(Cpu_list));
    if(list == NULL)
    {
        printf("memory allocation for list error");
        return NULL;
    }
    list->head = NULL;
    return list;
}

void add_to_list(Cpu_list* const list,
    const unsigned int cpu_num,
    const unsigned long user,
    const unsigned long nice,
    const unsigned long system,
    const unsigned long idle,
    const unsigned long iowait,
    const unsigned long irq,
    const unsigned long softirg,
    const unsigned long steal)
{
    if(list == NULL)
    {
        printf("list is NULL\n");
        return;
    }
    
    Cpu_node* node = calloc(1, sizeof(Cpu_node));
    if(node == NULL)
    {
        printf("memory allocation for list node error");
        return;
    }
    *node = (Cpu_node)
    {
        .cpu_num = cpu_num,
        .user = user,
        .nice = nice,
        .system = system,
        .idle = idle,
        .iowait = iowait,
        .irq = irq,
        .softirg = softirg,
        .steal = steal,
        .next = NULL
    };

    if(list->head == NULL)
    {
        list->head = node;
        return;
    }
    Cpu_node* temp = list->head;
    while (temp->next!=NULL)
    {
        temp = temp->next;
    }
    temp->next = node;
}

void print_list(Cpu_list* list)
{
    Cpu_node* node = list->head;
    while(node!=NULL)
    {
        printf("cpu%d: %lu %lu %lu %lu %lu %lu %lu %lu\n",
        node->cpu_num, 
        node->user, 
        node->nice, 
        node->system, 
        node->idle, 
        node->iowait, 
        node->irq, 
        node->softirg, 
        node->steal);
        node = node->next;
    }
}

void delete_list(Cpu_list* list)
{
    if(list == NULL)
    {
        return;
    }
    while(list->head->next != NULL)
    {
        Cpu_node* prev;
        Cpu_node* node = list->head;
        while(node->next != NULL)
        {
            prev = node;
            node = node->next;
        }
        prev->next=NULL;
        free(node);
    }
    free(list->head);
    free(list);
}