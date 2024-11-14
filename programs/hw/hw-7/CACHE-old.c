#include "cache.h"
#include "cache_trace.h"
#include "DRAM.h"
#include "memory_parameters.h"
#include <string.h>
#include <stdint.h>


// Global variable for tracking access time to implement Least Recently Used

typedef struct Line {
    uint32_t tag;
    uint32_t set;
    uint32_t offset;
    cache_line_t data;
    uint8_t valid;
    uint8_t dirty;
    int time;
} Line;
struct Line cache[NUM_SETS][N_WAY]; // 4 sets, 2 way, these varaibles are defined in the cache.h file
int clock = 0;

void cache_init(){
   for(int cacheSet = 0; cacheSet < NUM_SETS; cacheSet++){
       for(int cacheLine = 0; cacheLine < N_WAY; cacheLine++){
           memset(cache[cacheSet][cacheLine].data, 0, CACHE_LINE_SIZE); // CACHE_LINE_SIZE = 32
           cache[cacheSet][cacheLine].valid = 0;
           cache[cacheSet][cacheLine].dirty = 0;
           cache[cacheSet][cacheLine].tag = 0;
           cache[cacheSet][cacheLine].set = 0;
           cache[cacheSet][cacheLine].offset = 0;
           cache[cacheSet][cacheLine].time = 0; 
       }
   }
}

word_t cache_read_word(address_t addr) {
   int tag = (addr >> 7) & 0x1FF;
   int cacheSet = (addr >> 5) & 0x3;
   int offset = addr & 0x1F;
   word_t result;

   //for loop for a cache hit
   for(int cacheLine = 0; cacheLine < NUM_SETS; cacheLine++) {
       if(cache[cacheSet][cacheLine].tag == tag && cache[cacheSet][cacheLine].valid == 1) {
           cache_hit(addr, cacheSet, cacheLine);
           clock++;
           cache[cacheSet][cacheLine].time = clock;
           memcpy(&result, &cache[cacheSet][cacheLine].data + offset, (CACHE_LINE_SIZE /sizeof(word_t))); //copy the data from the cache to the result
           return result;
       }
   }

   //for loop for cache miss
   for(int cacheLine = 0; cacheLine < NUM_SETS; cacheLine++) {
       if(cache[cacheSet][cacheLine].valid == 0) {
           cache_miss(addr, cacheSet, cacheLine);
           clock++;
           cache[cacheSet][cacheLine].valid = 1;
           cache[cacheSet][cacheLine].tag = tag;
           cache[cacheSet][cacheLine].set = cacheSet;
           cache[cacheSet][cacheLine].time = clock;
           read_line((addr & 0xFFFFFFFFFFFFFFE0), cache[cacheSet][cacheLine].data);
           memcpy(&result, &cache[cacheSet][cacheLine].data + offset, sizeof(word_t)); //copy the data from the cache to the result
           return result;
       }
   }

   //if the cache is full but there is a cache miss
   int lru = 0;
   if(cache[cacheSet][1].time < cache[cacheSet][0].time) { //if the time of the second cache line is less than the time of the first cache line
       lru = 1;
   }

   if (cache[cacheSet][lru].dirty == 1) { // If the cache line is dirty, write it back to the DRAM
        // write_line(addr, cache[cacheSet][lru].data); // Write the line back to the DRAM
        // before writing, reconstruct
       // instead of passing address, pass new dirty addrress
       // set dirty flag to false
       address_t dirtyAddr = 0;
       dirtyAddr = (dirtyAddr | tag) << 7;
       dirtyAddr = (cacheSet << 5) | dirtyAddr;
       
       write_line(dirtyAddr, cache[cacheSet][lru].data);
       cache[cacheSet][lru].dirty = 0;
}
        
   cache_miss(addr, cacheSet, lru);
   clock++;
   read_line((addr & 0xFFFFFFFFFFFFFFE0), cache[cacheSet][lru].data);
   cache[cacheSet][lru].valid = 1; //set the valid bit to 1
   cache[cacheSet][lru].tag = tag; //set the tag to the tag of the address
   cache[cacheSet][lru].time = clock; //set the time to the current time
   memcpy(&result, &cache[cacheSet][lru].data + offset, sizeof(word_t)); //copy the data from the cache to the result
   return result;
}


void cache_write_word(address_t addr, word_t value) {
   int tag = (addr >> 7) & 0x1FF;
   int cacheSet = (addr >> 5) & 0x3;
   int offset = addr & 0x1F;

   //for loop for a cache hit
   for(int cacheLine = 0; cacheLine < NUM_SETS; cacheLine++) {
       if(cache[cacheSet][cacheLine].tag == tag && cache[cacheSet][cacheLine].valid == 1) {
           cache_hit(addr, cacheSet, cacheLine);
           clock++;
           memcpy(cache[cacheSet][cacheLine].data + offset, &value, sizeof(word_t)); // Write the data to the cache
           cache[cacheSet][cacheLine].dirty = 1; // Mark the cache line as dirty
           return;
       }
   }

   //for loop for cache miss
   for(int cacheLine = 0; cacheLine < NUM_SETS; cacheLine++) {
       if(cache[cacheSet][cacheLine].valid == 0) {
           cache_miss(addr, cacheSet, cacheLine);
           clock++;
            cache[cacheSet][cacheLine].tag = tag;
           read_line((addr & 0xFFFFFFFFFFFFFFE0), cache[cacheSet][cacheLine].data);
           cache[cacheSet][cacheLine].valid = 1;
           memcpy(cache[cacheSet][cacheLine].data + offset, &value, sizeof(word_t)); // Write the data to the cache
           cache[cacheSet][cacheLine].dirty = 1; // Mark the cache line as dirty
           return;
       }
   }

   //if the cache is full but there is a cache miss
   int lru = 0;
   if(cache[cacheSet][1].time < cache[cacheSet][0].time) { //if the time of the second cache line is less than the time of the first cache line
       lru = 1;
   }

   if (cache[cacheSet][lru].dirty == 1) { // If the cache line is dirty, write it back to the DRAM
       write_line((addr & 0xFFFFFFFFFFFFFFE0), cache[cacheSet][lru].data); // Write the line back to the DRAM
       cache[cacheSet][lru].dirty = 0;
   }

   cache_miss(addr, cacheSet, lru); // Call the cache miss function
    clock++;
    cache[cacheSet][lru].valid = 1;
    cache[cacheSet][lru].tag = tag;
    cache[cacheSet][lru].set = cacheSet;
    cache[cacheSet][lru].time = clock;
    read_line((addr & 0xFFFFFFFFFFFFFFE0), cache[cacheSet][lru].data);
   memcpy(cache[cacheSet][lru].data + offset, &value, sizeof(word_t)); // Write the data to the cache
   cache[cacheSet][lru].dirty = 1; // Mark the cache line as dirty
} 

void cache_flush() {
   for (int set = 0; set < NUM_SETS; set++) {
       for (int line = 0; line < N_WAY; line++) {
           if (cache[set][line].valid && cache[set][line].dirty) {
               // Write the dirty cache line back to memory
               write_line(set, cache[set][line].data);
               // Reset the dirty bit
               cache[set][line].dirty = 0;
           }
       }
   }
}

