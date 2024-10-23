#include <stdio.h>
int main()
{
    unsigned short val = 0x3417;
    // 0011 0100 0001 0101
    // 00110 100 0001 0101

    // 4 bit int; 7 = 0101
    // 7 bit char; 41 = 0100 0001
    // 5 bit int = 0011

    int f1 = val & 0xF;
    char f2 = val >> 4 & 0x7F; // >> = shift; & = mask
    // 0x7F 0111 1111
    int f3 = val >> 11 & 0x1F;
    // 0x7F 0001 1111

    printf("f1:%d  f2:%c  f3:%d\n", f1, f2, f3);
}