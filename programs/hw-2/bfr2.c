#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to hold a single record's data
typedef struct {
    float latitude;
    float longitude;
    short altitude;
    char name[5];    // 4 chars + null terminator
    char id;         // ID (friend/foe/neutral)
    char category[30]; // Category (airplane, ground vehicle, etc.)
} Record;

// Function to interpret the ID and return a string
const char* interpret_id(char id) {
    if (id == 0x09)
        return "friend";
    else if (id == 0x06)
        return "foe";
    else if (id == 0x03)
        return "neutral";
    else
        return "unknown";
}

// Function to interpret the category based on the record data
const char* interpret_category(char id, char alt) {
    if (id == 0x09 && alt == 100)
        return "airplane";
    else if (id == 0x06 && alt == 200)
        return "ground vehicle";
    else if (id == 0x03 || id == 0x06)
        return (alt == 10 || alt == -10) ? "ship engaged" : "ship";
    else
        return "unknown";
}

int main() {
    FILE *file;
    Record records[6]; // To store 6 records
    char buffer[16];   // 16-byte buffer for reading each record
    
    // Open the binary file
    file = fopen("datafile.dat", "rb");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    
    // Read each record and process it
    for (int i = 0; i < 6; i++) {
        // Read 16 bytes for each record
        fread(buffer, sizeof(char), 16, file);
        
        // Extract data from buffer and store in the record structure
        records[i].latitude = *(float*)&buffer[0];  // 4 bytes float for latitude
        records[i].longitude = *(float*)&buffer[4]; // 4 bytes float for longitude
        records[i].altitude = *(short*)&buffer[8];  // 2 bytes short for altitude
        
        // Copy name (4 characters)
        strncpy(records[i].name, &buffer[10], 4);
        records[i].name[4] = '\0';  // Null terminate the string
        
        records[i].id = buffer[14]; // 1 byte for ID
        
        // Interpret category based on altitude and ID
        strcpy(records[i].category, interpret_category(records[i].id, records[i].altitude));
    }

    // Close the file
    fclose(file);

    // Output the results in the format shown in the image
    for (int i = 0; i < 6; i++) {
        printf("lat:%.1f lon:%.2f alt:%d name:%s id:%s cat:%s\n", 
               records[i].latitude, 
               records[i].longitude, 
               records[i].altitude, 
               records[i].name, 
               interpret_id(records[i].id), 
               records[i].category);
    }

    return 0;
}