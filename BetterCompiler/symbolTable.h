#ifndef SYMBOL_TABLE1_H
#define SYMBOL_TABLE1_H

#include <stdlib.h>
#include <string.h>

// Symbol structure

// Define the Symbol struct
typedef struct Symbol {
    char* functionName;
    char* returnType;
    struct VariableSymbolTable* variables;
    struct Symbol* next;
} Symbol;

// Define the Variable struct
typedef struct Variable {
    char* variableName;
    char* variableType;
    int arraySize;
    struct Variable* next;
} Variable;

// Define the variableTable struct
typedef struct VariableSymbolTable {
    int size;
    struct Variable** table;
} VariableSymbolTable;

// Define the SymbolTable struct
typedef struct SymbolTable {
    int size;
    struct Symbol** table;
    VariableSymbolTable* topLevelStatements;  // Holds non-function variables
} SymbolTable;

// Function declarations
SymbolTable* createSymbolTable(int size);
VariableSymbolTable* createVariableSymbolTable(int size);

void addSymbol(SymbolTable* table, char* name, char* type);
void addVariable(VariableSymbolTable* table, char* name, char* type, int arraySize);

Symbol* lookupSymbol(SymbolTable* table, char* name);
Variable* lookupVariable(VariableSymbolTable* table, char* name);

void freeSymbolTable(SymbolTable* table);
void freeVariableSymbolTable(VariableSymbolTable* table);

void printSymbolTable(SymbolTable* table);  // For debugging
void printVariableSymbolTable(VariableSymbolTable* table);  // For debugging

#endif // SYMBOL_TABL1_H