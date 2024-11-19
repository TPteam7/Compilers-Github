#include "semantic.h"
#include <stdio.h>


// Perform semantic analysis on the AST
int printDebugSemantic = 1;

void semanticAnalysis(ASTNode* node, SymbolTable* symTab, VariableSymbolTable* varTab) 
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
    const char* leftType = NULL;
    const char* rightType = NULL;
    if (node == NULL)
        return;

    switch (node->nType) {
        case NodeType_Program:
            if (printDebugSemantic == 1)
                printf("Performing semantic analysis on program\n");

            semanticAnalysis(node->program.stmtList, symTab, varTab);
            break;
        case NodeType_StmtList:
            if (printDebugSemantic == 1)
                printf("Performing semantic analysis on stmtlist\n");

            semanticAnalysis(node->stmtList.stmt, symTab, varTab);
            semanticAnalysis(node->stmtList.stmtList, symTab, varTab);
            break;
        case NodeType_Stmt:
            if (printDebugSemantic == 1)
                printf("Performing semantic analysis on stmt\n");

            semanticAnalysis(node->stmt.child, symTab, varTab);
            break;
        // Check if function has already been declared. If not, add to symbol table
        case NodeType_FunctionDeclaration:
            if (lookupSymbol(symTab, node->functionDeclaration.id->id.name) != NULL) {
                fprintf(stderr, "\nSEMANTIC ERROR:\nFunction %s has already been declared\n\n", node->functionDeclaration.id->id.name);
                exit(0);
                break;
            }
            else {	
                // Add function Symbol to symbol table
                addSymbol(symTab, node->functionDeclaration.id->id.name, node->functionDeclaration.type->type.typeName); 
            }

            if (printDebugSemantic == 1)
                printf("Performing semantic analysis on function declaration\n");

            varTab = lookupSymbol(symTab, node->functionDeclaration.id->id.name)->variables;

            semanticAnalysis(node->functionDeclaration.type, symTab, NULL);
            semanticAnalysis(node->functionDeclaration.id, symTab, NULL);
            semanticAnalysis(node->functionDeclaration.paramList, symTab, varTab);
            semanticAnalysis(node->functionDeclaration.block, symTab, varTab);

            //----------------------------------------------------------------------------
            // This section is performing Type Checking on the assignment

            const char* type = lookupSymbol(symTab, node->functionDeclaration.id->id.name)->returnType;
            const char* returnType = NULL;
            if (node->functionDeclaration.block != NULL && node->functionDeclaration.block->block.returnStmt != NULL && node->functionDeclaration.block->block.returnStmt->returnStmt.expr != NULL) {
                returnType = evaluateType(node->functionDeclaration.block->block.returnStmt->returnStmt.expr, symTab, varTab);
            } else {
                returnType = "void";
            }
            
            if (type == NULL || returnType == NULL) {
                if (type == NULL) {
                    fprintf(stderr, "Semantic error: Left operand type is NULL\n");
                }
                if (returnType == NULL) {
                    fprintf(stderr, "Semantic error: Return type is NULL\n");
                }
                exit(0);
            } else if (strcmp(type, returnType) != 0) {
                fprintf(stderr, "Semantic error: Type mismatch in assignment: %s vs %s\n", type, returnType);
                exit(0);
            }
            
            // Type checking done
            //----------------------------------------------------------------------

            break;
        // Check that function exists here in symbol table
        case NodeType_FunctionCall:
            if (lookupSymbol(symTab, node->functionCall.id->id.name) == NULL) {
                fprintf(stderr, "\nSEMANTIC ERROR:\nFunction %s has not been declared\n\n", node->functionCall.id->id.name);
                exit(0);
                break;
            }

            if (printDebugSemantic == 1)
                printf("Performing semantic analysis on function call\n");

            semanticAnalysis(node->functionCall.id, symTab, NULL);
            semanticAnalysis(node->functionCall.argList, symTab, varTab);
            break;
        case NodeType_IfBlock:
            if (printDebugSemantic == 1)
                printf("Performing semantic analysis on if-elseif-else block\n");
            
            semanticAnalysis(node->ifBlock.ifStmt, symTab, varTab);
            semanticAnalysis(node->ifBlock.elseIfList, symTab, varTab);
            semanticAnalysis(node->ifBlock.elseStmt, symTab, varTab);
            break;
        case NodeType_IfStmt:
            if (printDebugSemantic == 1)
                printf("Performing semantic analysis on if statement\n");

            // Check condition type
            const char* condType = evaluateType(node->ifStmt.condition, symTab, varTab);
            if (condType == NULL || strcmp(condType, "int") != 0) {
                fprintf(stderr, "Semantic error: Condition in if statement must be an int\n");
                exit(0);
            }

            semanticAnalysis(node->ifStmt.condition, symTab, varTab);
            semanticAnalysis(node->ifStmt.block, symTab, varTab);
            break;
        case NodeType_ElseIfStmt:
            if (printDebugSemantic == 1)
                printf("Performing semantic analysis on else if statement\n");

            // Check condition type
            const char* elseifCondType = evaluateType(node->elseIfStmt.condition, symTab, varTab);
            if (elseifCondType == NULL || strcmp(elseifCondType, "int") != 0) {
                fprintf(stderr, "Semantic error: Condition in else if statement must be an int\n");
                exit(0);
            }
            
            semanticAnalysis(node->elseIfStmt.condition, symTab, varTab);
            semanticAnalysis(node->elseIfStmt.block, symTab, varTab);
            semanticAnalysis(node->elseIfStmt.next, symTab, varTab);
            break;
        case NodeType_ElseStmt:
            if (printDebugSemantic == 1)
                printf("Performing semantic analysis on else statement\n");

            semanticAnalysis(node->elseStmt.block, symTab, varTab);
            break;
        case NodeType_Condition:
            if (printDebugSemantic == 1)
                printf("Performing semantic analysis on condition\n");

            // Evaluate type of the expression if it's not a function call
            evaluateType(node, symTab, varTab);

            semanticAnalysis(node->condition.expr, symTab, varTab);
            semanticAnalysis(node->condition.sign, symTab, varTab);
            semanticAnalysis(node->condition.expr2, symTab, varTab);
            break;
        case NodeType_Sign:
            if (printDebugSemantic == 1)
                printf("Sign: %s\n", node->sign.op);

            break;
        case NodeType_ParamList:
            if (printDebugSemantic == 1)
                printf("Performing semantic analysis on paramlist\n");

            semanticAnalysis(node->paramList.paramTail, symTab, varTab);
            break;
        case NodeType_ParamTail:
            if (printDebugSemantic == 1)
                printf("Performing semantic analysis on paramtail\n");

            semanticAnalysis(node->paramTail.param, symTab, varTab);
            semanticAnalysis(node->paramTail.paramTail, symTab, varTab);
            break;
        case NodeType_Param:
            if (printDebugSemantic == 1)
                printf("Performing semantic analysis on param\n");

            semanticAnalysis(node->param.child, symTab, varTab);
            break;
        case NodeType_ArgList:
            if (printDebugSemantic == 1)
                printf("Performing semantic analysis on arglist\n");

            semanticAnalysis(node->argList.argTail, symTab, varTab);
            break;
        case NodeType_ArgTail:
            if (printDebugSemantic == 1)
                printf("Performing semantic analysis on argtail\n");

            semanticAnalysis(node->argTail.expr, symTab, varTab);
            semanticAnalysis(node->argTail.argTail, symTab, varTab);
            break;
        case NodeType_Block:
            if (printDebugSemantic == 1)
                printf("Performing semantic analysis on block\n");

            semanticAnalysis(node->block.blockStmtList, symTab, varTab);
            semanticAnalysis(node->block.returnStmt, symTab, varTab);
            break;
        case NodeType_BlockStmtList:
            if (printDebugSemantic == 1)
                printf("Performing semantic analysis on blockStmtlist\n");

            semanticAnalysis(node->blockStmtList.blockStmt, symTab, varTab);
            semanticAnalysis(node->blockStmtList.blockStmtList, symTab, varTab);
            break;
        case NodeType_BlockStmt:
            if (printDebugSemantic == 1)
                printf("Performing semantic analysis on blockStmt\n");

            semanticAnalysis(node->blockStmt.child, symTab, varTab);
            break;
        case NodeType_Return:
            if (printDebugSemantic == 1)
                printf("Performing semantic analysis on return\n");

            semanticAnalysis(node->returnStmt.expr, symTab, varTab);
            break;
        // Check if vriable has already been declared. If not, add to VariableSymbolTable
        case NodeType_Declaration:
            if (lookupVariable(varTab, node->declaration.id->id.name) != NULL) {
                fprintf(stderr, "\nSEMANTIC ERROR:\nVariable %s has already been declared\n\n", node->declaration.id->id.name);
                exit(0);
                break;
            }
            else	
                // Add variable to VariableSymbolTable
                addVariable(varTab, node->declaration.id->id.name, node->declaration.type->type.typeName, 0);

            if(printDebugSemantic == 1)
                printf("Performing semantic analysis on declaration\n");

            semanticAnalysis(node->declaration.type, symTab, NULL);
            semanticAnalysis(node->declaration.id, symTab, varTab);
            break;
        // Check if variable has been declared in VariableSymbolTable
        case NodeType_DeclarationAssignment:
            addVariable(varTab, node->declarationAssignment.id->id.name, node->declarationAssignment.type->type.typeName, 0);

            if (lookupVariable(varTab, node->declarationAssignment.id->id.name) == NULL) {
                fprintf(stderr, "\nSEMANTIC ERROR:\nVariable %s has not been declared\n\n", node->declarationAssignment.id->id.name);
                exit(0);
                break;
            }

            evaluateType(node, symTab, varTab);

            if (printDebugSemantic == 1)
                printf("Performing semantic analysis on declaration assignment\n");

            semanticAnalysis(node->declaration.type, symTab, NULL);
            semanticAnalysis(node->declarationAssignment.id, symTab, varTab);
            semanticAnalysis(node->declarationAssignment.expr, symTab, varTab);

            break;
        // Check if array has been declared. If not, add to VariableSymbolTable
        case NodeType_ArrayDeclaration:
            if (lookupVariable(varTab, node->arrayDeclaration.id->id.name) != NULL) {
                fprintf(stderr, "\nSEMANTIC ERROR:\nArray %s has already been declared\n\n", node->arrayDeclaration.id->id.name);
                exit(0);
                break;
            }
            else {	
                // Add array to VariableSymbolTable
                // if size does not exist, set to 0
                if (node->arrayDeclaration.size == NULL)
                    addVariable(varTab, node->arrayDeclaration.id->id.name, node->arrayDeclaration.type->type.typeName, 0);  
                else 
                    addVariable(varTab, node->arrayDeclaration.id->id.name, node->arrayDeclaration.type->type.typeName, node->arrayDeclaration.size->number.value);
            }

            if (printDebugSemantic == 1)
                printf("Performing semantic analysis on array declaration\n");

            semanticAnalysis(node->arrayDeclaration.type, symTab, NULL);
            semanticAnalysis(node->arrayDeclaration.id, symTab, varTab);
            semanticAnalysis(node->arrayDeclaration.size, symTab, varTab);
            break;
        // Check that array has been declared in variable symbol table
        case NodeType_ArrayAssignment:
            if (lookupVariable(varTab, node->arrayAssignment.id->id.name) == NULL) {
                fprintf(stderr, "\nSEMANTIC ERROR:\nArray %s has not been declared\n\n", node->arrayAssignment.id->id.name);
                exit(0);
                break;
            }

            if (printDebugSemantic == 1)
                printf("Performing semantic analysis on array assignment\n");

            semanticAnalysis(node->arrayAssignment.id, symTab, varTab);
            semanticAnalysis(node->arrayAssignment.index, symTab, varTab);
            semanticAnalysis(node->arrayAssignment.value, symTab, varTab);
            break;
        // Check that array has been declared in VariableSymbolTable
        case NodeType_ArrayAccess:
            if (lookupVariable(varTab, node->arrayAccess.id->id.name) == NULL) {
                fprintf(stderr, "\nSEMANTIC ERROR:\nArray %s has not been declared\n\n", node->arrayAccess.id->id.name);
                exit(0);
                break;
            }

            if (printDebugSemantic == 1)
                printf("Performing semantic analysis on array access\n");

            semanticAnalysis(node->arrayAccess.id, symTab, varTab);
            semanticAnalysis(node->arrayAccess.index, symTab, varTab);
            break;
        case NodeType_Type:
            if (printDebugSemantic == 1)
                printf("Performing semantic analysis on type: %s\n", node->type.typeName);

            break;
        // Check for declaration of variables in VariableSymbolTable
        case NodeType_Assignment:
            if (lookupVariable(varTab, node->assignment.id->id.name) == NULL) {
                fprintf(stderr, "\nSEMANTIC ERROR:\nVariable %s has already been declared\n\n", node->assignment.id->id.name);
                exit(0);
                break;
            }

            if (printDebugSemantic == 1)
                printf("Performing semantic analysis on assignment\n");

            semanticAnalysis(node->assignment.id, symTab, varTab);
            semanticAnalysis(node->assignment.expr, symTab, varTab);

            evaluateType(node, symTab, varTab);

            break;
        case NodeType_Print:
            if (printDebugSemantic == 1)
                printf("Performing semantic analysis on print\n");

            semanticAnalysis(node->print.expr, symTab, varTab);
            break;
        case NodeType_Expr:
            if (printDebugSemantic == 1)
                printf("Performing semantic analysis on expr\n");

            semanticAnalysis(node->expr.left, symTab, varTab);
            semanticAnalysis(node->expr.right, symTab, varTab);

            evaluateType(node, symTab, varTab);

            break;
        case NodeType_Term:
            if (printDebugSemantic == 1)
                printf("Performing semantic analysis on term\n");

            semanticAnalysis(node->term.left, symTab, varTab);
            semanticAnalysis(node->term.right, symTab, varTab);

            evaluateType(node, symTab, varTab);
            
            break;
        case NodeType_Factor:
            if (printDebugSemantic == 1)
                printf("Performing semantic analysis on factor\n");

            semanticAnalysis(node->factor.child, symTab, varTab);
            break;
        // Check for declaration of the ID. This can be a variable or a function
        // Function is in symTab, variable is in varTab
        case NodeType_ID:
            // if varTab is NULL, then we are checking a function ID
            if (varTab == NULL) {
                if (lookupSymbol(symTab, node->id.name) == NULL) {
                    fprintf(stderr, "Semantic error: Function %s has not been declared\n", node->id.name);
                    exit(0);
                    break;
                }
            }
            // if varTab is not NULL, then we are checking a variable ID
            else 
            {
                if (lookupVariable(varTab, node->id.name) == NULL) {
                    fprintf(stderr, "Semantic error: Variable %s has not been declared\n", node->id.name);
                    exit(0);
                    break;
                }
            }
            if (printDebugSemantic == 1)
                printf("ID: %s\n", node->id.name);
            break;
        case NodeType_Number:
            if (printDebugSemantic == 1)
                printf("Number: %i\n", node->number.value);
            break;
        default:
            fprintf(stderr, "Unknown Node Type\n");
    }
}

