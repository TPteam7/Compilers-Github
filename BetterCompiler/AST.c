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

ASTNode* createStmtNode(ASTNode* child) {
    ASTNode* node = createNode(NodeType_Stmt);
    node->stmt.child = child;
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

ASTNode* createFunctionCallNode(ASTNode* id, ASTNode* argList) {
    ASTNode* node = createNode(NodeType_FunctionCall);
    node->functionCall.id = id;
    node->functionCall.argList = argList;
    return node;
}

ASTNode* createIfBlockNode(ASTNode* child) {
    ASTNode* node = createNode(NodeType_IfBlock);
    node->ifBlock.child = child;
    return node;
}

ASTNode* createIfStmtNode(ASTNode* condition, ASTNode* block) {
    ASTNode* node = createNode(NodeType_IfStmt);
    node->ifStmt.condition = condition;
    node->ifStmt.block = block;
    return node;
}

ASTNode* createElseIfStmtNode(ASTNode* condition, ASTNode* block) {
    ASTNode* node = createNode(NodeType_ElseIfStmt);
    node->elseIfStmt.condition = condition;
    node->elseIfStmt.block = block;
    return node;
}

ASTNode* createElseStmtNode(ASTNode* block) {
    ASTNode* node = createNode(NodeType_ElseStmt);
    node->elseStmt.block = block;
    return node;
}

ASTNode* createConditionNode(ASTNode* expr, ASTNode* sign, ASTNode* expr2) {
    ASTNode* node = createNode(NodeType_Condition);
    node->condition.expr = expr;
    node->condition.sign = sign;
    node->condition.expr2 = expr2;
    return node;
}

ASTNode* createSignNode(char* op) {
    ASTNode* node = createNode(NodeType_Sign);
    node->sign.op = op;
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

ASTNode* createParamNode(ASTNode* child) {
    ASTNode* node = createNode(NodeType_Param);
    node->param.child = child;
    return node;
}

ASTNode* createArgListNode(ASTNode* argTail) {
    ASTNode* node = createNode(NodeType_ArgList);
    node->argList.argTail = argTail;
    return node;
}

ASTNode* createArgTailNode(ASTNode* expr, ASTNode* argTail) {
    ASTNode* node = createNode(NodeType_ArgTail);
    node->argTail.expr = expr;
    node->argTail.argTail = argTail;
    return node;
}

ASTNode* createBlockNode(ASTNode* blockStmtList, ASTNode* returnStmt) {
    ASTNode* node = createNode(NodeType_Block);
    node->block.blockStmtList = blockStmtList;
    node->block.returnStmt = returnStmt;
    return node;
}

ASTNode* createBlockStmtListNode(ASTNode* blockStmt, ASTNode* blockStmtList) {
    ASTNode* node = createNode(NodeType_BlockStmtList);
    node->blockStmtList.blockStmt = blockStmt;
    node->blockStmtList.blockStmtList = blockStmtList;
    return node;
}

ASTNode* createBlockStmtNode(ASTNode* child) {
    ASTNode* node = createNode(NodeType_BlockStmt);
    node->blockStmt.child = child;
    return node;
}

ASTNode* createReturnNode(ASTNode* expr) {
    ASTNode* node = createNode(NodeType_Return);
    node->returnStmt.expr = expr;
    return node;
}

ASTNode* createDeclarationNode(ASTNode* type, ASTNode* id) {
    ASTNode* node = createNode(NodeType_Declaration);
    node->declaration.type = type;
    node->declaration.id = id;
    return node;
}

ASTNode* createDeclarationAssignmentNode(ASTNode* type, ASTNode* id, ASTNode* expr) {
    ASTNode* node = createNode(NodeType_DeclarationAssignment);
    node->declarationAssignment.type = type;
    node->declarationAssignment.id = id;
    node->declarationAssignment.expr = expr;
    return node;
}

// Array Declaration Node
ASTNode* createArrayDeclarationNode(ASTNode* type, ASTNode* id, ASTNode* size) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->nType = NodeType_ArrayDeclaration;
    node->arrayDeclaration.type = type;
    node->arrayDeclaration.id = id;
    node->arrayDeclaration.size = size;
    return node;
}

// Array Access Node
ASTNode* createArrayAccessNode(ASTNode* id, ASTNode* index) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->nType = NodeType_ArrayAccess;
    node->arrayAccess.id = id;
    node->arrayAccess.index = index;
    return node;
}

