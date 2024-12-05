#include "TAC.h"
#include <string.h>
#include <stdio.h>

TAC* tacHead = NULL;
int tempVars[60];
int printDebugTAC = 1;

// Counter for if-elseif-else statements
char labelBuffer[20];
int ifStmtCounter = 0;
int whileStmtCounter = 0;
//int elseIfStmtCounter = 0;
//int elseStmtCounter = 0;

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

    //printf("Processing Node Type: %d\n", node->nType);  // Debug Statement

    switch (node->nType) {
        case NodeType_Program: {
            //print debug statement
            if (printDebugTAC == 1)
                printf("Performing TAC generation on program\n");

            generateTAC(node->program.stmtList);
            break;
        }
        case NodeType_StmtList: {
            //print debug statement
            if (printDebugTAC == 1)
                printf("Performing TAC generation on stmtlist\n");

            generateTAC(node->stmtList.stmt);
            generateTAC(node->stmtList.stmtList);
            break;
        }
        case NodeType_Stmt: {
            //print debug statement
            if (printDebugTAC == 1)
                printf("Performing TAC generation on stmt\n");

            generateTAC(node->stmt.child);
            break;
        }
        case NodeType_FunctionDeclaration: {
            //print debug statement
            if (printDebugTAC == 1)
                printf("Performing TAC generation on function declaration\n");

            instruction->op = "function";
            instruction->arg2 = createOperand(node->functionDeclaration.id);
            instruction->nodetype = "FunctionDeclaration";

            instruction->next = NULL;
            appendTAC(&tacHead, instruction);

            generateTAC(node->functionDeclaration.type);
            generateTAC(node->functionDeclaration.id);
            generateTAC(node->functionDeclaration.paramList);
            generateTAC(node->functionDeclaration.block);

            break;
        }
        case NodeType_FunctionCall: {
            //print debug statement
            if (printDebugTAC == 1)
                printf("Performing TAC generation on function call\n");

            generateTAC(node->functionCall.id);
            generateTAC(node->functionCall.argList);

            if(node->parent->nType == NodeType_Assignment || node->parent->nType == NodeType_ArrayAssignment)
                instruction->result = createTempVar();
                instruction->op = "=";
            
            instruction->arg1 = "call";
            instruction->arg2 = createOperand(node->functionCall.id);
            instruction->nodetype = "FunctionCall";
            break;
        }
        case NodeType_IfBlock: {
            //print debug statement
            if (printDebugTAC == 1)
                printf("Performing TAC generation on if-elseif-else block\n");

            generateTAC(node->ifBlock.ifStmt);
            generateTAC(node->ifBlock.elseIfList);
            generateTAC(node->ifBlock.elseStmt);

            break;
        }
        case NodeType_IfStmt: {
            //print debug statement
            if (printDebugTAC == 1)
                printf("Performing TAC generation on if statement\n");

            TAC* conditionTAC = generateTAC(node->ifStmt.condition);

            // Create the call to the if statement
            sprintf(labelBuffer, "L%d", ifStmtCounter);
            instruction->result = strdup(labelBuffer);
            instruction->op = conditionTAC->op;
            instruction->arg1 = conditionTAC->arg1;
            instruction->arg2 = conditionTAC->arg2;
            instruction->nodetype = "IfStmtCall";

            instruction->next = NULL;
            appendTAC(&tacHead, instruction);

            // Create the label for the if statement block
            instruction = (TAC*)malloc(sizeof(TAC)); // Create a new instruction
            sprintf(labelBuffer, "L%d:", ifStmtCounter);
            instruction->result = strdup(labelBuffer);
            instruction->op = "if";
            instruction->arg1 = NULL;
            instruction->arg2 = NULL;
            instruction->nodetype = "IfStmt";

            ifStmtCounter++;        

            instruction->next = NULL;
            appendTAC(&tacHead, instruction);

            // Generate TAC for the if statement block
            generateTAC(node->ifStmt.block);

            // Add a instruction to end the else if block
            instruction = (TAC*)malloc(sizeof(TAC)); // Create a new instruction
            instruction->op = "end_if";
            instruction->nodetype = "End_IfStmt";

            instruction->next = NULL;
            appendTAC(&tacHead, instruction);
            
            break;
        }
        case NodeType_ElseIfStmt: {
            //print debug statement
            if (printDebugTAC == 1)
                printf("Performing TAC generation on else if statement\n");

            // Generate TAC for the condition of the else if statement
            TAC* conditionTAC = generateTAC(node->elseIfStmt.condition);

            // Create the call to the else if statement
            sprintf(labelBuffer, "L%d", ifStmtCounter);
            instruction->result = strdup(labelBuffer);
            instruction->op = conditionTAC->op;
            instruction->arg1 = conditionTAC->arg1;
            instruction->arg2 = conditionTAC->arg2;
            instruction->nodetype = "ElseIfStmtCall";

            instruction->next = NULL;
            appendTAC(&tacHead, instruction);

            // Create the label for the else if statement block
            instruction = (TAC*)malloc(sizeof(TAC)); // Create a new instruction
            sprintf(labelBuffer, "L%d:", ifStmtCounter);
            instruction->result = strdup(labelBuffer);
            instruction->op = "elseIf";
            instruction->arg1 = NULL;
            instruction->arg2 = NULL;
            instruction->nodetype = "ElseIfStmt";

            ifStmtCounter++;

            // Append the instruction to the TAC list
            instruction->next = NULL;
            appendTAC(&tacHead, instruction);

            // Generate TAC for the else if statement block
            generateTAC(node->elseIfStmt.block);

            // Add a instruction to end the else if block
            instruction = (TAC*)malloc(sizeof(TAC)); // Create a new instruction
            instruction->op = "end_elseIf";
            instruction->nodetype = "End_ElseIfStmt";

            instruction->next = NULL;
            appendTAC(&tacHead, instruction);

            generateTAC(node->elseIfStmt.next);
            break;
        }
        case NodeType_ElseStmt: {
            //print debug statement
            if (printDebugTAC == 1)
                printf("Performing TAC generation on else statement\n");

            sprintf(labelBuffer, "L%d", ifStmtCounter);
            instruction->result = strdup(labelBuffer);
            instruction->op = "else";
            instruction->nodetype = "ElseStmtCall";

            instruction->next = NULL;
            appendTAC(&tacHead, instruction);

            instruction = (TAC*)malloc(sizeof(TAC)); // Create a new instruction
            sprintf(labelBuffer, "L%d:", ifStmtCounter);
            instruction->result = strdup(labelBuffer);
            instruction->op = "else";
            instruction->arg1 = NULL;
            instruction->arg2 = NULL;
            instruction->nodetype = "ElseStmt";

            ifStmtCounter++;

            instruction->next = NULL;
            appendTAC(&tacHead, instruction);

            generateTAC(node->elseStmt.block);

            // Add a instruction to end the else block
            instruction = (TAC*)malloc(sizeof(TAC)); // Create a new instruction
            instruction->op = "end_else";
            instruction->nodetype = "End_ElseStmt";

            instruction->next = NULL;
            appendTAC(&tacHead, instruction);

            break;
        }
        case NodeType_WhileStmt: {
            //print debug statement
            if (printDebugTAC == 1)
                printf("Performing TAC generation on while statement\n");

            // Create the label for the while statement block
            sprintf(labelBuffer, "WhileStart%d:", whileStmtCounter);
            instruction->result = strdup(labelBuffer);
            instruction->op = "while";
            instruction->arg1 = NULL;
            instruction->arg2 = NULL;
            instruction->nodetype = "WhileStmt";

            whileStmtCounter++;

            instruction->next = NULL;
            appendTAC(&tacHead, instruction);

            TAC* conditionTAC = generateTAC(node->whileStmt.condition);

            // Create the call to the while statement
            instruction = (TAC*)malloc(sizeof(TAC)); // Create a new instruction
            sprintf(labelBuffer, "While%d", whileStmtCounter);
            instruction->result = strdup(labelBuffer);
            instruction->op = conditionTAC->op;
            instruction->arg1 = conditionTAC->arg1;
            instruction->arg2 = conditionTAC->arg2;
            instruction->nodetype = "WhileStmtCall";

            instruction->next = NULL;
            appendTAC(&tacHead, instruction);

            whileStmtCounter++;

            // Generate TAC for the while statement block
            generateTAC(node->whileStmt.block);

            //Add a instruction to end the while block
            instruction = (TAC*)malloc(sizeof(TAC)); // Create a new instruction
            instruction->op = "end_while";
            instruction->nodetype = "End_WhileStmt";

            instruction->next = NULL;
            appendTAC(&tacHead, instruction);

            break;
        }
        case NodeType_Condition: {
            //print debug statement
            if (printDebugTAC == 1)
                printf("Performing TAC generation on condition\n");

            TAC *leftExprTAC = generateTAC(node->condition.expr);
            TAC *rightExprTAC = generateTAC(node->condition.expr2);

            instruction->arg1 = leftExprTAC->result;
            instruction->arg2 = rightExprTAC->result;
            instruction->op = strdup(node->condition.sign->sign.op);
            instruction->nodetype = "Condition";

            generateTAC(node->condition.conditionTail);

            break;
        }
        case NodeType_ConditionTail: {
            //print debug statement
            if (printDebugTAC == 1)
                printf("Performing TAC generation on conditiontail\n");

            generateTAC(node->conditionTail.conjunction);

            generateTAC(node->conditionTail.condition);
            break;
        }
        case NodeType_Sign: {
            //print debug statement
            if (printDebugTAC == 1)
                printf("Performing TAC generation on sign\n");

            break;
        }
        case NodeType_Conjunction: {
            //print debug statement
            if (printDebugTAC == 1)
                printf("Performing TAC generation on conjunction\n");

            instruction->op = strdup(node->conjunction.op);
            instruction->nodetype = "Conjunction";
            break;
        }
        case NodeType_ParamList: {
            //print debug statement
            if (printDebugTAC == 1)
                printf("Performing TAC generation on paramlist\n");

            generateTAC(node->paramList.paramTail);
            break;
        }
        case NodeType_ParamTail: {
            //print debug statement
            if (printDebugTAC == 1)
                printf("Performing TAC generation on paramtail\n");
            
            generateTAC(node->paramTail.param);
            generateTAC(node->paramTail.paramTail);
            break;
        }
        case NodeType_Param: {
            //print debug statement
            if (printDebugTAC == 1)
                printf("Performing TAC generation on param\n");

            generateTAC(node->param.child);

            instruction->arg1 = createOperand(node->param.child->declaration.id);
            instruction->arg2 = NULL;
            instruction->op = "param";
            instruction->result = NULL;
            instruction->nodetype = "ParamDecl";
 
            break;
        }
        case NodeType_ArgList: {
            //print debug statement
            if (printDebugTAC == 1)
                printf("Performing TAC generation on arglist\n");

            generateTAC(node->argList.argTail);
            break;
        }
        case NodeType_ArgTail: {
            //print debug statement
            if (printDebugTAC == 1)
                printf("Performing TAC generation on argtail\n");

            TAC* exprTAC = generateTAC(node->argTail.expr);

            instruction->arg1 = exprTAC->result;
            instruction->arg2 = NULL;
            instruction->op = "arg";
            instruction->result = NULL;
            instruction->nodetype = "ArgTail";

            instruction->next = NULL;
            appendTAC(&tacHead, instruction);

            generateTAC(node->argTail.argTail);
            
            break;
        }
        case NodeType_Block: {
            //print debug statement
            if (printDebugTAC == 1)
                printf("Performing TAC generation on block\n");

            generateTAC(node->block.blockStmtList);
            generateTAC(node->block.returnStmt);
            break;
        }
        case NodeType_BlockStmtList: {
            //print debug statement
            if (printDebugTAC == 1)
                printf("Performing TAC generation on blockStmtlist\n");

            generateTAC(node->blockStmtList.blockStmt);
            generateTAC(node->blockStmtList.blockStmtList);
            break;
        }
        case NodeType_BlockStmt: {
            //print debug statement
            if (printDebugTAC == 1)
                printf("Performing TAC generation on blockStmt\n");

            generateTAC(node->blockStmt.child);
            break;
        }
        case NodeType_Return: {
            //print debug statement
            if (printDebugTAC == 1)
                printf("Performing TAC generation on return\n");

            TAC* exprTAC = generateTAC(node->returnStmt.expr);

            instruction->arg1 = exprTAC->result;
            instruction->op = "return";
            instruction->arg2 = NULL;
            instruction->result = NULL;
            instruction->nodetype = "Return";
            break;
        }
        case NodeType_Declaration: {
            //print debug statement
            if (printDebugTAC == 1)
                printf("Performing TAC generation on declaration\n");

            printf("Declaration: %s\n", node->declaration.id->id.name);

            generateTAC(node->declaration.type);
            generateTAC(node->declaration.id);
            break;
        }
        case NodeType_DeclarationAssignment: {
            //print debug statement
            if (printDebugTAC == 1)
                printf("Performing TAC generation on declaration assignment\n");

            generateTAC(node->declarationAssignment.type);
            generateTAC(node->declarationAssignment.id);
            TAC* exprTAC = generateTAC(node->declarationAssignment.expr);

            instruction->arg1 = exprTAC->result;
            instruction->op = "=";
            instruction->arg2 = NULL;
            instruction->result = createOperand(node->declarationAssignment.id);
            instruction->nodetype = "DeclarationAssignment";

            break;
        }
        case NodeType_ArrayDeclaration: {
            //print debug statement
            if (printDebugTAC == 1)
                printf("Performing TAC generation on array declaration\n");

            // Generate TAC for the size of the array
            generateTAC(node->arrayDeclaration.type);
            generateTAC(node->arrayDeclaration.id);
            TAC* sizeTAC = generateTAC(node->arrayDeclaration.size);

            instruction->arg1 = NULL;
            instruction->op = "array_decl";
            instruction->arg2 = sizeTAC->result;
            instruction->result = createOperand(node->arrayDeclaration.id);
            instruction->nodetype = "ArrayDeclaration";

            break;
        }
        case NodeType_ArrayAssignment: {
            //print debug statement
            if (printDebugTAC == 1)
                printf("Performing TAC generation on array assignment\n");

            generateTAC(node->arrayAssignment.id);
            TAC* indexTAC = generateTAC(node->arrayAssignment.index);
            TAC* valueTAC = generateTAC(node->arrayAssignment.value);

            instruction->arg1 = valueTAC->result;
            instruction->op = "array_assign";
            instruction->arg2 = indexTAC->result;
            instruction->result = createOperand(node->arrayAssignment.id);
            instruction->nodetype = "ArrayAssignment";

            break;
        }
        case NodeType_ArrayAccess: {
            //print debug statement
            if (printDebugTAC == 1)
                printf("Performing TAC generation on array access\n");

            // Skip the array access if it is part of an assignment
            // if (node->parent->nType == NodeType_Assignment || node->parent->nType == NodeType_ArrayAssignment) {
            //     return NULL;
            // }

            generateTAC(node->arrayAccess.id);
            TAC* indexTAC = generateTAC(node->arrayAccess.index);

            instruction->arg1 = createOperand(node->arrayAccess.id);
            instruction->op = "array_access";
            instruction->arg2 = indexTAC->result;
            instruction->result = createTempVar();
            instruction->nodetype = "ArrayAccess";

            break;
        }
        case NodeType_Type: {
            //print debug statement
            if (printDebugTAC == 1)
                printf("Performing TAC generation on type: %s\n", node->type.typeName);

            break;
        }
        case NodeType_Assignment: {
            //print debug statement
            if (printDebugTAC == 1)
                printf("Performing TAC generation on assignment\n");

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
            //print debug statement
            if (printDebugTAC == 1)
                printf("Performing TAC generation on print\n");

            TAC* exprTAC = generateTAC(node->print.expr); 
            
            instruction->arg1 = exprTAC->result;
            instruction->op = "print";
            instruction->arg2 = NULL;
            instruction->result = NULL;
            instruction->nodetype = "Print";
            break;
        }
        case NodeType_Expr: {
            //print debug statement
            if (printDebugTAC == 1)
                printf("Performing TAC generation on expr\n");

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
            //print debug statement
            if (printDebugTAC == 1)
                printf("Performing TAC generation on term\n");

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
            //print debug statement
            if (printDebugTAC == 1)
                printf("Performing TAC generation on factor\n");

            generateTAC(node->factor.child);
            break;
        }
        case NodeType_ID: {
            //print debug statement
            if (printDebugTAC == 1)
                printf("Performing TAC generation on ID\n");

            instruction->result = createOperand(node); 
            instruction->op = NULL; 
            instruction->arg1 = NULL;
            instruction->arg2 = NULL;
            instruction->nodetype = "Expr";

            printf("ID: %s\n", instruction->result);

            break;
        }
        case NodeType_Number: {
            //print debug statement
            if (printDebugTAC == 1)
                printf("Performing TAC generation on number\n");

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

    if (!isNonActionableNodeType(node->nType)) {
        instruction->next = NULL;  // Make sure to null-terminate the new instruction
        appendTAC(&tacHead, instruction);
    }
        
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
        // Add new line for specific operators
        if (strcmp(current->nodetype, "FunctionDeclaration") == 0 || strcmp(current->nodetype, "IfStmt") == 0 || strcmp(current->nodetype, "ElseIfStmt") == 0 || strcmp(current->nodetype, "ElseStmt") == 0) {
            fprintf(file, "\n");
        }
        else if (strcmp(current->nodetype, "WhileStmt") == 0) {
            fprintf(file, "%s\n", current->result);
        }
        else if (strcmp(current->op, "array_decl") == 0) {
            fprintf(file, "%s = %s %s\n", current->result, current->op, current->arg2);
        }
        else if (strcmp(current->op, "array_assign") == 0) {
            fprintf(file, "%s[%s] = %s\n", current->result, current->arg2, current->arg1);
        }
        else if (strcmp(current->op, "array_access") == 0) {
            fprintf(file, "%s = %s[%s]\n", current->result, current->arg1, current->arg2);
        }
        else if (strcmp(current->op,"=") == 0) {
            if (strcmp(current->arg1, "call") == 0) {
                fprintf(file, "%s = %s %s\n", current->result, current->arg1, current->arg2);
            } else {
                fprintf(file, "%s = %s\n", current->result, current->arg1);
            }
        }
        else if (strcmp(current->op, "arg") == 0) {
            fprintf(file, "%s %s\n", current->op, current->arg1);
        }
        else if (strcmp(current->nodetype, "IfStmtCall") == 0 || strcmp(current->nodetype, "ElseIfStmtCall") == 0) {
            fprintf(file, "if %s %s %s %s\n", current->arg1, current->op, current->arg2, current->result);
        }
        else if(strcmp(current->nodetype, "ElseStmtCall") == 0) {
            fprintf(file, "%s\n", current->result);
        }
        else if (strcmp(current->nodetype, "IfStmt") == 0 || strcmp(current->nodetype, "ElseIfStmt") == 0 || strcmp(current->nodetype, "ElseStmt") == 0) {
            fprintf(file, "%s\n", current->result);
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

bool isNonActionableNodeType(NodeType type) {
    return type == NodeType_Condition ||
           type == NodeType_FunctionDeclaration ||
           type == NodeType_ArgTail ||
           type == NodeType_IfStmt ||
           type == NodeType_ElseIfStmt ||
           type == NodeType_ElseStmt ||
           type == NodeType_WhileStmt;
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