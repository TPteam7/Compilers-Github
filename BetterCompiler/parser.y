%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AST.h"
//#include "symbolTable.h"
//#include "semantic.h"
//#include "optimizer.h"
//#include "codeGenerator.h"

#define TABLE_SIZE 100

extern int lines;
extern int chars;

extern int yylex(); // Declare yylex, the lexer function
extern int yyparse(); // Declare yyparse, the parser function
extern FILE* yyin; // Declare yyin, the file pointer for the input file
extern int yylineno;  // Declare yylineno, the line number counter
extern char *yytext;  // The text from the lexer file
//extern TAC* tacHead;  // Declare the head of the linked list of TAC entries

void yyerror(const char* s);

ASTNode* root = NULL;
//SymbolTable* symTab = NULL;
//Symbol* symbol = NULL;

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
%token <string> INT FLOAT BOOL VOID TRUE FALSE
%token <string> PRINT IF ELSE WHILE RETURN
%token <character> SEMICOLON COMMA
%token <character> LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET
%token <op> ASSIGN PLUS MINUS MULT DIV
%token <number> NUMBER

%printer { fprintf(yyoutput, "%s", $$); } ID;

%type <node> Program StmtList Stmt Declaration Type Assignment Print Expr Term Factor
%type <node> FunctionDefinition FunctionCall ParamList ParamTail Param ArgList ArgTail Block
%start Program

%%

Program: StmtList { $$ = createProgramNode($1); root = $$; };


StmtList:  { $$ = NULL; }
	| Stmt StmtList { $$ = createStmtListNode($1, $2); }
	| FunctionDefinition StmtList { $$ = createStmtListNode($1, $2); };


FunctionDefinition: Type ID LPAREN ParamList RPAREN LBRACE Block RBRACE { $$ = createFunctionDeclarationNode($1, createIDNode($2), $4, $7); };


FunctionCall: ID LPAREN ArgList RPAREN SEMICOLON{ printf("HERE\n"); $$ = createFunctionCallNode(createIDNode($1), $3); };


ParamList: { $$ = NULL; }
	| ParamTail { $$ = createParamListNode($1); };


ParamTail: Param { $$ = createParamTailNode($1, NULL); }
	| Param COMMA ParamTail { $$ = createParamTailNode($1, $3); };


Param: Type ID { $$ = createParamNode($1, createIDNode($2) ); }
    | Type ID LBRACKET RBRACKET { $$ = createParamNode($1, createIDNode($2) ); }
    | Type ID LBRACKET NUMBER RBRACKET { $$ = createParamNode($1, createIDNode($2) ); };


ArgList: { $$ = NULL; }
       | ArgTail { $$ = createArgListNode($1); };


ArgTail: Expr { $$ = createArgTailNode($1, NULL); } 
       | Expr COMMA ArgTail { $$ = createArgTailNode($1, $3); };


Block: StmtList RETURN Expr SEMICOLON { $$ = createBlockNode($1); $$ = createReturnNode($3); }
     | StmtList { $$ = createBlockNode($1); };



Stmt: Declaration { $$ = createStmtNode($1); } 
	| Assignment { $$ = createStmtNode($1); }
	| Print { $$ = createStmtNode($1); }
	| FunctionCall { $$ = createStmtNode($1); };


Declaration: Type ID SEMICOLON { $$ = createDeclarationNode($1, createIDNode($2)); }
	| Type ID LBRACKET Expr RBRACKET SEMICOLON { $$ = createDeclarationNode($1, createIDNode($2)); };


Type: INT { printf("HERE\n"); $$ = createTypeNode($1); }
    | FLOAT { $$ = createTypeNode($1); }
	| BOOL { $$ = createTypeNode($1); }
	| VOID { $$ = createTypeNode($1); };


Assignment: ID ASSIGN Expr SEMICOLON { $$ = createAssignmentNode(createIDNode($1), $3); }
	| ID ASSIGN FunctionCall { $$ = createAssignmentNode(createIDNode($1), $3); }
	| ID LBRACKET Expr RBRACKET ASSIGN Expr SEMICOLON { $$ = createAssignmentNode(createIDNode($1), $3); }
	| ID LBRACKET Expr RBRACKET ASSIGN FunctionCall { $$ = createAssignmentNode(createIDNode($1), $3); };


Print: PRINT LPAREN Expr RPAREN SEMICOLON { $$ = createPrintNode($3); };


Expr: Expr PLUS Term { $$ = createExprNode(strdup(&($2)), $1, $3); }
	| Expr MINUS Term { $$ = createExprNode(strdup(&($2)), $1, $3); }
	| Term { $$ = $1; };


Term: Term MULT Factor { $$ = createTermNode(strdup(&($2)), $1, $3); }
	| Term DIV Factor { $$ = createTermNode(strdup(&($2)), $1, $3); }
	| Factor { $$ = $1; };


Factor: LPAREN Expr RPAREN { $$ = createFactorNode($2); }
	| ID { $$ = createIDNode($1); }
	| ID LBRACKET Expr RBRACKET { $$ = createIDNode($1); }
	| NUMBER { $$ = createNumberNode($1); };


%%



int main() {
    yyin = fopen("testProg.cmm", "r");

	yydebug = 0;

	printf("\nPARSER:\nStarting to parse\n\n");
    int result = yyparse();

    if (result == 0) {

		printf("\nPARSER:\nParsing successful!\n");

		printAST(root, 0);

    }

    fclose(yyin);
    return 0;
}

void yyerror(const char* s) {
    fprintf(stderr, "\nPARSER ERROR:\n%s at line %d, column %d\n", s, lines, chars);
}

