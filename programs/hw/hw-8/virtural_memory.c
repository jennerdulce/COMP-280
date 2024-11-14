#include "memory_parameters.h"
#include "virtual_memory.h"
#include "virtual_memory_trace.h"
#include "memory_faults.h"
#include <stdlib.h>
#include <string.h>


#define TLB_SIZE 2

typedef struct tlb_entry_t{
   address_t vpn; // time of last access
   page_table_entry_t pte;
} tlb_entry_t;

static int round_robin = 0;

// We have an array [tlb_entry1, tlb_entry2]
static tlb_entry_t tlb[TLB_SIZE]; // Translation Lookaside Buffer (TLB)

static int isVmEnabled = 0; // 1 = enabled, 0 = disabled
static int current_time = 0;

// May or may not need this
static address_t current_page_table_address; // current page table

void vm_disable(){
   vm_enabled = 0;
}

void vm_enable(address_t page_table){
   current_page_table_address = page_table;
   vm_enabled = 1;
   memset(TLB, 0, sizeof(tlb));
}

word_t vm_read_word(address_t addr){
    if(isVmEnabled == 0){
        // VM Disabled
        // No translation necessary
        // Pass addr directly to using cache functions from part 2
       return cache_read_word(addr);
    } else {
        // VM Enabled
        // Check TLB CHECKER: for page table entry
            // Check VPN Virtural Page Number
        address_t vpn = (addr >> 10) & 0x3FFFFF;
        address_t offset = addr & 0x3FF;
        
        for(int i = 0; i < TLB_SIZE; i++){
            if(tlb[i].pte.valid && tlb[i].vpn == vpn){
                // TBL HIT;
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


// TLB
// PHYSICAL ADDR
// VIRTURAL ADDR
// TLB ENTRY
// PAGE TABLE ENTRY

//
// Look in PTE
    // Check valid bit
    // Is valid? get physical page, put into address now you can use cache_read_word / cache_write_word
        // Indicate TLB hit

// Dont find it in PTE
    // look in TLB for VPN
    // found: copy PTE into P
    // not fund:
        // RR = RR + 1 % 2
        // Calculate Addr of PTE
        // Entry addr = Page tble addr + 4 * VPN
        // newPTE= Cache read_word (entry addr)
        // TLB[RR].vpn = vpn
        // memcpy(&tlb[RR].pte, &newpte, 4);
        // *p = TLB[RR].pte;

// Virtural to Physical Address Translation
// 1. Check TLB for page table entry
// 2. If TLB hit, return physical address
// 3. If TLB miss, translate addr to real addr with vpn