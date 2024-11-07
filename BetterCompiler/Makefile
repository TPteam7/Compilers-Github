all: parser

# Generate the parser files (parser.tab.c and parser.tab.h) from Bison file
parser.tab.c parser.tab.h: parser.y
	bison -t -v -d parser.y

# Generate the lexer file (lex.yy.c) from Flex file, depends on the parser files
lex.yy.c: lexer.l parser.tab.h
	flex lexer.l

# Compile and link all necessary files, including AST.c
parser: lex.yy.c parser.tab.c symbolTable.c AST.c semantic.c TAC.c parser.tab.h 
	gcc -o parser parser.tab.c semantic.c symbolTable.c TAC.c lex.yy.c AST.c 
	./parser testProg.cmm

# Clean up generated files
clean:
	rm -f parser parser.tab.c lex.yy.c parser.tab.h parser.output symbolTable.o optimizer.o semantic.o codeGenerator.o TAC.o lex.yy.o parser.tab.o
	ls -l
