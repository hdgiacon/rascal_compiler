a.out: lex.yy.c
	g++ lex.yy.c

lex.yy.c: flex.lex
	lex flex.lex

.PHONY clean
clean: rm a.out lex.yy.c