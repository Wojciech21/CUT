#ifndef PRINTER_H
#define PRINTER_H

#include "cpu_usage_buffer.h"

void printer_init(Cpu_usage_buffer* buffer);
void printer_join();

#endif