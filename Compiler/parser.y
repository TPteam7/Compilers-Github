%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex();
extern int yyparse();
extern FILE* yyin;

extern int yyparse();

void yyerror(const char* s);

%}

%union {
	int number;
	char character;
	char* string;
	char* operator;
}

%token <string> ID
%token INT FLOAT
%token <string> PRINT IF ELSE WHILE RETURN
%token <char> SEMICOLON COMMA PLUS MINUS MULT DIV ASSIGN
%token <char> OPEN_PAREN OPEN_BRACE CLOSE_BRACE CLOSE_PAREN
%token <operator> EQ
%token <number> NUMBER

%printer { fprintf(yyoutput, "%s", $$); } ID;

%type <string> Program Stmt StmtList Expr
%start Program

%%

Program: StmtList { printf("Recieved statement list\n"); };

StmtList:  
	  {}
	| Stmt StmtList;

Stmt: Declaration {} 
	| Assignment {}
	| Print {};

Declaration: Type ID SEMICOLON { printf("Declared variable: %s\n", $2); };

Type: INT { printf("Parsed INT type\n"); }
    | FLOAT { printf("Parsed FLOAT type\n"); };

Assignment: ID EQ Expr SEMICOLON { printf("Assigned value to variable: %s\n", $1); };

Print: PRINT OPEN_PAREN Expr CLOSE_PAREN SEMICOLON { printf("Print statement\n"); };

Expr: Expr PLUS Term { printf("Add operation\n"); }
	| Expr MINUS Term { printf("Subtract operation\n"); }
	| Term {};

Term: Term MULT Factor { printf("Multiply operation\n"); }
	| Term DIV Factor { printf("Divide operation\n"); }
	| Factor {};

Factor: OPEN_PAREN Expr CLOSE_PAREN { printf("Parenthesized expression\n"); }
	| ID { printf("Variable: %s\n", $1); }
	| NUMBER { printf("Number: %d\n", $1); };

%%

int main() {
    yyin = fopen("testProg.cmm", "r");

	yydebug = 0;  // Disable Bison debug mode by default

	printf("Starting to parse\n");
    int result = yyparse();
    printf("yyparse() returned %d\n", result);

    if (result == 0) {
        printf("Parsing successful!\n");
    }

    fclose(yyin);
    return 0;
}

void yyerror(const char* s) {
    fprintf(stderr, "Parse error: %s\n", s);
    exit(1);
}
