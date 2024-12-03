#include <stdio.h>
#include <string.h>
#include "TACStack.h"

// Initialize the stack
void initTACStack(TACStack *stack) {
    stack->top = -1;
}

// Check if the stack is full
bool isTACStackFull(TACStack *stack) {
    return stack->top == MAX_SIZE - 1;
}

// Check if the stack is empty
bool isTACStackEmpty(TACStack *stack) {
    return stack->top == -1;
}

// Push a TAC object onto the stack
void pushTAC(TACStack *stack, TAC value) {
    if (isTACStackFull(stack)) {
        printf("Stack overflow! Cannot push TAC object\n");
        return;
    }
    stack->items[++(stack->top)] = value;
}

// Pop a TAC object from the stack
TAC popTAC(TACStack *stack) {
    if (isTACStackEmpty(stack)) {
        printf("Stack underflow! Cannot pop TAC object\n");
        return (TAC){"", "", "", ""};  // Return a default TAC object
    }
    return stack->items[(stack->top)--];
}

// Peek at the top TAC object without removing it
TAC peekTAC(TACStack *stack) {
    if (isTACStackEmpty(stack)) {
        printf("Stack is empty! Nothing to peek\n");
        return (TAC){"", "", "", ""};  // Return a default TAC object
    }
    return stack->items[stack->top];
}
