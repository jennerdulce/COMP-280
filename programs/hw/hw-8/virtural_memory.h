// reading and writing of memory
word_t vm_read_word(address_t addr);
void vm_write_word(address_t asddr, word_t value);

// control of the virtual memory.  
// When disabled the memory addresses are interpreted as physical 
// addresses - no translation occurs.
// enabling virtual memory clears the translation lookaside buffer
void vm_disable();
void vm_enable(address_t page_table);

#define PAGE_TABLE_ENTRIES 64
#define BYTES_PER_PTE 4        // each page table entry is 32-bits.
struct page_table_entry_t{
    unsigned int physical_page_number : 6;
    unsigned int valid : 1;
    unsigned int filler : 25;
};

#endif
