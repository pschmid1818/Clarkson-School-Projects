#include "randfuncs.h"
#include "stdio.h"

int main() {
    initRand;

    //print 100 random integers 0 <= x <= 80
    for(int i = 0; i <= 1000; i++) 
        printf("%d\n", getIntRandom(81));

    //print 100 random floats 0 <= x <= 1.0
    for(int i = 0; i <= 500; i++) 
        printf("%f\n", getFloatRandom());

    return 0;
}
