%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "AST.h"
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

//ASTNode* root = NULL;
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
%start Program

%%

Program: StmtList {  };


StmtList:  {  }
	| Stmt StmtList {  }
	| FunctionDefinition StmtList {  };x


FunctionDefinition: Type ID LPAREN ParamList RPAREN LBRACE Block RBRACE { };


FunctionCall: ID LPAREN ArgList RPAREN { };


ParamList: {  }
	| ParamTail {  };


ParamTail: Param {  }
	| Param COMMA ParamTail {  };


Param: Type ID { }
    | Type ID LBRACKET RBRACKET { }
    | Type ID LBRACKET NUMBER RBRACKET { };


ArgList:
       | ArgTail { };


ArgTail: Expr { } 
       | Expr COMMA ArgTail { };


Block: StmtList RETURN Expr SEMICOLON { }
    | StmtList { };


Stmt: Declaration {  } 
	| Assignment {  }
	| Print {  }
	| FunctionCall {  };


Declaration: Type ID SEMICOLON {  }
	| Type ID LBRACKET Expr RBRACKET SEMICOLON {  };


Type: INT {  }
    | FLOAT {  }
	| BOOL {  }
	| VOID {  };


Assignment: ID ASSIGN Expr SEMICOLON {  }
	| ID ASSIGN FunctionCall SEMICOLON {  }
	| ID LBRACKET Expr RBRACKET ASSIGN Expr SEMICOLON {  }
	| ID LBRACKET Expr RBRACKET ASSIGN FunctionCall SEMICOLON {  };


Print: PRINT LPAREN Expr RPAREN SEMICOLON {  };


Expr: Expr PLUS Term {  }
	| Expr MINUS Term {  }
	| Term {  };


Term: Term MULT Factor {  }
	| Term DIV Factor {  }
	| Factor {  };


Factor: LPAREN Expr RPAREN {  }
	| ID {  }
	| ID LBRACKET Expr RBRACKET { }
	| NUMBER {  };


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
    fprintf(stderr, "\nPARSER ERROR:\n%s at line %d, column %d\n", s, lines, chars);
}

