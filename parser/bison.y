%{

#include <iostream>
using namespace std;

//#include "util/util.h"
#include "../ast/ast.h"

int yylex(void)

void yyerror(cont char *s){
	cout << "Erro sintatico: "
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
%type <decParam> declaracao_parametros
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

programa:	TK_PROGRAM TK_IDENT TK_PONTVIRG bloco TK_PONTO { absyn_root = A_Programa($2, $4); }
;

bloco:	secao_declaracao_variaveis secao_declaracao_subrotinas comando_composto { $$ = A_Bloco($1, $2, $3); } 
;

secao_declaracao_variaveis:		secao_declaracao_variaveis declaracao_variaveis TK_PONTVIRG		{ $$ = A_LstDecVar($2); }
							|	TK_VAR declaracao_variaveis										{ $$ = $2; }
;

declaracao_variaveis:	lista_identificadores TK_DOISPONTOS tipo	{ $$ = A_DecVar($1, $3); }
;


lista_identificadores:	identificador 									{ $$ = A_ListaId($1); }		//$$ = constr
					|	identificador TK_VIRGULA lista_identificadores	{ $$ = $3.push_back($1); }	//$$ = $3.push($1)
;


tipo:	identificador	{ $$ = $1; }
;

secao_declaracao_subrotinas:	secao_declaracao_subrotinas_op TK_PONTVIRG secao_declaracao_subrotinas	{ $$ = $1; }
							|	secao_declaracao_subrotinas_op TK_PONTVIRG	{ $$ = $1; }
;

secao_declaracao_subrotinas_op:		declaracao_procedimento	{ $$ = A_LstDecSub($1); }
								|	declaracao_funcao		{ $$ = A_LstDecSub($1); }
;

declaracao_procedimento:	TK_PROCEDURE identificador TK_LPAREN parametros_formais TK_RPAREN TK_PONTVIRG bloco_subrotinas	{ $$ = A_DecProc($2, $4, $7); }
;

declaracao_funcao:	TK_FUNCTION identificador TK_LPAREN parametros_formais TK_RPAREN TK_DOISPONTOS tipo TK_PONTVIRG bloco_subrotinas	{ $$ = A_DecProc($2, $4, $7, $9); }
;

bloco_subrotinas:	secao_declaracao_variaveis comando_composto { $$ = A_BlocoSub($1, $2); }
;


parametros_formais:	parametros_formais declaracao_parametros	{ $$ = A_DecParamList($2); }
				|	declaracao_parametros TK_PONTVIRG			{ $$ = A_DecParamList($2); }
;

declaracao_parametros:	TK_VAR lista_identificadores TK_DOISPONTOS tipo	{ $$ = A_DecParam($2, $4); }
					|	lista_identificadores TK_DOISPONTOS tipo		{ $$ = A_DecParam($2, $4); }
;


comando_composto:	TK_BEGIN comando_rec TK_END	{ $$ = $2;}
;

comando_rec:	comando TK_PONTVIRG comando_rec	{ $$ = A_CmdComp($1); }
			|	comando	TK_PONTVIRG				{ $$ = A_CmdComp($1); }
;


comando:	atribuicao				{ $$ = $1; }
		|   chamada_procedimento	{ $$ = $1; }
		|   condicional				{ $$ = $1; }
		|   repeticao				{ $$ = $1; }
		|   leitura					{ $$ = $1; }
		|   escrita					{ $$ = $1; }
		|   comando_composto		{ $$ = $1; }
;


atribuicao:	TK_IDENT TK_ATRIBUICAO expressao	{ $$ = A_Atrib($3); }
;

chamada_procedimento:	identificador TK_LPAREN lista_expressoes	TK_RPAREN	{ $$ = A_ChamProc($1, $3); }
				|		identificador TK_LPAREN TK_RPAREN						{ $$ = A_ChamProc($1); }
;


condicional:	TK_IF expressao TK_THEN comando TK_ELSE comando	{ $$ = A_Cond($2, $4, $6); }
			|	TK_IF expressao TK_THEN comando					{ $$ = A_Cond($2, $4); }
;

repeticao:	TK_WHILE expressao TK_DO comando	{ $$ = A_Loop($2, $4); }
;

leitura:	TK_READ TK_LPAREN lista_identificadores TK_RPAREN	{ $$ = A_IO($3); }
;

escrita:	TK_WRITE TK_LPAREN lista_expressoes TK_RPAREN	{ $$ = A_IO($3); }
;


lista_expressoes:	lista_expressoes TK_VIRGULA expressao	{ $$ = $3.push_back($3); }
				|	expressao								{ $$ = A_ListExp($1); }
;


expressao:	expressao_simples							{ $$ = $1; }
		|	expressao_simples relacao expressao_simples	{ $$ = A_Exp_Binaria($1, $2, $3); }
;


relacao:	TK_IGUAL			{ $$ = 00; }
		|   TK_DIFERENTE		{ $$ = 01; }
		|   TK_MENOR			{ $$ = 02; }
		|   TK_MENORIGUAL		{ $$ = 03; }
		|   TK_MAIOR			{ $$ = 04; }
		|   TK_MAIORIGUAL		{ $$ = 05; }
;      


expressao_simples:	expressao_simples or_op termo	{ $$ = A_Exp_Binaria($1, $2, $3); }
				|	termo							{ $$ = $1; }
;

or_op:		TK_MAIS					{ $$ = 10; }
		|   TK_MENOS				{ $$ = 11; }
		|   TK_OR					{ $$ = 12; }
;


termo:		fator and_op termo		{ $$ = A_Exp_Binaria($1, $2, $3); }
		|	fator					{ $$ = $1; }
;

and_op:		TK_MULT					{ $$ = 20; }
		|   TK_DIV					{ $$ = 21; }
		|   TK_AND					{ $$ = 22; }
;

fator:      variavel						{ $$ = A_Fator($1); }
		|	TK_NUM							{ $$ = $1; }
		|   logico							{ $$ = $1; }
		|   chamada_funcao					{ $$ = A_Fator($1); }
		|   TK_LPAREN expressao TK_RPAREN	{ $$ = A_Fator($2); }
		|   TK_NOT fator					{ $$ = $2; }
		|   TK_MENOS fator					{ $$ = $2; }
;


variavel:   identificador	{ $$ = $1; }
;

logico:     TK_FALSE		{ $$ = 30; }
		|   TK_TRUE			{ $$ = 31; }
;

chamada_funcao:		identificador TK_LPAREN lista_expressoes TK_RPAREN	{ $$ = A_ChamFunc($1, $3); }
;

identificador: 		TK_IDENT
;

%%