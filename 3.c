#include <stdio.h>

unsigned int amp(unsigned int num){
    printf("Number: %d \n", num);
    return (num << 1) + (num >> 1);
}

int main(){

    printf("Answer: %d \n", amp(4));
    printf("Answer: %d \n", amp(20));
    printf("Answer: %d \n", amp(24));
    printf("Answer: %d", amp(16));
    return 1;
}