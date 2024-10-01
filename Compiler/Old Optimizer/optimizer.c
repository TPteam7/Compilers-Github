#include "optimizer.h"

int isConstant(char* arg) {
    for (int i = 0; arg[i] != '\0'; i++) {
        if (arg[i] < '0' || arg[i] > '9') return 0;
    }
    return 1;
}

void constantFolding(TAC* head) {
    TAC* current = head;
    while (current) {
        if ((strcmp(current->op, "+") == 0 || strcmp(current->op, "*") == 0) &&
            isConstant(current->arg1) && isConstant(current->arg2)) {
            // Perform constant folding.
            int val1 = atoi(current->arg1);
            int val2 = atoi(current->arg2);
            int result = (strcmp(current->op, "+") == 0) ? (val1 + val2) : (val1 * val2);
            
            // Replace with constant value.
            char buffer[20];
            snprintf(buffer, sizeof(buffer), "%d", result);
            
            free(current->op);
            current->op = strdup("ASSIGN");
            free(current->arg1);
            current->arg1 = strdup(buffer);
            free(current->arg2);
            current->arg2 = NULL;
        }
        current = current->next;
    }
}

void copyPropagation(TAC* head) {
    TAC* current = head;
    while (current) {
        // If the instruction is of type `result = arg1`
        if (strcmp(current->op, "ASSIGN") == 0) {
            char* target = current->result;
            char* source = current->arg1;

            // Traverse the rest of the TAC and replace uses of `target` with `source`.
            TAC* next = current->next;
            while (next) {
                if (next->arg1 && strcmp(next->arg1, target) == 0) {
                    free(next->arg1);
                    next->arg1 = strdup(source);
                }
                if (next->arg2 && strcmp(next->arg2, target) == 0) {
                    free(next->arg2);
                    next->arg2 = strdup(source);
                }
                next = next->next;
            }
        }
        current = current->next;
    }
}

int isVariableUsed(TAC* head, char* var) {
    TAC* current = head;
    while (current) {
        if ((current->arg1 && strcmp(current->arg1, var) == 0) ||
            (current->arg2 && strcmp(current->arg2, var) == 0)) {
            return 1; // Variable is used.
        }
        current = current->next;
    }
    return 0;
}

TAC* deadCodeElimination(TAC* head) {
    TAC* current = head;
    TAC* prev = NULL;
    
    while (current) {
        // Skip `print` statements and label instructions.
        if (strcmp(current->op, "print") == 0) {
            prev = current;
            current = current->next;
            continue;
        }

        if (!isVariableUsed(current->next, current->result)) {
            // Variable is not used, so eliminate this instruction.
            if (prev) prev->next = current->next;
            else head = current->next;

            TAC* temp = current;
            current = current->next;
            // free(temp->op);
            // free(temp->arg1);
            // free(temp->arg2);
            // free(temp->result);
            // free(temp);
        } else {
            prev = current;
            current = current->next;
        }
    }
    return head;
}

// Apply all optimizations.
void optimize(TAC* head) {
    constantFolding(head);
    copyPropagation(head);
    head = deadCodeElimination(head);
}