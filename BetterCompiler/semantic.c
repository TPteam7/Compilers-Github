#include "semantic.h"
#include <stdio.h>


// Perform semantic analysis on the AST
TAC* tacHead = NULL;
int printDebugSemantic = 1;
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

    // ASTNode* current = NULL;
    // if(node->nType == NodeType_Expr) {
    //     current = node;
    //     while (current != NULL && current->nType == NodeType_Expr) {
    //         current = current->parent;
    //     }
    // }


    printf("Break before TAC");
    // Generate TAC for the expression node, assignment, declaration, or print
    if ((node->nType == NodeType_Expr && (node->parent->nType != NodeType_Assignment && node->parent->nType != NodeType_Expr)) || node->nType == NodeType_Assignment || node->nType == NodeType_Print) {
        // Generate Three-Address Code (TAC) for the expression node
        printf("Generating TAC");
        generateTAC(node);
    }
}

int isUnderAssignmentWithOnlyExprInBetween(ASTNode* node) {
    ASTNode* current = node->parent;
    
    // Traverse up as long as we encounter Expr nodes
    while (current != NULL && current->nType == NodeType_Expr) {
        current = current->parent;
    }

    if (current != NULL && current->nType == NodeType_Assignment)
        return 1;
    else
        return 0;
}


//---------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------


// Implement functions to generate TAC expressions
TAC* generateTAC(ASTNode* expr) {

    if (expr == NULL) return NULL;

    TAC* instruction = (TAC*)malloc(sizeof(TAC));
    if (!instruction) return NULL;

    // Initialize fields to avoid garbage values
    instruction->arg1 = NULL;
    instruction->arg2 = NULL;
    instruction->op = NULL;
    instruction->result = NULL;
    instruction->nodetype = NULL;
    instruction->next = NULL;

    switch (expr->nType) {
        // Expression
        case NodeType_Expr: {
            TAC* leftTAC = generateTAC(expr->expr.left);
            TAC* rightTAC = generateTAC(expr->expr.right);


            instruction->arg1 = leftTAC->result; 
            instruction->arg2 = rightTAC->result;
            instruction->op = expr->expr.op;
            instruction->result = createTempVar();
            instruction->nodetype = "Expr";

            break;
        }
        // Term
        case NodeType_Term: {
            TAC* leftTAC = generateTAC(expr->term.left);
            TAC* rightTAC = generateTAC(expr->term.right);

            instruction->arg1 = leftTAC->result;
            instruction->arg2 = rightTAC->result;
            instruction->op = expr->expr.op;
            instruction->result = createTempVar();
            instruction->nodetype = "Term";

            break;
        }
        // Assignment
        case NodeType_Assignment: {
            TAC* exprTAC = generateTAC(expr->assignment.expr); 

            instruction->arg1 = exprTAC->result;
            instruction->op = "=";
            instruction->arg2 = NULL;      
            instruction->result = createOperand(expr->assignment.id);
            instruction->nodetype = "Assignment";

            break;
        }
        // Print
        case NodeType_Print: {
            TAC* exprTAC = generateTAC(expr->print.expr); 

            instruction->arg1 = exprTAC->result;
            instruction->op = "print";
            instruction->arg2 = NULL;
            instruction->result = NULL;
            instruction->nodetype = "Print";
            break;
        }
        // Number
        case NodeType_Number: {
            
            instruction->op = "=";
            instruction->arg1 = createOperand(expr);
            instruction->arg2 = NULL;
            instruction->result = createTempVar();
            instruction->nodetype = "Number";

            break;
        }
        // ID
        case NodeType_ID: {
            instruction->result = createOperand(expr); 
            instruction->op = NULL; 
            instruction->arg1 = NULL;
            instruction->arg2 = NULL;
            instruction->nodetype = "Expr";

            break;
        }
        default:
            fprintf(stderr, "Unknown Node Type: %d\n", expr->nType);
            free(instruction);
            return NULL;
    }

    instruction->next = NULL; // Make sure to null-terminate the new instruction

    // Print a new line for the current TAC instruction
    printf("\n");
        // Print the fields of the current TAC node, handling null pointers
    if (instruction->result != NULL)
        printf("%s\t", instruction->result);
    else
        printf("NULL\t");

    if (instruction->arg1 != NULL)
        printf("%s\t", instruction->arg1);
    else
        printf("NULL\t");

    if (instruction->op != NULL)
        printf("%s\t", instruction->op);
    else
        printf("NULL\t");

    if (instruction->arg2 != NULL)
        printf("%s\t", instruction->arg2);
    else
        printf("NULL\t");

    if (instruction->nodetype != NULL)
        printf("%s\t", instruction->nodetype);
    else
        printf("NULL\t");

    // Print a new line for the current TAC instruction
    printf("\n");
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

// Function to print all elements of the TAC linked list
void printTAC(TAC* tac) {
    if (!tac) return;

    cleanupTAC(&tac);

    // Print header
    printf("\nRESULT\tARG1\tOP\tARG2\tNodeType\n");

    // Iterate through the linked list using a for loop
    for (TAC* current = tac; current != NULL; current = current->next) {
        // Print the fields of the current TAC node, handling null pointers
        if (current->result != NULL)
            printf("%s\t", current->result);
        else
            printf("NULL\t");

        if (current->arg1 != NULL)
            printf("%s\t", current->arg1);
        else
            printf("NULL\t");

        if (current->op != NULL)
            printf("%s\t", current->op);
        else
            printf("NULL\t");

        if (current->arg2 != NULL)
            printf("%s\t", current->arg2);
        else
            printf("NULL\t");

        if (current->nodetype != NULL)
            printf("%s\t", current->nodetype);
        else
            printf("NULL\t");

        // Print a new line for the current TAC instruction
        printf("\n");
    }
    printf("\n");
}

void printTACToFile(const char* filename, TAC* tac) {

    cleanupTAC(&tac);
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

char* createOperand(ASTNode* node) {
    if (!node) return NULL;

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
        }
        default:
            return NULL;
    }
}

// Function to remove nodes with NULL arg1, arg2, and op
void cleanupTAC(TAC** head) {
    if (!head || !*head) return;

    TAC* current = *head;
    TAC* prev = NULL;

    while (current != NULL) {
        TAC* next = current->next;
        // Check if current node should be removed
        if (current->arg1 == NULL && current->arg2 == NULL && current->op == NULL) {
            // Remove current node
            if (prev == NULL) {
                // If current is the head, update the head
                *head = current->next;
            } else {
                // Skip the current node
                prev->next = current->next;
            }
            // Free the node's memory
            free(current);
        } else {
            // Move prev pointer only if current node is not removed
            prev = current;
        }
        // Move to the next node
        current = next;
    }
}