#include <stdio.h>
#include <stdlib.h>

typedef struct Record {
    // 4 Words:
    // 1. P - Parity
    // 2. SSM - Sign / Status MAtrix
    // 3. Data
    // 4. SDI - Souce / Destination Identifier
    // 5. Label - Identifies the Data Type
    // Each word is 4 bytes in length
        // or 32 bits in length
    unsigned int parity:1;
    unsigned int smm:2;
    unsigned int data:19;
    unsigned int sdi:2;
    unsigned int label:8;
} Record;

unsigned int floatToBinary(float f) {
     //1001011.01 to 100101101
    unsigned int altitude = (unsigned int) (f * 8);

    // Handling negatives
    if(altitude < 0) {
        altitude = (1 << 19) + altitude;
    }

    // 0111 1111 1111 1111 1111
    return altitude & 0x7FFFF; // Masking 19 bits that we need
}

unsigned int setParity(Record record) {
    unsigned int count = 0;
    
    while (record.smm) {
        count += record.smm & 1;
        record.smm >>= 1;
    }

    while (record.data) {
        count += record.data & 1;
        record.data >>= 1;
    }

    while (record.sdi) {
        count += record.sdi & 1;
        record.sdi >>= 1;
    }

    while (record.label) {
        count += record.label & 1;
        record.label >>= 1;
    }
    
    if(count % 2 == 0){
        return 0b1;
    } else {
        return 0b0;
    }
}

void printMessage(Record record) {
    // Creating the binary string
    unsigned int message = (record.parity << 31) | 
                           (record.smm << 29) | 
                           (record.data << 10) |
                           (record.sdi << 8) |
                           (record.label);


    // (message >> 24)
    // (message >> 16) & 0xFF: data
    // (message >> 8): 
    //  message & 0xFF : label
    printf("%02x %02x %02x %02x\n",(message >> 24) & 0xFF, (message >> 16) & 0xFF, (message >> 8) & 0xFF, message & 0xFF);     
}

int main(int argc, char * argv[]) {
    Record record;
    float altitudes[] = {135.7, 1.0, -0.5, 0.0, 75.25, -1.5};
    for(int i = 0; i < 6; i++){
        printf("%f ", altitudes[i]);

        // Create Binary String
        record.smm = 0b11;
        record.sdi = 0b00;
        record.data = floatToBinary(altitudes[i]);
        record.label = 0xb1;

        //  Count Total number of 1s for Parity
        record.parity = setParity(record);
        
        // Convert Binary To Hex
        printMessage(record);
    }
    
    return 0;
}