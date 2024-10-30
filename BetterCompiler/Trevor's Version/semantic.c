#include "semantic.h"
#include <stdio.h>


// Perform semantic analysis on the AST
int printDebugSemantic = 0;

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
    if (node == NULL)
        return;

    switch (node->nType) {
        case NodeType_Program: {
            semanticAnalysis(node->program.stmtList, symTab, varTab);
            break;
        }
        case NodeType_StmtList: {
            semanticAnalysis(node->stmtList.stmt, symTab, varTab);
            semanticAnalysis(node->stmtList.stmtList, symTab, varTab);
            break;
        }
        case NodeType_Stmt: {
            semanticAnalysis(node->stmt.child, symTab, varTab);
            break;
        }
        case NodeType_FunctionDeclaration: {
            if (lookupSymbol(symTab, node->functionDeclaration.id->id.name) != NULL) {
                fprintf(stderr, "\nSEMANTIC ERROR:\nFunction %s has already been declared\n\n", node->functionDeclaration.id->id.name);
                exit(0);
            }
            
            addSymbol(symTab, node->functionDeclaration.id->id.name, node->functionDeclaration.type->type.typeName); 

            varTab = lookupSymbol(symTab, node->functionDeclaration.id->id.name)->variables;

            semanticAnalysis(node->functionDeclaration.type, symTab, varTab);
            semanticAnalysis(node->functionDeclaration.id, symTab, varTab);
            semanticAnalysis(node->functionDeclaration.paramList, symTab, varTab);
            semanticAnalysis(node->functionDeclaration.block, symTab, varTab);
            break;
        }
        case NodeType_FunctionCall: {
            if (lookupSymbol(symTab, node->functionCall.id->id.name) == NULL) {
                fprintf(stderr, "\nSEMANTIC ERROR:\nFunction %s has not been declared\n\n", node->functionCall.id->id.name);
                exit(0);
            }

            semanticAnalysis(node->functionCall.id, symTab, varTab);
            semanticAnalysis(node->functionCall.argList, symTab, varTab);
            break;
        }
        case NodeType_ParamList: {
            semanticAnalysis(node->paramList.paramTail, symTab, varTab);
            break;
        }
        case NodeType_ParamTail: {
            semanticAnalysis(node->paramTail.param, symTab, varTab);
            semanticAnalysis(node->paramTail.paramTail, symTab, varTab);
            break;
        }
        case NodeType_Param: {
            semanticAnalysis(node->param.child, symTab, varTab);
            break;
        }
        case NodeType_ArgList: {
            semanticAnalysis(node->argList.argTail, symTab, varTab);
            break;
        }
        case NodeType_ArgTail: {
            semanticAnalysis(node->argTail.expr, symTab, varTab);
            semanticAnalysis(node->argTail.argTail, symTab, varTab);
            break;
        }
        case NodeType_Block: {
            semanticAnalysis(node->block.blockStmtList, symTab, varTab);
            semanticAnalysis(node->block.returnStmt, symTab, varTab);
            break;
        }
        case NodeType_BlockStmtList: {
            semanticAnalysis(node->blockStmtList.blockStmt, symTab, varTab);
            semanticAnalysis(node->blockStmtList.blockStmtList, symTab, varTab);
            break;
        }
        case NodeType_BlockStmt: {
            semanticAnalysis(node->blockStmt.child, symTab, varTab);
            break;
        }
        case NodeType_Return: {
            semanticAnalysis(node->returnStmt.expr, symTab, varTab);
            break;
        }
        case NodeType_Declaration: {
            if (lookupVariable(varTab, node->declaration.id->id.name) != NULL) {
                fprintf(stderr, "\nSEMANTIC ERROR:\nVariable %s has already been declared\n\n", node->declaration.id->id.name);
                exit(0);
            }	

            addVariable(varTab, node->declaration.id->id.name, node->declaration.type->type.typeName, 0);

            semanticAnalysis(node->declaration.type, symTab, varTab);
            semanticAnalysis(node->declaration.id, symTab, varTab);
            break;
        }
        case NodeType_ArrayDeclaration: {
            if (lookupVariable(varTab, node->arrayDeclaration.id->id.name) != NULL) {
                fprintf(stderr, "\nSEMANTIC ERROR:\nArray %s has already been declared\n\n", node->arrayDeclaration.id->id.name);
                exit(0);
            }	
            
            if (node->arrayDeclaration.size == NULL)
                addVariable(varTab, node->arrayDeclaration.id->id.name, node->arrayDeclaration.type->type.typeName, 0);  
            else 
                addVariable(varTab, node->arrayDeclaration.id->id.name, node->arrayDeclaration.type->type.typeName, node->arrayDeclaration.size->number.value);

            semanticAnalysis(node->arrayDeclaration.type, symTab, varTab);
            semanticAnalysis(node->arrayDeclaration.id, symTab, varTab);
            semanticAnalysis(node->arrayDeclaration.size, symTab, varTab);
            break;
        }
        case NodeType_ArrayAssignment: {
            if (lookupVariable(varTab, node->arrayAssignment.id->id.name) == NULL) {
                fprintf(stderr, "\nSEMANTIC ERROR:\nArray %s has not been declared\n\n", node->arrayAssignment.id->id.name);
                exit(0);
            }

            semanticAnalysis(node->arrayAssignment.id, symTab, varTab);
            semanticAnalysis(node->arrayAssignment.index, symTab, varTab);
            semanticAnalysis(node->arrayAssignment.value, symTab, varTab);
            break;
        }
        case NodeType_ArrayAccess: {
            if (lookupVariable(varTab, node->arrayAccess.id->id.name) == NULL) {
                fprintf(stderr, "\nSEMANTIC ERROR:\nArray %s has not been declared\n\n", node->arrayAccess.id->id.name);
                exit(0);
            }

            semanticAnalysis(node->arrayAccess.id, symTab, varTab);
            semanticAnalysis(node->arrayAccess.index, symTab, varTab);
            break;
        }
        case NodeType_Type: {
            break;
        }
        case NodeType_Assignment: {
            if (lookupVariable(varTab, node->assignment.id->id.name) == NULL) {
                fprintf(stderr, "\nSEMANTIC ERROR:\nVariable %s has already been declared\n\n", node->assignment.id->id.name);
                exit(0);
            }

            semanticAnalysis(node->assignment.id, symTab, varTab);
            semanticAnalysis(node->assignment.expr, symTab, varTab);
            break;
        }
        case NodeType_Print: {
            semanticAnalysis(node->print.expr, symTab, varTab);
            break;
        }
        case NodeType_Expr: {
            semanticAnalysis(node->expr.left, symTab, varTab);
            semanticAnalysis(node->expr.right, symTab, varTab);
            break;
        }
        case NodeType_Term: {
            semanticAnalysis(node->term.left, symTab, varTab);
            semanticAnalysis(node->term.right, symTab, varTab);
            break;
        }
        case NodeType_Factor: {
            semanticAnalysis(node->factor.child, symTab, varTab);
            break;
        }
        case NodeType_ID: {
            if (varTab == NULL) {
                if (lookupSymbol(symTab, node->id.name) == NULL) {
                    fprintf(stderr, "Semantic error: Function %s has not been declared\n", node->id.name);
                    exit(0);
                }
            }
            else 
            {
                if (lookupVariable(varTab, node->id.name) == NULL) {
                    fprintf(stderr, "Semantic error: Variable %s has not been declared\n", node->id.name);
                    exit(0);
                }
            }
            break;
        }
        case NodeType_Number: {
            break;
        }
        default: {
            fprintf(stderr, "Unknown Node Type\n");
        }
    }



    // if ((node->nType == NodeType_Expr && (node->parent->nType != NodeType_Assignment && node->parent->nType != NodeType_Expr))) 
    // {
    //     printf("Generating TAC for standalone expression\n");
    //     generateTAC(node);
    // }
    // else if(node->nType == NodeType_Assignment) {
    //     printf("Generating TAC for assignment\n");
    //     generateTAC(node);
    // }
    // else if(node->nType == NodeType_Print) {
    //     printf("Generating TAC for print\n");
    //     generateTAC(node);
    // }
    // // else if(node->nType == NodeType_FunctionCall) {
    // //     printf("Generating TAC for function call\n");
    // //     generateTAC(node);
    // // }
    // else if(node->nType == NodeType_FunctionDeclaration) {
    //     printf("Generating TAC for function declaration\n");
    //     generateTAC(node);
    // }
    // // else if(node->nType == NodeType_ParamList) {
    // //     printf("Generating TAC for param list\n");
    // //     generateTAC(node);
    // // }
    // // else if(node->nType == NodeType_ArgList) {
    // //     printf("Generating TAC for arg list\n");
    // //     generateTAC(node);
    // // }
    // else if(node->nType == NodeType_ArrayDeclaration) {
    //     printf("Generating TAC for array declaration\n");
    //     generateTAC(node);
    // }
    // // else if(node->nType == NodeType_ArrayAccess) {
    // //     printf("Generating TAC for array access\n");
    // //     generateTAC(node);
    // // }
    // else if(node->nType == NodeType_ArrayAssignment) {
    //     printf("Generating TAC for array assignment\n");
    //     generateTAC(node);
    // }
}

// void performSemanticAndTAC(ASTNode* root, SymbolTable* symTab, VariableSymbolTable* varTab) {
//     // Step 1: Perform semantic analysis
//     semanticAnalysis(root, symTab, varTab);
//     // Step 2: Generate TAC after successful semantic analysis
//     generateTAC(root);
// }


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