// Helper function to get the type of an expression
const char* evaluateType(ASTNode* node, SymbolTable* symTab, VariableSymbolTable* varTab) {
    const char* leftType = NULL;
    const char* rightType = NULL;
    
    if (node->nType == NodeType_Number) {
        return "int";  // Assuming all numbers are int for simplicity
    } else if (node->nType == NodeType_ID) {
        Variable* var = lookupVariable(varTab, node->id.name);
        if (var == NULL) {
            fprintf(stderr, "Semantic error: Variable %s has not been declared\n", node->id.name);
            exit(0);
        }

        return var->variableType;
    } else if (node->nType == NodeType_Assignment) {
        Variable* var = lookupVariable(varTab, node->assignment.id->id.name);

        leftType = var->variableType;
        rightType = evaluateType(node->assignment.expr, symTab, varTab);

        // Check type compatibility for both sides
        if (strcmp(leftType, rightType) != 0) {
            fprintf(stderr, "Type mismatch in expression: %s vs %s\n", leftType, rightType);
            exit(0);
        }

        return leftType;
    } else if (node->nType == NodeType_DeclarationAssignment) {
        Variable* var = lookupVariable(varTab, node->assignment.id->id.name);

        leftType = node->declarationAssignment.type->type.typeName;
        rightType = evaluateType(node->declarationAssignment.expr, symTab, varTab);

        // Check type compatibility for both sides
        if (strcmp(leftType, rightType) != 0) {
            fprintf(stderr, "Type mismatch in expression: %s vs %s\n", leftType, rightType);
            exit(0);
        }

        return leftType;
    } else if (node->nType == NodeType_Expr) {
        leftType = evaluateType(node->expr.left, symTab, varTab);
        rightType = evaluateType(node->expr.right, symTab, varTab);

        // Check type compatibility for both sides
        if (strcmp(leftType, rightType) != 0) {
            fprintf(stderr, "Type mismatch in expression: %s vs %s\n", leftType, rightType);
            exit(0);
        }

        return leftType;  // Return the resulting type of the expression
    } else if (node->nType == NodeType_Condition) {
        leftType = evaluateType(node->condition.expr, symTab, varTab);
        rightType = evaluateType(node->condition.expr2, symTab, varTab);

        // Check type compatibility for both sides
        if (strcmp(leftType, rightType) != 0) {
            fprintf(stderr, "Type mismatch in expression: %s vs %s\n", leftType, rightType);
            exit(0);
        }

        return leftType;
    } else if (node->nType == NodeType_FunctionCall) {
        // Retrieve the function's return type
            Symbol* func = lookupSymbol(symTab, node->functionCall.id->id.name);
            if (func == NULL) {
                fprintf(stderr, "Semantic error: Function %s not declared\n", node->assignment.expr->functionCall.id->id.name);
                exit(0);
            }

        return func->returnType;
    } 

    if (leftType == NULL || rightType == NULL) {
        if (leftType == NULL) {
            fprintf(stderr, "Semantic error: Left operand type is NULL\n");
        }
        if (rightType == NULL) {
            fprintf(stderr, "Semantic error: Right operand type is NULL\n");
        }
        exit(0);
    } else if (strcmp(leftType, rightType) != 0) {
        fprintf(stderr, "Type mismatch in assignment: %s vs %s\n", leftType, rightType);
        exit(0);
    }

    return NULL;  // Error or unsupported type
}