// codeGenerator.c

#include "codeGenerator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static FILE* outputFile;
bool endOfProgram = false;
// Keep track of the array register. 
    //This register will remain and be used for all arrays
int arrReg = NULL;       

// Keep track of the element being accessed in the array
int elementID = NULL;

// Name of the current array being accessed
char* accessedArr = NULL;   

typedef struct {
    char* name; // Name of the register, e.g., "$t0"
    bool inUse; // Whether the register is currently in use
} MIPSRegister;

// Array of temporary registers, used for register allocation
// and tracking which registers are currently in use

MIPSRegister tempRegisters[NUM_TEMP_REGISTERS] = {
    {"$t0", false}, {"$t1", false}, {"$t2", false}, {"$t3", false},
    {"$t4", false}, {"$t5", false}, {"$t6", false}, {"$t7", false},
    {"$t8", false}, {"$t9", false}
};

MIPSRegister argumentRegisters[NUM_ARG_REGISTERS] = {
    {"$a0", false}, {"$a1", false}, {"$a2", false}, {"$a3", false}
};

void initCodeGenerator(const char* outputFilename) {
    outputFile = fopen(outputFilename, "w");
    if (outputFile == NULL) {
        perror("Failed to open output file");
        exit(EXIT_FAILURE);
    }
}

