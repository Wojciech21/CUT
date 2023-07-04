#ifndef READER_H
#define READER_H

#include "cpu_stat_buffer.h"

void reader_init(Cpu_stat_buffer* buffer);
void reader_join();

#endif