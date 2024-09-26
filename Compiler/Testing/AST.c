

// AST.c
#include "AST.h"
#include <stdio.h>
#include <stdlib.h>

void traverseAST(ASTNode* root, int level) {
    if (root == NULL) return;
    for(int i = 0; i < level; i++) printf("  ");
    switch(root->type) {
        case NodeType_Program:
            printf("Program\n");
            traverseAST(root->program.stmtList, level + 1);
            break;
        case NodeType_StmtList:
            printf("StmtList\n");
            traverseAST(root->stmtList.stmt, level + 1);
            traverseAST(root->stmtList.stmtList, level + 1);
            break;
        case NodeType_Declaration:
            printf("Declaration: %s %s\n", root->declaration.varType, root->declaration.varName);
            break;
        case NodeType_Assignment:
            printf("Assignment: %s =\n", root->assignment.varName);
            traverseAST(root->assignment.expr, level + 1);
            break;
        case NodeType_Print:
            printf("Print\n");
            traverseAST(root->print.expr, level + 1);
            break;
        case NodeType_Expr:
            printf("Expr: %c\n", root->expr.operator);
            traverseAST(root->expr.left, level + 1);
            traverseAST(root->expr.right, level + 1);
            break;
        case NodeType_Term:
            printf("Term: %c\n", root->term.operator);
            traverseAST(root->term.left, level + 1);
            traverseAST(root->term.right, level + 1);
            break;
        case NodeType_Factor:
            printf("Factor: %s\n", root->factor.value);
            break;
        // Handle other node types
        default:
            printf("Unknown node type\n");
    }
}

void freeAST(ASTNode* root) {
    if (root == NULL) return;
    switch(root->type) {
        case NodeType_Program:
            freeAST(root->program.stmtList);
            break;
        case NodeType_StmtList:
            freeAST(root->stmtList.stmt);
            freeAST(root->stmtList.stmtList);
            break;
        case NodeType_Assignment:
            free(root->assignment.varName);
            freeAST(root->assignment.expr);
            break;
        case NodeType_Declaration:
            free(root->declaration.varType);
            free(root->declaration.varName);
            break;
        case NodeType_Print:
            freeAST(root->print.expr);
            break;
        case NodeType_Expr:
            freeAST(root->expr.left);
            freeAST(root->expr.right);
            break;
        case NodeType_Term:
            freeAST(root->term.left);
            freeAST(root->term.right);
            break;
        case NodeType_Factor:
            free(root->factor.value);
            break;
        // Free other node types
        default:
            break;
    }
    free(root);
}