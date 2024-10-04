#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Record{
    float latitude; // 4 bytes
    float longitude; // 4 bytes
    short altitude; // 2 bytes
    char name[5]; // 5 bytes
    unsigned char misc; // 1 bytes
} Record;

void processID(int id){
    printf("id:");
    switch(id){
        case 0:
            printf("unknown ");
            break;
        case 1:
            printf("friend ");
            break;
        case 2:
            printf("foe ");
            break;
        case 3:
            printf("neutral ");
            break;
    }
}

void processCategory(int cat){
    printf("cat:");
    switch(cat){
        case 0:
            printf("ship ");
            break;
        case 1:
            printf("ground vehicle ");
            break;
        case 2:
            printf("airplane ");
            break;
    }
}

void processEngaged(int engaged){
    switch(engaged){
        case 0:

        case 1:
            printf("engaged");
            break;
    }

}

int main(int argc, char * argv[]) {
    if(argc == 2){
        FILE * f = fopen(argv[1], "r");
        if(f == NULL){
            perror("Error: No file found.");
            return 1;
        } else {
            Record record;
            while(fread(&record, sizeof(Record), 1, f) == 1){
                // fread returns 1 or a 0; 1 = data; 0 = no data / EOF
                int id = record.misc & 0b11; // 0x3
                int category = (record.misc >> 2) & 0b11; // 0x3
                int engaged = (record.misc >> 4) & 0b01; // 0x10

                printf("lat:%f ", record.latitude);
                printf("lon:%f ", record.longitude);
                printf("alt:%d ", record.altitude);
                printf("name:%s ", record.name);
                processID(id);
                processCategory(category);
                processEngaged(engaged);
                printf("\n");
            }
        }
    } else {
        perror("Error: Too many files.");
    }
    return 0;
}