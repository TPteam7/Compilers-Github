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

//ASTNode* root = NULL; 
%}

%union {
	int number;
	char character;
	char* string;
	char* operator;
	struct ASTNode* ast;
}


%token <string> ID
%token INT FLOAT
%token <string> PRINT IF ELSE WHILE RETURN
%token <char> SEMICOLON COMMA PLUS MINUS MULT DIV
%token <char> OPEN_PAREN OPEN_BRACE CLOSE_BRACE CLOSE_PAREN
%token <operator> EQ
%token <number> NUM

%printer { fprintf(yyoutput, "%s", $$); } ID;

%type <ast> Program Stmt StmtList Expr
%start Program

%%

Program: StmtList {};

StmtList:  {} 
	| Stmt StmtList {};

Stmt: Declaration {} 
	| Assignment {}
	| Print {};

Declaration: Type ID SEMICOLON { printf("Declared variable: %s\n", $2); };

Type: INT { printf("Parsed INT type\n"); }
    | FLOAT { printf("Parsed FLOAT type\n"); };

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
    yyin = fopen("testProg.cmm", "r");

	yydebug = 1;  // Enable Bison debug mode

	printf("Starting to parse\n");
    int result = yyparse();
    printf("yyparse() returned %d\n", result);

	

    if (result == 0) {
        printf("Parsing successful!\n");
        //traverseAST(root, 0);
        //freeAST(root);
    }

    fclose(yyin);
    return 0;
}

void yyerror(const char* s) {
    fprintf(stderr, "Parse error: %s\n", s);
    exit(1);
}
