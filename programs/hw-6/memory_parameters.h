#ifndef MEMORY_PARAMETERS_H
#define MEMORY_PARAMETERS_H

#include <stdint.h>

// General types and constants used throughout the memory simulator

#define MEMORY_SIZE       (48 * 1024)
#define CACHE_LINE_SIZE   32

typedef uint8_t cache_line_t[CACHE_LINE_SIZE];
typedef uint32_t word_t;
typedef uint32_t address_t;

typedef uint8_t page_number_t;
#endif