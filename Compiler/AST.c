#include "AST.h"

// Utility function to create a new AST node with a specified type
ASTNode* createNode(NodeType nType) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Memory allocation failed for AST node\n");
        exit(1);
    }
    node->nType = nType;
    return node;
}

// Functions for creating AST nodes
ASTNode* createProgramNode(ASTNode* stmtList) {
    ASTNode* node = createNode(NodeType_Program);
    node->program.stmtList = stmtList;
    return node;
}

ASTNode* createStmtListNode(ASTNode* stmt, ASTNode* stmtList) {
    ASTNode* node = createNode(NodeType_StmtList);
    node->stmtList.stmt = stmt;
    node->stmtList.stmtList = stmtList;
    return node;
}

ASTNode* createStmtNode(ASTNode* child) {
    ASTNode* node = createNode(NodeType_Stmt);
    node->stmt.child = child;
    return node;
}

ASTNode* createDeclarationNode(ASTNode* type, ASTNode* id) {
    ASTNode* node = createNode(NodeType_Declaration);
    node->declaration.type = type;
    node->declaration.id = id;
    return node;
}

ASTNode* createTypeNode(char* typeName) {
    ASTNode* node = createNode(NodeType_Type);
    node->type.typeName = typeName;
    return node;
}

ASTNode* createAssignmentNode(ASTNode* id, ASTNode* expr) {
    ASTNode* node = createNode(NodeType_Assignment);
    node->assignment.id = id;
    node->assignment.expr = expr;
    return node;
}

ASTNode* createPrintNode(ASTNode* expr) {
    ASTNode* node = createNode(NodeType_Print);
    node->print.expr = expr;
    return node;
}

ASTNode* createExprNode(char op, ASTNode* left, ASTNode* right) {
    ASTNode* node = createNode(NodeType_Expr);
    node->expr.op = op;
    node->expr.left = left;
    node->expr.right = right;
    return node;
}

ASTNode* createTermNode(char op, ASTNode* left, ASTNode* right) {
    ASTNode* node = createNode(NodeType_Term);
    node->term.op = op;
    node->term.left = left;
    node->term.right = right;
    return node;
}

ASTNode* createFactorNode(ASTNode* child) {
    ASTNode* node = createNode(NodeType_Factor);
    node->factor.child = child;
    return node;
}

ASTNode* createIDNode(char* name) {
    ASTNode* node = createNode(NodeType_ID);
    node->id.name = name;
    return node;
}

ASTNode* createNumberNode(int value) {
    ASTNode* node = createNode(NodeType_Number);
    node->number.value = value;
    return node;
}

// Function to print the AST with indentation
void printAST(ASTNode* node, int indent) {
    if (!node) return;

    for (int i = 0; i < indent; i++) {
        printf("  ");
    }

    switch (node->nType) {
        case NodeType_Program:
            printf("Program\n");
            printAST(node->program.stmtList, indent + 1);
            break;
        case NodeType_StmtList:
            printf("StmtList\n");
            printAST(node->stmtList.stmt, indent + 1);
            printAST(node->stmtList.stmtList, indent + 1);
            break;
        case NodeType_Stmt:
            printf("Stmt\n");
            printAST(node->stmt.child, indent + 1);
            break;
        case NodeType_Declaration:
            printf("Declaration\n");
            printAST(node->declaration.type, indent + 1);
            printAST(node->declaration.id, indent + 1);
            break;
        case NodeType_Type:
            printf("Type: %s\n", node->type.typeName);
            break;
        case NodeType_Assignment:
            printf("Assignment\n");
            printAST(node->assignment.id, indent + 1);
            printAST(node->assignment.expr, indent + 1);
            break;
        case NodeType_Print:
            printf("Print\n");
            printAST(node->print.expr, indent + 1);
            break;
        case NodeType_Expr:
            printf("Expr: %c\n", node->expr.op);
            printAST(node->expr.left, indent + 1);
            printAST(node->expr.right, indent + 1);
            break;
        case NodeType_Term:
            printf("Term: %c\n", node->term.op);
            printAST(node->term.left, indent + 1);
            printAST(node->term.right, indent + 1);
            break;
        case NodeType_Factor:
            printf("Factor\n");
            printAST(node->factor.child, indent + 1);
            break;
        case NodeType_ID:
            printf("ID: %s\n", node->id.name);
            break;
        case NodeType_Number:
            printf("Number: %d\n", node->number.value);
            break;
        default:
            printf("Unknown node type\n");
            break;
    }
}

// Function to free the AST
void freeAST(ASTNode* node) {
    if (!node) return;

    switch (node->nType) {
        case NodeType_Program:
            freeAST(node->program.stmtList);
            break;
        case NodeType_StmtList:
            freeAST(node->stmtList.stmt);
            freeAST(node->stmtList.stmtList);
            break;
        case NodeType_Stmt:
            freeAST(node->stmt.child);
            break;
        case NodeType_Declaration:
            freeAST(node->declaration.type);
            freeAST(node->declaration.id);
            break;
        case NodeType_Assignment:
            freeAST(node->assignment.id);
            freeAST(node->assignment.expr);
            break;
        case NodeType_Print:
            freeAST(node->print.expr);
            break;
        case NodeType_Expr:
            freeAST(node->expr.left);
            freeAST(node->expr.right);
            break;
        case NodeType_Term:
            freeAST(node->term.left);
            freeAST(node->term.right);
            break;
        case NodeType_Factor:
            freeAST(node->factor.child);
            break;
        case NodeType_ID:
        case NodeType_Type:
        case NodeType_Number:
            // No children to free in these cases
            break;
        default:
            break;
    }
    free(node);
}
