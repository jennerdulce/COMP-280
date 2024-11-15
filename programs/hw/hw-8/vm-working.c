#include "memory_parameters.h"
#include "cache.h"
#include "virtual_memory.h"
#include "virtual_memory_trace.h"
#include "memory_faults.h"
#include <stdlib.h>
#include <string.h>

#define TLB_SIZE 2

typedef struct tlb_entry_t{
   address_t vpn; // time of last access
   struct page_table_entry_t pte;
} tlb_entry_t;

// We have an array [tlb_entry1, tlb_entry2]
static tlb_entry_t tlb[TLB_SIZE];
static int roundRobinToggle = 0;
static int isVmEnabled = 0; // 1 = enabled, 0 = disabled
static address_t currentPageTableAddress;

void vm_disable(){
   isVmEnabled = 0;
}

void vm_enable(address_t page_table){
   currentPageTableAddress = page_table;
   isVmEnabled = 1;
   roundRobinToggle = 0;
   memset(tlb, 0, sizeof(tlb));
   
}

void findPTE(int vpn, struct page_table_entry_t *p){
   int tlbIndex = 999;
   // Check TLB for VPN
    for(int i = 0; i < TLB_SIZE; i++){
        if(tlb[i].pte.valid && tlb[i].vpn == vpn){
            // TBL HIT
            tlb_hit(vpn);
            tlbIndex = i;
            *p = tlb[i].pte;
        	return;
        }
    }

   if(tlbIndex == 999){

	tlb_miss(vpn);
	address_t pteAddress = currentPageTableAddress + (vpn * 4);
	uint32_t pteData = cache_read_word(pteAddress);
	memcpy(p, &pteData, 4);
   
	if(!p->valid){
        page_fault(vpn);
        return;
	}
   	 
	memcpy(&tlb[roundRobinToggle].pte, &pteData, 4);
	tlb[roundRobinToggle].vpn = vpn;
	roundRobinToggle = (roundRobinToggle + 1) % 2;
   }

}


address_t processAddress(address_t addr){
    int vpn = (addr >> 10) & 0x3FFFFF; // 22 Bits
    int offset = addr & 0x3FF; // 10 Bits
    address_t pAddress;
    struct page_table_entry_t pte;
    
    findPTE(vpn, &pte);
    if(!pte.valid){
            return(address_t) 999;
    }

    // pAddress = (tlb[roundRobinToggle].pte.physical_page_number << 10) | offset;
    pAddress = (pte.physical_page_number << 10) | offset;
    address_translation(addr, pAddress);
    return pAddress;
    
}

word_t vm_read_word(address_t addr){
    if(isVmEnabled == 0){ // VM Disabled
        // No translation necessary
       return cache_read_word(addr);
    } 
    
    // VM Enabled
    address_t pAddress = processAddress(addr); // Translate Address: Virtual to Physical
    if(pAddress == (address_t) 999){
        return 0;
    }
    return cache_read_word(pAddress);
}
  
void vm_write_word(address_t addr, word_t value){
    if(isVmEnabled == 0){ // VM Disabled
        // No translation necessary
       cache_write_word(addr, value);
       return;
    } 
    
    address_t pAddress = processAddress(addr); // Translate Address: Virtual to Physical
    if(pAddress == (address_t) 999){
        return;
    }
    cache_write_word(pAddress, value);
}