%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int lines;
extern int chars;

extern int yylex();
extern int yyparse();
extern FILE* yyin;
extern char *yytext;

extern int yyparse();

void yyerror(const char* s);

%}

%union {
	int number;
	char* character;
	char* string;
	char* operator;
}

%token <string> ID
%token INT FLOAT
%token <string> PRINT IF ELSE WHILE RETURN
%token <character> SEMICOLON COMMA
%token <character> OPEN_PAREN OPEN_BRACE CLOSE_BRACE CLOSE_PAREN
%token <operator> ASSIGN PLUS MINUS MULT DIV
%token <number> NUMBER

%printer { fprintf(yyoutput, "%s", $$); } ID;

%type <string> Program Stmt StmtList Expr
%start Program

%%

Program: StmtList { printf("\nPARSER:\nRecieved statement list\n\n"); };

StmtList:  
	  {}
	| Stmt StmtList;

Stmt: Declaration {} 
	| Assignment {}
	| Print {};

Declaration: Type ID SEMICOLON { printf("\nPARSER:\nDeclared variable: %s\n\n", $2); 
}
| error SEMICOLON { 
    printf("\nPARSER ERROR:\nInvalid declaration near '%s'. Expecting format (INT/FLOAT) ID SEMICOLON.\n", yytext); 
	exit(1);
    yyerrok; 
};

Type: INT { printf("\nPARSER:\nParsed INT type\n\n"); }
    | FLOAT { printf("\nPARSER:\nParsed FLOAT type\n\n"); };

Assignment: ID ASSIGN Expr SEMICOLON { printf("\nPARSER:\nAssigned value to variable: %s\n\n", $1); };

Print: PRINT OPEN_PAREN Expr CLOSE_PAREN SEMICOLON { printf("\nPARSER:\nPrint statement\n\n"); };

Expr: Expr PLUS Term { }
	| Expr MINUS Term { }
	| Term {};

Term: Term MULT Factor { }
	| Term DIV Factor { }
	| Factor {};

Factor: OPEN_PAREN Expr CLOSE_PAREN { printf("\nPARSER:\nParenthesized expression\n\n"); }
	| ID { printf("\nPARSER:\nVariable: %s\n\n", $1); }
	| NUMBER { };

%%

int main() {
    yyin = fopen("testProg.cmm", "r");

	yydebug = 0;

	printf("\nPARSER:\nStarting to parse\n\n");
    int result = yyparse();

    if (result == 0) {
        printf("\nPARSER:\nParsing successful!\n");
    }

    fclose(yyin);
    return 0;
}

void yyerror(const char* s) {
    fprintf(stderr, "Parse error: %s at line %d, column %d\n", s, lines, chars);
}

