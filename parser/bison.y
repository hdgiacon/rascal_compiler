%{

#include <iostream>
using namespace std;

#include "util/util.h"

int yylex(void)

void yyerror(cont char *s){
	cout << "Erro sintatico: "
}

%}

%union {
   String str;
   int num;
   A_Programa programa;
   A_Bloco bloco;
   A_LstDecSub secDecVar;
   A_DecVar decVar;
   A_LstDecVar secDecSub;
   A_ListaId listaId;
   A_DecProc decProc;
   A_DecParam decParam;
   A_DecParamList decParamList;
   A_CmdComp cmdComp;
   A_Cmd cmd;
   A_CmdList cmdList;
   A_Atrib atrib;
   A_ChamProc chamProc;
   A_Cond cond;
   A_Loop loop;
   A_IO IO;
   A_ListExp listExp;
   A_Exp exp;
   A_ListTermo listTermo;
   A_Termo termo;
   A_Fator fator;
   A_Var var;
   A_ChamFunc chamFunc;
}

%token TK_PROGRAM
%token TK_VAR
%token TK_PROCEDURE
%token TK_FUNCTION
%token TK_BEGIN
%token TK_END
%token TK_FALSE
%token TK_TRUE
%token TK_IF
%token TK_THEN
%token TK_ELSE
%token TK_WHILE
%token TK_DO
%token TK_READ
%token TK_WRITE
%token TK_AND
%token TK_OR
%token TK_NOT
%token TK_DIV

%token TK_LPAREN
%token TK_RPAREN
%token TK_ATRIBUICAO
%token TK_MAIS TK_MENOS TK_MULT
%token TK_IGUAL TK_DIFERENTE TK_MAIOR TK_MENOR TK_MAIORIGUAL TK_MENORIGUAL
%token TK_VIRGULA TK_PONTVIRG TK_DOISPONTOS TK_PONTO

%token <str> TK_IDENT

%type <programa> programa
%type <bloco> bloco
%type <secDecVar> secao_declaracao_variaveis secao_declaracao_variaveis_rec
%type <decVar> declaracao_variaveis
%type <str> tipo
%type <secDecSub> secao_declaracao_subrotinas secao_declaracao_subrotinas_rec secao_declaracao_subrotinas_op
%type <listaId> lista_identificadores lista_identificadores_rec
%type <decProc> declaracao_procedimento declaracao_funcao
%type <decParam> declaracao_parametros
%type <decParamList> parametros_formais declaracao_parametros_rec
%type <cmdComp> comando_composto
%type <cmd> comando
%type <cmdList> comando_rec
%type <atrib> atribuicao
%type <chamProc> chamada_procedimento chamada_procedimento_op
%type <cond> condicional elsee
%type <loop> repeticao
%type <IO> leitura escrita
%type <listExp> lista_expressoes expressao_simples_rec
%type <exp> expressao expressao_op expressao_simples
%type <listTermo> termo_rec
%type <termo> termo
%type <fator> fator
%type <var> variavel
%type <chamFunc> chamada_funcao chamada_funcao_op


%define parse.error verbose
%define parse.lac full


%start programa

%%

programa:	TK_PROGRAM TK_IDENT TK_PONTVIRG bloco TK_PONTO {}
;

bloco:	secao_declaracao_variaveis secao_declaracao_subrotinas comando_composto {} 
;


secao_declaracao_variaveis:		TK_VAR declaracao_variaveis TK_PONTVIRG secao_declaracao_variaveis_rec	{}
							|	/*vazio*/	{}
;

secao_declaracao_variaveis_rec:		declaracao_variaveis TK_PONTVIRG secao_declaracao_variaveis_rec	{}
								|	declaracao_variaveis	{}

declaracao_variaveis:	lista_identificadores TK_DOISPONTOS tipo	{}
;


lista_identificadores:	identificador lista_identificadores_rec		{}
;

lista_identificadores_rec:	TK_VIRGULA identificador lista_identificadores_rec	{}
						|	TK_VIRGULA identificador	{}	/* pode isso? */
