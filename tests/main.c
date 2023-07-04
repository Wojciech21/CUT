#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "cpu_stat_buffer_test.h"

int main(void)
{
    cpu_stat_buffer_create_test();
    cpu_stat_buffer_add_get_test();

    return 0;
}