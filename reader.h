#ifndef READER_H
#define READER_H

#include "cpu_stat_buffer.h"

int reader_init(Cpu_stat_buffer* buffer);
int reader_join(void);

#endif
