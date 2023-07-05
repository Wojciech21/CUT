#include <stdio.h>
#include <assert.h>

#include "../analyzer.h"

void analyzer_read_test()
{
    Cpu_stat_buffer* buffer1 = cpu_stat_buffer_create();
    Cpu_usage_buffer* buffer2 = cpu_usage_buffer_create();
    
    Cpu_stat_list* list1 = cpu_stat_list_create();
    cpu_stat_list_add(list1, 1, 10, 10, 10, 10, 10, 10, 10, 10);
    cpu_stat_list_add(list1, 2, 50, 100, 100, 100, 50, 50, 100, 100);
    cpu_stat_buffer_add_list(buffer1, list1);

    Cpu_stat_list* list2 = cpu_stat_list_create();
    cpu_stat_list_add(list2, 1, 20, 20, 20, 20, 20, 20, 20, 20);
    cpu_stat_list_add(list2, 2, 150, 200, 150, 150, 150, 200, 200, 200);
    cpu_stat_buffer_add_list(buffer1, list2);

    Cpu_stat_list* list3 = cpu_stat_list_create();
    cpu_stat_list_add(list3, 1, 30, 30, 30, 30, 30, 30, 30, 30);
    cpu_stat_list_add(list3, 2, 300, 300, 300, 300, 300, 300, 300, 300);
    cpu_stat_buffer_add_list(buffer1, list3);

    Cpu_stat_list* list4 = cpu_stat_list_create();
    cpu_stat_list_add(list4, 1, 40, 40, 40, 40, 40, 40, 40, 40);
    cpu_stat_list_add(list4, 2, 375, 375, 400, 350, 350, 475, 450, 425);
    cpu_stat_buffer_add_list(buffer1, list4);

    analyzer_init(buffer1, buffer2);
    // cpu_stat_list_delete(list1);
    // cpu_stat_list_delete(list2);
    // cpu_stat_list_delete(list3);
    // cpu_stat_list_delete(list4);
    analyzer_join();

    Cpu_usage_list* get_list1 = cpu_usage_buffer_get_list(buffer2);
    Cpu_usage_list* get_list2 = cpu_usage_buffer_get_list(buffer2);
    Cpu_usage_list* get_list3 = cpu_usage_buffer_get_list(buffer2);
    Cpu_usage_list* get_list4 = cpu_usage_buffer_get_list(buffer2);

    assert(cpu_usage_list_get_size(get_list1) == 2);
    assert(cpu_usage_list_get_size(get_list2) == 2);
    assert(cpu_usage_list_get_size(get_list3) == 2);
    assert(get_list4 == NULL);

    assert(cpu_usage_list_get_cpu_num(get_list1, 0) == 1);
    assert(cpu_usage_list_get_percent(get_list1, 0) == 75);
    assert(cpu_usage_list_get_cpu_num(get_list2, 0) == 1);
    assert(cpu_usage_list_get_percent(get_list2, 0) == 75);
    assert(cpu_usage_list_get_cpu_num(get_list3, 0) == 1);
    assert(cpu_usage_list_get_percent(get_list3, 0) == 75);

    assert(cpu_usage_list_get_cpu_num(get_list1, 1) == 2);
    assert(cpu_usage_list_get_percent(get_list1, 1) == 80);
    assert(cpu_usage_list_get_cpu_num(get_list2, 1) == 2);
    assert(cpu_usage_list_get_percent(get_list2, 1) == 70);
    assert(cpu_usage_list_get_cpu_num(get_list3, 1) == 2);
    assert(cpu_usage_list_get_percent(get_list3, 1) == 87.5);

    cpu_usage_list_delete(get_list1);
    cpu_usage_list_delete(get_list2);
    cpu_usage_list_delete(get_list3);
    cpu_usage_list_delete(get_list4);

    cpu_stat_buffer_delete(buffer1);
    cpu_usage_buffer_delete(buffer2);
    printf("analyzer read test done\n");
}