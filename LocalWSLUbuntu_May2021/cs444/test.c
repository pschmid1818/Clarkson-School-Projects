#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "time.h"
#include "pthread.h"
#include "semaphore.h"

int main() {
    int shiftDur = 0;
    clock_t start = clock();
    do {

        clock_t difference =  clock() - start;
        shiftDur = difference / CLOCKS_PER_SEC;


    } while(shiftDur < 5);
    printf("%d seconds taken", shiftDur);
}