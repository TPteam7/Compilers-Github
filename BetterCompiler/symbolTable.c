#include "symbolTable.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define DEFAULT_VAR_TABLE_SIZE 100

int printDebug = 0;

// Function to create a new symbol table
SymbolTable* createSymbolTable(int size) {
    printf("Creating symbol table\n");

    SymbolTable* newTable = (SymbolTable*)malloc(sizeof(SymbolTable));
    if (!newTable) return 0;

    newTable->size = size;
    newTable->table = (Symbol**)malloc(sizeof(Symbol*) * size);
    if (!newTable->table) {
        free(newTable);
        return 0;
    }

    for (int i = 0; i < size; i++) {
        newTable->table[i] = 0;
    }

    return newTable;
}

// Function to create a new variable symbol table
VariableSymbolTable* createVariableSymbolTable(int size) {
    VariableSymbolTable* newTable = (VariableSymbolTable*)malloc(sizeof(VariableSymbolTable));
    if (!newTable) return 0;

    newTable->size = size;
    newTable->table = (Variable**)malloc(sizeof(Variable*) * size);
    if (!newTable->table) {
        free(newTable);
        return 0;
    }

    for (int i = 0; i < size; i++) {
        newTable->table[i] = 0;
    }

    return newTable;
}

// Hash function to map a name to an index in the SymbolTable
unsigned int hashSymbolTable(SymbolTable* table, char* name) {
    unsigned int hashval = 0;
    for (; *name != '\0'; name++) hashval = *name + (hashval << 5) - hashval;
    return hashval % table->size;
}

// Hash function to map a name to an index in the VariableSymbolTable
unsigned int hashVariableTable(VariableSymbolTable* table, char* name) {
    unsigned int hashval = 0;
    for (; *name != '\0'; name++) hashval = *name + (hashval << 5) - hashval;
    return hashval % table->size;
}

// Function to add a function to the table
void addSymbol(SymbolTable* table, char* functionName, char* returnType) {
    Symbol* newSymbol = (Symbol*)malloc(sizeof(Symbol));
    if (!newSymbol) return;

    // Initialize the new symbol
    newSymbol->functionName = strdup(functionName);
    newSymbol->returnType = strdup(returnType);

    // Create the VariableSymbolTable for the function
    newSymbol->variables = createVariableSymbolTable(DEFAULT_VAR_TABLE_SIZE);

    if (table == NULL || table->table == NULL) {
        fprintf(stderr, "Symbol table or table array not initialized\n");
        // Handle the error, possibly free newSymbol and return
    }

    unsigned int hashval = hashSymbolTable(table, functionName);
    newSymbol->next = table->table[hashval];  
    table->table[hashval] = newSymbol;
}

// Function to add a variable to the table
void addVariable(VariableSymbolTable* table, char* variableName, char* variableType, int arraySize) {
    Variable* newVariable = (Variable*)malloc(sizeof(Variable));
    if (!newVariable) return;

    // Initialize the new variable
    newVariable->variableName = strdup(variableName);
    newVariable->variableType = strdup(variableType);
    newVariable->arraySize = arraySize;

    if (table == NULL || table->table == NULL) {
        fprintf(stderr, "Variable table or table array not initialized\n");
        // Handle the error, possibly free newVariable and return
    }

    unsigned int hashval = hashVariableTable(table, variableName);
    newVariable->next = table->table[hashval];  
    table->table[hashval] = newVariable;
}

// Function to look up a functionName in the SymbolTable
Symbol* lookupSymbol(SymbolTable* table, char* functionName) {
    if (printDebug == 1)
        printf("Looking up %s\n", functionName);

    unsigned int hashval = hashSymbolTable(table, functionName);
    #include <stddef.h> // Include the header file for NULL macro

    // Search the linked list at table->table[hashval]
    // Check if the entry at hashval is null

    
    if (table->table[hashval] == NULL) {
        if (printDebug == 1)
            printf("No symbol found at hash value %u\n", hashval);
        return NULL;
    } else {
            if (printDebug == 1)
                printf("SYMBOL TABLE ERROR:\nSymbol found at hash value %u\n", hashval);
            for (Symbol* sym = table->table[hashval]; sym != 0; sym = sym->next) {
                if(printDebug == 1)
                    printf("Symbol Function Name: %s\n", sym->functionName);
                if (strcmp(functionName, sym->functionName) == 0) return sym;
            }
      }   
    
    return NULL;
}

// Function to look up a variable in the VariableSymbolTable
Variable* lookupVariable(VariableSymbolTable* table, char* variableName) {
    if (printDebug == 1)
        printf("Looking up %s\n", variableName);

    unsigned int hashval = hashVariableTable(table, variableName);
    #include <stddef.h> // Include the header file for NULL macro

    // Search the linked list at table->table[hashval]
    // Check if the entry at hashval is null
    if (table->table[hashval] == NULL) {
        if (printDebug == 1)
            printf("No variable found at hash value %u\n", hashval);
        return NULL;
    } else {
            if (printDebug == 1)
                printf("VARIABLE SYMBOL TABLE ERROR:\nVariable found at hash value %u\n", hashval);
            for (Variable* var = table->table[hashval]; var != 0; var = var->next) {
                if(printDebug == 1)
                    printf("Variable Name: %s\n", var->variableName);
                if (strcmp(variableName, var->variableName) == 0) return var;
            }
      }   
    
    return NULL;
}

// Function to free the symbol table
void freeSymbolTable(SymbolTable* table) {
    for (int i = 0; i < table->size; i++) {
        Symbol* sym = table->table[i];
        while (sym != 0) {
            Symbol* nextSym = sym->next;

            // Free dynamically allocated fields of Symbol
            free(sym->functionName);
            free(sym->returnType);
            freeVariableSymbolTable(sym->variables);

            // Free other dynamically allocated fields of Symbol
            free(sym);
            sym = nextSym;
        }
    }
    free(table->table);
    free(table);
}

// Function to free the variable symbol table
void freeVariableSymbolTable(VariableSymbolTable* table) {
    for (int i = 0; i < table->size; i++) {
        Variable* var = table->table[i];
        while (var != 0) {
            Variable* nextVar = var->next;
            free(var->variableName);
            free(var->variableType);

            // Free other dynamically allocated fields of Variable
            free(var);
            var = nextVar;
        }
    }
    free(table->table);
    free(table);
}

// Function to print the symbol table
void printSymbolTable(SymbolTable* table) {
    printf("\n----- SYMBOL TABLE -----\n");
    for (int i = 0; i < table->size; i++) {
        Symbol* sym = table->table[i];
        while (sym != 0) {
            printf("Name: %s, Type: %s\n", sym->functionName, sym->returnType);

            // Print the variable symbol table
            printVariableSymbolTable(sym->variables);

            // Print other fields of Symbol
            sym = sym->next;
        }
    }
    printf("------------------------\n\n");
}

// Function to print the variable symbol table
void printVariableSymbolTable(VariableSymbolTable* table) {
    printf("\n----- VARIABLE SYMBOL TABLE -----\n");
    for (int i = 0; i < table->size; i++) {
        Variable* var = table->table[i];
        while (var != 0) {
            printf("Name: %s, Type: %s, Array Size: %d\n", var->variableName, var->variableType, var->arraySize);

            // Print other fields of Variable
            var = var->next;
        }
    }
    printf("------------------------\n\n");
}
