#ifndef READER_H
#define READER_H

#include <pthread.h>

void reader_createThread(void);
void* reader_read(void* param);

#endif