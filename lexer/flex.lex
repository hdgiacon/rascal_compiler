%{
    #include <iostream>
    using namespace std;

    #include "bison.tab.h"

    int numOfLines = 1;

%}

%option noyywrap

ID [a-zA-Z][a-zA-Z_0-9]*
NUM [0-9]+
COMENTARIO_BLOCO "{"[^\}]*"}"
COMENTARIO_LINHA  "//"[^"\n"]*"\n"
NEWLINE [\n]
SPACE [\t ]+

%%

{COMENTARIO_BLOCO} { cout << "comentario bloco\n";}
{COMENTARIO_LINHA} { cout << "comentario linha\n";}

{NEWLINE} {
    cout << numOfLines + "\n";
    numOfLines++;
}

{SPACE} {}

"program"   return TK_PROGRAM; 
"var"       return TK_VAR; 
"procedure" return TK_PROCEDURE;
"function"  return TK_FUNCTION; 
"begin"     return TK_BEGIN;
"end"       return TK_END;
"false"     return TK_FALSE;
"true"      return TK_TRUE;
"if"        return TK_IF;
"then"      return TK_THEN;
"else"      return TK_ELSE;
"while"     return TK_WHILE;
"do"        return TK_DO;
"read"      return TK_READ;
"write"     return TK_WRITE;
"and"       return TK_AND;
"or"        return TK_OR;
"not"       return TK_NOT;
"div"       return TK_DIV;

"("         return TK_LPAREN;
")"         return TK_RPAREN;
"."         return TK_PONTO;
","         return TK_VIRGULA;
";"         return TK_PONTVIRG;
"+"         return TK_MAIS;
"-"         return TK_MENOS;
"*"         return TK_MULT;
"="         return TK_IGUAL;
"<>"        return TK_DIFERENTE;
">"         return TK_MAIOR;
"<"         return TK_MENOR;
">="        return TK_MAIORIGUAL;
"<="        return TK_MENORIGUAL;
":"         return TK_DOISPONTOS;
":="        return TK_ATRIBUICAO;

{ID} {
    yylval.str = std::string(yytext); 
    return TK_ID;
}

{NUM} {
    yylval.ival = std::stoi(yytext);
    return TK_NUM;
}

.     {
    cout << std::string("Error: Token '") + yytext + std::string("' unkwown.\n");
}
%%