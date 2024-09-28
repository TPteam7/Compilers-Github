#include "semantic.h"
#include <stdio.h>

// Perform semantic analysis on the AST
TAC* tacHead = NULL;
int printDebugSemantic = 0;
int tempVars[60];

void semanticAnalysis(ASTNode* node, SymbolTable* symTab) 
/*
Purpose: 
    Performs semantic analysis by traversing the AST, 
        checks for undeclared variables

ARGS:
    ASTNode* node: the AST node to be analyzed

    SymbolTable* symTab: the symbol table to be used for checking 
        undeclared variables
*/
{
    if (node == NULL)
        return;

    switch (node->nType) {
        // No check needed
        case NodeType_Program:
            printf("Performing semantic analysis on program\n");

            semanticAnalysis(node->program.stmtList, symTab);
            break;
        // No check needed
        case NodeType_StmtList:
            if (printDebugSemantic == 1)
                printf("Performing semantic analysis on stmtlist\n");

            semanticAnalysis(node->stmtList.stmt, symTab);
            semanticAnalysis(node->stmtList.stmtList, symTab);
            break;
        // No check needed
        case NodeType_Stmt:
            if (printDebugSemantic == 1)
                printf("Performing semantic analysis on stmt\n");

            semanticAnalysis(node->stmt.child, symTab);
            break;
        // Check for redeclaration of variables
        case NodeType_Declaration:
            if (lookupSymbol(symTab, node->declaration.id->id.name) != NULL) {
                fprintf(stderr, "\nSEMANTIC ERROR:\nVariable %s has already been declared\n\n", node->declaration.id->id.name);
                exit(0);
                break;
            }
            else {	
                // Add variable to symbol table
                addSymbol(symTab, node->declaration.id->id.name, node->declaration.type->type.typeName);
            }
            if (printDebugSemantic == 1)
                printf("Performing semantic analysis on declaration\n");

            semanticAnalysis(node->declaration.type, symTab);
            semanticAnalysis(node->declaration.id, symTab);
            break;
        // No check needed
        case NodeType_Type:
            if (printDebugSemantic == 1)
                printf("Performing semantic analysis on type: %s\n", node->type.typeName);

            break;
        // Check for declaration of variables
        case NodeType_Assignment:
            if (lookupSymbol(symTab, node->assignment.id->id.name) == NULL) {
                fprintf(stderr, "\nSEMANTIC ERROR:\nVariable %s has already been declared\n\n", node->assignment.id->id.name);
                exit(0);
                break;
            }
            if (printDebugSemantic == 1)
                printf("Performing semantic analysis on assignment\n");

            semanticAnalysis(node->assignment.id, symTab);
            semanticAnalysis(node->assignment.expr, symTab);
            break;
        // So this needs a check but I think it will just go to expression first
        case NodeType_Print:
            if (printDebugSemantic == 1)
                printf("Performing semantic analysis on print\n");

            semanticAnalysis(node->print.expr, symTab);
            break;
        // Check needed for declaration of variables
        case NodeType_Expr:
            if (printDebugSemantic == 1)
                printf("Performing semantic analysis on expr\n");

            semanticAnalysis(node->expr.left, symTab);
            semanticAnalysis(node->expr.right, symTab);
            break;
        // Check needed for declaration of variables
        case NodeType_Term:
            if (printDebugSemantic == 1)
                printf("Performing semantic analysis on term\n");

            semanticAnalysis(node->term.left, symTab);
            semanticAnalysis(node->term.right, symTab);
            break;
        // Check needed for declaration of variables
        case NodeType_Factor:
            if (printDebugSemantic == 1)
                printf("Performing semantic analysis on factor\n");

            semanticAnalysis(node->factor.child, symTab);
            break;
        // Check for declaration of variable
        case NodeType_ID:
            if (lookupSymbol(symTab, node->id.name) == NULL) {
                fprintf(stderr, "Semantic error: Variable %s has not been declared\n", node->id.name);
                exit(0);
                break;
            }
            if (printDebugSemantic == 1)
                printf("ID: %s\n", node->id.name);
            break;
        // No check needed
        case NodeType_Number:
            if (printDebugSemantic == 1)
                printf("Number: %i\n", node->number.value);
            break;
        default:
            fprintf(stderr, "Unknown Node Type\n");
    }

    // Generate TAC for the expression node, assignment, declaration, or print
    if (node->nType == NodeType_Expr || node->nType == NodeType_Assignment ||  node->nType == NodeType_Print) {
        // Generate Three-Address Code (TAC) for the expression node
        TAC* tac = generateTACForExpr(node);

        // Process or store the generated TAC
        printTAC(tac);
    }

}

