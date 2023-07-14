#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "../analyzer.h"

void analyzer_test()
{
    double eps = 0.001;
    #undef STAT_BUFFER_SIZE
    #define STAT_BUFFER_SIZE 2
    assert(STAT_BUFFER_SIZE==2);
    Cpu_stat_buffer* cpu_stat_buffer = cpu_stat_buffer_create();
    Cpu_stat_list* cpu_stat_list = cpu_stat_list_create();
    cpu_stat_list_add(cpu_stat_list, 1, 91, 25, 47, 31, 10, 40, 98, 90);
    cpu_stat_list_add(cpu_stat_list, 2, 0, 18, 92, 7, 67, 51, 23, 65);
    cpu_stat_buffer_add_list(cpu_stat_buffer, cpu_stat_list);
    cpu_stat_list = cpu_stat_list_create();
    cpu_stat_list_add(cpu_stat_list, 1, 426, 384, 321, 448, 369, 273, 152, 787);
    cpu_stat_list_add(cpu_stat_list, 2, 0, 18, 92, 7, 67, 51, 23, 65);
    cpu_stat_buffer_add_list(cpu_stat_buffer, cpu_stat_list);
    cpu_stat_list = cpu_stat_list_create();
    cpu_stat_list_add(cpu_stat_list, 1, 3743, 2096, 4480, 2639, 1966, 2844, 4663, 2316);
    cpu_stat_list_add(cpu_stat_list, 2, 10, 18, 92, 7, 67, 51, 23, 65);
    cpu_stat_buffer_add_list(cpu_stat_buffer, cpu_stat_list);
    cpu_stat_list = cpu_stat_list_create();
    cpu_stat_list_add(cpu_stat_list, 1, 3744, 2097, 4481, 2640, 1967, 2845, 4664, 2317);
    cpu_stat_list_add(cpu_stat_list, 2, 10, 18, 92, 70, 67, 51, 23, 65);
    cpu_stat_buffer_add_list(cpu_stat_buffer, cpu_stat_list);
    
    Cpu_usage_buffer* cpu_usage_buffer = cpu_usage_buffer_create();
    
    analyze_data(cpu_stat_buffer, cpu_usage_buffer);
    analyze_data(cpu_stat_buffer, cpu_usage_buffer);
    analyze_data(cpu_stat_buffer, cpu_usage_buffer);

    Cpu_usage_list* cpu_usage_list = cpu_usage_buffer_get_list(cpu_usage_buffer);
    assert(cpu_usage_list_get_size(cpu_usage_list)==2);
    assert(cpu_usage_list_get_cpu_num(cpu_usage_list, 0)==1);
    // printf("%f\n", fabs(cpu_usage_list_get_percent(cpu_usage_list, 0)-71.554));
    assert(fabs(cpu_usage_list_get_percent(cpu_usage_list, 0)-71.554)<=eps);
    assert(cpu_usage_list_get_cpu_num(cpu_usage_list, 1)==2);
    assert(fabs(cpu_usage_list_get_percent(cpu_usage_list, 1)-0)<=eps);
    cpu_usage_list = cpu_usage_buffer_get_list(cpu_usage_buffer);
    assert(cpu_usage_list_get_size(cpu_usage_list)==2);
    assert(cpu_usage_list_get_cpu_num(cpu_usage_list, 0)==1);
    assert(fabs(cpu_usage_list_get_percent(cpu_usage_list, 0)-82.452)<=eps);
    assert(cpu_usage_list_get_cpu_num(cpu_usage_list, 1)==2);
    assert(fabs(cpu_usage_list_get_percent(cpu_usage_list, 1)-100)<=eps);
    cpu_usage_list = cpu_usage_buffer_get_list(cpu_usage_buffer);
    assert(cpu_usage_list_get_size(cpu_usage_list)==2);
    assert(cpu_usage_list_get_cpu_num(cpu_usage_list, 0)==1);
    assert(fabs(cpu_usage_list_get_percent(cpu_usage_list, 0)-75.00)<=eps);
    assert(cpu_usage_list_get_cpu_num(cpu_usage_list, 1)==2);
    assert(fabs(cpu_usage_list_get_percent(cpu_usage_list, 1)-0)<=eps);


    printf("analyzer read test done\n");
}