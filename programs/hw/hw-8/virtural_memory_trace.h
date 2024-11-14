#ifndef VIRTUAL_MEMORY_TRACE_H
#define VIRTUAL_MEMORY_TRACE_H

// report on whether the virtual address translation resulted in
// a hit or a miss on the translation lookaside buffer (tlb).

void tlb_hit(int vpn);
void tlb_miss(int vpn);

// the result of the virtual address translation
void address_translation(address_t virt, address_t phys);
#endif
