// To Identify Objects
    // Unoptimized
        // gcc -o asma.o asma.c -c -Wall -g
        // objdump -d -S asma.o > asma.objdump
        // cat asma.objdump
    // Optimized
        // gcc -o asmao.o asma.c -c -Wall -g -O ** FOR OPTIMIZED **
        // objdump -d -S asmao.o > asma.objdump
        // cat asmao.objdump

typedef struct Record {
    // Unsigned int = 32 bits
    unsigned int offset: 6;
    unsigned int bits: 14;
    unsigned int padding: 12;
} Record;

// Takes in a pointer
unsigned int exShiftMask(unsigned int* x){
    // 1111 1111 1111 ||1111 1111 1111 11||11 1111
    // 0011 1111 1111 1111
    return (*x >> 6) & 0x3FFF;
}

// Takes in a pointer
unsigned int exBitField(Record *r){
    return r-> bits;
}

void setShiftMask(unsigned int *x, unsigned int val){
// 1111 1111 1111 ||0000 0000 0000 00||11 1111
// 0000 0000 0000 ||1111 1111 1111 11||00 0000
    *x = (*x & 0xFFF000CF) | ((val & 0x3FFF) << 6);
}

void setBitField(Record *r, unsigned int x){
    r-> bits = x;
}