%{
    #include <iostream>
    using namespace std;

%}

%x COMENTARIO
%x COMENTARIO_BLOCO

%%

" " {
    cout << "espaco\n";
    continue;
}

\n {
    continue;
}

"//" {
    BEGIN(COMENTARIO);
}
<COMENTARIO> {
    \n {
        BEGIN(INITIAL);
    }
}

"{" {
    BEGIN (COMENTARIO_BLOCO);
}

<COMENTARIO_BLOCO> {
    "}" {
        BEGIN(INITIAL)
    }

    <<EOF>> {

    }

    . {

    }
}

"program" {
    cout << "program\n";
}

"var" {
    cout << "var\n";
}

"procedure" {
    cout << "procedure\n";
}

"function" {
    cout << "function\n";
}

"begin" {
    cout << "begin\n";
}

"end" {
    cout << "end\n";
}

"false" {
    cout << "false\n";
}

"true" {
    cout << "true\n";
}

"if" {
    cout << "if\n";
}

"then" {
    cout << "then\n";
}

"else" {
    cout << "else\n";
}

"while" {
    cout << "while\n";
}

"do" {
    cout << "do\n";
}

"read" {
    cout << "read\n";
}

"write" {
    cout << "write\n";
}

"and" {
    cout << "and\n";
}

"or" {
    cout << "or\n";
}

"not" {
    cout << "not\n";
}

"div" {
    cout << "div\n";
}

"(" {
    cout << "abre paren\n";
}

")" {
    cout << "fecha paren\n";
}

"." {
    cout << "ponto\n";
}

"," {
    cout << "virgula\n";
}

";" {
    cout << "pontoVirgula\n";
}

"+" {
    cout << "mais\n";
}

"-" {
    cout << "menos\n";
}

"*" {
    cout << "vezes\n";
}

"=" {
    cout << "igual\n";
}

"<>" {
    cout << "diferente\n";
}

">" {
    cout << "maior\n";
}

"<" {
    cout << "menor\n";
}

">=" {
    cout << "maiorIgual\n";
}

"<=" {
    cout << "menorIgual\n";
}

":=" {
    cout << "atribuicao\n";
}

[a-zA-Z][a-zA-Z_0-9]* {
    cout << yytext + std::string(" ser um ID\n");
}

[0-9]+ {
    //yylval.ival = atoi(yytext);
    cout << "parabens isso ser um numero\n";
}

.     {}
%%
 
int yywrap(){return 0;}

int main(){
 
 
    yylex();
    return 0;
}