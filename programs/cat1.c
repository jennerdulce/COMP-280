// gcc -o cat1 cat1.c -Wall
// TEST:
// ./cat1 -> type in any characters and should output what you just typed
// ./cat1 <filename> -> ./cat1 cat1.c -> should display ALL of the contents within file
// ./cat1 <filename> <filename> -> ./cat1 cat1.c sqrt.c-> should display error

#include <stdio.h>
void ProcessFile(FILE * f){
    int ch = fgetc(f);
    while(ch != EOF){
        putchar(ch);
        ch = fgetc(f);
    }
}

int main(int argc, char * argv[]){
    if(argc == 1){
        ProcessFile(stdin);
    }  else if(argc == 2){
        FILE * f = fopen(argv[1], "r");
        if(f == NULL){
            // fprintf(Stderr, "usage: cat1 [file]\n")
            perror("Error: ");
            return 2;
        } else {
            ProcessFile(f);
        }
    } else if(argc <= 3){
        perror("Error: Too many files to process.");
        return 1;
    }
    return 0;
}
