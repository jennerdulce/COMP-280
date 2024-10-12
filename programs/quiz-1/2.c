#include <stdio.h>

int numUCChars(char *str) {
    int count = 0;
    
    while (*str) {
        if(*str >= 'A' && *str <= 'Z') {
            count++;
        }
        str++;
    }
    
    return count;
}

int main(){
    char someString[] = "HELLO worldWOrld ZZZZ 10 Looool";
    int count = numUCChars(someString);
    printf("Count: %d", count);
    return 1;
}

