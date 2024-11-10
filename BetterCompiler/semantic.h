#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "AST.h"        
#include "symbolTable.h" 

void semanticAnalysis(ASTNode* node, SymbolTable* symTab, VariableSymbolTable* varTab);
const char* evaluateExprType(ASTNode* expr, VariableSymbolTable* varTab);
int isFloat(const char* numberStr);


#endif // SEMANTIC_H
