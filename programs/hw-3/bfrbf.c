#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Record {
    float latitude; // 4 bytes
    float longitude; // 4 bytes
    short altitude; // 2 bytes
    char name[5]; // 5 bytes

    //  Misc is 1 byte / 8 bits
    unsigned char id:2; // 2/8 bits
    unsigned char cat:2; // 2/8 bits
    unsigned char engaged:1; // 1/8 bits
    unsigned char unused:3; // 3/8 bits; 8/8

    // Each word is 16 bits
    // Short is 2 bytes which equals 16 bits
    // We are specifying how many bits per unsigned short variable
    // ** ORDER MATTERS **
    // Word 0
    unsigned short year:7; // 7/16 bits
    unsigned short month:4; // 4/16 bits
    unsigned short day:5;// 5/16 bits; 16/16

    // Word 1
    unsigned short hr:5; // 5/16 bits
    unsigned short min:6; // 6/16 bits
    unsigned short reserved1:5; // 5/16 bits; 16/16

    // Word 2
    unsigned short sec:6; // 6/16 bits
    unsigned short reserved2:10; // 10/16 bits; 16/16
    
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

void processDate(Record rec){
    char month[4] = "def";

    switch(rec.month){
        case 1:
            strcpy(month, "jan"); 
            break;
        case 2:
            strcpy(month, "fed");
            break;
        case 3:
            strcpy(month, "mar");
            break;
        case 4:
            strcpy(month, "apr");
            break;
        case 5:
            strcpy(month, "may");
            break;
        case 6:
            strcpy(month, "jun");
            break;
        case 7:
            strcpy(month, "jul");
            break;
        case 8:
            strcpy(month, "aug");
            break;
        case 9:
            strcpy(month, "sep");
            break;
        case 10:
            strcpy(month, "oct");
            break;
        case 11:
            strcpy(month, "nav");
            break;
        case 12:
            strcpy(month, "dec");
            break;
    }

    printf("reported: 20%02hd/%s/%02hd ", rec.year, month, rec.day);

}

void processEngaged(Record rec){
    if(rec.engaged){
        printf("[engaged] ");
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
            while(fread(&record, 22, 1, f) == 1){
                printf("lat:%.1f ", record.latitude);
                printf("lon:%f ", record.longitude);
                printf("alt:%d ", record.altitude);
                printf("name:%.5s ", record.name);
                processID(record.id);
                processCategory(record.cat);
                processEngaged(record);
                processDate(record);

                // 02 specifies how many places you want to display
                printf("%02hd:%02hd:%02hd", record.hr, record.min, record.sec);
                printf("\n");
            }
        } 
    } else {
        perror("Error: Too many files.");
    }
    return 0;
}