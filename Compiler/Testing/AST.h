// AST.h
#ifndef AST_H
#define AST_H

typedef enum {
    NodeType_Program,
    NodeType_StmtList,
    NodeType_Declaration,
    NodeType_Assignment,
    NodeType_Print,
    NodeType_Expr,
    NodeType_Term,
    NodeType_Factor,
    // Add other node types as needed
} NodeType;

typedef struct ASTNode {
    NodeType type;
    union {
        // Program node
        struct {
            struct ASTNode* stmtList;
        } program;

        // Statement list node
        struct {
            struct ASTNode* stmt;
            struct ASTNode* stmtList;
        } stmtList;

        // Declaration node
        struct {
            char* varType;
            char* varName;
        } declaration;

        // Assignment node
        struct {
            char* varName;
            struct ASTNode* expr;
        } assignment;

        // Print node
        struct {
            struct ASTNode* expr;
        } print;

        // Expression node
        struct {
            struct ASTNode* left;
            char operator;
            struct ASTNode* right;
        } expr;

        // Term node
        struct {
            struct ASTNode* left;
            char operator;
            struct ASTNode* right;
        } term;

        // Factor node
        struct {
            char* value;
        } factor;

        // Add other structures as needed
    };
} ASTNode;

// Function declarations
void traverseAST(ASTNode* root, int level);
void freeAST(ASTNode* root);

#endif // AST_H
