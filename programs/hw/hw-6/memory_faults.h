#ifndef MEMORY_FAULTS_H
#define MEMORY_FAULTS_H

#include "memory_parameters.h"

// The following functions are used to report a memory fault.

// an address error is an address that is outside the valid range of an address
void address_error(address_t addr);

// an alignment error is an address that is not properly aligned for a word
// or a cache line
void alignment_error(address_t addr);

// a page fault is only applicable to the virtual memory version of the
// memory simulator.  It signifies that there is no valid physical address
// for the specified virtual address.
void page_fault(address_t addr);
#endif