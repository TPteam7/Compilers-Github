%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AST.h"
#include "symbolTable.h"
#include "semantic.h"
#include "TAC.h"
#include "optimizer.h"
#include "codeGenerator.h"

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
	char* stringOp;
	char op;
	struct ASTNode* node;
}

%token <string> ID
%token <string> INT FLOAT BOOL VOID TRUE FALSE
%token <string> PRINT IF ELSE ELSE_IF WHILE RETURN
%token <character> SEMICOLON COMMA
%token <character> LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET
%token <op> ASSIGN PLUS MINUS MULT DIV
%token <stringOp> GREATER_THAN LESS_THAN EQUAL_TO GREATER_THAN_EQUAL_TO LESS_THAN_EQUAL_TO AND OR NOT_EQUAL_TO
%token <number> NUMBER

%printer { fprintf(yyoutput, "%s", $$); } ID;

%type <node> Program StmtList Stmt Declaration Type Assignment Print Expr Term Factor
%type <node> FunctionDeclaration FunctionCall ParamList ParamTail Param ArgList ArgTail BlockStmtList BlockStmt Block ReturnStmt
%type <node> DeclarationAssignment IfBlock IfStmt ElseIfStmt ElseStmt Condition ConditionTail SIGN CONJUNCTION
%type <node> WhileStmt
%start Program

%%

Program: StmtList { $$ = createProgramNode($1); root = $$; };


StmtList:  { $$ = NULL; }
	| Stmt StmtList { $$ = createStmtListNode($1, $2); };


Stmt: Declaration { $$ = createStmtNode($1); } 
	| DeclarationAssignment { $$ = createStmtNode($1); } 
	| Assignment { $$ = createStmtNode($1); }
	| Print { $$ = createStmtNode($1); }
	| FunctionCall { $$ = createStmtNode($1); }
	| FunctionDeclaration { $$ = createStmtNode($1); }
	| IfBlock { $$ = createStmtNode($1); }
	| WhileStmt { $$ = createStmtNode($1); };


IfBlock: IfStmt ElseIfStmt ElseStmt { $$ = createIfBlockNode($1, $2, $3); };


IfStmt: IF LPAREN Condition RPAREN LBRACE Block RBRACE { $$ = createIfStmtNode($3, $6); };


ElseIfStmt: { $$ = NULL; }
	| ELSE_IF LPAREN Condition RPAREN LBRACE Block RBRACE ElseIfStmt { $$ = createElseIfStmtNode($3, $6, $8); };


ElseStmt: { $$ = NULL; }
	| ELSE LBRACE Block RBRACE { $$ = createElseStmtNode($3); };


WhileStmt: WHILE LPAREN Condition RPAREN LBRACE Block RBRACE { $$ = createWhileStmtNode($3, $6); };


Condition: Expr SIGN Expr ConditionTail{ $$ = createConditionNode($1, $2, $3, $4); };


ConditionTail: { $$ = NULL; }
	| CONJUNCTION Condition { $$ = createConditionTailNode($1, $2); };


SIGN: GREATER_THAN { $$ = createSignNode($1); }
	| LESS_THAN { $$ = createSignNode($1); }
	| EQUAL_TO { $$ = createSignNode($1); }
	| GREATER_THAN_EQUAL_TO { $$ = createSignNode($1); }
	| LESS_THAN_EQUAL_TO { $$ = createSignNode($1); };
	| NOT_EQUAL_TO { $$ = createSignNode($1); };


CONJUNCTION: AND { $$ = createConjunctionNode($1); }
	| OR { $$ = createConjunctionNode($1); };


FunctionDeclaration: Type ID LPAREN ParamList RPAREN LBRACE Block RBRACE { $$ = createFunctionDeclarationNode($1, createIDNode($2), $4, $7); };


FunctionCall: ID LPAREN ArgList RPAREN SEMICOLON{ printf("HERE\n"); $$ = createFunctionCallNode(createIDNode($1), $3); };


ParamList: { $$ = NULL; }
	| ParamTail { $$ = createParamListNode($1); };


ParamTail: Param { $$ = createParamTailNode($1, NULL); }
	| Param COMMA ParamTail { $$ = createParamTailNode($1, $3); };


Param: Type ID { $$ = createParamNode(createDeclarationNode($1, createIDNode($2))); }
    | Type ID LBRACKET RBRACKET { $$ = createParamNode(createArrayDeclarationNode($1, createIDNode($2), NULL)); };


