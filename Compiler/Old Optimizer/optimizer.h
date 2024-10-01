#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include "semantic.h"

int isConstant(char* arg);
void constantFolding(TAC* head);
void copyPropagation(TAC* head);
int isVariableUsed(TAC* head, char* var);
TAC* deadCodeElimination(TAC* head);

// Apply all optimizations.
void optimize(TAC* head);

#endif