#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "AST.h"        
#include "symbolTable.h" 

void semanticAnalysis(ASTNode* node, SymbolTable* symTab, VariableSymbolTable* varTab);

#endif // SEMANTIC_H
