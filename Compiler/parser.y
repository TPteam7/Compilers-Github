%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AST.h"

extern int yylex();
extern int yyparse();
extern FILE* yyin;

extern int yyparse();

void yyerror(const char* s);

ASTNode* root = NULL; 
%}

%union {
	int number;
	char character;
	char* string;
	char* operator;
	struct ASTNode* ast;
}

%token <string> TYPE
%token <string> ID
%token <char> SEMICOLON
%token <operator> EQ
%token <char> PLUS
%token <number> NUMBER
%token <string> WRITE

%printer { fprintf(yyoutput, "%s", $$); } ID;

%type <ast> Program VarDecl VarDeclList Stmt StmtList Expr BinOp
%start Program

%%

Program: StmtList {};

StmtList:  {} 
	| Stmt StmtList {};

Stmt: Declaration {} 
	| Assignment {}
	| Print {};

Declaration: Type ID SEMICOLON {};

Type: INT {}
	| FLOAT {};

Assignment: ID EQ Expr SEMICOLON {};

Print: PRINT OPEN_PAREN Expr CLOSE_PAREN SEMICOLON {};

Expr: Expr PLUS Term {}
	| Expr MINUS Term {}
	| Term {};

Term: Term MULT Factor {}
	| Term DIV Factor {}
	| Factor {};

Factor: OPEN_PAREN Expr CLOSE_PAREN {}
	| ID {}
	| NUM {};

%%

int main() {
    // Initialize file or input source
    yyin = fopen("testProg.cmm", "r");

    // Start parsing
    if (yyparse() == 0) {
        // Successfully parsed
		printf("Parsing successful!\n");
        traverseAST(root, 0);
        freeAST(root);
reeAST(root);
se(yyin);
    return 0;
}

void yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
	exit(1);
}
