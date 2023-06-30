#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "buffer_test.h"

int main(void)
{
    buffer_create_test();
    buffer_add_get_test();

    return 0;
}