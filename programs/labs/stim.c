// Convert into 

#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>

typedef struct Datagram {
	double xAxisGyro;
	double yAxisGyro;
	double zAxisGyro;
	bool startup;
} Datagram;

void decode(Datagram *dg, uint8_t buffer[])
{
    uint8_t AR_0x = 00;
    uint8_t AR_0y = 00;
    uint8_t AR_0z = 00;

    // Check for negatives
    if((buffer[1] >> 7) == 1){
        AR_0x = 0xff;
    }
    if((buffer[4] >> 7) == 1){
        AR_0y = 0xff;
    }
    if((buffer[7] >> 7) == 1){
        AR_0z = 0xff;
    }

    uint8_t AR_1x = buffer[1];
    uint8_t AR_2x = buffer[2];
    uint8_t AR_3x = buffer[3];
    int32_t x = (AR_0x << 24) | (AR_1x << 16) | (AR_2x << 8) | AR_3x;
    dg->xAxisGyro = x / 16384.0;

    uint8_t AR_1y = buffer[4];
    uint8_t AR_2y = buffer[5];
    uint8_t AR_3y = buffer[6];
    int32_t y = (AR_0y << 24) | (AR_1y << 16) | (AR_2y << 8) | AR_3y;
    dg->yAxisGyro = y / 16384.0;

    uint8_t AR_1z = buffer[7];
    uint8_t AR_2z = buffer[8];
    uint8_t AR_3z = buffer[9];
    int32_t z = (AR_0z << 24) | (AR_1z << 16) | (AR_2z << 8) | AR_3z;
    dg->zAxisGyro = z / 16384.0;

    // Byte 11 of message focusing 6 bit if 1 on that 6th bit then start up if 0 the okay
    // 0x40: 0100 0000
    dg->startup = (buffer[10] & 0x40) != 0;
}

void printDatagram(struct Datagram* dg)
{
	printf("xAxisGyro: %lf  yAxisGyro: %lf  zAxisGyro: %lf", dg->xAxisGyro, dg->yAxisGyro, dg->zAxisGyro);
	if (dg->startup) {
		printf(" is startup");
	}
	else {
		printf(" is not startup");
	}
	printf("\n");
}

void doTest(uint8_t data[])
{
	struct Datagram dg;
	decode(&dg, data);
	printDatagram(&dg);
}



int main()
//       0    1       4       7       10
// (AR0{x,y,z}) af | x x x | y y y | z z z | status
// 
{
	uint8_t test1[] = { 0xAF, 0x00, 0x00, 0x01, 0xFF, 0x00, 0x35, 0x71, 0x01, 0x02, 0x40 }; 
	doTest(test1);
	uint8_t test2[] = { 0xAF, 0x00, 0x00, 0x02, 0xFF, 0xFF, 0xFF, 0x00, 0x01, 0x02, 0xBF };
	doTest(test2);
	return 0;
}