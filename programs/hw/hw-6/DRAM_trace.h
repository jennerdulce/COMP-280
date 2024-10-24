#ifndef DRAM_TRACE_H
#define DRAM_TRACE_H

#include "memory_parameters.h"

// This trace interface is for the DRAM operations to report
// what they are doing.

// word oriented interface to memory
void trace_read_word(address_t addr, word_t value);
void trace_write_word(address_t addr, word_t value);

// cache line oriented interface to memory
void trace_read_line(address_t addr, cache_line_t line);
void trace_write_line(address_t addr, cache_line_t line);

#endif
