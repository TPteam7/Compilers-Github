all: parser

# Generate the parser files (parser.tab.c and parser.tab.h) from Bison file
parser.tab.c parser.tab.h: parser.y
	bison -t -v -d parser.y

# Generate the lexer file (lex.yy.c) from Flex file, depends on the parser files
lex.yy.c: lexer.l parser.tab.h
	flex lexer.l

# Compile and link all necessary files, including AST.c
# remove for now semantic.c codeGenerator.c
#  semantic.c codeGenerator.c 
parser: lex.yy.c parser.tab.c parser.tab.h AST.c symbolTable.c TAC.c optimizer.c
	gcc -o parser lex.yy.c parser.tab.c AST.c symbolTable.c TAC.c optimizer.c
	./parser testProg.cmm

# Clean up generated files
# codeGenerator.o
clean:
	rm -f parser parser.tab.c lex.yy.c parser.tab.h parser.output lex.yy.o parser.tab.o semantic.o symbolTable.o TAC.o optimizer.o
	ls -l