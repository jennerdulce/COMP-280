#include <stdint.h>
#include <stdio.h>

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

void sort(int arr[]){
    for(int i = 0; i < 9; i++){
        for(int j = i + 1; j < 10; j++){
            if(arr[i] > arr[j]){
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void createMatrix(int32_t matrix[SIZE][SIZE]){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            matrix[i][j] = 1;
        }
    }
}

uint64_t row_sum(int32_t matrix[SIZE][SIZE], int32_t *sum){
    uint64_t rowStart = rdtscp();
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            *sum += matrix[i][j];
        }
    }
    uint64_t rowEnd = rdtscp();

    return rowEnd - rowStart;
}

uint64_t column_sum(int32_t matrix[SIZE][SIZE], int32_t *sum){
    uint64_t colStart = rdtscp();
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            *sum += matrix[j][i];
        }
    }

    uint64_t colEnd = rdtscp();
    return colEnd - colStart;
}

int main(){
    int32_t mat[SIZE][SIZE];
    int total = 0;
    int rowTimes[10];
    int columnTimes[10];
    createMatrix(mat);

    for(int i = 1; i < TIMES + 1; i++){
        printf("=======================================================\n");
        printf("Loop Count: %d \n", i);
        uint64_t rowTime = row_sum(mat, &total);
        uint64_t columnTime = column_sum(mat, &total);

        printf("Processing time (Rows): %ld \n", rowTime);
        rowTimes[i] = rowTime;

        printf("Processing time (Columns): %ld  \n", columnTime);
        columnTimes[i] = columnTime;
        printf("=======================================================\n");
        total = 0;
    }

    sort(rowTimes);
    sort(columnTimes);

    printf("(Row Median: %d) \n", rowTimes[4]);
    printf("(Column Median: %d) \n", columnTimes[4]);
    return 0;
}