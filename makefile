LEXER = lexer/flex.lex
PARSER = parser/bison.y
AST_CPP = ast/ast.cpp
AST_H = ast/ast.h

rascal: rascal.cpp bison.tab.c lex.yy.c ast.cpp

bison.tab.c bison.tab.h: bison.y
	bison -Werror -tvd -r all bison.y

lex.yy.c: flex.lex bison.tab.h
	flex -o lex.yy.c flex.lex

#ast: ast/ast.cpp ast/ast.h
#	g++ ast.cpp

.PHONY: clean
clean: 
	rm rascal *.out lex.yy.c bison.tab.c bison.tab.h bison.output
