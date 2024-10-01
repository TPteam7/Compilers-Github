all: parser

# Generate the parser files (parser.tab.c and parser.tab.h) from Bison file
parser.tab.c parser.tab.h: parser.y
	bison -t -v -d parser.y

# Generate the lexer file (lex.yy.c) from Flex file, depends on the parser files
lex.yy.c: lexer.l parser.tab.h
	flex lexer.l

# Compile and link all necessary files, including AST.c
parser: lex.yy.c parser.tab.c symbolTable.c AST.c semantic.c parser.tab.h optimizer.c
	gcc -o parser parser.tab.c symbolTable.c semantic.c lex.yy.c AST.c optimizer.c
	./parser testProg.cmm

# Clean up generated files
clean:
	rm -f parser parser.tab.c lex.yy.c parser.tab.h parser.output symbolTable.o semantic.o lex.yy.o parser.tab.o
	ls -l
