#include "optimizer.h"
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

void optimizeTAC(TAC** head) {
    constantFolding(head);

    constantPropagation(head);
    
    //copyPropagation(head);            
    
    deadCodeElimination(head);
}

bool isConstant(const char* str) 
/*
    Params:
        const char* str: the string to check

    Returns:
        bool: true if the string is an integer constant, false otherwise
    
    Functionality:
    First, the function checks if the input is 'NULL' or an empty string. 
        False if so, as they don't represent a valid constant.

    Next, if the first character is '-', the function skips it, 
        as negative numbers are allowed.

    The function then iterates over each character of the string using a while loop.
        For each character, it uses isdigit() to check if it's a numeric digit.

    If any character is not a digit, the function immediately returns 'false'.

    If the end of the string is reached without encountering any non-digit characters, 
        the function returns 'true', indicating the string is a numeric constant.
*/ 
{
    if (str == NULL || *str == '\0') {
        return false; // Empty string is not a constant
    }

    // Optional: Handle negative numbers
    if (*str == '-') {
        ++str;
    }

    // Check if string is numeric
    while (*str) {
        if (!isdigit((unsigned char)*str)) {
            return false; // Found a non-digit character
        }
        ++str;
    }

    return true; // All characters were digits
}

bool isVariable(const char* str) 
/*
    Args:
        const char* str: the string to check

    Returns:
        bool: true if the string is a valid variable name, false otherwise

    Functionality:
    The function checks if the input is 'NULL' or an empty string. 
        False if so, as they don't represent a valid variable.

    Next, the function checks if the first character is a letter or underscore.

    The function then iterates over each character of the string using a while loop.
        For each character, it uses isalnum() to check if it's a letter or digit.

    If any character is not a letter, digit, or underscore, the function immediately returns 'false'.

    If the end of the string is reached without encountering any non-letter, non-digit, or non-underscore characters, 
        the function returns 'true', indicating the string is a valid variable name.
*/
{
    if (str == NULL || *str == '\0') {
        return false; // Null or empty string is not a variable
    }

    // Check if the first character is a letter or underscore
    if (!isalpha((unsigned char)*str) && *str != '_') {
        return false;
    }

    // Check remaining characters for letters, digits, or underscores
    ++str; // Move past the first character
    while (*str) {
        if (!isalnum((unsigned char)*str) && *str != '_') {
            return false; // Invalid character found
        }
        ++str;
    }

    return true; // String meets the criteria for a variable name
}

void constantFolding(TAC** head) 
/*
    Params:
        TAC** head: a pointer to the head of the TAC list

    Functionality:
        This function performs constant folding optimization on the provided TAC list.

        Constant folding is the process of evaluating constant expressions at compile time
            instead of computing them at runtime. 

        For example, if the TAC contains an addition operation (e.g., t0 = 2 + 3), 
            the constant folding optimization will replace the addition operation with the result (t0 = 5).
*/
{
    TAC* current = *head; // Current TAC instruction

    // Apply constant folding optimization
    while (current != NULL) {
        // Addition
        if (strcmp(current->op, "+") == 0) {
            // Check if both operands are constants
            if (isConstant(current->arg1) && isConstant(current->arg2)) {
                int result = atoi(current->arg1) + atoi(current->arg2); // Perform the addition
                char resultStr[20];
                sprintf(resultStr, "%d", result); // Convert the result to a string
                free(current->arg1);
                free(current->arg2);
                current->arg1 = strdup(resultStr);
                current->op = "="; // Change the operation to assignment";
                current->arg2 = NULL;
                printf("Constant folding applied\n");
                printCurrentOptimizedTAC(current);
            }
        }
        // Subtraction
        else if (strcmp(current->op, "-") == 0) {
            // Check if both operands are constants
            if (isConstant(current->arg1) && isConstant(current->arg2)) {
                int result = atoi(current->arg1) - atoi(current->arg2); // Perform the subtraction
                char resultStr[20];
                sprintf(resultStr, "%d", result); // Convert the result to a string
                free(current->arg1);
                free(current->arg2);
                current->arg1 = strdup(resultStr);
                current->op = "="; // Change the operation to assignment
                current->arg2 = NULL;
                printf("Constant folding applied\n");
                printCurrentOptimizedTAC(current);
            }
        }
        // Multiplication
        else if (strcmp(current->op, "*") == 0) {
            // Check if both operands are constants
            if (isConstant(current->arg1) && isConstant(current->arg2)) {
                int result = atoi(current->arg1) * atoi(current->arg2); // Perform the multiplication
                char resultStr[20];
                sprintf(resultStr, "%d", result); // Convert the result to a string
                free(current->arg1);
                free(current->arg2);
                current->arg1 = strdup(resultStr);
                current->op = "="; // Change the operation to assignment
                current->arg2 = NULL;
                printf("Constant folding applied\n");
                printCurrentOptimizedTAC(current);
            }
        }
        // Division
        else if (strcmp(current->op, "/") == 0) {
            // Check if both operands are constants
            if (isConstant(current->arg1) && isConstant(current->arg2)) {
                int result = atoi(current->arg1) / atoi(current->arg2); // Perform the division
                char resultStr[20];
                sprintf(resultStr, "%d", result); // Convert the result to a string
                free(current->arg1);
                free(current->arg2);
                current->arg1 = strdup(resultStr);
                current->op = "="; // Change the operation to assignment
                current->arg2 = NULL;
                printf("Constant folding applied\n");
                printCurrentOptimizedTAC(current);
            }
        }

        current = current->next; // Move to the next TAC instruction
    }
}


