#include <stdint.h>
#include <string.h> 
#include "cache.h"
#include "DRAM.h"
#include "cache_trace.h"
// Global variable for tracking access time to implement Least Recently Used
static int current_time = 0;
typedef struct Line{
    uint8_t valid;
    uint8_t dirty;
    uint32_t tag;
    uint8_t data[32]; // Assuming 32 bytes per cache line
    int time; 
} Line;
struct Line cache[NUM_SETS][N_WAY]; // 4 sets, 2 way, these variables are defined in the cache.h file 
void cache_init(){
    for(int cacheSet = 0; cacheSet < NUM_SETS; cacheSet++){
        for(int cacheLine = 0; cacheLine < N_WAY; cacheLine++){
            memset(cache[cacheSet][cacheLine].data, 0, 32); 
            cache[cacheSet][cacheLine].valid = 0;
            cache[cacheSet][cacheLine].dirty = 0;
            cache[cacheSet][cacheLine].tag = 0;
            cache[cacheSet][cacheLine].time = 0;  
        }
    }
}
word_t cache_read_word(address_t addr) {
    int tag = (addr >> 7) & 0x1FF;
    int cacheSet = (addr >> 5) & 0x3;
    int offset = addr & 0x1F; // Assuming 32 bytes per cache line
    word_t result;
    // Check for a cache hit
    for (int cacheLine = 0; cacheLine < N_WAY; cacheLine++) {
        if (cache[cacheSet][cacheLine].valid && cache[cacheSet][cacheLine].tag == tag) {
            cache_hit(addr, cacheSet, cacheLine);
            cache[cacheSet][cacheLine].time = current_time++;
            memcpy(&result, &cache[cacheSet][cacheLine].data[offset], sizeof(word_t)); // Write the data to the cache
            return result; // Return the data
        }
    }
    //for loop for cache miss
    for(int cacheLine = 0; cacheLine < N_WAY; cacheLine++) {
        if(cache[cacheSet][cacheLine].valid == 0) {
            cache_miss(addr, cacheSet, cacheLine);
            cache[cacheSet][cacheLine].valid = 1;
            cache[cacheSet][cacheLine].tag = tag;
            cache[cacheSet][cacheLine].time = current_time++;
            read_line((addr & 0xFFFFFFFFFFFFFFE0), cache[cacheSet][cacheLine].data);
            memcpy(&result, &cache[cacheSet][cacheLine].data[offset], sizeof(word_t)); //copy the data from the cache to the result 
            return result;
        }
    }
    // cache miss but no empty line
    int lru_index = 0;
    for (int i = 1; i < N_WAY; i++) {
        if (cache[cacheSet][i].time < cache[cacheSet][lru_index].time) {
            lru_index = i;
        }
    }
    // Write back the dirty line if necessary
    if (cache[cacheSet][lru_index].dirty) {
        address_t write_back_addr = (cache[cacheSet][lru_index].tag << 7) | (cacheSet << 5);
        write_line(write_back_addr, cache[cacheSet][lru_index].data); // Write back the cache line to memory
        cache[cacheSet][lru_index].dirty = 0; // Reset the dirty bit
    }
    // Replace the cache line with the new data
    read_line((addr & 0xFFFFFFFFFFFFFFE0), cache[cacheSet][lru_index].data); // Read the cache line from memory and store it in the cache (Will give us the addr - the offset)
    cache_miss(addr, cacheSet, lru_index); // Update the cache line with the new data
    cache[cacheSet][lru_index].tag = tag;
    cache[cacheSet][lru_index].valid = 1;
    cache[cacheSet][lru_index].time = current_time++;
    memcpy(&result, &cache[cacheSet][lru_index].data[offset], sizeof(word_t)); //copy the data from the cache to the result
    return result; 
}
void cache_write_word(address_t addr, word_t value) {
    int tag = (addr >> 7) & 0x1FF;
    int cacheSet = (addr >> 5) & 0x3;
    int offset = addr & 0x1F;
    // Check for a cache hit
    for (int cacheLine = 0; cacheLine < N_WAY; cacheLine++) {
        if (cache[cacheSet][cacheLine].valid && cache[cacheSet][cacheLine].tag == tag) {
            cache_hit(addr, cacheSet, cacheLine);
            cache[cacheSet][cacheLine].time = current_time++;
            memcpy(&cache[cacheSet][cacheLine].data[offset], &value, sizeof(word_t)); // Write the data to the cache
            cache[cacheSet][cacheLine].dirty = 1; // Mark the cache line as dirty
            return;
        }
    }
    //for loop for cache miss
    for(int cacheLine = 0; cacheLine < N_WAY; cacheLine++) {
        if(cache[cacheSet][cacheLine].valid == 0) {
            cache_miss(addr, cacheSet, cacheLine);
            cache[cacheSet][cacheLine].valid = 1;
            cache[cacheSet][cacheLine].tag = tag;
            
            cache[cacheSet][cacheLine].time = current_time++; // Update the time 
            read_line((addr & 0xFFFFFFFFFFFFFFE0), cache[cacheSet][cacheLine].data);
            memcpy(&cache[cacheSet][cacheLine].data[offset], &value, sizeof(word_t)); // Write the data to the cache
            cache[cacheSet][cacheLine].dirty = 1; // Mark the cache line as dirty
            return;
        }
    }
    // cache miss but no empty line
    int lru_index = 0;
    for (int i = 1; i < N_WAY; i++) {
        if (cache[cacheSet][i].time < cache[cacheSet][lru_index].time) {
            lru_index = i;
        }
    }
    // Write back the dirty line if necessary
    if (cache[cacheSet][lru_index].dirty){
        address_t write_back_addr = (cache[cacheSet][lru_index].tag << 7) | (cacheSet << 5);
        write_line(write_back_addr, cache[cacheSet][lru_index].data); // Write back the cache line to memory
        cache[cacheSet][lru_index].dirty = 0; // Reset the dirty bit
    }
    // Replace the cache line with the new data 
    read_line((addr & 0xFFFFFFFFFFFFFFE0), cache[cacheSet][lru_index].data); // Read the cache line from memory and store it in the cache (Will give us the addr - the offset)
    cache_miss(addr, cacheSet, lru_index); // Update the cache line with the new data 
    cache[cacheSet][lru_index].tag = tag;
    cache[cacheSet][lru_index].valid = 1;
    cache[cacheSet][lru_index].time = current_time++;
    memcpy(&cache[cacheSet][lru_index].data[offset], &value, sizeof(word_t)); // Write the data to the cache
    cache[cacheSet][lru_index].dirty = 1; // Mark the cache line as dirty
}
void cache_flush() {
    for (int set = 0; set < NUM_SETS; set++) {
        for (int line = 0; line < N_WAY; line++) {
            if (cache[set][line].valid && cache[set][line].dirty) {
                // Write the dirty cache line back to memory
                write_line((cache[set][line].tag << 7) | (set << 5), cache[set][line].data); // | rather than + because you are putting the two fields together in the same word
                // Reset the dirty bit
                cache[set][line].dirty = 0; 
            }
        }
    }
}
