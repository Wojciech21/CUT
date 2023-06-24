#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "reader.h"
#include "analyzer.h"
#include "buffer.h"
#include "sigterm.h"

int main(void)
{
    sigterm_init();
    Buffer* buffer1 = buffer_create();
    
    reader_init(buffer1);
    analyzer_init(buffer1);

    reader_join();
    analyzer_join();

    buffer_delete(buffer1);
    return 0;
}