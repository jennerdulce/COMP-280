// gcc -o quad quad.c -Wall -lm
// lm is to compile math library
#include <math.h>
#include <stdio.h>

void quadratic(double a, double b, double c){
    double underSqrt = (b * b) - (4 * a * c);
    double sqrtValue;
    double rootA;
    double rootB;

    if(underSqrt < 0){
        printf("Number is imaginary. \n");
    } else {
        sqrtValue = sqrt(underSqrt);
        rootA = ((b * -1) + sqrtValue) / (2 * a);
        rootB = ((b * -1) - sqrtValue) / (2 * a);
        printf("Root 1: %lf \n", rootA);
        printf("Root 2: %lf \n", rootB);
    }
}

int main(){
        double a;
        double b;
        double c;
        printf("Enter a Number 3 numbers for variables a, b, and c: ");
        int result = scanf("%lf %lf %lf", &a, &b, &c);
        if(result == 3){
                quadratic(a, b, c);
        }
        return 0;
}
