#ifndef AST_H
#define AST_H

#include <stdlib.h>
#include <stdio.h>

typedef enum {
    NodeType_Program,
    NodeType_StmtList,
    NodeType_Function,
    NodeType_ParamList,
    NodeType_ParamTail,
    NodeType_Param,
    NodeType_Block,
    NodeType_Stmt,
    NodeType_Declaration,
    NodeType_Type,
    NodeType_Assignment,
    NodeType_Print,
    NodeType_Expr,
    NodeType_Term,
    NodeType_Factor,
    NodeType_ID,
    NodeType_Number
} NodeType;

// Structure for AST nodes
typedef struct ASTNode {

    NodeType nType;
    
    struct ASTNode* parent; // Pointer to the parent node

    union {
        struct {
            struct ASTNode* stmtList;
        } program;
        
        struct {
            struct ASTNode* stmt;
            struct ASTNode* stmtList;
        } stmtList;

        struct {
            struct ASTNode* child; // Declaration, assignment, or print
        } stmt;

        struct {
            struct ASTNode* type;
            struct ASTNode* id;
        } declaration;

        struct {
            char* typeName;
        } type;

        struct {
            struct ASTNode* id;
            struct ASTNode* expr;
        } assignment;

        struct {
            struct ASTNode* expr;
        } print;

        struct {
            char* op;
            struct ASTNode* left;
            struct ASTNode* right;
        } expr;

        struct {
            char* op;
            struct ASTNode* left;
            struct ASTNode* right;
        } term;

        struct {
            struct ASTNode* child; // Expression, ID, or Number
        } factor;

        struct {
            char* name;
        } id;

        struct {
            int value;
        } number;

        char* tempVar; 
    };

} ASTNode;


// Functions for creating AST nodes
ASTNode* createProgramNode(ASTNode* stmtList);
ASTNode* createStmtListNode(ASTNode* stmt, ASTNode* stmtList);
ASTNode* createStmtNode(ASTNode* child);
ASTNode* createDeclarationNode(ASTNode* type, ASTNode* id);
ASTNode* createTypeNode(char* typeName);
ASTNode* createAssignmentNode(ASTNode* id, ASTNode* expr);
ASTNode* createPrintNode(ASTNode* expr);
ASTNode* createExprNode(char* op, ASTNode* left, ASTNode* right);
ASTNode* createTermNode(char* op, ASTNode* left, ASTNode* right);
ASTNode* createFactorNode(ASTNode* child);
ASTNode* createIDNode(char* name);
ASTNode* createNumberNode(int value);

// Functions to print and free the AST
void printAST(ASTNode* node, int indent);
void freeAST(ASTNode* node);
void traverseAST(ASTNode* node, int level);

#endif