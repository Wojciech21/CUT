#include "../analyzer.h"

void analyzer_read_test()
{
    Cpu_stat_buffer* buffer = buffer_create();
    
    Cpu_stat_list* list1 = cpu_stat_list_create();
    // cpu_stat_list_add(list1, );
    cpu_stat_buffer_add_list(buffer, list1);
    Cpu_stat_list* list2 = cpu_stat_list_create();
    // cpu_stat_list_add(list2, );
    cpu_stat_buffer_add_list(buffer, list2);
    Cpu_stat_list* list3 = cpu_stat_list_create();
    cpu_stat_list_add(list3, );
    buffer_add_list(buffer, list3);

    analyzer_init(buffer1);



    analyzer_join();

    cpu_stat_buffer_delete(buffer1);
    return 0; 

}