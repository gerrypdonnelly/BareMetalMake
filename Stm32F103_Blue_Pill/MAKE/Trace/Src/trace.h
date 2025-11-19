#ifndef TRACE_H
#define TRACE_H

#include <stdint.h>
#include <stdarg.h>

void trace_init(void);
void printg(const char *fmt, ...);

#endif
