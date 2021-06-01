#ifndef STACK_H
#define STACK_H

#include "set.h"

typedef struct {
  int max_stack_size;
  int topOfStack;
  intSetPtr* thestack;
} intsetStack;

typedef intsetStack* intsetStackPtr;

intsetStackPtr initStack(int maxStackSize);

void push(intsetStackPtr, intSetPtr);

intSetPtr pop(intsetStackPtr);

void printTopOfStack(intsetStackPtr);

#endif
