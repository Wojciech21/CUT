#ifndef BUFFER_H
#define BUFFER_H

#include "cpu_list.h"

typedef struct buffer Buffer;

Buffer* buffer_create(void);
void buffer_delete(Buffer* buffer);
void buffer_add_list(Buffer* buffer, Cpu_list* list);



void buffer_print(Buffer* buffer);

#endif