// Implement functions to generate TAC expressions
TAC* generateTACForExpr(ASTNode* expr) {
    // Depending on your AST structure, generate the appropriate TAC
    // If the TAC is generated successfully, append it to the global TAC list
    // Return the generated TAC, so that it can be used by the caller, e.g. for printing

    //printf("Start: %d\n", expr->nType);
    if (!expr) return NULL;

    TAC* instruction = (TAC*)malloc(sizeof(TAC));
    if (!instruction) return NULL;

    switch (expr->nType) {
        // Expression
        case NodeType_Expr: {
            if(printDebugSemantic == 1)
                printf("Generating TAC for expression\n");      // output: t1 = 2 + 3

            TAC* leftTAC = generateTACForExpr(expr->expr.left); // Generate TAC for the left side of the expression
            TAC* rightTAC = generateTACForExpr(expr->expr.right); // Generate TAC for the right side of the expression


            instruction->arg1 = leftTAC->result; // The result of the left side of the expression
            instruction->arg2 = rightTAC->result; // The result of the right side of the expression

            // instruction->arg1 = createOperand(expr->expr.left);     // 2. Could also be a temp variable
            // instruction->arg2 = createOperand(expr->expr.right);    // 3. Could also be a temp variable
            instruction->op = "+";            // +
            instruction->result = createTempVar();            // t1

            //deallocateTempVar(tempVars, atoi(leftTAC->result + 1));  // Free left temp (assumes temp is "tN")
            //deallocateTempVar(tempVars, atoi(rightTAC->result + 1)); // Free right temp

            break;
        }
        // Assignment
        case NodeType_Assignment: {
            if(printDebugSemantic == 1)
                printf("Generating TAC for assignment\n");

            TAC* exprTAC = generateTACForExpr(expr->assignment.expr); // Generate TAC for the expression part

            instruction->arg1 = exprTAC->result; // The result of the expression
            instruction->op = "=";
            instruction->arg2 = NULL;       // We already have the result of the expression so no need for arg2
            instruction->result = createOperand(expr->assignment.id); // The variable being assigned to
            
            //deallocateTempVar(tempVars, atoi(exprTAC->result + 1));

            break;
        }
        // Print
        case NodeType_Print: {
            if(printDebugSemantic == 1)
                printf("Generating TAC for print\n");

            // print the print expression
            TAC* exprTAC = generateTACForExpr(expr->print.expr); // Generate TAC for the expression to print

            instruction->arg1 = exprTAC->result; // The expression to print
            instruction->op = "print";
            instruction->arg2 = NULL; // No second argument
            instruction->result = NULL; // No result
            break;
        }
        // Number
        case NodeType_Number: {
            if(printDebugSemantic == 1)
                printf("Generating TAC for number\n");

            instruction->result = createOperand(expr); // The number to assign
            instruction->op = NULL; // No operation for a number
            instruction->arg1 = NULL;
            instruction->arg2 = NULL;
            break;
        }
        // ID
        case NodeType_ID: {
            if(printDebugSemantic == 1)
                printf("Generating TAC for ID\n");

            instruction->result = createOperand(expr); // The ID to assign
            instruction->op = NULL; // No operation for an ID
            instruction->arg1 = NULL;
            instruction->arg2 = NULL;
            break;
        }
        default:
            fprintf(stderr, "Unknown Node Type: %d\n", expr->nType);
            free(instruction);
            return NULL;
    }

    instruction->next = NULL; // Make sure to null-terminate the new instruction

    // Append to the global TAC list
    appendTAC(&tacHead, instruction);

    return instruction;
}
// Function to create a new temporary variable for TAC
char* createTempVar() {
    static int count = 0;
    char* tempVar = malloc(10); // Enough space for "t" + number
    if (!tempVar) return NULL;
    count = allocateNextAvailableTempVar(tempVars);
    sprintf(tempVar, "t%d", count++);
    return tempVar;
}

