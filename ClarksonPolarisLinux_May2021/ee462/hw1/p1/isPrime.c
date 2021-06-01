#include <stdio.h>

int isPrime(int x) {

    int count = 0;
    if(x < 1) 
        printf("Error: Given number less than 1\n");
    else if(x == 1) {
        //just to specify it is different, count remains 0
    }
    else {
        for(int i = 2; i < x; i++) {
            if(x % i == 0) {
                count++;
            }
        }
    }

    int test;
    if(count == 0) 
        test = 1;
    else 
        test = 0;

    return test;
}