void generateMIPS(TAC* tacInstructions)
/*
    Params:
        tacInstructions: The list of TAC instructions to generate MIPS code from

    Functionality:
        Generates MIPS assembly code from the provided TAC instructions
*/ 
{

    TAC* current = tacInstructions;
    fprintf(outputFile, ".data\n"); // Data segment for variables

    // Make a list to store the variables in order to not declare them multiple times
    char* variables[100] = {NULL}; // Initialize all elements to NULL
    int varIndex = 0;

    // Get the list of variables from the TAC instructions
    addDataSection(current, variables, varIndex);

    current = tacInstructions;


    fprintf(outputFile, ".text\n.globl main\nmain:\n");

    printf("Generating MIPS code...\n");

    while (current != NULL) {
        int reg1, reg2, regResult;

        // Handle assignment operation. Skip if it's a function call
        if (strcmp(current->op, "=") == 0 && strcmp(current->arg1, "call") != 0) {
            printf("Generating MIPS for Assignment operation\n");
            
            // Allocate a register for the result
            regResult = allocateRegister();
            if (regResult == -1) {
                fprintf(stderr, "No available register for assignment operation\n");
                exit(EXIT_FAILURE);
            }

            // Check if arg1 is a constant
            if (isConstant(current->arg1)) {
                fprintf(outputFile, "\tli %s, %s\n", tempRegisters[regResult].name, current->arg1); // Load immediate
            } else {
                // Allocate a register for arg1
                reg1 = allocateRegister();
                if (reg1 == -1) {
                    fprintf(stderr, "No available register for arg1\n");
                    exit(EXIT_FAILURE);
                }
                

                fprintf(outputFile, "\tlw %s, %s\n", tempRegisters[reg1].name, current->arg1); // Load from memory
                fprintf(outputFile, "\tmove %s, %s\n", tempRegisters[regResult].name, tempRegisters[reg1].name); // Move to result

                // Deallocate arg1 register after use
                deallocateRegister(reg1);
            }

            // Store result in memory
            fprintf(outputFile, "\tsw %s, %s\n", tempRegisters[regResult].name, current->result);

            // Deallocate result register
            deallocateRegister(regResult);
        }
        // Handle addition operation
        else if (strcmp(current->op, "+") == 0) {
            // Allocate registers for both operands and the result
            reg1 = allocateRegister();
            reg2 = allocateRegister();
            regResult = allocateRegister();

            if (reg1 == -1 || reg2 == -1 || regResult == -1) {
                fprintf(stderr, "No available register for addition operation\n");
                exit(EXIT_FAILURE);
            }

            // Load both arguments into registers
            if (isConstant(current->arg1)) {
                fprintf(outputFile, "\tli %s, %s\n", tempRegisters[reg1].name, current->arg1);
            } 
            else {
                fprintf(outputFile, "\tlw %s, %s\n", tempRegisters[reg1].name, current->arg1);
            }
            
            if (isConstant(current->arg2)) {
                fprintf(outputFile, "\tli %s, %s\n", tempRegisters[reg2].name, current->arg2);
            } 
            else {
                fprintf(outputFile, "\tlw %s, %s\n", tempRegisters[reg2].name, current->arg2);
            }

            // Perform addition
            fprintf(outputFile, "\tadd %s, %s, %s\n", tempRegisters[regResult].name, tempRegisters[reg1].name, tempRegisters[reg2].name);

            // Store result in memory
            fprintf(outputFile, "\tsw %s, %s\n", tempRegisters[regResult].name, current->result);

            // Deallocate registers
            deallocateRegister(reg1);
            deallocateRegister(reg2);
            deallocateRegister(regResult);
        }
        // Handle subtraction operation
        else if (strcmp(current->op, "-") == 0) {
            // Allocate registers for both operands and the result
            reg1 = allocateRegister();
            reg2 = allocateRegister();
            regResult = allocateRegister();

            if (reg1 == -1 || reg2 == -1 || regResult == -1) {
                fprintf(stderr, "No available register for addition operation\n");
                exit(EXIT_FAILURE);
            }

            // Load both arguments into registers
            if (isConstant(current->arg1)) {
                fprintf(outputFile, "\tli %s, %s\n", tempRegisters[reg1].name, current->arg1);
            } 
            else {
                fprintf(outputFile, "\tlw %s, %s\n", tempRegisters[reg1].name, current->arg1);
            }
            
            if (isConstant(current->arg2)) {
                fprintf(outputFile, "\tli %s, %s\n", tempRegisters[reg2].name, current->arg2);
            } 
            else {
                fprintf(outputFile, "\tlw %s, %s\n", tempRegisters[reg2].name, current->arg2);
            }

            printf("Generating MIPS for Subtraction operation\n");

            // Perform addition
            fprintf(outputFile, "\tsubu %s, %s, %s\n", tempRegisters[regResult].name, tempRegisters[reg1].name, tempRegisters[reg2].name);

            // Store result in memory
            fprintf(outputFile, "\tsw %s, %s\n", tempRegisters[regResult].name, current->result);

            // Deallocate registers
            deallocateRegister(reg1);
            deallocateRegister(reg2);
            deallocateRegister(regResult);
        }
        // Handle multiplication operation
        else if (strcmp(current->op, "*") == 0) {
            // Allocate registers for both operands and the result
            reg1 = allocateRegister();
            reg2 = allocateRegister();
            regResult = allocateRegister();

            if (reg1 == -1 || reg2 == -1 || regResult == -1) {
                fprintf(stderr, "No available register for multiplication operation\n");
                exit(EXIT_FAILURE);
            }

            if(isConstant(current->arg1)) {
                fprintf(outputFile, "\tli %s, %s\n", tempRegisters[reg1].name, current->arg1);
            } 
            else {
                fprintf(outputFile, "\tlw %s, %s\n", tempRegisters[reg1].name, current->arg1);
            }

            if(isConstant(current->arg2)) {
                fprintf(outputFile, "\tli %s, %s\n", tempRegisters[reg2].name, current->arg2);
            } 
            else {
                fprintf(outputFile, "\tlw %s, %s\n", tempRegisters[reg2].name, current->arg2);
            }

            // Perform multiplication
            fprintf(outputFile, "\tmul %s, %s, %s\n", tempRegisters[regResult].name, tempRegisters[reg1].name, tempRegisters[reg2].name);

            // Store result in memory
            fprintf(outputFile, "\tsw %s, %s\n", tempRegisters[regResult].name, current->result);

            // Deallocate registers
            deallocateRegister(reg1);
            deallocateRegister(reg2);
            deallocateRegister(regResult);
        }
        // Handle division operation
        else if(strcmp(current->op, "/") == 0)
        {
            // Allocate registers for both operands and the result
            reg1 = allocateRegister();
            reg2 = allocateRegister();
            regResult = allocateRegister();

            if (reg1 == -1 || reg2 == -1 || regResult == -1) {
                fprintf(stderr, "No available register for division operation\n");
                exit(EXIT_FAILURE);
            }

            if(isConstant(current->arg1)) {
                fprintf(outputFile, "\tli %s, %s\n", tempRegisters[reg1].name, current->arg1);
            } 
            else {
                fprintf(outputFile, "\tlw %s, %s\n", tempRegisters[reg1].name, current->arg1);
            }

            if(isConstant(current->arg2)) {
                fprintf(outputFile, "\tli %s, %s\n", tempRegisters[reg2].name, current->arg2);
            } 
            else {
                fprintf(outputFile, "\tlw %s, %s\n", tempRegisters[reg2].name, current->arg2);
            }

            // Perform division
            fprintf(outputFile, "\tdiv %s, %s\n", tempRegisters[reg1].name, tempRegisters[reg2].name);
            fprintf(outputFile, "\tmflo %s\n", tempRegisters[regResult].name);

            // Store result in memory
            fprintf(outputFile, "\tsw %s, %s\n", tempRegisters[regResult].name, current->result);

            // Deallocate registers
            deallocateRegister(reg1);
            deallocateRegister(reg2);
            deallocateRegister(regResult);
        }
        // Handle print operation
        else if (strcmp(current->op, "print") == 0) {
            // Allocate a register for the value to print
            reg1 = allocateRegister();
            if (reg1 == -1) {
                fprintf(stderr, "No available register for print operation\n");
                exit(EXIT_FAILURE);
            }

            // // Load the value to print into the register
            if (isConstant(current->arg1)) {
                fprintf(outputFile, "\tli %s, %s\n", tempRegisters[reg1].name, current->arg1);
            } 
            else {
                fprintf(outputFile, "\tlw %s, %s\n", tempRegisters[reg1].name, current->arg1);
            }

            // Print the value
            fprintf(outputFile, "\tli $v0, 1\n\tmove $a0, %s\n\tsyscall\n", tempRegisters[reg1].name);
            printNewLineMIPS();



            // Deallocate the register
            deallocateRegister(reg1);
        }
        // Handle arg operation
        else if (strcmp(current->op, "arg") == 0) {
            // Allocate a register for the argument
            reg1 = allocateArgRegister();
            if (reg1 == -1) {
                fprintf(stderr, "No available register for arg operation\n");
                exit(EXIT_FAILURE);
            }

            // Load the argument into the register
            if (isConstant(current->arg1)) {
                fprintf(outputFile, "\tli %s, %s\n", argumentRegisters[reg1].name, current->arg1);
            } 
            else {
                fprintf(outputFile, "\tlw %s, %s\n", argumentRegisters[reg1].name, current->arg1);
            }

            // Deallocate the register
            //deallocateArgRegister(reg1);
        }
        // Handle function calls
        else if (current->arg1 != NULL && strcmp(current->arg1, "call") == 0) {
            printf("Generating MIPS for Function call\n");

            // Free up all argument registers
            for (int i = 0; i < NUM_ARG_REGISTERS; i++) {
                argumentRegisters[i].inUse = false;
            }

            // Call the function
            fprintf(outputFile, "\tjal %s\n", current->arg2);
              
            // Handle print operation
            if (strcmp(current->arg2, "print") == 0) {
                // Load the argument into $a0
                if (isConstant(current->result)) {
                    fprintf(outputFile, "\tli $a0, %s\n", current->result);
                } 
                else {
                    fprintf(outputFile, "\tlw $a0, %s\n", current->result);
                }

                // Print the value
                fprintf(outputFile, "\tli $v0, 1\n\tsyscall\n");
                printNewLineMIPS();
            }
            // Handle if it is used as an assignment
            else if(strcmp(current->op, "=") == 0) {
                // Allocate a register for the result
                regResult = allocateRegister();
                if (regResult == -1) {
                    fprintf(stderr, "No available register for assignment operation\n");
                    exit(EXIT_FAILURE);
                }

                // Load the result into the register
                fprintf(outputFile, "\tmove %s, $v0\n", tempRegisters[regResult].name);

                // Store result in memory
                fprintf(outputFile, "\tsw %s, %s\n", tempRegisters[regResult].name, current->result);

                // Deallocate the register
                deallocateRegister(regResult);
            }
            // Handle if it is used as an argument
            // else if(strcmp(current->op, "arg") == 0) {
            //     // Load the argument into the argument register
            //     fprintf(outputFile, "\tmove %s, $v0\n", argumentRegisters[0].name);
            // }
        }
        // Handle function declarations
        else if (strcmp(current->op, "function") == 0) {
            printf("Generating MIPS for Function declaration\n");

            // if end of program is false print the end in main first
            if(!endOfProgram) {
                fprintf(outputFile, "\tli $v0, 10\n\tsyscall\n");
                endOfProgram = true;
            }

            // Function label
            fprintf(outputFile, "\n%s:\n", current->arg2);

            // Add a stack for return address. This is needed for nested function calls
            fprintf(outputFile, "\taddi $sp, $sp, -4\n");
            fprintf(outputFile, "\tsw $ra, 0($sp)\n\n");
        }
        // Handle return operation
        else if (strcmp(current->op, "return") == 0) {
            // Load the return value into $v0
            if (isConstant(current->arg1)) {
                fprintf(outputFile, "\tli $v0, %s\n", current->arg1);
            } 
            else {
                fprintf(outputFile, "\tlw $v0, %s\n", current->arg1);
            }

            // Free up all argument registers
            for (int i = 0; i < NUM_ARG_REGISTERS; i++) {
                argumentRegisters[i].inUse = false;
            }

            // Restore the return address from the stack
            fprintf(outputFile, "\n\tlw $ra, 0($sp)\n");
            fprintf(outputFile, "\taddi $sp, $sp, 4\n\n");

            // Return from the function
            fprintf(outputFile, "\tjr $ra\n");
        }
        // Handle params
        else if (strcmp(current->op, "param") == 0) {
            // Allocate a register for the argument
            reg1 = allocateArgRegister();
            if (reg1 == -1) {
                fprintf(stderr, "No available register for arg operation\n");
                exit(EXIT_FAILURE);
            }

            // Load the argument into the register
            if (isConstant(current->arg1)) {
                fprintf(outputFile, "\tli %s, %s\n", argumentRegisters[reg1].name, current->arg1);
            } 
            else {
                fprintf(outputFile, "\tsw %s, %s\n", argumentRegisters[reg1].name, current->arg1);
            }

            // Deallocate all registers
            if(current->next != NULL && strcmp(current->next->op, "param") != 0) {
                for (int i = 0; i < NUM_ARG_REGISTERS; i++) {
                    argumentRegisters[i].inUse = false;
                }
            }
        }
        // Handle array declaration
        else if(strcmp(current->op, "array_decl") == 0) {
            printf("Generating MIPS for Array declaration\n");

            // Allocate a register for the size of the array if it is not already allocated
            if(arrReg == NULL) {
                arrReg = allocateRegister();
            }

            if (arrReg == -1) {
                fprintf(stderr, "No available register for array declaration\n");
                exit(EXIT_FAILURE);
            }

            // Allocate memory for the array using la if it is not already allocated
            if(accessedArr == NULL || strcmp(accessedArr, current->result) != 0) {
                accessedArr = current->result;
                elementID = NULL;       // Reset the element being accessed since it is a new array
                fprintf(outputFile, "\tla %s, %s\n", tempRegisters[arrReg].name, current->result);
            }
        }
        // Handle array assignment
        else if(strcmp(current->op, "array_assign") == 0) {
            printf("Generating MIPS for Array assignment\n");

            // Allocate a register for the index
            int indexReg = allocateRegister();
            int resultReg = allocateRegister();
            int offsetReg = allocateRegister();

            if (indexReg == -1 || resultReg == -1 || offsetReg == -1) {
                fprintf(stderr, "No available register for array assignment\n");
                exit(EXIT_FAILURE);
            }

            printf("ASSIGN Current array: %s\n", accessedArr);
            printf("ASSIGN Array to assign: %s\n", current->result);

            // Current array to assign to
            char* arr_to_assign = current->result;

            // If the array is different then the current array, load the address of the array into the register
            if(accessedArr == NULL || strcmp(accessedArr, arr_to_assign) != 0) {
                accessedArr = arr_to_assign;
                elementID = NULL;       // Reset the element being accessed since it is a new array
                fprintf(outputFile, "\tla %s, %s\n", tempRegisters[arrReg].name, accessedArr);
            }

            // Load the index into the register
            if (isConstant(current->arg2))
                fprintf(outputFile, "\tli %s, %s\n", tempRegisters[indexReg].name, current->arg2);
            
            else
                fprintf(outputFile, "\tlw %s, %s\n", tempRegisters[indexReg].name, current->arg2);
            

            // Load the value to assign into the register
            if (isConstant(current->arg1))
                fprintf(outputFile, "\tli %s, %s\n", tempRegisters[resultReg].name, current->arg1);
            
            else
                fprintf(outputFile, "\tlw %s, %s\n", tempRegisters[resultReg].name, current->arg1);
            

            // Calculate the address of the element to assign
            fprintf(outputFile, "\tmul %s, %s, 4\n", tempRegisters[indexReg].name, tempRegisters[indexReg].name);
            
            // newReg, arrReg, indexReg
            fprintf(outputFile, "\tadd %s, %s, %s\n", tempRegisters[offsetReg].name, tempRegisters[arrReg].name, tempRegisters[indexReg].name);       

            // Load the value from the array
            fprintf(outputFile, "\tsw %s, 0(%s)\n", tempRegisters[resultReg].name, tempRegisters[offsetReg].name);

            // Deallocate the registers
            deallocateRegister(indexReg);
            deallocateRegister(resultReg);
            deallocateRegister(offsetReg);
        }
        // Handle array access
        else if(strcmp(current->op, "array_access") == 0) {
            printf("Generating MIPS for Array access\n");

            // Allocate a register for the index
            int indexReg = allocateRegister();
            int accessedElementArg = allocateRegister();
            int offsetReg = allocateRegister();

            if (indexReg == -1 || accessedElementArg == -1 || offsetReg == -1) {
                fprintf(stderr, "No available register for array assignment\n");
                exit(EXIT_FAILURE);
            }

            printf("ACCESS Current array: %s\n", accessedArr);
            printf("ACCESS Array to assign: %s\n", current->arg1);

            // Current array to assign to
            char* arr_to_assign = current->arg1;

            // If the array is different then the current array, load the address of the array into the register
            if(accessedArr == NULL || strcmp(accessedArr, arr_to_assign) != 0) {
                accessedArr = arr_to_assign;
                fprintf(outputFile, "\tla %s, %s\n", tempRegisters[arrReg].name, accessedArr);
            }

            // Load the index into the register
            if (isConstant(current->arg2))
                fprintf(outputFile, "\tli %s, %s\n", tempRegisters[indexReg].name, current->arg2);
            
            else
                fprintf(outputFile, "\tlw %s, %s\n", tempRegisters[indexReg].name, current->arg2);

            // Calculate the address of the element to assign
            fprintf(outputFile, "\tmul %s, %s, 4\n", tempRegisters[indexReg].name, tempRegisters[indexReg].name);
            
            // newReg, arrReg, indexReg
            fprintf(outputFile, "\tadd %s, %s, %s\n", tempRegisters[offsetReg].name, tempRegisters[arrReg].name, tempRegisters[indexReg].name);       

            // Load the value from the array
            fprintf(outputFile, "\tlw %s, 0(%s)\n", tempRegisters[accessedElementArg].name, tempRegisters[offsetReg].name);

            // Deallocate the registers
            deallocateRegister(indexReg);
            deallocateRegister(accessedElementArg);
            deallocateRegister(offsetReg);
        }
        else
        {
            printf("Generating MIPS for other operations\n");
        }
        
        current = current->next; // Move to the next TAC instruction

        if(current == NULL && !endOfProgram) {
            fprintf(outputFile, "\tli $v0, 10\n\tsyscall\n");
            endOfProgram = true;
        }
    }
}



