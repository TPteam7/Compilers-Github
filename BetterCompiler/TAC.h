// Define a structure for TAC instructions
#ifndef TAC_H
#define TAC_H

#include "AST.h"
#include <stdbool.h>

typedef struct TAC {
    char* op;   // Operator
    char* arg1; // Argument 1
    char* arg2; // Argument 2
    char* result; // Result
    char* nodetype; //Debug helper
    struct TAC* next; // Next instruction
} TAC;

extern TAC* tacHead;

#define MAX 100  // Maximum stack size

// Define the Stack structure
typedef struct Stack {
    char* endLabel[MAX];  // Array to store stack elements
    int top;        // Index of the top element
} Stack;

// Function declarations
void initializeStack(Stack* stack);        // Initialize the stack
int isEmpty(Stack* stack);                // Check if the stack is empty
int isFull(Stack* stack);                 // Check if the stack is full
void push(Stack* stack, char* value);        // Push an element onto the stack
char* pop(Stack* stack);                     // Pop an element from the stack
char* peek(Stack* stack);                    // Peek at the top element without popping

int allocateNextAvailableTempVar(int tempVars[]);
TAC* generateTAC(ASTNode* expr);
void freeTAC(TAC* tac);
char* findOrCreateTemp(ASTNode* node);
char* createTempVar();
char* createOperand(ASTNode* node);
void printTAC(TAC** tac);
void initializeTempVars();
void deallocateTempVar(int tempVars[], int index);
bool isNonActionableNodeType(NodeType nType);
int allocateNextAvailableTempVar(int tempVars[]);
void appendTAC(TAC** head, TAC* newInstruction);
void printTACToFile(const char* filename, TAC** tac);
void cleanupTAC(TAC** tac);

#endif // TAC_H