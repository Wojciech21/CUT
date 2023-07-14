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
    long user;
    long nice;
    long system;
    long idle;
    long iowait;
    long irq;
    long softirq;
    long steal;
    int cpu_num;
    char allign[4];
    struct Cpu_stat_node* next;
} Cpu_stat_node;

Cpu_stat_list* cpu_stat_list_create(void)
{
    Cpu_stat_list* list = calloc(1, sizeof(Cpu_stat_list));
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
    const int cpu_num,
    const long user,
    const long nice,
    const long system,
    const long idle,
    const long iowait,
    const long irq,
    const long softirq,
    const long steal)
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
            Cpu_stat_node* prev = NULL;
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
    if(list == NULL) return 0;

    return list->size;
    
}
int cpu_stat_list_get_cpu_num(Cpu_stat_list* list, size_t n)
{
    if(n==0) return list->head->cpu_num;
    Cpu_stat_node* node = list->head;
    for(size_t i=0; i<n; i++)
    {
        if(node->next == NULL) return -1;
        node = node->next;
    }
    return node->cpu_num;
}

long cpu_stat_list_get_user(Cpu_stat_list* list, size_t n)
{
    if(n==0) return list->head->user;
    Cpu_stat_node* node = list->head;
    for(size_t i=0; i<n; i++)
    {
        if(node->next == NULL) return -1;
        node = node->next;
    }
    return node->user;
}

long cpu_stat_list_get_nice(Cpu_stat_list* list, size_t n)
{
    if(n==0) return list->head->nice;
    Cpu_stat_node* node = list->head;
    for(size_t i=0; i<n; i++)
    {
        if(node->next == NULL) return -1;
        node = node->next;
    }
    return node->nice;
}

long cpu_stat_list_get_system(Cpu_stat_list* list, size_t n)
{
    if(n==0) return list->head->system;
    Cpu_stat_node* node = list->head;
    for(size_t i=0; i<n; i++)
    {
        if(node->next == NULL) return -1;
        node = node->next;
    }
    return node->system;
}

long cpu_stat_list_get_idle(Cpu_stat_list* list, size_t n)
{
    if(n==0) return list->head->idle;
    Cpu_stat_node* node = list->head;
    for(size_t i=0; i<n; i++)
    {
        if(node->next == NULL) return -1;
        node = node->next;
    }
    return node->idle;
}

long cpu_stat_list_get_iowait(Cpu_stat_list* list, size_t n)
{
    if(n==0) return list->head->iowait;
    Cpu_stat_node* node = list->head;
    for(size_t i=0; i<n; i++)
    {
        if(node->next == NULL) return -1;
        node = node->next;
    }
    return node->iowait;
}

long cpu_stat_list_get_irq(Cpu_stat_list* list, size_t n)
{
    if(n==0) return list->head->irq;
    Cpu_stat_node* node = list->head;
    for(size_t i=0; i<n; i++)
    {
        if(node->next == NULL) return -1;
        node = node->next;
    }
    return node->irq;
}

long cpu_stat_list_get_softirq(Cpu_stat_list* list, size_t n)
{
    if(n==0) return list->head->softirq;
    Cpu_stat_node* node = list->head;
    for(size_t i=0; i<n; i++)
    {
        if(node->next == NULL) return -1;
        node = node->next;
    }
    return node->softirq;
}

long cpu_stat_list_get_steal(Cpu_stat_list* list, size_t n)
{
    if(n==0) return list->head->steal;
    Cpu_stat_node* node = list->head;
    for(size_t i=0; i<n; i++)
    {
        if(node->next == NULL) return -1;
        node = node->next;
    }
    return node->steal;
}
