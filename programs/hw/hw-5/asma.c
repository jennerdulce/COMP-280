typedef struct Record {
    unsigned int offset: 6;
    unsigned int bits: 14;
    unsigned int padding: 12;
} Record;

unsigned int exShiftMask(unsigned int* x){
    return (*x >> 6) & 0x3FFF;
}

unsigned int exBitField(struct Record *r){
    return r-> bits;
}

void setShiftMask(unsigned int *x, unsigned int val){
    *x = (*x & 0xFFF000CF) | ((val & 0x3FFF) << 6);
}

void setBitField(Record *r, unsigned int x){
    r-> bits = x;
}