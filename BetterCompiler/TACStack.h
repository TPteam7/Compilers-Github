#ifndef TACSTACK_H
#define TACSTACK_H
#include "TAC.h"

#include <stdbool.h>

// Define the maximum size of the stack
#define MAX_SIZE 100

// Stack Structure for TAC
typedef struct {
    TAC items[MAX_SIZE];
    int top;
} TACStack;

// Function declarations
void initTACStack(TACStack *stack);
bool isTACStackFull(TACStack *stack);
bool isTACStackEmpty(TACStack *stack);
void pushTAC(TACStack *stack, TAC value);
TAC popTAC(TACStack *stack);
TAC peekTAC(TACStack *stack);

#endif  // TACSTACK_H