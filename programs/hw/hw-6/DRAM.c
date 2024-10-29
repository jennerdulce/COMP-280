#include "DRAM.h"
#include "DRAM_trace.h"
#include "memory_faults.h"
#include "memory_parameters.h"
#include <string.h>

unsigned char dram[49125];

word_t read_word(address_t addr){
    if((addr & 3) != 0){
        alignment_error(addr);
        return 0;
    }

    if(addr >= MEMORY_SIZE){
        address_error(addr);
        return 0;
    }
    word_t result;

    memcpy(&result, &dram[addr], 4);
    trace_read_word(addr, result);
    return result;
}

void write_word(address_t addr, word_t value){
    if((addr & 3) != 0){
        alignment_error(addr);
        return;
    }

    if(addr >= MEMORY_SIZE){
        address_error(addr);
        return;
    }

    memcpy(&dram[addr], &value, 4);
    trace_write_word(addr, value);
}

void read_line(address_t addr, cache_line_t line){
    if((addr & 0x1F) != 0){
        alignment_error(addr);
        return;
    }

    if(addr >= MEMORY_SIZE){
        address_error(addr);
        return;
    }

    int totalWords = (CACHE_LINE_SIZE / sizeof(word_t));
    int originalAddr = addr;
    for(int i = 0; i < totalWords; i++){
        memcpy(line, &dram[addr], 4);
        addr = addr + sizeof(word_t);
        line = line + sizeof(word_t);
    }

    trace_read_line(originalAddr, line);
}

void write_line(address_t addr, cache_line_t line){
    if((addr & 0x1F) != 0){
        alignment_error(addr);
        return;
    }

    if(addr >= MEMORY_SIZE){
        address_error(addr);
        return;
    }
    int totalWords = (CACHE_LINE_SIZE / sizeof(word_t));

    for(int i = 0; i < totalWords; i++){
        memcpy(&dram[addr], line, 4);
        addr = addr + sizeof(word_t);
        line = line + sizeof(word_t);
    }

    trace_write_line(addr, line);
}

void dram_clear(){
    memset(&dram, 0, 49152);
}