void constantPropagation(TAC** head) {
    TAC* current = *head;

    while (current != NULL) {
        if (current->op != NULL && strcmp(current->op, "=") == 0) {
            // Check if the argument is a constant
            if (isConstant(current->arg1)) {
                // Propagate the constant value to all uses of the variable
                TAC* temp = current->next;
                int isReassigned = 0;

                // Check if the variable is reassigned later
                TAC* reassignmentCheck = current->next;
                while (reassignmentCheck != NULL) {
                    if (reassignmentCheck->result != NULL && 
                        strcmp(reassignmentCheck->result, current->result) == 0) {
                        isReassigned = 1;
                        break;
                    }
                    reassignmentCheck = reassignmentCheck->next;
                }

                // Only propagate if the variable is not reassigned
                if (!isReassigned) {
                    while (temp != NULL) {
                        // Skip if it's a print operation
                        if (strcmp(temp->op, "print") == 0) {
                            temp = temp->next;
                            continue;
                        }
                        // Replace temp->arg1 if it matches current->result
                        if (temp->arg1 != NULL && strcmp(temp->arg1, current->result) == 0) {
                            free(temp->arg1);
                            temp->arg1 = strdup(current->arg1);
                        }
                        // Replace temp->arg2 if it matches current->result
                        if (temp->arg2 != NULL && strcmp(temp->arg2, current->result) == 0) {
                            free(temp->arg2);
                            temp->arg2 = strdup(current->arg1);
                        }
                        temp = temp->next;
                    }
                }
            }
        }
        current = current->next;
    }
}


void copyPropagation(TAC** head) 
/*
    Params:
        TAC** head: a pointer to the head of the TAC list. This has ** because we need to modify the head pointer.
            If we only pass TAC* head, we would only have a copy of the pointer, and changes to it would not reflect outside the function.

    Functionality:
        This function performs copy propagation optimization on the provided TAC list.

        Copy propagation is the process of replacing uses of a variable that has been assigned the value of another variable.

        For example, if the TAC contains an assignment operation (e.g., t0 = t1), 
            the copy propagation optimization will replace all uses of 't1' with 't0'.
*/
{
    TAC* current = *head;
    while (current != NULL) {
        if (current->op != NULL) {
            // Check if the argument is a variable
            if (isVariable(current->arg1)) {
                // Propagate the variable value to all uses of the variable
                TAC* temp = current->next;
                while (temp != NULL) {
                    if (temp->arg1 != NULL && strcmp(temp->arg1, current->result) == 0) {
                        free(temp->arg1);
                        printf("Copy propagation applied\n");
                        printf("current arg1: %s\n", current->arg1);
                        temp->arg1 = strdup(current->arg1);
                    }
                    if (temp->arg2 != NULL && strcmp(temp->arg2, current->result) == 0) {
                        free(temp->arg2);
                        temp->arg2 = strdup(current->arg1);
                    }
                    temp = temp->next;
                }
            }
        }
        current = current->next;
    }
}

