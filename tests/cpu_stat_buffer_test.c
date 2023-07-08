#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "cpu_stat_buffer_test.h"
#include "../cpu_stat_buffer.h"
#include "../cpu_stat_list.h"

void cpu_stat_buffer_create_test(void)
{
	int size = 10;
	Cpu_stat_buffer* buffer[size];
    
	for(int i=0; i<size; i++)
	{
		buffer[i] = cpu_stat_buffer_create();
	}
	for(int i=0; i<size; i++)
	{
		cpu_stat_buffer_delete(buffer[i]);
	}

	for(int i=0; i<size; i++)
	{
		cpu_stat_buffer_delete(NULL);
	}

	printf("buffer create test completed\n");
}

void cpu_stat_buffer_add_get_test(void)
{
	Cpu_stat_buffer* buffer = cpu_stat_buffer_create();


	Cpu_stat_list* list = cpu_stat_list_create();
    cpu_stat_list_add(list, 1,2,3,4,5,6,7,8,9);
    cpu_stat_list_add(list, 10,20,30,40,50,60,70,80,90);
	cpu_stat_buffer_add_list(buffer, list); 

	Cpu_stat_list* list2 = cpu_stat_list_create();
    cpu_stat_list_add(list2, 11,12,13,14,15,16,17,18,19);
	cpu_stat_buffer_add_list(buffer, list2);

	cpu_stat_buffer_add_list(NULL, list);
	cpu_stat_buffer_add_list(buffer, NULL);
	cpu_stat_buffer_add_list(NULL, NULL);
    // // cpu_stat_list_delete(list1);
    // // cpu_stat_list_delete(list2);
    

    Cpu_stat_list** lists = cpu_stat_buffer_get_lists(buffer);
    Cpu_stat_list* get_list_1 = lists[0];
    Cpu_stat_list* get_list_2 = lists[1];
    free(lists);
    

    assert(get_list_1!=NULL);
    assert(cpu_stat_list_get_size(get_list_1)==2);
    assert(cpu_stat_list_get_cpu_num(get_list_1, 0)==1);
    assert(cpu_stat_list_get_user(get_list_1, 0)==2);
    assert(cpu_stat_list_get_nice(get_list_1, 0)==3);
    assert(cpu_stat_list_get_system(get_list_1, 0)==4);
    assert(cpu_stat_list_get_idle(get_list_1, 0)==5);
    assert(cpu_stat_list_get_iowait(get_list_1, 0)==6);
    assert(cpu_stat_list_get_irq(get_list_1, 0)==7);
    assert(cpu_stat_list_get_softirq(get_list_1, 0)==8);
    assert(cpu_stat_list_get_steal(get_list_1, 0)==9);
    
    assert(get_list_1!=NULL);
    assert(cpu_stat_list_get_size(get_list_1)==2);
    assert(cpu_stat_list_get_cpu_num(get_list_1, 1)==10);
    assert(cpu_stat_list_get_user(get_list_1, 1)==20);
    assert(cpu_stat_list_get_nice(get_list_1, 1)==30);
    assert(cpu_stat_list_get_system(get_list_1, 1)==40);
    assert(cpu_stat_list_get_idle(get_list_1, 1)==50);
    assert(cpu_stat_list_get_iowait(get_list_1, 1)==60);
    assert(cpu_stat_list_get_irq(get_list_1, 1)==70);
    assert(cpu_stat_list_get_softirq(get_list_1, 1)==80);
    assert(cpu_stat_list_get_steal(get_list_1, 1)==90);
    cpu_stat_list_delete(get_list_1);

    assert(get_list_2!=NULL);
    assert(cpu_stat_list_get_size(get_list_2)==1);
    assert(cpu_stat_list_get_cpu_num(get_list_2, 0)==11);
    assert(cpu_stat_list_get_user(get_list_2, 0)==12);
    assert(cpu_stat_list_get_nice(get_list_2, 0)==13);
    assert(cpu_stat_list_get_system(get_list_2, 0)==14);
    assert(cpu_stat_list_get_idle(get_list_2, 0)==15);
    assert(cpu_stat_list_get_iowait(get_list_2, 0)==16);
    assert(cpu_stat_list_get_irq(get_list_2, 0)==17);
    assert(cpu_stat_list_get_softirq(get_list_2, 0)==18);
    assert(cpu_stat_list_get_steal(get_list_2, 0)==19);

    cpu_stat_buffer_delete(buffer);
    printf("buffer add and get test completed\n");
}