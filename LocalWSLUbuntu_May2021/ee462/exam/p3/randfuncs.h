#ifndef RANDFUNCS_H
#define RANDFUNCS_H

//initialize the random number generator (call this first)
extern void initRand( void );

//returns an (integral) random number between 0 and max-1
extern int getIntRandom( int max );

//returns a floating-point random number between 0.0 and 1.0
extern float getFloatRandom( void );

#endif