char* createOperand(ASTNode* node) {
    // Depending on your AST structure, return the appropriate string
    // representation of the operand. For example, if the operand is a simple
    // expression or an identifier, return its string representation.
    // This function needs to be implemented based on your AST structure.
    if (!node) return NULL;

    if(printDebugSemantic == 1)
        printf("Creating operand for node type\n");

    switch (node->nType) {
        // Return the string representation of the number
        case NodeType_Number: {
            char* buffer = malloc(60);
            snprintf(buffer, 60, "%d", node->number.value);     //converts the number to a string
            return buffer;
        }
        // Return the string representation of the identifier
        case NodeType_ID: {
            return node->id.name;
            //return createTempVar();
        }
        // Create a temp variable for the expression
        case NodeType_Expr: {
            return createTempVar();
        }
        // Factor
        case NodeType_Factor: {
            return createOperand(node->factor.child);
        }
        default:
            return NULL;
    }
}

void printTAC(TAC* tac) {
    if (!tac) return;
    printf("\n");
    printf("RESULT\tARG1\tOP\tARG2\n");

    // Print the TAC instruction with non-null fields
    if(tac->result != NULL)
        printf("%s\t", tac->result);
    if(tac->arg1 != NULL)
        printf("%s\t", tac->arg1);
    if(tac->op != NULL)
        printf("%s\t", tac->op);
    if(tac->arg2 != NULL)
        printf("%s\t", tac->arg2);
    printf("\n\n");
}

// Print the TAC list to a file
// This function is provided for reference, you can modify it as needed

void printTACToFile(const char* filename, TAC* tac) {
    FILE* file = fopen(filename , "w");
    if (!file) {
        perror("Failed to open file");
        return;
    }
    TAC* current = tac;
    while (current != NULL) {
        if (strcmp(current->op,"=") == 0) {
            fprintf(file, "%s = %s\n", current->result, current->arg1);
        }
        else {
            if(current->result != NULL)
                fprintf(file, "%s = ", current->result);
            if(current->arg1 != NULL)
                fprintf(file, "%s ", current->arg1);
            if(current->op != NULL)
                fprintf(file, "%s ", current->op);
            if(current->arg2 != NULL)
                fprintf(file, "%s ", current->arg2);
            fprintf(file, "\n");
    }
        current = current->next;
    }
    fclose(file);
    printf("TAC written to %s\n", filename);
}


// Temporary variable allocation and deallocation functions //

void initializeTempVars() {
    for (int i = 0; i < 60; i++) {
        tempVars[i] = 0;
    }
}

int allocateNextAvailableTempVar(int tempVars[]) {
   // implement the temp var allocation logic
   // use the tempVars array to keep track of allocated temp vars

    // search for the next available temp var
    for (int i = 0; i < 60; i++) {
        if (tempVars[i] == 0) {
            tempVars[i] = 1;
            return i;
        }
    }
    return -1; // No available temp var
}

void deallocateTempVar(int tempVars[], int index) {
    // implement the temp var deallocation logic
    // use the tempVars array to keep track of allocated temp vars
    if (index >= 0 && index < 60) {
        tempVars[index] = 0;
    }
}

void appendTAC(TAC** head, TAC* newInstruction) {
    if (!*head) {
        *head = newInstruction;
    } else {
        TAC* current = *head;
        while (current->next) {
            current = current->next;
        }
        current->next = newInstruction;
    }
}
