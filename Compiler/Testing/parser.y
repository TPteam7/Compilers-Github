%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AST.h"
#include "symbolTable.h"

#define TABLE_SIZE 100

extern int lines;
extern int chars;

extern int yylex(); // Declare yylex, the lexer function
extern int yyparse(); // Declare yyparse, the parser function
extern FILE* yyin; // Declare yyin, the file pointer for the input file
extern char *yytext;  // The text from the lexer file

extern int yydebug; // Add this line to declare yydebug

void yyerror(const char* s);
SymbolTable* symTab = NULL;
Symbol* symbol = NULL;

ASTNode* root = NULL; // Root of the AST
%}

%union {
    double number;
    char character;
    char* string;
    char op;
    struct ASTNode* ast;
}

%token <string> ID INT FLOAT PRINT IF ELSE WHILE RETURN
%token <character> SEMICOLON COMMA OPEN_PAREN OPEN_BRACE CLOSE_BRACE CLOSE_PAREN
%token <op> ASSIGN PLUS MINUS MULT DIV
%token <number> NUMBER
%token ERROR

%printer { fprintf(yyoutput, "%s", $$); } ID;

%type <string> Type
%type <ast> Program Stmt StmtList Expr Term Factor Declaration Assignment Print

%start Program

%%

Program: StmtList { 
    printf("\nPARSER:\nReceived statement list\n\n"); 
    root = malloc(sizeof(ASTNode));
    if (!root) {
        fprintf(stderr, "Memory allocation failed for AST root.\n");
        exit(EXIT_FAILURE);
    }
    root->type = NodeType_Program;
    root->program.stmtList = $1;
};

StmtList:  
      { 
          // Empty statement list
          $$ = NULL; 
      }
    | Stmt StmtList {
          printf("PARSER: Adding statement to statement list.\n");
          ASTNode* stmtListNode = malloc(sizeof(ASTNode));
          if (!stmtListNode) {
              fprintf(stderr, "Memory allocation failed for StmtList node.\n");
              exit(EXIT_FAILURE);
          }
          stmtListNode->type = NodeType_StmtList;
          stmtListNode->stmtList.stmt = $1;
          stmtListNode->stmtList.stmtList = $2;
          $$ = stmtListNode;
      };

Stmt: Declaration { 
            printf("PARSER: Declaration statement parsed.\n"); 
            $$ = $1; 
        }
    | Assignment { 
            printf("PARSER: Assignment statement parsed.\n"); 
            $$ = $1; 
        }
    | Print { 
            printf("PARSER: Print statement parsed.\n"); 
            $$ = $1; 
        }
    | ERROR SEMICOLON { 
            fprintf(stderr, "Parser Error: Invalid statement near '%s'.\n", yytext); 
            yyerrok; 
            $$ = NULL; // Or handle error appropriately
        };

Declaration: Type ID SEMICOLON {    
        printf("\nPARSER:\nDeclared variable: %s %s\n\n", $1, $2); 

        printf("\nPARSER:\nPrinting symbol table\n");
        printSymbolTable(symTab);

        printf("\nPARSER:\nChecking if variable has already been declared\n");
        symbol = lookupSymbol(symTab, $2);

        if (symbol != NULL) {    // Check if variable has already been declared
            printf("PARSER: Variable %s at line %d has already been declared - COMPILATION HALTED\n", $2, lines);
            exit(EXIT_FAILURE);
        } else {    
            // Variable has not been declared yet    
            // Create AST node for VarDecl
            ASTNode* declNode = malloc(sizeof(ASTNode));
            if (!declNode) {
                fprintf(stderr, "Memory allocation failed for Declaration node.\n");
                exit(EXIT_FAILURE);
            }
            declNode->type = NodeType_Declaration;
            declNode->declaration.varType = strdup($1);
            declNode->declaration.varName = strdup($2);
            // Add variable to symbol table
            addSymbol(symTab, $2, $1);
            printSymbolTable(symTab);
            $$ = declNode;
        }
    }
    | error ASSIGN { 
        printf("Invalid declaration near '%s'. Expecting format (INT/FLOAT) ID SEMICOLON.\n\n", yytext); 
        exit(1);
        yyerrok; 
        $$ = NULL; // Or handle error appropriately
    };

Type: INT { 
            // Return type as string
            $$ = strdup("INT"); 
        }
    | FLOAT { 
            $$ = strdup("FLOAT"); 
        };

Assignment: ID ASSIGN Expr SEMICOLON { 
        printf("\nPARSER:\nAssigned value to variable: %s\n\n", $1); 
        ASTNode* assignNode = malloc(sizeof(ASTNode));
        if (!assignNode) {
            fprintf(stderr, "Memory allocation failed for Assignment node.\n");
            exit(EXIT_FAILURE);
        }
        assignNode->type = NodeType_Assignment;
        assignNode->assignment.varName = strdup($1);
        assignNode->assignment.expr = $3;
        $$ = assignNode;
    };

