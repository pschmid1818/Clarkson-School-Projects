#include <stdio.h>
#include <math.h>

void printFactors(int num) {

    if(num < 1) 
        printf("Error: Given number less than 1");
    else {
        for(int i = 1; i < sqrt(num); i++) { 
            if (num % i == 0) {
                printf("%d %d ", i, (num/i));
            }
        }  
    } 
    printf("\n");
}