// Assignment exercising states, switch, entering files, testing, and reading files.

// Terminal Commands used:
// od -t x1 tracks.dat
// cp /home/tburger/comp280/tracks.dat .
// cp /home/tburger/comp280/tracks2.dat .
// rm bfr.c
// vim bfr.c
// gcc -o bfr bfr.c -Wall
// ./bfr tracks.c

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
    FILE *f = fopen(argv[1], "r");
    char record[16]; // Buffer to store each 16-byte record
    int record_count = 5; // We are expecting 6 records
    
    // Loop through and read each record
    for (int i = 0; i < record_count; i++) {
        // Read exactly 16 bytes from the file into the buffer 'record'
        fread(record, sizeof(char), 16, f);
        
        // Output the record (optionally handle it in a different way)
        printf("Record %d: ", i + 1);
        for (int j = 0; j < 16; j++) {
            printf("%02x ", (unsigned char)record[j]); // Print each byte in hexadecimal format
        }
        printf("\n");
    }

    // Close the file
    fclose(f);
    
    return 0;
}
