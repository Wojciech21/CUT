#include <stdio.h>
#include <stdlib.h>

#include "cpu_stat_list.h"

struct Cpu_stat_list
{
    struct Cpu_stat_node* head;
    size_t size;
};

typedef struct Cpu_stat_node
{
    unsigned int cpu_num;
    unsigned long user;
    unsigned long nice;
    unsigned long system;
    unsigned long idle;
    unsigned long iowait;
    unsigned long irq;
    unsigned long softirq;
    unsigned long steal;
    struct Cpu_stat_node* next;
} Cpu_stat_node;

Cpu_stat_list* cpu_stat_list_create(void)
{
    Cpu_stat_list* list = malloc(sizeof(Cpu_stat_list));
    if(list == NULL)
    {
        printf("memory allocation for list error");
        return NULL;
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

void cpu_stat_list_add(Cpu_stat_list* const list,
    const unsigned int cpu_num,
    const unsigned long user,
    const unsigned long nice,
    const unsigned long system,
    const unsigned long idle,
    const unsigned long iowait,
    const unsigned long irq,
    const unsigned long softirq,
    const unsigned long steal)
{
    if(list == NULL)
    {
        printf("list is NULL\n");
        return;
    }
    
    Cpu_stat_node* node = calloc(1, sizeof(Cpu_stat_node));
    if(node == NULL)
    {
        printf("memory allocation for list node error");
        return;
    }
    *node = (Cpu_stat_node)
    {
        .cpu_num = cpu_num,
        .user = user,
        .nice = nice,
        .system = system,
        .idle = idle,
        .iowait = iowait,
        .irq = irq,
        .softirq = softirq,
        .steal = steal,
        .next = NULL
    };
    list->size++;

    if(list->head == NULL)
    {
        list->head = node;
        return;
    }
    Cpu_stat_node* temp = list->head;
    while (temp->next!=NULL)
    {
        temp = temp->next;
    }
    temp->next = node;
}


void cpu_stat_list_delete(Cpu_stat_list* list)
{
    if(list == NULL)
    {
       return;
    }
    if(list->head != NULL)
    {
        while(list->head->next != NULL)
        {
            Cpu_stat_node* prev;
            Cpu_stat_node* node = list->head;
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

size_t cpu_stat_list_get_size(Cpu_stat_list* list)
{
    return list->size;
}

unsigned int cpu_stat_list_get_cpu_num(Cpu_stat_list* list, int n)
{
    if(n==0) return list->head->cpu_num;
    Cpu_stat_node* node = list->head;
    for(int i=0; i<n; i++)
    {
        if(node->next == NULL) return -1;
        node = node->next;
    }
    return node->cpu_num;
}

unsigned long cpu_stat_list_get_user(Cpu_stat_list* list, int n)
{
    if(n==0) return list->head->user;
    Cpu_stat_node* node = list->head;
    for(int i=0; i<n; i++)
    {
        if(node->next == NULL) return -1;
        node = node->next;
    }
    return node->user;
}

unsigned long cpu_stat_list_get_nice(Cpu_stat_list* list, int n)
{
    if(n==0) return list->head->nice;
    Cpu_stat_node* node = list->head;
    for(int i=0; i<n; i++)
    {
        if(node->next == NULL) return -1;
        node = node->next;
    }
    return node->nice;
}

unsigned long cpu_stat_list_get_system(Cpu_stat_list* list, int n)
{
    if(n==0) return list->head->system;
    Cpu_stat_node* node = list->head;
    for(int i=0; i<n; i++)
    {
        if(node->next == NULL) return -1;
        node = node->next;
    }
    return node->system;
}

unsigned long cpu_stat_list_get_idle(Cpu_stat_list* list, int n)
{
    if(n==0) return list->head->idle;
    Cpu_stat_node* node = list->head;
    for(int i=0; i<n; i++)
    {
        if(node->next == NULL) return -1;
        node = node->next;
    }
    return node->idle;
}

unsigned long cpu_stat_list_get_iowait(Cpu_stat_list* list, int n)
{
    if(n==0) return list->head->iowait;
    Cpu_stat_node* node = list->head;
    for(int i=0; i<n; i++)
    {
        if(node->next == NULL) return -1;
        node = node->next;
    }
    return node->iowait;
}

unsigned long cpu_stat_list_get_irq(Cpu_stat_list* list, int n)
{
    if(n==0) return list->head->irq;
    Cpu_stat_node* node = list->head;
    for(int i=0; i<n; i++)
    {
        if(node->next == NULL) return -1;
        node = node->next;
    }
    return node->irq;
}

unsigned long cpu_stat_list_get_softirq(Cpu_stat_list* list, int n)
{
    if(n==0) return list->head->softirq;
    Cpu_stat_node* node = list->head;
    for(int i=0; i<n; i++)
    {
        if(node->next == NULL) return -1;
        node = node->next;
    }
    return node->softirq;
}

unsigned long cpu_stat_list_get_steal(Cpu_stat_list* list, int n)
{
    if(n==0) return list->head->steal;
    Cpu_stat_node* node = list->head;
    for(int i=0; i<n; i++)
    {
        if(node->next == NULL) return -1;
        node = node->next;
    }
    return node->steal;
}


void cpu_stat_list_print(Cpu_stat_list* list)
{
    Cpu_stat_node* node = list->head;
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
        node->softirq, 
        node->steal);
        node = node->next;
    }
}