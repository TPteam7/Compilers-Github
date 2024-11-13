all: parser

# Generate the parser files (parser.tab.c and parser.tab.h) from Bison file
parser.tab.c parser.tab.h: parser.y
	bison -t -v -d parser.y

# Generate the lexer file (lex.yy.c) from Flex file, depends on the parser files
lex.yy.c: lexer.l parser.tab.h
	flex lexer.l

# Compile and link all necessary files, including AST.c
# remove for now AST.c semantic.c symbolTable.c optimizer.c codeGenerator.c TAC.c
#	AST.c semantic.c symbolTable.c optimizer.c codeGenerator.c TAC.c
parser: lex.yy.c parser.tab.c  parser.tab.h 
	gcc -o lex.yy.c  parser parser.tab.c 
	./parser testProg.cmm

# Clean up generated files
#	symbolTable.o optimizer.o codeGenerator.o optimizer.o semantic.o codeGenerator.o TAC.o
clean:
	rm -f parser parser.tab.c lex.yy.c parser.tab.h parser.output lex.yy.o parser.tab.o
	ls -l
