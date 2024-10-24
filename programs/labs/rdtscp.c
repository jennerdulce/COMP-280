#define SIZE 1300
#define TIMES 10

static __inline__ unsigned long long rdtscp(void)
{
    unsigned long long tsc;
    __asm__ __volatile__(
       "rdtscp;"
       "shl $32, %%rdx;"
       "or %%rdx, %%rax"
       : "=a"(tsc)
       :
       : "%rcx", "rdx");
    return tsc;
}

void createMatrix(int32_t matrix[SIZE][SIZE]){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            matrix[i][j] = 1;
        }
    }
}

uint64_t row_sum(int32_t matrix[SIZE][SIZE], int32_t *sum){
    uint64_t rowStart = rdtscp()
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            *sum += matrix[i][j];
        }
    }
    uint64_t rowEnd = rdtscp()

    return rowStart - rowEnd;
}

uint64_t column_sum(int32_t matrix[SIZE][SIZE], int32_t *sum){
    uint64_t colStart = rdtscp()
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            *sum += matrix[j][i];
        }
    }

    uint64_t colEnd = rdtscp()
    return colStart - colEnd;
}

int main(){
    int32_t mat[SIZE][SIZE];
    int total = 0;
    createMatrix();
    for(int i = 0; i < TIMES; i++){
        if(i == 0){
            printf("=======================================================")
 
        }
        printf("Loop: %d", i)
        printf("Processing time (Rows): %d \n", row_sum(mat, total));
        printf("Processing time (Columns): %d  \n", column_sum(mat, total));
        printf("Total Sum: %d \n", total);
        printf("=======================================================")
        int total = 0;
    }

    return 0;
}