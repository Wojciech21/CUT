#include <stdio.h>
#include <stdlib.h>

#include "reader.h"
#include "buffer.h"
#include "sigterm.h"

int main(void)
{
    sigterm_init();
    Buffer* buffer1 = buffer_create();

    reader_init(buffer1);

    buffer_delete(buffer1);
    return 0;
}