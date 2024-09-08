%option noyywrap

%{
#include <stdio.h>
#include <string.h>

#define YY_DECL int yylex()

enum yytokentype {
    INT = 258,
    FLOAT = 259,
    PRINT = 260,
    IF = 261,
    ELSE = 262,
    WHILE = 263,
    RETURN = 264,
    ID = 265,
    NUM = 266,
    PLUS = 267,
    MINUS = 268,
    MULT = 269,
    DIV = 270,
    ASSIGN = 271,
    OPEN_PAREN = 272,
    CLOSE_PAREN = 273,
    OPEN_BRACE = 274,
    CLOSE_BRACE = 275,
    SEMICOLON = 276,
    COMMA = 277
};

int words = 0;
int chars = 0;
int lines = 1;

%}

letter      [a-zA-Z]
digit       [0-9]
ID          {letter}({letter}|{digit})*
delim       [ \t\n]
NUMBER      {digit}+(\.{digit}+)?(E[+\-]?{digit}+)?
ws          {delim}+

%%
"/*"        { 
                int c;
                while((c = input()) != 0) {
                    if(c == '*') {
                        if((c = input()) == '/')
                            break;
                        else
                            unput(c);
                    }
                }
            }

"//".*       { /* Ignore single-line comments */ }

"int"       { words++; chars += strlen(yytext); 
              printf("%s : TYPE\n", yytext); 
              return INT; }

"float"     { words++; chars += strlen(yytext); 
              printf("%s : TYPE\n", yytext); 
              return FLOAT; }

"print"      { words++; chars += strlen(yytext); 
              printf("%s : KEYWORD\n", yytext); 
              return PRINT; }

"if"        { words++; chars += strlen(yytext); 
              printf("%s : KEYWORD\n", yytext); 
              return IF; }
              
"else"      { words++; chars += strlen(yytext); 
              printf("%s : KEYWORD\n", yytext); 
              return ELSE; }

"while"     { words++; chars += strlen(yytext); 
              printf("%s : KEYWORD\n", yytext); 
              return WHILE; }

"return"    { words++; chars += strlen(yytext); 
              printf("%s : KEYWORD\n", yytext); 
              return RETURN; }

{ID}        { words++; chars += strlen(yytext); 
              printf("%s : IDENTIFIER\n", yytext); 
              return ID; }

{NUMBER}    { words++; chars += strlen(yytext); 
              printf("%s : NUMBER\n", yytext); 
              return NUM; }

"+"         { chars++; 
              printf("%s : PLUS\n", yytext); 
              return PLUS; }

"-"         { chars++; 
              printf("%s : MINUS\n", yytext); 
              return MINUS; }

"*"         { chars++; 
              printf("%s : MULT\n", yytext); 
              return MULT; }

"/"         { chars++; 
              printf("%s : DIV\n", yytext); 
              return DIV; }

"="         { chars++; 
              printf("%s : ASSIGN\n", yytext); 
              return ASSIGN; }

"("         { chars++;
              printf("%s : OPEN_PAREN\n", yytext);
              return OPEN_PAREN; }
            
")"         { chars++;
              printf("%s : CLOSE_PAREN\n", yytext);
              return CLOSE_PAREN; }

"{"         { chars++;
              printf("%s : OPEN_BRACE\n", yytext);
              return OPEN_BRACE; }  

"}"         { chars++;
              printf("%s : CLOSE_BRACE\n", yytext);
              return CLOSE_BRACE; }

";"         { chars++; 
              printf("%s : SEMICOLON\n", yytext); 
              return SEMICOLON; }

","         { chars++;
              printf("%s : COMMA\n", yytext);
              return COMMA; }           

\n          { lines++; 
              chars = 0; 
              return '\n'; }

{ws}        { chars++; /* Ignore whitespace */ }

%%

int main(int argc, char** argv)
{
    #ifdef YYDEBUG
        yydebug = 1;
    #endif

    printf("Compiler started. \n\n");

    if (argc > 1){
        if(!(yyin = fopen(argv[1], "r"))) {
            perror(argv[1]);
            return(1);
        }
    }
    
    while(yylex()) {

    }
}