void deadCodeElimination(TAC** head) 
/*
    Params:
        TAC** head: a pointer to the head of the TAC list. This has ** because we need to modify the head pointer.
            If we only pass TAC* head, we would only have a copy of the pointer, and changes to it would not reflect outside the function.

    Functionality:
        This function performs dead code elimination optimization on the provided TAC list.

        Dead code elimination is the process of removing instructions that compute values not used by subsequent instructions or the program's output.
*/
{
    TAC* current = *head; // Pointer to the current TAC instruction
    TAC* prev = NULL;     // Pointer to the previous TAC instruction, used for list traversal

    // Loop through the TAC linked list
    while (current != NULL) {
        // Check if the operation is an assignment (e.g., t0 = ...)
        if (current->op != NULL && strcmp(current->op, "=") == 0) {
            // Flag to track whether the assigned result is ever used
            int isUsed = 0;

            // Temporary pointer to traverse the rest of the list and check usage of 'result'
            TAC* temp = current->next;
            while (temp != NULL) {
                // Check if the result of the current assignment is used in later instructions (either as arg1 or arg2)
                if ((temp->arg1 != NULL && strcmp(temp->arg1, current->result) == 0) ||
                    (temp->arg2 != NULL && strcmp(temp->arg2, current->result) == 0)) {
                    isUsed = 1;  // Mark it as used if found
                    break;        // Exit the loop once usage is found
                }
                temp = temp->next;  // Move to the next TAC instruction
            }
            // if the result is an integer, it is not used
            if (isConstant(current->result)) {
                isUsed = 0;
            }
            // If the result of the assignment is not used anywhere later, it's dead code
            if (!isUsed) {
                // Remove the dead code (the current TAC instruction)
                if (current == *head) {
                    // If it's the head (first instruction), update the head pointer to the next instruction
                    *head = current->next;
                    free(current); // Free the current (now removed) node
                    current = *head; // Move to the next instruction
                } else {
                    // If it's not the head, update the previous node's 'next' to skip over the current node
                    prev->next = current->next;
                    free(current); // Free the current (now removed) node
                    current = prev->next; // Move to the next instruction
                }
            } 
            else {
                // If the current assignment is used, just move to the next instruction
                prev = current;
                current = current->next;
            }
        } 
        else {
            // If the operation is not an assignment, just move to the next instruction
            prev = current;
            current = current->next;
        }
    }
}



// Print the optimized TAC list to a file
void printOptimizedTAC(const char* filename, TAC* head) {
    FILE* outputFile = fopen(filename, "w");
    if (outputFile == NULL) {
        perror("Failed to open output file");
        exit(EXIT_FAILURE);
    }

    TAC* current = head;
    while (current != NULL) {
        if(current->result != NULL)
            fprintf(outputFile, "%s = ", current->result);
        if(current->arg1 != NULL)
            fprintf(outputFile, "%s ", current->arg1);
        if(current->op != NULL && (strcmp(current->op, "=") != 0)) // Skip printing the "=" operator
            fprintf(outputFile, "%s ", current->op);
        if(current->arg2 != NULL)
            fprintf(outputFile, "%s ", current->arg2);
        fprintf(outputFile, "\n");
        current = current->next;
    }
    printf("Optimized TAC written to %s\n", filename);
    fclose(outputFile);
}

// Print current TAC instruction
void printCurrentOptimizedTAC(TAC* current) {
    if(current->result != NULL)
        printf("%s = ", current->result);
    if(current->arg1 != NULL)
        printf("%s ", current->arg1);
    if(current->op != NULL)
        printf("%s ", current->op);
    if(current->arg2 != NULL)
        printf("%s ", current->arg2);
    printf("\n");
}
