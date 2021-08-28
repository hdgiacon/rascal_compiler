LEXER = lexer/flex.lex
PARSER = parser/bison.y

a.out: lex.yy.c
	g++ lex.yy.c

lex.yy.c: $(LEXER)
	lex $(LEXER)

.PHONY: clean
clean: 
	rm *.out lex.yy.c
