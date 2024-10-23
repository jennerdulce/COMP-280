#ifndef DRAM_H
#define DRAM_H

#include "memory_parameters.h"

// word oriented interface to memory
word_t read_word(address_t addr);
void write_word(address_t addr, word_t value);

// cache line oriented interface to memory
void read_line(address_t addr, cache_line_t line);
void write_line(address_t addr, cache_line_t line);

// initialize all of memory to 0
void dram_clear();

#endif
