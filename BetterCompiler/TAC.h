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

#endif // TAC_H

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
