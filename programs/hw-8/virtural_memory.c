#include "memory_parameters.h"
#include "virtual_memory.h"
#include "virtual_memory_trace.h"
#include "memory_faults.h"
#include <stdlib.h>
#include <string.h>


#define TLB_SIZE 2

typedef struct tlb_entry_t{
   address_t virtual_addr; // virtual address
   address_t physical_addr; // physical address
   int time;
   // Maybe a page?
   page_table_entry_t pte;
} tlb_entry_t;

// We have an array [tlb_entry1, tlb_entry2]
static tlb_entry_t tlb[TLB_SIZE]; // Translation Lookaside Buffer (TLB)
static int isVmEnabled = 0; // 1 = enabled, 0 = disabled
static int current_time = 0;

// May or may not need this
static address_t current_page_table = 0; // current page table

word_t vm_read_word(address_t addr){
    if(isVmEnabled == 0){
        // VM Disabled
        // No translation necessary
        // Pass addr directly to using cache functions from part 2
       return cache_read_word(addr);
    } else {
        // VM Enabled
        // Check TLB for page table entry
        for(int i = 0; i < TLB_SIZE; i++){
            if(tlb[i].virtual_addr == addr){
                // TLB HIT
                tlb[i].time = current_time++; // Update access time
                address_t physical_addr = tlb[i].physical_addr;
                return cache_read_word(physical_addr);
            }
        }

        // TLB MISS
        // Translate addr to real addr with vpn
        address_t page_table_entry = current_page_table + ((addr / PAGE_SIZE) * BYTES_PER_PTE);
        word_t page_table_entry = pte_addr;
        
        // Update TLB with new entry
        int lru_index = 0;
        if(tlb[1].time < tlb[0].time){
            current_time++
            lru_index = 1;
        }

        // Construct physical address
        address_t physical_addr = (pte.physical_page_number * PAGE_SIZE) + (addr % PAGE_SIZE);

        tlb[lru_index].virtual_addr = addr;
        tlb[lru_index].physical_addr = physical_addr;
        tlb[lru_index].time = current_time;
        tlb[lru_index].pte;
        // Read from cache using the physical address
        return cache_read_word(physical_addr);

        // If hit,
            // Pull page from flb
            // Read/write from page
        // If miss,
            // Pull page into tlb from disk/dram/cache
            // Read/write from page
    }


}
  
void vm_write_word(address_t addr, word_t value){

}

void vm_disable(){
   vm_enabled = 0;
}

void vm_enable(address_t page_table){
   current_page_table = page_table;
   vm_enabled = 1;
}

// TLB
// PHYSICAL ADDR
// VIRTURAL ADDR
// TLB ENTRY
// PAGE TABLE ENTRY