void finalizeCodeGenerator(const char* outputFilename) {
    if (outputFile) {
        fclose(outputFile);
        printf("MIPS code generated and saved to file %s\n", outputFilename);
        outputFile = NULL;
    }
}


/*

Implementing register allocation in your MIPS code generation phase is a crucial step 
for optimizing the use of CPU resources. The goal is to map your temporary variables (from TAC) 
to a limited set of MIPS registers, ideally minimizing memory access by keeping 
frequently used values in registers.

MIPS architecture provides a set of general-purpose registers, 
$t0 to $t9 for temporary values, and $s0 to $s7 for saved values. 
For simplicity, let's focus on using the temporary registers.

Strategy for Register Allocation:
--------------------------------

A simple strategy for register allocation could involve:

Register Pool: Keep track of which registers are currently available.
Allocation and Deallocation: Allocate registers when needed for operations and 
                             deallocate them when they are no longer needed.
Spilling: If all registers are in use and another one is needed,
          "spill" a register's value to memory and reuse the register.

*/

//Create a function to add to the data section of the MIPS code
void addDataSection(TAC* current, char* variables[], int varIndex) {
    while (current != NULL) {
        printf("\nOP:%s\n", current->op);
        if(strcmp(current->op, "param") == 0) {
            printf("HERE");
        }
        // Check if the operation is '=', '+', '*', '-', or '/'
        if (strcmp(current->op, "=") == 0 || strcmp(current->op, "+") == 0 || 
            strcmp(current->op, "*") == 0 || strcmp(current->op, "-") == 0 || 
            strcmp(current->op, "/") == 0) {
            // Check if the result is a variable
            if (current->result != NULL && !isConstant(current->result)) {
                int found = 0;
                for (int i = 0; i < varIndex; i++) {
                    if (variables[i] != NULL && strcmp(variables[i], current->result) == 0) {
                        found = 1;
                        break;
                    }
                }

                if (!found && varIndex < 100) {
                    variables[varIndex] = current->result;
                    varIndex++;
                    fprintf(outputFile, "\t%s: .word 0\n", current->result);
                }
            }
        }
        // Params
        else if (strcmp(current->op, "param") == 0) {
            if (current->arg1 != NULL && !isConstant(current->arg1)) {
                int found = 0;
                for (int i = 0; i < varIndex; i++) {
                    if (variables[i] != NULL && strcmp(variables[i], current->arg1) == 0) {
                        found = 1;
                        break;
                    }
                }

                if (!found && varIndex < 100) {
                    variables[varIndex] = current->arg1;
                    varIndex++;
                    fprintf(outputFile, "\t%s: .word 0\n", current->arg1);
                }
            }
        }
        // Array declaration
        else if(strcmp(current->op, "array_decl") == 0) {
            // Get the int value of the array size
            int size = atoi(current->arg2);

            if (current->result != NULL && !isConstant(current->result)) {
                int found = 0;
                for (int i = 0; i < varIndex; i++) {
                    if (variables[i] != NULL && strcmp(variables[i], current->result) == 0) {
                        found = 1;
                        break;
                    }
                }

                if (!found && varIndex < 100) {
                    variables[varIndex] = current->result;
                    varIndex++;
                    fprintf(outputFile, "\t%s: .space %d\n", current->result, size * 4);
                }
            }
        }
        // Any access or assignment of array
        else if(strcmp(current->op, "array_assign") == 0 || strcmp(current->op, "array_access") == 0)
        {
            printf(current->result);
            if (current->result != NULL && !isConstant(current->result)) {
                int found = 0;
                for (int i = 0; i < varIndex; i++) {
                    if (variables[i] != NULL && strcmp(variables[i], current->result) == 0) {
                        found = 1;
                        break;
                    }
                }

                if (!found && varIndex < 100) {
                    variables[varIndex] = current->result;
                    varIndex++;
                    fprintf(outputFile, "\t%s: .word 0\n", current->result);
                }
            }
        }
        current = current->next;
    }
}


