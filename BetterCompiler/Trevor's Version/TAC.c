#include "TAC.h"
#include <string.h>
#include <stdio.h>

TAC* tacHead = NULL;
int tempVars[60];

// Implement functions to generate TAC expressions
TAC* generateTAC(ASTNode* node) {

    if (node == NULL) return NULL;

    TAC* instruction = (TAC*)malloc(sizeof(TAC));
    if (!instruction) return NULL;

    // Initialize fields to avoid garbage values
    instruction->arg1 = NULL;
    instruction->arg2 = NULL;
    instruction->op = NULL;
    instruction->result = NULL;
    instruction->nodetype = NULL;
    instruction->next = NULL;

    printf("Processing Node Type: %d\n", node->nType);  // Debug Statement

    switch (node->nType) {
        case NodeType_Program: {
            generateTAC(node->program.stmtList);
            break;
        }
        case NodeType_StmtList: {
            generateTAC(node->stmtList.stmt);
            generateTAC(node->stmtList.stmtList);
            break;
        }
        case NodeType_Stmt: {
            generateTAC(node->stmt.child);
            break;
        }
        case NodeType_FunctionDeclaration: {
            generateTAC(node->functionDeclaration.type);
            generateTAC(node->functionDeclaration.id);
            generateTAC(node->functionDeclaration.paramList);
            generateTAC(node->functionDeclaration.block);

            //instruction->arg1 = blockTAC->result;
            instruction->op = "function";
            //instruction->arg2 = createOperand(node->functionDeclaration.id);
            //instruction->result = createTempVar();
            //instruction->nodetype = "FunctionDeclaration";

            break;
        }
        case NodeType_FunctionCall: {
            generateTAC(node->functionCall.id);
            generateTAC(node->functionCall.argList);
            break;
        }
        case NodeType_ParamList: {
            generateTAC(node->paramList.paramTail);
            break;
        }
        case NodeType_ParamTail: {
            generateTAC(node->paramTail.param);
            generateTAC(node->paramTail.paramTail);
            break;
        }
        case NodeType_Param: {
            generateTAC(node->param.child);
            break;
        }
        case NodeType_ArgList: {
            generateTAC(node->argList.argTail);
            break;
        }
        case NodeType_ArgTail: {
            generateTAC(node->argTail.expr);
            generateTAC(node->argTail.argTail);
            break;
        }
        case NodeType_Block: {
            generateTAC(node->block.blockStmtList);
            generateTAC(node->block.returnStmt);
            break;
        }
        case NodeType_BlockStmtList: {
            generateTAC(node->blockStmtList.blockStmt);
            generateTAC(node->blockStmtList.blockStmtList);
            break;
        }
        case NodeType_BlockStmt: {
            generateTAC(node->blockStmt.child);
            break;
        }
        case NodeType_Return: {
            generateTAC(node->returnStmt.expr);
            break;
        }
        case NodeType_Declaration: {
            generateTAC(node->declaration.type);
            generateTAC(node->declaration.id);
            break;
        }
        case NodeType_ArrayDeclaration: {
            // Generate TAC for the size of the array
            generateTAC(node->arrayDeclaration.type);
            generateTAC(node->arrayDeclaration.id);
            TAC* sizeTAC = generateTAC(node->arrayDeclaration.size);

            instruction->arg1 = NULL;
            instruction->op = "alloc";
            instruction->arg2 = sizeTAC->result;
            instruction->result = createOperand(node->arrayDeclaration.id);
            instruction->nodetype = "ArrayDeclaration";

            break;
        }
        case NodeType_ArrayAssignment: {
            generateTAC(node->arrayAssignment.id);
            TAC* indexTAC = generateTAC(node->arrayAssignment.index);
            TAC* valueTAC = generateTAC(node->arrayAssignment.value);

            instruction->arg1 = valueTAC->result;
            instruction->op = "assign";
            instruction->arg2 = indexTAC->result;
            instruction->result = createOperand(node->arrayAssignment.id);
            instruction->nodetype = "ArrayAssignment";

            break;
        }
        case NodeType_ArrayAccess: {
            generateTAC(node->arrayAccess.id);
            TAC* indexTAC = generateTAC(node->arrayAccess.index);

            instruction->arg1 = createOperand(node->arrayAccess.id);
            instruction->op = "access";
            instruction->arg2 = indexTAC->result;
            instruction->result = createTempVar();
            instruction->nodetype = "ArrayAccess";

            break;
        }
        case NodeType_Type: {
            break;
        }
        case NodeType_Assignment: {
            generateTAC(node->assignment.id);
            TAC* exprTAC = generateTAC(node->assignment.expr); 

            instruction->arg1 = exprTAC->result;
            instruction->op = "=";
            instruction->arg2 = NULL;      
            instruction->result = createOperand(node->assignment.id);
            instruction->nodetype = "Assignment";

            break;
        }
        case NodeType_Print: {
            generateTAC(node->print.expr);
            TAC* exprTAC = generateTAC(node->print.expr); 
            
            instruction->arg1 = exprTAC->result;
            instruction->op = "print";
            instruction->arg2 = NULL;
            instruction->result = NULL;
            instruction->nodetype = "Print";
            break;
        }
        case NodeType_Expr: {
            TAC* leftTAC = generateTAC(node->expr.left);
            TAC* rightTAC = generateTAC(node->expr.right);

            instruction->arg1 = leftTAC->result; 
            instruction->arg2 = rightTAC->result;
            instruction->op = node->expr.op;
            instruction->result = createTempVar();
            instruction->nodetype = "Expr";

            break;
        }
        case NodeType_Term: {
            TAC* leftTAC = generateTAC(node->term.left);
            TAC* rightTAC = generateTAC(node->term.right);

            instruction->arg1 = leftTAC->result;
            instruction->arg2 = rightTAC->result;
            instruction->op = node->expr.op;
            instruction->result = createTempVar();
            instruction->nodetype = "Term";

            break;
        }
        case NodeType_Factor: {
            generateTAC(node->factor.child);
            break;
        }
        case NodeType_ID: {
            instruction->result = createOperand(node); 
            instruction->op = NULL; 
            instruction->arg1 = NULL;
            instruction->arg2 = NULL;
            instruction->nodetype = "Expr";

            break;
        }
        case NodeType_Number: {
            instruction->op = "=";
            instruction->arg1 = createOperand(node);
            instruction->arg2 = NULL;
            instruction->result = createTempVar();
            instruction->nodetype = "Number";

            break;
        }
        

        default:
            fprintf(stderr, "Unknown Node Type: %d\n", node->nType);
            free(instruction);
            return NULL;
    }


    instruction->next = NULL;  // Make sure to null-terminate the new instruction
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
void printTAC(TAC** tac) {
    if (!tac) return;

    cleanupTAC(tac);

    // Print header
    printf("\nRESULT\tARG1\tOP\tARG2\tNodeType\n");

    // Iterate through the linked list using a for loop
    for (TAC* current = *(tac); current != NULL; current = current->next) {
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

void printTACToFile(const char* filename, TAC** tac) {
    if (!tac) return;

    cleanupTAC(tac);
    FILE* file = fopen(filename , "w");
    if (!file) {
        perror("Failed to open file");
        return;
    }
    TAC* current = *(tac);
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