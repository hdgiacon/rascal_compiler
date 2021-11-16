#LEXER = lexer/flex.lex
#PARSER = parser/bison.y
#AST_CPP = ast/ast.cpp
#AST_H = ast/ast.h

rascal: rascal.c bison.tab.c lex.yy.c ast.c util.c

bison.tab.c bison.tab.h: bison.y
	bison -Werror -tvd -r all bison.y

lex.yy.c: flex.lex bison.tab.h
	flex -o lex.yy.c flex.lex


.PHONY: clean
clean: 
	rm rascal lex.yy.c bison.tab.c bison.tab.h bison.output
