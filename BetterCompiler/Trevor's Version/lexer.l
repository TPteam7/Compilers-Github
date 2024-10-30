%option noyywrap

%{
#include <stdio.h>
#include <string.h>
#include "parser.tab.h"

#define YY_DECL int yylex()

int words = 0;
int chars = 0;
int lines = 1;

%}

TRUE        [Tt][Rr][Uu][Ee]
FALSE       [Ff][Aa][Ll][Ss][Ee]
letter      [a-zA-Z]
digit       [0-9]
ID          {letter}({letter}|{digit})*
NUMBER      {digit}+(\.{digit}+)?(E[+\-]?{digit}+)?

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
              yylval.string = strdup(yytext); 
              return INT; }

"float"     { words++; chars += strlen(yytext); 
              printf("%s : TYPE\n", yytext); 
              yylval.string = strdup(yytext); 
              return FLOAT; }

"bool"      { words++; chars += strlen(yytext); 
              printf("%s : TYPE\n", yytext); 
              yylval.string = strdup(yytext); 
              return BOOL; }

"void"      { words++; chars += strlen(yytext); 
              printf("%s : TYPE\n", yytext); 
              yylval.string = strdup(yytext); 
              return VOID; }

{TRUE}      { words++; chars += strlen(yytext); 
              printf("%s : BOOL LITERAL\n", yytext); 
              yylval.string = strdup(yytext); 
              return TRUE; }

{FALSE}     { words++; chars += strlen(yytext); 
              printf("%s : BOOL LITERAL\n", yytext); 
              yylval.string = strdup(yytext); 
              return FALSE; }  

"print"     { words++; chars += strlen(yytext); 
              printf("%s : KEYWORD\n", yytext); 
              yylval.string = strdup(yytext); 
              return PRINT; }

"if"        { words++; chars += strlen(yytext); 
              printf("%s : KEYWORD\n", yytext); 
              yylval.string = strdup(yytext); 
              return IF; }
              
"else"      { words++; chars += strlen(yytext); 
              printf("%s : KEYWORD\n", yytext); 
              yylval.string = strdup(yytext); 
              return ELSE; }

"while"     { words++; chars += strlen(yytext); 
              printf("%s : KEYWORD\n", yytext); 
              yylval.string = strdup(yytext); 
              return WHILE; }

"return"    { words++; chars += strlen(yytext); 
              printf("%s : KEYWORD\n", yytext); 
              yylval.string = strdup(yytext); 
              return RETURN; }

{ID}        { words++; chars += strlen(yytext); 
              printf("%s : IDENTIFIER\n", yytext); 
              yylval.string = strdup(yytext); 
              return ID; }

{NUMBER}    { words++; chars += strlen(yytext); 
              printf("%s : NUMBER\n", yytext);
              yylval.number = atoi(strdup(yytext));  
              return NUMBER; }

"+"         { chars++; 
              printf("%s : PLUS\n", yytext); 
              yylval.op = yytext[0]; 
              return PLUS; }

"-"         { chars++; 
              printf("%s : MINUS\n", yytext); 
              yylval.op = yytext[0];
              return MINUS; }

"*"         { chars++; 
              printf("%s : MULT\n", yytext); 
              yylval.op = yytext[0]; 
              return MULT; }

"/"         { chars++; 
              printf("%s : DIV\n", yytext); 
              yylval.op = yytext[0];
              return DIV; }

"="         { chars++; 
              printf("%s : ASSIGN\n", yytext); 
              yylval.op = yytext[0]; 
              return ASSIGN; }

"("         { chars++;
              printf("%s : LPAREN\n", yytext);
              yylval.character = yytext[0]; 
              return LPAREN; }
            
")"         { chars++;
              printf("%s : RPAREN\n", yytext);
              yylval.character = yytext[0];
              return RPAREN; }

"{"         { chars++;
              printf("%s : LBRACE\n", yytext);
              yylval.character = yytext[0];
              return LBRACE; }  

"}"         { chars++;
              printf("%s : RBRACE\n", yytext);
              yylval.character = yytext[0];
              return RBRACE; }

"["         { chars++;
              printf("%s : LBRACKET\n", yytext);
              yylval.character = yytext[0];
              return LBRACKET; }

"]"         { chars++;
              printf("%s : RBRACKET\n", yytext);
              yylval.character = yytext[0];
              return RBRACKET; }

";"         { chars++; 
              printf("%s : SEMICOLON\n", yytext);
              yylval.character = yytext[0];
              return SEMICOLON; }

","         { chars++;
              printf("%s : COMMA\n", yytext);
              yylval.character = yytext[0];
              return COMMA; }           


\r\n    { lines++; chars = 0; }
\n		{lines++; chars=0;}
[ \t]	{chars++;}
.		{chars++;
         printf("%s : Unrecognized symbol at line %d char %d\n", yytext,lines,chars);
		}

%%