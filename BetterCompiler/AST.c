#include "AST.h"

// Utility function to create a new AST node with a specified type
ASTNode* createNode(NodeType nType) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Memory allocation failed for AST node\n");
        exit(1);
    }
    node->nType = nType;
    node->parent = NULL;
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

//Create a function declaration AST. We need to pass in the type, id, paramList, and block
ASTNode* createFunctionDeclarationNode(ASTNode* type, ASTNode* id, ASTNode* paramList, ASTNode* block) {
    ASTNode* node = createNode(NodeType_FunctionDeclaration);
    node->functionDeclaration.type = type;
    node->functionDeclaration.id = id;
    node->functionDeclaration.paramList = paramList;
    node->functionDeclaration.block = block;
    return node;
}

ASTNode* createFunctionCallNode(ASTNode* id, ASTNode* paramList) {
    ASTNode* node = createNode(NodeType_FunctionCall);
    node->functionCall.id = id;
    node->functionCall.paramList = paramList;
    return node;
}

ASTNode* createParamListNode(ASTNode* paramTail) {
    ASTNode* node = createNode(NodeType_ParamList);
    node->paramList.paramTail = paramTail;
    return node;
}

ASTNode* createParamTailNode(ASTNode* param, ASTNode* paramTail) {
    ASTNode* node = createNode(NodeType_ParamTail);
    node->paramTail.param = param;
    node->paramTail.paramTail = paramTail;
    return node;
}

ASTNode* createParamNode(ASTNode* type, ASTNode* id) {
    ASTNode* node = createNode(NodeType_Param);
    node->param.type = type;
    node->param.id = id;
    return node;
}

ASTNode* createBlockNode(ASTNode* stmtList) {
    ASTNode* node = createNode(NodeType_Block);
    node->block.stmtList = stmtList;
    return node;
}

ASTNode* createReturnNode(ASTNode* expr) {
    ASTNode* node = createNode(NodeType_Return);
    node->returnStmt.expr = expr;
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
    if (expr) expr->parent = node;
    return node;
}

ASTNode* createPrintNode(ASTNode* expr) {
    ASTNode* node = createNode(NodeType_Print);
    node->print.expr = expr;
    return node;
}

ASTNode* createExprNode(char* op, ASTNode* left, ASTNode* right) {
    ASTNode* node = createNode(NodeType_Expr);
    node->expr.op = op;
    node->expr.left = left;
    node->expr.right = right;
    if (left) left->parent = node;
    if (right) right->parent = node;
    return node;
}

ASTNode* createTermNode(char* op, ASTNode* left, ASTNode* right) {
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
        case NodeType_FunctionDeclaration:
            printf("Function Declaration\n");
            printAST(node->functionDeclaration.type, indent + 1);
            printAST(node->functionDeclaration.id, indent + 1);
            printAST(node->functionDeclaration.paramList, indent + 1);
            printAST(node->functionDeclaration.block, indent + 1);
            break;
        case NodeType_FunctionCall:
            printf("Function Call\n");
            printAST(node->functionCall.id, indent + 1);
            printAST(node->functionCall.paramList, indent + 1);
            break;
        case NodeType_ParamList:
            printf("ParamList\n");
            printAST(node->paramList.paramTail, indent + 1);
            break;
        case NodeType_ParamTail:
            printf("ParamTail\n");
            printAST(node->paramTail.param, indent + 1);
            printAST(node->paramTail.paramTail, indent + 1);
            break;
        case NodeType_Param:
            printf("Param\n");
            printAST(node->param.type, indent + 1);
            printAST(node->param.id, indent + 1);
            break;
        case NodeType_Block:
            printf("Block\n");
            printAST(node->block.stmtList, indent + 1);
            break;
        case NodeType_Return:
            printf("Return\n");
            printAST(node->returnStmt.expr, indent + 1);
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
            printf("Expr: %s\n", node->expr.op);
            printAST(node->expr.left, indent + 1);
            printAST(node->expr.right, indent + 1);
            break;
        case NodeType_Term:
            printf("Term: %s\n", node->term.op);
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
        case NodeType_FunctionDeclaration:
            freeAST(node->functionDeclaration.type);
            freeAST(node->functionDeclaration.id);
            freeAST(node->functionDeclaration.paramList);
            freeAST(node->functionDeclaration.block);
            break;
        case NodeType_FunctionCall:
            freeAST(node->functionCall.id);
            freeAST(node->functionCall.paramList);
            break;
        case NodeType_ParamList:
            freeAST(node->paramList.paramTail);
            break;
        case NodeType_ParamTail:
            freeAST(node->paramTail.param);
            freeAST(node->paramTail.paramTail);
            break;
        case NodeType_Param:
            freeAST(node->param.type);
            freeAST(node->param.id);
            break;
        case NodeType_Block:
            freeAST(node->block.stmtList);
            break;
        case NodeType_Return:
            freeAST(node->returnStmt.expr);
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