ArgList: { $$ = NULL; }
       | ArgTail { $$ = createArgListNode($1); };


ArgTail: Expr { $$ = createArgTailNode($1, NULL); } 
       | Expr COMMA ArgTail { $$ = createArgTailNode($1, $3); };


Block: BlockStmtList ReturnStmt { $$ = createBlockNode($1, $2); }
     | BlockStmtList { $$ = createBlockNode($1, NULL); };


BlockStmtList:  { $$ = NULL; }
	| BlockStmt BlockStmtList { $$ = createBlockStmtListNode($1, $2); };


BlockStmt: Declaration { $$ = createBlockStmtNode($1); } 
	| DeclarationAssignment { $$ = createStmtNode($1); } 
	| Assignment { $$ = createBlockStmtNode($1); }
	| Print { $$ = createBlockStmtNode($1); }
	| FunctionCall { $$ = createBlockStmtNode($1); }
	| IfBlock { printf("IF Stmt\n"); };


ReturnStmt: RETURN Expr SEMICOLON { $$ = createReturnNode($2); };


Declaration: Type ID SEMICOLON { $$ = createDeclarationNode($1, createIDNode($2)); }
	| Type ID LBRACKET Expr RBRACKET SEMICOLON { $$ = createArrayDeclarationNode($1, createIDNode($2), $4); };


DeclarationAssignment: Type ID ASSIGN Expr SEMICOLON { $$ = createDeclarationAssignmentNode($1, createIDNode($2), $4);}


Type: INT { printf("HERE\n"); $$ = createTypeNode($1); }
    | FLOAT { $$ = createTypeNode($1); }
	| BOOL { $$ = createTypeNode($1); }
	| VOID { $$ = createTypeNode($1); };


Assignment: ID ASSIGN Expr SEMICOLON { $$ = createAssignmentNode(createIDNode($1), $3); }
	| ID ASSIGN FunctionCall { $$ = createAssignmentNode(createIDNode($1), $3); }
	| ID LBRACKET Expr RBRACKET ASSIGN Expr SEMICOLON { $$ = createArrayAssignmentNode(createIDNode($1), $3, $6); }
	| ID LBRACKET Expr RBRACKET ASSIGN FunctionCall { $$ = createArrayAssignmentNode(createIDNode($1), $3, $6); };


Print: PRINT LPAREN Expr RPAREN SEMICOLON { $$ = createPrintNode($3); };


Expr: Expr PLUS Term { char opStr[2]; snprintf(opStr, sizeof(opStr), "%c", $2);$$ = createExprNode(strdup(opStr), $1, $3); }
	| Expr MINUS Term { char opStr[2]; snprintf(opStr, sizeof(opStr), "%c", $2);$$ = createExprNode(strdup(opStr), $1, $3); }
	| Term { $$ = $1; };


Term: Term MULT Factor { char opStr[2]; snprintf(opStr, sizeof(opStr), "%c", $2);$$ = createExprNode(strdup(opStr), $1, $3); }
	| Term DIV Factor { char opStr[2]; snprintf(opStr, sizeof(opStr), "%c", $2);$$ = createExprNode(strdup(opStr), $1, $3); }
	| Factor { $$ = $1; };


Factor: LPAREN Expr RPAREN { $$ = createFactorNode($2); }
	| ID { $$ = createIDNode($1); }
	| ID LBRACKET Expr RBRACKET { $$ = createArrayAccessNode(createIDNode($1), $3); }
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

	printf("\n=== PARSER ===\n\n");
    int result = yyparse();

    if (result == 0) {

		// Print symbol table for debugging
		if(printSymbolDebug == 1)
		{
			printSymbolTable(symTab);
		}

		printf("\n=== AST ===\n\n");

		printAST(root, 0);
		

		// Semantic analysis
		printf("\n=== SEMANTIC ANALYSIS ===\n\n");
		semanticAnalysis(root, symTab, symTab->topLevelStatements);


		// print symbolTable
		printSymbolTable(symTab);

		printf("\n=== THREE ADDRESS CODE ===\n");
		generateTAC(root);
		printTAC(&tacHead);

		printTACToFile("TAC.ir", &tacHead);

		// Code optimization
		printf("\n\n=== CODE OPTIMIZATION ===\n");

		optimizeTAC(&tacHead);
		printTACToFile("TACOptimized.ir", &tacHead);

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