// Array Assignment Node
ASTNode* createArrayAssignmentNode(ASTNode* id, ASTNode* index, ASTNode* value) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->nType = NodeType_ArrayAssignment;
    node->arrayAssignment.id = id;
    node->arrayAssignment.index = index;
    node->arrayAssignment.value = value;
    if (id) id->parent = node;
    if (index) index->parent = node;
    if (value) value->parent = node;
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
    printf("Creating Expr Node %s\n", op);
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
            printAST(node->functionCall.argList, indent + 1);
            break;
        case NodeType_IfBlock:
            printf("If Block\n");
            printAST(node->ifBlock.child, indent + 1);
            break;
        case NodeType_IfStmt:
            printf("If Statement\n");
            printAST(node->ifStmt.condition, indent + 1);
            printAST(node->ifStmt.block, indent + 1);
            break;
        case NodeType_ElseIfStmt:
            printf("Else If Statement\n");
            printAST(node->elseIfStmt.condition, indent + 1);
            printAST(node->elseIfStmt.block, indent + 1);
            break;
        case NodeType_ElseStmt:
            printf("Else Statement\n");
            printAST(node->elseStmt.block, indent + 1);
            break;
        case NodeType_Condition:
            printf("Condition\n");
            printAST(node->condition.expr, indent + 1);
            printAST(node->condition.sign, indent + 1);
            printAST(node->condition.expr2, indent + 1);
            break;
        case NodeType_Sign:
            printf("Sign: %s\n", node->sign.op);
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
            printAST(node->param.child, indent + 1);
            break;
        case NodeType_ArgList:
            printf("ArgList\n");
            printAST(node->argList.argTail, indent + 1);
            break;
        case NodeType_ArgTail:
            printf("ArgTail\n");
            printAST(node->argTail.expr, indent + 1);
            printAST(node->argTail.argTail, indent + 1);
            break;
        case NodeType_Block:
            printf("Block\n");
            printAST(node->block.blockStmtList, indent + 1);
            printAST(node->block.returnStmt, indent + 1);
            break;
        case NodeType_BlockStmtList:
            printf("BlockStmtList\n");
            printAST(node->blockStmtList.blockStmt, indent + 1);
            printAST(node->blockStmtList.blockStmtList, indent + 1);
            break;
        case NodeType_BlockStmt:
            printf("BlockStmt\n");
            printAST(node->blockStmt.child, indent + 1);
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
        case NodeType_DeclarationAssignment:
            printf("Declaration Assignment\n");
            printAST(node->declarationAssignment.type, indent + 1);
            printAST(node->declarationAssignment.id, indent + 1);
            printAST(node->declarationAssignment.expr, indent + 1);
            break;
        case NodeType_ArrayDeclaration:
            printf("Array Declaration\n");
            printAST(node->arrayDeclaration.type, indent + 1);
            printAST(node->arrayDeclaration.id, indent + 1);
            for (int i = 0; i < indent + 1; i++) printf("  ");
            printf("Size\n");
            printAST(node->arrayDeclaration.size, indent + 2);
            break;
        case NodeType_ArrayAssignment:
            printf("Array Assignment\n");
            printAST(node->arrayAssignment.id, indent + 1);
            for (int i = 0; i < indent + 1; i++) printf("  ");
            printf("Index\n");
            printAST(node->arrayAssignment.index, indent + 2);
            for (int i = 0; i < indent + 1; i++) printf("  ");
            printf("Value\n");
            printAST(node->arrayAssignment.value, indent + 2);
            break;
        case NodeType_ArrayAccess:
            printf("Array Access\n");
            printAST(node->arrayAccess.id, indent + 1);
            for (int i = 0; i < indent + 1; i++) printf("  ");
            printf("Index\n");
            printAST(node->arrayAccess.index, indent + 2);
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
            freeAST(node->functionCall.argList);
            break;
        case NodeType_IfBlock:
            freeAST(node->ifBlock.child);
            break;
        case NodeType_IfStmt:
            freeAST(node->ifStmt.condition);
            freeAST(node->ifStmt.block);
            break;
        case NodeType_ElseIfStmt:
            freeAST(node->elseIfStmt.condition);
            freeAST(node->elseIfStmt.block);
            break;
        case NodeType_ElseStmt:
            freeAST(node->elseStmt.block);
            break;
        case NodeType_Condition:
            freeAST(node->condition.expr);
            freeAST(node->condition.sign);
            freeAST(node->condition.expr2);
            break;
        case NodeType_Sign:
            // Free the operator string if allocated
            if (node->sign.op != NULL) {
                free(node->sign.op);
                node->sign.op = NULL;
            }
            break;
        case NodeType_ParamList:
            freeAST(node->paramList.paramTail);
            break;
        case NodeType_ParamTail:
            freeAST(node->paramTail.param);
            freeAST(node->paramTail.paramTail);
            break;
        case NodeType_Param:
            freeAST(node->param.child);
            break;
        case NodeType_ArgList:
            freeAST(node->argList.argTail);
            break;
        case NodeType_ArgTail:
            freeAST(node->argTail.expr);
            freeAST(node->argTail.argTail);
            break;
        case NodeType_Block:
            freeAST(node->block.blockStmtList);
            freeAST(node->block.returnStmt);
            break;
        case NodeType_Return:
            freeAST(node->returnStmt.expr);
            break;
        case NodeType_Declaration:
            freeAST(node->declaration.type);
            freeAST(node->declaration.id);
            break;
        case NodeType_DeclarationAssignment:
            freeAST(node->declarationAssignment.type);
            freeAST(node->declarationAssignment.id);
            freeAST(node->declarationAssignment.expr);
            break;
        case NodeType_ArrayDeclaration:
            freeAST(node->arrayDeclaration.type);
            freeAST(node->arrayDeclaration.id);
            freeAST(node->arrayDeclaration.size);
            break;
        case NodeType_ArrayAssignment:
            freeAST(node->arrayAssignment.id);
            freeAST(node->arrayAssignment.index);
            freeAST(node->arrayAssignment.value);
            break;
        case NodeType_ArrayAccess:
            freeAST(node->arrayAccess.id);
            freeAST(node->arrayAccess.index);
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
            // Free the operator string if allocated
            if (node->expr.op != NULL) {
                free(node->expr.op);
                node->expr.op = NULL;
            }
            break;
        case NodeType_Term:
            freeAST(node->term.left);
            freeAST(node->term.right);
            break;
        case NodeType_Factor:
            freeAST(node->factor.child);
            break;
        case NodeType_ID:
            // Free the identifier string
            if (node->id.name != NULL) {
                free(node->id.name);
                node->id.name = NULL;
            }
        case NodeType_Type:
            // Free the type string
            if (node->type.typeName != NULL) {
                free(node->type.typeName);
                node->type.typeName = NULL;
            }
        case NodeType_Number:
            // No children to free in these cases
            break;
        default:
            break;
    }
    free(node);
}
