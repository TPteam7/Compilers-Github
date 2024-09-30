%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AST.h"
#include "symbolTable.h"
#include "semantic.h"
#include "optimizer.h"

#define TABLE_SIZE 100

extern int lines;
extern int chars;

extern int yylex(); // Declare yylex, the lexer function
extern int yyparse(); // Declare yyparse, the parser function
extern FILE* yyin; // Declare yyin, the file pointer for the input file
extern int yylineno;  // Declare yylineno, the line number counter
extern char *yytext;  // The text from the lexer file
extern TAC* tacHead;  // Declare the head of the linked list of TAC entries

void yyerror(const char* s);

ASTNode* root = NULL;
SymbolTable* symTab = NULL;
Symbol* symbol = NULL;

// Declare global print booleans
int printSymbolDebug = 0;
int printParserDebug = 0;

%}

%union {
	int number;
	char character;
	char* string;
	char op;
	struct ASTNode* node;
}

%token <string> ID
%token <string> INT FLOAT
%token <string> PRINT IF ELSE WHILE RETURN
%token <character> SEMICOLON COMMA
%token <character> OPEN_PAREN OPEN_BRACE CLOSE_BRACE CLOSE_PAREN
%token <op> ASSIGN PLUS MINUS MULT DIV
%token <number> NUMBER

%printer { fprintf(yyoutput, "%s", $$); } ID;

%type <node> Program StmtList Stmt Declaration Type Assignment Print Expr Term Factor
%start Program

%%

Program: StmtList { $$ = createProgramNode($1); root = $$; };



StmtList:  { $$ = NULL; }
	| Stmt StmtList { $$ = createStmtListNode($1, $2); };



Stmt: Declaration { $$ = createStmtNode($1); } 
	| Assignment { $$ = createStmtNode($1); }
	| Print { $$ = createStmtNode($1); };



Declaration: Type ID SEMICOLON { $$ = createDeclarationNode($1, createIDNode($2)); };



Type: INT { $$ = createTypeNode("int"); }
    | FLOAT { $$ = createTypeNode("float"); };



Assignment: ID ASSIGN Expr SEMICOLON { $$ = createAssignmentNode(createIDNode($1), $3); };



Print: PRINT OPEN_PAREN Expr CLOSE_PAREN SEMICOLON { $$ = createPrintNode($3); };



Expr: Expr PLUS Term { $$ = createExprNode($2, $1, $3); }
	| Expr MINUS Term { $$ = createExprNode($2, $1, $3); }
	| Term { $$ = $1; };

Term: Term MULT Factor { $$ = createTermNode($2, $1, $3); }
	| Term DIV Factor { $$ = createTermNode($2, $1, $3); }
	| Factor { $$ = $1; };



Factor: OPEN_PAREN Expr CLOSE_PAREN { $$ = createFactorNode($2); }
	| ID { $$ = createIDNode($1); }
	| NUMBER { $$ = createNumberNode($1); };



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
		if(printSymbolDebug == 1)
		{
			printSymbolTable(symTab);
		}

        printf("\nPARSER:\nParsing successful!\n");

		printAST(root, 0);

		// Semantic analysis
		printf("\n=== SEMANTIC ANALYSIS ===\n\n");
		semanticAnalysis(root, symTab);

		printTAC(tacHead);

		printTACToFile("TAC.ir", tacHead);

		// Code optimization
		printf("\n\n=== CODE OPTIMIZATION ===\n");
		// Traverse the linked list of TAC entries and optimize
		// But - you MIGHT need to traverse the AST again to optimize

		optimizeTAC(&tacHead);
		printOptimizedTAC("TACOptimized.ir", tacHead);

		// Code generation
		printf("\n=== CODE GENERATION ===\n");
		initCodeGenerator("output.s");
		generateMIPS(tacHead);
		finalizeCodeGenerator("output.s");

        freeAST(root);
		freeSymbolTable(symTab);
    }

    fclose(yyin);
    return 0;
}

void yyerror(const char* s) {
    fprintf(stderr, "\nPARSER ERROR:\n%s at line %d, column %d\n", s, lines, chars);
}

