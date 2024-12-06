#ifndef AST_H
#define AST_H

#include <stdlib.h>
#include <stdio.h>

typedef enum {
    NodeType_Program,
    NodeType_StmtList,
    NodeType_Stmt,
    NodeType_FunctionDeclaration,
    NodeType_FunctionCall,
    NodeType_IfBlock,
    NodeType_IfStmt,
    NodeType_ElseIfStmt,
    NodeType_ElseStmt,
    NodeType_WhileStmt,
    NodeType_Condition,
    NodeType_ConditionTail,
    NodeType_ConditionList,
    NodeType_Sign,
    NodeType_Conjunction,
    NodeType_ParamList,
    NodeType_ParamTail,
    NodeType_Param,
    NodeType_ArgList,
    NodeType_ArgTail,
    NodeType_Block,
    NodeType_BlockStmtList,
    NodeType_BlockStmt,
    NodeType_Return,
    NodeType_Declaration,
    NodeType_DeclarationAssignment,
    NodeType_ArrayDeclaration,
    NodeType_ArrayAccess,
    NodeType_ArrayAssignment,
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
            struct ASTNode* child; // Declaration, assignment, print, functionCall, functionDeclaration, DeclarationAssignment
        } stmt;

        struct {
            struct ASTNode* type;
            struct ASTNode* id;
            struct ASTNode* paramList;
            struct ASTNode* block;
        } functionDeclaration;

        struct {
            struct ASTNode* id;
            struct ASTNode* argList;      // switched from paramList to argList
        } functionCall;

        struct {
            struct ASTNode* ifStmt;        // IfStmt 
            struct ASTNode* elseIfList;    // Linked list of ElseIfStmt nodes
            struct ASTNode* elseStmt;      // Optional ElseStmt node
        } ifBlock;

        struct {
            struct ASTNode* condition; 
            struct ASTNode* block;
        } ifStmt;

        struct {
            struct ASTNode* condition;
            struct ASTNode* block;
            struct ASTNode* next; // Next ElseIfStmt in the list
        } elseIfStmt;

        struct {
            struct ASTNode* block;
        } elseStmt;

        struct {
            struct ASTNode* condition;
            struct ASTNode* block;
        } whileStmt;

        struct {
            struct ASTNode* expr;
            struct ASTNode* sign;
            struct ASTNode* expr2;
        } condition;

        struct{
            struct ASTNode* conjunction;
            struct ASTNode* condition; 
            struct ASTNode* conditionTail;
        } conditionTail;

        struct {
            struct ASTNode* condition;
            struct ASTNode* conditionTail;
        } conditionList;

        struct {
            char* op; 
        } sign;

        struct {
            char* op;
        } conjunction;

        struct {
            struct ASTNode* paramTail;
        } paramList;

        struct {
            struct ASTNode* param;
            struct ASTNode* paramTail;
        } paramTail;

        struct {
            struct ASTNode* child;          // Declaration or Array Declaration
        } param;

        struct {
            struct ASTNode* argTail;
        } argList;

        struct {
            struct ASTNode* expr;
            struct ASTNode* argTail;
        } argTail;

        struct {
            struct ASTNode* blockStmtList;
            struct ASTNode* returnStmt;
        } block;

        struct {
            struct ASTNode* blockStmt;
            struct ASTNode* blockStmtList;
        } blockStmtList;

        struct {
            struct ASTNode* child; // Declaration, assignment, print, functionCall, functionDeclaration
        } blockStmt;

        struct {
            struct ASTNode* expr;
        } returnStmt;

        struct {
            struct ASTNode* type;
            struct ASTNode* id;
        } declaration;

        struct {
            struct ASTNode* type;
            struct ASTNode* id;
            struct ASTNode* expr;
        } declarationAssignment;

        struct {
            struct ASTNode* type;
            struct ASTNode* id;
            struct ASTNode* size;
        } arrayDeclaration;

        struct {
            struct ASTNode* id;
            struct ASTNode* index;
        } arrayAccess;

        struct {
            struct ASTNode* id;
            struct ASTNode* index;
            struct ASTNode* value;
        } arrayAssignment;

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
ASTNode* createFunctionDeclarationNode(ASTNode* type, ASTNode* id, ASTNode* paramList, ASTNode* block);
ASTNode* createFunctionCallNode(ASTNode* id, ASTNode* argList);
ASTNode* createIfBlockNode(ASTNode* ifStmt, ASTNode* elseIfList, ASTNode* elseStmt);
ASTNode* createIfStmtNode(ASTNode* condition, ASTNode* block);
ASTNode* createElseIfStmtNode(ASTNode* condition, ASTNode* block, ASTNode* next);
ASTNode* createElseStmtNode(ASTNode* block);
ASTNode* createWhileStmtNode(ASTNode* condition, ASTNode* block);
ASTNode* createConditionNode(ASTNode* expr, ASTNode* sign, ASTNode* expr2);
ASTNode* createConditionTailNode(ASTNode* conjunction, ASTNode* condition, ASTNode* conditionTail);
ASTNode* createConditionListNode(ASTNode* condition, ASTNode* conditionTail);
ASTNode* createSignNode(char* op);
ASTNode* createConjunctionNode(char* op);
ASTNode* createParamListNode(ASTNode* paramTail);
ASTNode* createParamTailNode(ASTNode* param, ASTNode* paramTail);
ASTNode* createParamNode(ASTNode* child);
ASTNode* createArgListNode(ASTNode* argTail);
ASTNode* createArgTailNode(ASTNode* expr, ASTNode* argTail);
ASTNode* createBlockNode(ASTNode* blockStmtList, ASTNode* returnStmt);
ASTNode* createBlockStmtListNode(ASTNode* blockStmt, ASTNode* blockStmtList);
ASTNode* createBlockStmtNode(ASTNode* child);
ASTNode* createReturnNode(ASTNode* expr);
ASTNode* createDeclarationNode(ASTNode* type, ASTNode* id);
ASTNode* createDeclarationAssignmentNode(ASTNode* type, ASTNode* id, ASTNode* expr);
ASTNode* createArrayDeclarationNode(ASTNode* type, ASTNode* id, ASTNode* size);
ASTNode* createArrayAccessNode(ASTNode* id, ASTNode* index);
ASTNode* createArrayAssignmentNode(ASTNode* id, ASTNode* index, ASTNode* value);
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

#endif