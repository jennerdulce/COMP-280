#ifndef CACHE_TRACE_H
#define CACHE_TRACE_H

#include "memory_parameters.h"

// This trace interface is for the CACHE operations to report
// what they are doing.

void cache_hit(address_t addr, int set, int line);
void cache_miss(address_t addr, int set, int line);

#endif