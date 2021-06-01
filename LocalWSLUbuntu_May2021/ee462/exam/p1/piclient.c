#include "stdio.h"
#include "set.h"
#include "stack.h"


int main() {
printf("\n");    
//i.
    //init set
    intSetPtr s1 = initIntSet(5);
    //add values
    addToSet(s1, 10);
    addToSet(s1, -3);
    addToSet(s1, 88);
    addToSet(s1, 765);
    addToSet(s1, 21);

//ii.    
    //print set
    printf("Set 1: ");
    print(s1);

//iii.
    //add value
    addToSet(s1, 190);

printf("\n");
//iv.
    //init set
    intSetPtr s2 = initIntSet(10);
    //add values
    addToSet(s2, 100);
    addToSet(s2, 200);

//v.    
    //print set
    printf("Set 2: ");
    print(s2);

printf("\n");
//vi.
    //init stack
    intsetStackPtr xst = initStack(4);

//vii.
    //push to stack
    push(xst, s1);

//viii.
    //push to stack
    push(xst, s2);

//ix.
    //print topmost value of set
    printf("Top of Stack: ");
    printTopOfStack(xst);

//x.
    //remove topmost value of set
    pop(xst);

//xi.
    //print topmost value of set
    printf("Top of Stack: ");
    printTopOfStack(xst);

    printf("\n");
    return 0;
}