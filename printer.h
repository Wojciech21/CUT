#ifndef PRINTER_H
#define PRINTER_H

#include "cpu_usage_buffer.h"

int printer_init(Cpu_usage_buffer* buffer);
int printer_join(void);

#endif
