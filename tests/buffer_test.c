#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "buffer_test.h"
#include "../buffer.h"
#include "../cpu_list.h"

void buffer_create_test(void)
{
	int size = 10;
	Buffer* buffer[size];
    
	for(int i=0; i<size; i++)
	{
		buffer[i] = buffer_create();
	}
	for(int i=0; i<size; i++)
	{
		buffer_delete(buffer[i]);
	}

	for(int i=0; i<size; i++)
	{
		buffer_delete(NULL);
	}

	printf("buffer create test completed\n");
}

void buffer_add_get_test(void)
{
	Buffer* buffer = buffer_create();
	Cpu_list* list = cpu_list_create();
	Cpu_list* list2 = cpu_list_create();
    cpu_list_add(list, 1,2,3,4,5,6,7,8,9);
    cpu_list_add(list, 10,20,30,40,50,60,70,80,90);
    cpu_list_add(list2, 11,12,13,14,15,16,17,18,19);
	buffer_add_list(buffer, list);
	buffer_add_list(buffer, list2);
	buffer_add_list(NULL, list);
	buffer_add_list(buffer, NULL);
	buffer_add_list(NULL, NULL);
    
    Cpu_list* get_list_1 = buffer_get_list(buffer);
    Cpu_list* get_list_2 = buffer_get_list(buffer);
	buffer_delete(buffer);

    assert(cpu_list_get_size(get_list_1)==2);
    assert(cpu_list_get_cpu_num(get_list_1)==1);
    assert(cpu_list_get_user(get_list_1)==2);
    assert(cpu_list_get_nice(get_list_1)==3);
    assert(cpu_list_get_system(get_list_1)==4);
    assert(cpu_list_get_idle(get_list_1)==5);
    assert(cpu_list_get_iowait(get_list_1)==6);
    assert(cpu_list_get_irq(get_list_1)==7);
    assert(cpu_list_get_softirq(get_list_1)==8);
    assert(cpu_list_get_steal(get_list_1)==9);
    
    cpu_list_next(get_list_1);
    
    assert(cpu_list_get_size(get_list_1)==1);
    assert(cpu_list_get_cpu_num(get_list_1)==10);
    assert(cpu_list_get_user(get_list_1)==20);
    assert(cpu_list_get_nice(get_list_1)==30);
    assert(cpu_list_get_system(get_list_1)==40);
    assert(cpu_list_get_idle(get_list_1)==50);
    assert(cpu_list_get_iowait(get_list_1)==60);
    assert(cpu_list_get_irq(get_list_1)==70);
    assert(cpu_list_get_softirq(get_list_1)==80);
    assert(cpu_list_get_steal(get_list_1)==90);

    cpu_list_next(get_list_1);
    assert(cpu_list_get_size(get_list_1)==0);
    cpu_list_next(get_list_1);
    cpu_list_next(get_list_1);
    assert(cpu_list_get_size(get_list_1)==0);

    assert(cpu_list_get_size(get_list_2)==1);
    assert(cpu_list_get_cpu_num(get_list_2)==11);
    assert(cpu_list_get_user(get_list_2)==12);
    assert(cpu_list_get_nice(get_list_2)==13);
    assert(cpu_list_get_system(get_list_2)==14);
    assert(cpu_list_get_idle(get_list_2)==15);
    assert(cpu_list_get_iowait(get_list_2)==16);
    assert(cpu_list_get_irq(get_list_2)==17);
    assert(cpu_list_get_softirq(get_list_2)==18);
    assert(cpu_list_get_steal(get_list_2)==19);

    cpu_list_delete(get_list_1);
    cpu_list_delete(get_list_2);

    printf("buffer add and get test completed\n");
}