;

tipo:	identificador
;


secao_declaracao_subrotinas:	secao_declaracao_subrotinas_rec		{}
							|	/* vazio */		{}

secao_declaracao_subrotinas_rec:	secao_declaracao_subrotinas_op TK_PONTVIRG secao_declaracao_subrotinas_rec	{}
								|	secao_declaracao_subrotinas_op TK_PONTVIRG	{}
;

secao_declaracao_subrotinas_op:		declaracao_procedimento	{}
								|	declaracao_funcao		{}
;


declaracao_procedimento:	TK_PROCEDURE identificador parametros_formais TK_PONTVIRG bloco	{}
;

declaracao_funcao:	TK_FUNCTION identificador parametros_formais TK_DOISPONTOS tipo TK_PONTVIRG bloco	{}
;


parametros_formais:	TK_LPAREN declaracao_parametros_rec TK_RPAREN	{}
				|	/* vazio */		{}
;

declaracao_parametros_rec: 	declaracao_parametros TK_PONTVIRG declaracao_parametros_rec	{}
						|	declaracao_parametros	{}
;

declaracao_parametros:	TK_VAR lista_identificadores TK_DOISPONTOS tipo	{}
					|	lista_identificadores TK_DOISPONTOS tipo		{}
;


comando_composto:	TK_BEGIN comando_rec TK_PONTVIRG TK_END	{}
;

comando_rec:	comando TK_PONTVIRG comando_rec	{}
			|	comando							{}
;

comando:	atribuicao				{}
		|   chamada_procedimento	{}
		|   condicional				{}
		|   repeticao				{}
		|   leitura					{}
		|   escrita					{}
		|   comando_composto		{}
;


atribuicao:	TK_IDENT TK_ATRIBUICAO expressao	{}
;

chamada_procedimento:	identificador chamada_procedimento_op	{}
;

chamada_procedimento_op:	TK_LPAREN lista_expressoes TK_RPAREN	{}
					|       /* vazio */		{}
;


condicional:	TK_IF expressao TK_THEN comando elsee	{}
;

elsee:					{} 
	|	TK_ELSE comando	{}	/* comando esta acima desta regra, ta certo? */
;

repeticao:	TK_WHILE expressao TK_DO comando	{}
;

leitura:	TK_READ TK_LPAREN lista_identificadores TK_RPAREN	{}
;

escrita:	TK_WRITE TK_LPAREN lista_expressoes TK_RPAREN	{}
;


lista_expressoes:	expressao TK_VIRGULA lista_expressoes	{}
				|	expressao		{}
;

expressao:	expressao_simples expressao_op	{}
;

expressao_op:   relacao				{}
			|	expressao_simples	{}
;

relacao:	TK_IGUAL
		|   TK_DIFERENTE
		|   TK_MENOR
		|   TK_MENORIGUAL
		|   TK_MAIOR
		|   TK_MAIORIGUAL
;      

expressao_simples:	termo expressao_simples_rec		{}
;

expressao_simples_rec:	or_op termo expressao_simples_rec	{}
					|	or_op termo		{}
;

or_op:		TK_MAIS
		|   TK_MENOS
		|   TK_OR
;


termo:		fator termo_rec		{}
;

termo_rec:	and_op fator termo_rec	{}
		|	and_op fator			{}
;

and_op:		TK_MULT
		|   TK_DIV
		|   TK_AND
;

fator:      variavel						{}
		|   logico							{}
		|   chamada_funcao					{}
		|   TK_LPAREN expressao TK_RPAREN	{}
		|   TK_NOT fator					{}
		|   TK_MENOS fator					{}
;


variavel:   identificador	{}
;

logico:     TK_FALSE
		|   TK_TRUE
;

chamada_funcao: 	identificador chamada_funcao_op		{}
;

chamada_funcao_op:	TK_LPAREN lista_expressoes TK_RPAREN	{}
				|	/* vazio */		{}
;

identificador: 		TK_IDENT
;

%%