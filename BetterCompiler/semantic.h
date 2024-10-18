#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "AST.h"         // Assuming this includes the definition of ASTNode
#include "symbolTable.h" // Assuming this includes the definition of SymbolTable

// Define a structure for TAC instructions

typedef struct TAC {
    char* op;   // Operator
    char* arg1; // Argument 1
    char* arg2; // Argument 2
    char* result; // Result
    char* nodetype; //Debug helper
    struct TAC* next; // Next instruction
} TAC;

// This has been causing errors
//int tempVars[20];

extern TAC* tacHead; // Global head of the TAC instructions list

int allocateNextAvailableTempVar(int tempVars[]);
void semanticAnalysis(ASTNode* node, SymbolTable* symTab);
TAC* generateTAC(ASTNode* expr); //returns the TAC for the expression to print on console
int isUnderAssignmentWithOnlyExprInBetween(ASTNode* node);
char* findOrCreateTemp(ASTNode* node);
char* createTempVar();
char* createOperand(ASTNode* node);
void printTAC(TAC* tac);
void initializeTempVars();
void deallocateTempVar(int tempVars[], int index);
int allocateNextAvailableTempVar(int tempVars[]);
void appendTAC(TAC** head, TAC* newInstruction);
void printTACToFile(const char* filename, TAC* tac);
void cleanupTAC(TAC** tac);
// You can add more function declarations related to semantic analysis here

#endif // SEMANTIC_H
