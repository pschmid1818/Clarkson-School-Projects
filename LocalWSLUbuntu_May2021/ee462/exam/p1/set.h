#ifndef SET_H
#define SET_H


typedef struct {
  int max_size;
  int numElements;
  int* elems;
} intSet;

typedef intSet* intSetPtr;

//initialize a set of integers with a possible maximumSize
//@  precondition: maxSize > 0
intSetPtr initIntSet(int maxSize);

//add element to set x
//@ postcondition: returns 0 if elem is successfully added, otherwise returns 1
int addToSet(intSetPtr x, int elem);


//pritn elements of the set
void print(intSetPtr x);

#endif
