// gcc -o memap memap.c -Wall -lm
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "ext2_structures.h"

#define SUPERBLOCK_OFFSET 1024
#define BLOCK_GROUP_DESCRIPTOR_OFFSET 4096

void handle_error(const char *msg) {
   perror(msg);
   exit(1);
}


int main(int argc, char *argv[]) {
    const char *filename = "ext2_sample_vol";
    int fd = open(filename, O_RDONLY);

    // Open File
    if (fd == -1) {
        handle_error("Error opening file");
    }

    // Get File Size
    struct stat sb;
    if (fstat(fd, &sb) == -1) {
        close(fd);
        handle_error("Error fstat");
    }

    // Memory-Map File Size
    char * fileMemory = mmap(NULL,
        sb.st_size,
        PROT_READ,
        MAP_SHARED,
        fd,
        0);

    if (fileMemory == MAP_FAILED) {
        close(fd);
        handle_error("Error mmap");
    }

    // Pointer to superblock
    struct Superblock * sbPtr = (struct Superblock *) (fileMemory + SUPERBLOCK_OFFSET);

    // Print superblock information
    printf("Superblock Information:\n");
    printf("s_inodes_count: %u\n", sbPtr->s_inodes_count);
    printf("s_blocks_count: %u\n", sbPtr->s_blocks_count);
    printf("s_magic: 0x%X\n", sbPtr->s_magic);
    printf("s_last_mounted: %s\n", sbPtr->s_last_mounted);

    // Pointer to the block group descriptor (immediately after superblock)
    struct BlockGroupDescriptor *bgPtr = (struct BlockGroupDescriptor *)(fileMemory + BLOCK_GROUP_DESCRIPTOR_OFFSET);

    // Print block group descriptor information
    printf("\nBlock Group Descriptor Information:\n");
    printf("bg_free_blocks_count: %u\n", bgPtr->bg_free_blocks_count);
    printf("bg_free_inodes_count: %u\n", bgPtr->bg_free_inodes_count);
    printf("bg_used_dirs_count: %u\n", bgPtr->bg_used_dirs_count);

    // Clean up
    munmap(fileMemory, sb.st_size);
    close(fd);

    return 0;

}