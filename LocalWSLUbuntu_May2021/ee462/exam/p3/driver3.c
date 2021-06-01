#include "/data/class/ee462sp21/public/p3/include/randfuncs.h"
#include "stdio.h"

int main() {
    initRand;

    int sum = 0;
    //print 100 random integers 0 <= x <= 80
    for(int i = 0; i <= 1000; i++) 
        sum = sum + getIntRandom(81);
    printf("%d\n", sum);

    float fsum = 0.0;
    //print 100 random floats 0 <= x <= 1.0
    for(int i = 0; i <= 500; i++) 
        fsum = fsum + getFloatRandom();
    printf("%f\n", fsum);
    return 0;
}
