LEXER = lexer/flex.lex
PARSER = parser/bison.y

bison.tab.c bison.tab.h: $(PARSER)
	bison -Werror -tvd -r all $(PARSER)

lex.yy.c: $(LEXER) sintatico.tab.h
	flex -o lex.yy.c $(LEXER)

.PHONY: clean
clean: 
	rm *.out lex.yy.c bison.tab.c bison.tab.h bison.output
