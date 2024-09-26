all: parser

parser.tab.c parser.tab.h:	parser.y
	bison -t -v -d parser.y

lex.yy.c: lexer.l parser.tab.h
	flex lexer.l

lexer: lex.yy.c parser.tab.c parser.tab.h
	gcc -o lexer lex.yy.c parser.tab.c

parser: lex.yy.c parser.tab.c AST.c symbolTable.c parser.tab.h
	gcc -o parser parser.tab.c AST.c symbolTable.c lex.yy.c
	./parser testProg.cmm

clean:
	rm -f parser parser.tab.c lex.yy.c parser.tab.h parser.output AST.o symbolTable.o lex.yy.o parser.tab.o
	ls -l
