#include "virtual_memory.h"
#include "virtual_memory_trace.h"
#include "memory_faults.h"
#include "cache.h"
#include <stdio.h>
#include <string.h>

struct tlb_entry {address_t vpn; struct page_table_entry_t pte;};

static struct tlb_entry TLB[2];
static int round_robin = 0;
static int vi_enable = 0;
static address_t pte_addr;

void vm_enable(address_t page_table){
  vi_enable =1;
  pte_addr = page_table;
  memset(TLB, 0, sizeof(TLB));
}

void vm_disable(){
  vi_enable = 0;
}

void find_pte(int vpn,struct page_table_entry_t *p){
   int tlb_index = -1;
   for(int i=0; i <2; i++){
	if(TLB[i].pte.valid && TLB[i].vpn == vpn){
        	tlb_hit(vpn);
        	tlb_index = i;
        	*p=TLB[i].pte;
        	return;
	}
   }

   if(tlb_index == -1){

	tlb_miss(vpn);

	address_t entry_addr = pte_addr + (vpn*4);
	uint32_t pte_data = cache_read_word(entry_addr);
	memcpy(p,&pte_data,4);
   

	if(!p->valid){
	page_fault(vpn);
	return;
	}
   	 
	memcpy(&TLB[round_robin].pte,&pte_data,4);
	TLB[round_robin].vpn = vpn;
	round_robin = (round_robin +1)%2;
   }

}

     	
address_t translate_address(address_t vaddr){
    	int vpn = (vaddr >> 10) & 0x3FFFFF;
    	int offset = vaddr & 0x3FF;

    	struct page_table_entry_t pte;
    	find_pte(vpn,&pte);
   	 
    	if(!pte.valid){
            	return(address_t)-1;
    	}

    	address_t physAddr = (pte.physical_page_number << 10) | offset;
    	address_translation(vaddr,physAddr);

    	return physAddr;
}

word_t vm_read_word(address_t addr) {
	if (!vi_enable) {
    	// Virtual memory is disabled; use physical address directly
    	return cache_read_word(addr);
	}

	// Virtual memory is enabled; translate virtual address to physical address
	address_t phys_addr = translate_address(addr);
	if (phys_addr == (address_t)-1) {
   	 
    	return 0; // Return default value or handle error as needed
	}

	return cache_read_word(phys_addr);
}

void vm_write_word(address_t addr, word_t value) {
	if (!vi_enable) {
    	// Virtual memory is disabled; use physical address directly
    	cache_write_word(addr, value);
    	return;
	}

	// Virtual memory is enabled; translate virtual address to physical address
	address_t phys_addr = translate_address(addr);
	if (phys_addr == (address_t)-1) {
    	return;
	}

   
	cache_write_word(phys_addr, value);
}





