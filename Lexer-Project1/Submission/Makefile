# The default target is to build the lexer
all: lexer

# Build the lexer executable from the Flex file
lexer: lexer.l
	flex lexer.l
	gcc lex.yy.c -o lexer -lfl

# Clean up the generated files
clean:
	rm -f lexer lex.yy.c
	ls -l

# Run the lexer (optional target for running it on a specific file)
run: lexer
	./lexer testProg.cmm
