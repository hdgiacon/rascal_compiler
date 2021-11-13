%code requires{
	#include "util.h"
	#include "ast.h"
}

%{

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
//#include "util/util.h"
#include "ast.h"
#include "util.h"

int yylex(void)

void yyerror(cont char *s){
	fprintf(stderr, "Erro sintatico: %s", s);
}

extern A_Programa absyn_root;

%}

%union {
   String str;
   int num;
   A_Programa programa;
   A_Bloco bloco;
   A_BlocoSub bloco_sub;
   A_LstDecSub secDecSub;
   A_DecVar decVar;
   A_LstDecVar secDecVar;
   A_ListaId listaId;
   A_DecProc decProc;
   A_DecParam decParam;
   A_DecParamList decParamList;
   A_CmdComp cmdComp;
   A_Cmd cmd;
   A_Atrib atrib;
   A_ChamProc chamProc;
   A_Cond cond;
   A_Loop loop;
   A_IO IO;
   A_ListExp listExp;
   A_Exp exp;
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

%token <num> TK_NUM 
%token <str> TK_IDENT

%precedence TK_THEN
%precedence TK_ELSE

%type <programa> programa
%type <bloco> bloco 
%type <bloco_sub> bloco_subrotinas
%type <secDecVar> secao_declaracao_variaveis 
%type <decVar> declaracao_variaveis
%type <str> tipo identificador
%type <secDecSub> secao_declaracao_subrotinas  secao_declaracao_subrotinas_op
%type <listaId> lista_identificadores
%type <decProc> declaracao_procedimento declaracao_funcao
%type <decParam> declaracao_parametros declaracao_parametros_op
%type <decParamList> parametros_formais 
%type <cmdComp> comando_composto comando_rec
%type <cmd> comando
%type <atrib> atribuicao
%type <chamProc> chamada_procedimento 
%type <cond> condicional
%type <loop> repeticao
%type <IO> leitura escrita
%type <listExp> lista_expressoes 
%type <exp> expressao expressao_simples
%type <termo> termo
%type <fator> fator
%type <var> variavel
%type <chamFunc> chamada_funcao 

%type <num> relacao or_op and_op logico


%define parse.error verbose
%define parse.lac full


%start programa

%%

programa:	TK_PROGRAM TK_IDENT TK_PONTVIRG bloco TK_PONTO { absyn_root = A_programa($2, $4); }
;

bloco:	secao_declaracao_variaveis secao_declaracao_subrotinas comando_composto {$$ = A_Bloco($1, $2, $3); } 
;

secao_declaracao_variaveis:		secao_declaracao_variaveis declaracao_variaveis TK_PONTVIRG		{ $$ = $2; }
							|	TK_VAR declaracao_variaveis										{ $$ = NULL; }
;

declaracao_variaveis:	lista_identificadores TK_DOISPONTOS tipo	{ $$ = concatLstDecVar($1, $2); }
;


lista_identificadores:	identificador 									{ $$ = A_listaId($3, $1); }		//$$ = constr
					|	identificador TK_VIRGULA lista_identificadores	{ $$ = A_listaId($1, NULL); }	//$$ = $3.push($1)
;


tipo:	identificador	{ $$ = $1; }
;

secao_declaracao_subrotinas:	secao_declaracao_subrotinas_op TK_PONTVIRG secao_declaracao_subrotinas	{}
							|	secao_declaracao_subrotinas_op TK_PONTVIRG	{}
;

secao_declaracao_subrotinas_op:		declaracao_procedimento	{}
								|	declaracao_funcao		{}
;

declaracao_procedimento:	TK_PROCEDURE identificador TK_LPAREN parametros_formais TK_RPAREN TK_PONTVIRG bloco_subrotinas	{}
;

declaracao_funcao:	TK_FUNCTION identificador TK_LPAREN parametros_formais TK_RPAREN TK_DOISPONTOS tipo TK_PONTVIRG bloco_subrotinas	{}
;

bloco_subrotinas:	secao_declaracao_variaveis comando_composto {}
;


parametros_formais:	parametros_formais declaracao_parametros	{}
				|	declaracao_parametros TK_PONTVIRG			{}
;

declaracao_parametros:	TK_VAR declaracao_parametros_op	{}
					|	declaracao_parametros_op		{}
;

declaracao_parametros_op: lista_identificadores TK_DOISPONTOS tipo {}
;


comando_composto:	TK_BEGIN comando_rec TK_END	{}
;

comando_rec:	comando TK_PONTVIRG comando_rec	{}
			|	comando	TK_PONTVIRG				{}
;

//tem que arrumar o construtor de comando
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

chamada_procedimento:	identificador TK_LPAREN lista_expressoes	TK_RPAREN	{}
				|		identificador TK_LPAREN TK_RPAREN						{}
;


condicional:	TK_IF expressao TK_THEN comando TK_ELSE comando	{}
			|	TK_IF expressao TK_THEN comando					{}
;

repeticao:	TK_WHILE expressao TK_DO comando	{}
;

leitura:	TK_READ TK_LPAREN lista_identificadores TK_RPAREN	{}
;

escrita:	TK_WRITE TK_LPAREN lista_expressoes TK_RPAREN		{}
;


lista_expressoes:	lista_expressoes TK_VIRGULA expressao	{}
				|	expressao								{}
;


expressao:	expressao_simples							{}
		|	expressao_simples relacao expressao_simples	{}
;


relacao:	TK_IGUAL			{}
		|   TK_DIFERENTE		{}
		|   TK_MENOR			{}
		|   TK_MENORIGUAL		{}
		|   TK_MAIOR			{}
		|   TK_MAIORIGUAL		{}
;      


expressao_simples:	expressao_simples or_op termo	{}
				|	termo							{}
;

or_op:		TK_MAIS					{}
		|   TK_MENOS				{}
		|   TK_OR					{}
;


termo:		fator and_op termo		{}
		|	fator					{}
;

and_op:		TK_MULT					{}
		|   TK_DIV					{}
		|   TK_AND					{}
;

fator:      variavel						{}
		|	TK_NUM							{}	// o que fazer nesse?
		|   logico							{}	// o que fazer nesse?
		|   chamada_funcao					{}	// $$ = A_exp_fator_chamada_funcao($1);
		|   TK_LPAREN expressao TK_RPAREN	{}
		|   TK_NOT fator					{}	// $$ = $2;
		|   TK_MENOS fator					{}	// $$ = $2;
;


variavel:   identificador	{}
;

logico:     TK_FALSE		{}
		|   TK_TRUE			{}
;

chamada_funcao:		identificador TK_LPAREN lista_expressoes TK_RPAREN	{}
;

identificador: 		TK_IDENT
;

%%