Print: PRINT OPEN_PAREN Expr CLOSE_PAREN SEMICOLON { 
        printf("\nPARSER:\nPrint statement\n\n"); 
        ASTNode* printNode = malloc(sizeof(ASTNode));
        if (!printNode) {
            fprintf(stderr, "Memory allocation failed for Print node.\n");
            exit(EXIT_FAILURE);
        }
        printNode->type = NodeType_Print;
        printNode->print.expr = $3;
        $$ = printNode;
    };

Expr: Expr PLUS Term { 
        printf("\nPARSER:\nExpr: Addition\n\n"); 
        ASTNode* exprNode = malloc(sizeof(ASTNode));
        if (!exprNode) {
            fprintf(stderr, "Memory allocation failed for Expr node.\n");
            exit(EXIT_FAILURE);
        }
        exprNode->type = NodeType_Expr;
        exprNode->expr.left = $1;
        exprNode->expr.operator = '+';
        exprNode->expr.right = $3;
        $$ = exprNode;
    }
    | Expr MINUS Term { 
        printf("\nPARSER:\nExpr: Subtraction\n\n"); 
        ASTNode* exprNode = malloc(sizeof(ASTNode));
        if (!exprNode) {
            fprintf(stderr, "Memory allocation failed for Expr node.\n");
            exit(EXIT_FAILURE);
        }
        exprNode->type = NodeType_Expr;
        exprNode->expr.left = $1;
        exprNode->expr.operator = '-';
        exprNode->expr.right = $3;
        $$ = exprNode;
    }
    | Term { 
        $$ = $1; 
    };

Term: Term MULT Factor { 
        printf("\nPARSER:\nTerm: Multiplication\n\n"); 
        ASTNode* termNode = malloc(sizeof(ASTNode));
        if (!termNode) {
            fprintf(stderr, "Memory allocation failed for Term node.\n");
            exit(EXIT_FAILURE);
        }
        termNode->type = NodeType_Term;
        termNode->term.left = $1;
        termNode->term.operator = '*';
        termNode->term.right = $3;
        $$ = termNode;
    }
    | Term DIV Factor { 
        printf("\nPARSER:\nTerm: Division\n\n"); 
        ASTNode* termNode = malloc(sizeof(ASTNode));
        if (!termNode) {
            fprintf(stderr, "Memory allocation failed for Term node.\n");
            exit(EXIT_FAILURE);
        }
        termNode->type = NodeType_Term;
        termNode->term.left = $1;
        termNode->term.operator = '/';
        termNode->term.right = $3;
        $$ = termNode;
    }
    | Factor { 
        $$ = $1; 
    };

Factor: OPEN_PAREN Expr CLOSE_PAREN { 
        printf("\nPARSER:\nParenthesized expression\n\n"); 
        $$ = $2; // The expression inside the parentheses
    }
    | ID { 
        printf("\nPARSER:\nVariable: %s\n\n", $1); 
        ASTNode* factorNode = malloc(sizeof(ASTNode));
        if (!factorNode) {
            fprintf(stderr, "Memory allocation failed for Factor node.\n");
            exit(EXIT_FAILURE);
        }
        factorNode->type = NodeType_Factor;
        factorNode->factor.value = strdup($1);
        $$ = factorNode;
    }
    | NUMBER { 
        printf("\nPARSER:\nNumber: %f\n\n", $1); 
        ASTNode* factorNode = malloc(sizeof(ASTNode));
        if (!factorNode) {
            fprintf(stderr, "Memory allocation failed for Factor node.\n");
            exit(EXIT_FAILURE);
        }
        factorNode->type = NodeType_Factor;
        char buffer[32];
        sprintf(buffer, "%lf", $1);
        factorNode->factor.value = strdup(buffer);
        $$ = factorNode;
    };

%%

int main() {
    yyin = fopen("testProg.cmm", "r");
    if (!yyin) {
        perror("Failed to open input file");
        return EXIT_FAILURE;
    }

    yydebug = 0;

    // Initialize symbol table
    symTab = createSymbolTable(TABLE_SIZE);
    if (symTab == NULL) {
        fprintf(stderr, "Failed to create symbol table.\n");
        return EXIT_FAILURE;
    }

    printf("\nPARSER:\nStarting to parse\n\n");
    int result = yyparse();

    if (result == 0) {
        // Print symbol table for debugging
        printSymbolTable(symTab);

        printf("\nPARSER:\nParsing successful!\n");
        printf("\n=== AST Traversal ===\n");
        traverseAST(root, 0);
    } else {
        fprintf(stderr, "Parsing failed with errors.\n");
    }

    fclose(yyin);
    return result;
}

void yyerror(const char* s) {
    fprintf(stderr, "\nPARSER ERROR:\n%s at line %d, column %d\n", s, lines, chars);
}
