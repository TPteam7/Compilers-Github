// Define a structure for TAC instructions

#include "AST.h"

typedef struct TAC {
    char* op;   // Operator
    char* arg1; // Argument 1
    char* arg2; // Argument 2
    char* result; // Result
    char* nodetype; //Debug helper
    struct TAC* next; // Next instruction
} TAC;

extern TAC* tacHead;

int allocateNextAvailableTempVar(int tempVars[]);
TAC* generateTAC(ASTNode* expr);
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
