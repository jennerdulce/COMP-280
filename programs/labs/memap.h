#ifndef EXT2_STRUCTURES_H
#define EXT2_STRUCTURES_H

#include <stdint.h>

// abbreviated definition of the superblock
struct Superblock {
    uint32_t s_inodes_count;
    uint32_t s_blocks_count;
    uint32_t s_r_blocks_count;
    uint32_t s_free_blocks_count;
    uint32_t s_free_inodes_count;
    uint8_t  filler1[36];
    uint16_t s_magic;
    uint8_t  filler2[78];
    char     s_last_mounted[64];
};

struct BlockGroupDescriptor {
    uint32_t bg_block_bitmap;
    uint32_t bg_inode_bitmap;
    uint32_t bg_inode_table;
    uint16_t bg_free_blocks_count;
    uint16_t bg_free_inodes_count;
    uint16_t bg_used_dirs_count;
    uint16_t bg_pad;
    uint8_t  bg_reserved[12];
};

#endif