// Allocate a register
int allocateRegister() {
    for (int i = 0; i < NUM_TEMP_REGISTERS; i++) {
        if (!tempRegisters[i].inUse) {
            tempRegisters[i].inUse = true;
            return i; // Return the register index
        }
    }
    // No available register, implement spilling if necessary
    return -1; // Indicate failure
}

// Deallocate a register
void deallocateRegister(int regIndex) {
    if (regIndex >= 0 && regIndex < NUM_TEMP_REGISTERS) {
        tempRegisters[regIndex].inUse = false;
    }
}

// Alocate an argument register
int allocateArgRegister() {
    for (int i = 0; i < NUM_ARG_REGISTERS; i++) {
        if (!argumentRegisters[i].inUse) {
            argumentRegisters[i].inUse = true;
            return i; // Return the register index
        }
    }
    // No available register, implement spilling if necessary
    return -1; // Indicate failure
}

// Deallocate an argument register
void deallocateArgRegister(int regIndex) {
    if (regIndex >= 0 && regIndex < NUM_ARG_REGISTERS) {
        argumentRegisters[regIndex].inUse = false;
    }
}

void printCurrentTAC(TAC* tac) {
    TAC* current = tac;
    while (current != NULL) {
        printf("\n--- CURRENT TAC %s ---\n", current->op);
        if (strcmp(current->op,"=") == 0) {
            printf("%s = %s\n", current->result, current->arg1);
        } 
        else {
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
        current = current->next;
    }   
}

void printNewLineMIPS() 
/*
    Purpose:
        To print a new line to console in MIPS code generation

*/
{
    // Print a newline by printing the ASCII value 10
    fprintf(outputFile, "\tli $v0, 11\n\tli $a0, 10\n\tsyscall\n");
}