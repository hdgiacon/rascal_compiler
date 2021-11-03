LEXER = lexer/flex.lex
PARSER = parser/bison.y
AST_CPP = ast/ast.cpp

rascal: rascal.cpp bison.tab.c lexico.yy.c $(AST_CPP)

bison.tab.c bison.tab.h: $(PARSER)
	bison -Werror -tvd -r all $(PARSER)

lex.yy.c: $(LEXER) sintatico.tab.h
	flex -o lex.yy.c $(LEXER)

.PHONY: clean
clean: 
	rm rascal *.out lex.yy.c bison.tab.c bison.tab.h bison.output
