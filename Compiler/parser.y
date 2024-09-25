%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbolTable.h"

#define TABLE_SIZE 100

extern int lines;
extern int chars;

extern int yylex(); // Declare yylex, the lexer function
extern int yyparse(); // Declare yyparse, the parser function
extern FILE* yyin; // Declare yyin, the file pointer for the input file
extern int yylineno;  // Declare yylineno, the line number counter
extern char *yytext;  // The text from the lexer file


void yyerror(const char* s);
SymbolTable* symTab = NULL;
Symbol* symbol = NULL;

%}

%union {
	int number;
	char* character;
	char* string;
	char* operator;
}

%token <string> ID
%token <string> INT FLOAT
%token <string> PRINT IF ELSE WHILE RETURN
%token <character> SEMICOLON COMMA
%token <character> OPEN_PAREN OPEN_BRACE CLOSE_BRACE CLOSE_PAREN
%token <operator> ASSIGN PLUS MINUS MULT DIV
%token <number> NUMBER

%printer { fprintf(yyoutput, "%s", $$); } ID;

%type <string> Program Stmt StmtList Expr
%type <string> Type
%start Program

%%

Program: StmtList { printf("\nPARSER:\nRecieved statement list\n\n"); };

StmtList:  
	  {}
	| Stmt StmtList;

Stmt: Declaration {} 
	| Assignment {}
	| Print {};

Declaration: Type ID SEMICOLON { 	
	printf("\nPARSER:\nDeclared variable: %s %s %s\n\n", $1, $2, $3); 

	printf("\nPARSER:\nPrinting symbol table\n");
	printSymbolTable(symTab);

	printf("\nPARSER:\nChecking if variable has already been declared\n");
	symbol = lookupSymbol(symTab, $2);

	if (symbol != NULL) {	// Check if variable has already been declared
									printf("PARSER: Variable %s at line %d has already been declared - COMPILATION HALTED\n", $2, yylineno);
									exit(0);
								} else {	
										// Variable has not been declared yet	
										// Create AST node for VarDecl

										//$$ = malloc(sizeof(ASTNode));
										//$$->type = NodeType_VarDecl;
										//$$->varDecl.varType = strdup($1);
										//$$->varDecl.varName = strdup($2);
										// Set other fields as necessary

										// Add variable to symbol table
										addSymbol(symTab, $2, $1);
										printSymbolTable(symTab);
									}
}
| error ASSIGN { 
    printf("Invalid declaration near '%s'. Expecting format (INT/FLOAT) ID SEMICOLON.\n\n", yytext); 
	exit(1);
    yyerrok; 
};

Type: INT {
		$$ = strdup($1);
	 	printf("\nPARSER:\nParsed INT type\n\n"); 
	 }
    | FLOAT { 
			$$ = strdup($1);
			printf("\nPARSER:\nParsed FLOAT type\n\n"); 
		};

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

	// Initialize symbol table
	symTab = createSymbolTable(TABLE_SIZE);
    if (symTab == NULL) {
        // Handle error
        return EXIT_FAILURE;
    }

	//not sure if needed
	symbol = malloc(sizeof(Symbol));

	printf("\nPARSER:\nStarting to parse\n\n");
    int result = yyparse();

    if (result == 0) {
		// Print symbol table for debugging
		printSymbolTable(symTab);

        printf("\nPARSER:\nParsing successful!\n");
    }

    fclose(yyin);
    return 0;
}

void yyerror(const char* s) {
    fprintf(stderr, "\nPARSER ERROR:\n%s at line %d, column %d\n", s, lines, chars);
}

