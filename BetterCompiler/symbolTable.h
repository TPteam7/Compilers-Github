#ifndef SYMBOL_TABLE1_H
#define SYMBOL_TABLE1_H

#include <stdlib.h>
#include <string.h>

// Symbol structure

// Define the Symbol struct
typedef struct Symbol {
    char* functionName;
    char* returnType;
    struct variableSymbolTable* variables;
    struct Symbol* next;
} Symbol;

// Define the Variable struct
typedef struct Variable {
    char* variableName;
    char* variableType;
    int arraySize;
    struct Variable* next;
} Variable;

// Define the SymbolTable struct
typedef struct SymbolTable {
    int size;
    struct Symbol** table;
} SymbolTable;

// Define the variableTable struct
typedef struct variableSymbolTable {
    int size;
    struct Variable** table;
} variableSymbolTable;

// Function declarations
SymbolTable* createSymbolTable(int size);
variableSymbolTable* createVariableSymbolTable(int size);

void addSymbol(SymbolTable* table, char* name, char* type);
void addVariable(variableSymbolTable* table, char* name, char* type, int arraySize);

Symbol* lookupSymbol(SymbolTable* table, char* name);
Variable* lookupVariable(variableSymbolTable* table, char* name);

void freeSymbolTable(SymbolTable* table);
void freeVariableSymbolTable(variableSymbolTable* table);

void printSymbolTable(SymbolTable* table);  // For debugging
void printVariableSymbolTable(variableSymbolTable* table);  // For debugging

#endif // SYMBOL_TABL1_H