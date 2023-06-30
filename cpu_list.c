#include <stdio.h>
#include <stdlib.h>

#include "cpu_list.h"

struct cpu_list
{
    struct cpu_node* head;
    size_t size;
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
    unsigned long softirq;
    unsigned long steal;
    struct cpu_node* next;
} Cpu_node;

Cpu_list* cpu_list_create(void)
{
    Cpu_list* list = malloc(sizeof(Cpu_list));
    if(list == NULL)
    {
        printf("memory allocation for list error");
        return NULL;
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

void cpu_list_add(Cpu_list* const list,
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
    Cpu_node* temp = list->head;
    while (temp->next!=NULL)
    {
        temp = temp->next;
    }
    temp->next = node;
}

void cpu_list_print(Cpu_list* list)
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
        node->softirq, 
        node->steal);
        node = node->next;
    }
}

void cpu_list_delete(Cpu_list* list)
{
    if(list == NULL)
    {
       return;
    }
    if(list->head != NULL)
    {
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
    }
    free(list->head);
    free(list);
}

size_t cpu_list_get_size(Cpu_list* list)
{
    return list->size;
}

int cpu_list_get_cpu_num(Cpu_list* list)
{
    return list->head->cpu_num;
}

long cpu_list_get_user(Cpu_list* list)
{
    return list->head->user;
}

long cpu_list_get_nice(Cpu_list* list)
{
    return list->head->nice;
}

long cpu_list_get_system(Cpu_list* list)
{
    return list->head->system;
}

long cpu_list_get_idle(Cpu_list* list)
{
    return list->head->idle;
}

long cpu_list_get_iowait(Cpu_list* list)
{
    return list->head->iowait;
}

long cpu_list_get_irq(Cpu_list* list)
{
    return list->head->irq;
}

long cpu_list_get_softirq(Cpu_list* list)
{
    return list->head->softirq;
}

long cpu_list_get_steal(Cpu_list* list)
{
    return list->head->steal;
}

void cpu_list_next(Cpu_list* list)
{
    if(list == NULL) return;
    if(list->head == NULL) return;
    Cpu_node* next = list->head->next;
    free(list->head);
    list->head = next;
    list->size--;
}
