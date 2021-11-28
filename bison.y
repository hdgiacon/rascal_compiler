%code requires{
	#include "util.h"
	#include "ast.h"
}

%{

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "util.h"

int yylex(void);

void yyerror(const char *s){
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
   A_LstDecVar secDecVar;
   A_ListaId listaId;
   A_DecProc decProc;
   A_DecParam decParam;
   A_DecParamList decParamList;
   A_Cmd cmd;
   A_ListExp listExp;
   A_Exp exp;
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
%type <secDecVar> secao_declaracao_variaveis lista_declaracao_variaveis declaracao_variaveis
%type <str> tipo identificador
%type <secDecSub> secao_declaracao_subrotinas lista_declaracao_subrotinas
%type <listaId> lista_identificadores
%type <decProc> declaracao_procedimento declaracao_funcao secao_declaracao_subrotinas_op
%type <decParam> declaracao_parametros declaracao_parametros_op
%type <decParamList> parametros_formais 
%type <cmd> comando atribuicao chamada_procedimento condicional repeticao leitura escrita comando_composto comando_rec
%type <listExp> lista_expressoes 
%type <exp> expressao expressao_simples termo fator
%type <var> variavel
%type <chamFunc> chamada_funcao 

%type <num> relacao or_op and_op logico


%define parse.error verbose
%define parse.lac full


%start programa

%%

programa:	TK_PROGRAM TK_IDENT TK_PONTVIRG bloco TK_PONTO { absyn_root = A_programa($2, $4); }
;

bloco:	secao_declaracao_variaveis secao_declaracao_subrotinas comando_composto { $$ = A_bloco($1, $2, $3); } 
;

secao_declaracao_variaveis:		TK_VAR lista_declaracao_variaveis		{ $$ = $2; }
							|											{ $$ = NULL; }
;

lista_declaracao_variaveis:		declaracao_variaveis TK_PONTVIRG lista_declaracao_variaveis		{ $$ = concatLstDecVar($1, $3); }
							|	declaracao_variaveis TK_PONTVIRG								{ $$ = $1; }
;

declaracao_variaveis:	lista_identificadores TK_DOISPONTOS tipo	{
	String tipo = $3;
	A_LstDecVar lstDecVar = NULL;
	A_ListaId listaId = $1;
	
	while (listaId != NULL) {
		lstDecVar = A_lstDecVar(A_decVar(listaId->id, tipo), lstDecVar);
		listaId = listaId->prox;
	}
	
	$$ = lstDecVar;
}
;


lista_identificadores:	identificador 									{ $$ = A_listaId($1, NULL); }		
					|	identificador TK_VIRGULA lista_identificadores	{ $$ = A_listaId($1, $3); }			
;


tipo:	identificador	{ $$ = $1; }
;

secao_declaracao_subrotinas:	lista_declaracao_subrotinas		{$$ = $1;}
						|		{ $$ = NULL; }
;

lista_declaracao_subrotinas:	secao_declaracao_subrotinas_op TK_PONTVIRG lista_declaracao_subrotinas	{ $$ = A_lstDecSub($1, $3); }
							|	secao_declaracao_subrotinas_op TK_PONTVIRG								{ $$ = A_lstDecSub($1, NULL); }
;

secao_declaracao_subrotinas_op:		declaracao_procedimento	{ $$ = $1; }
								|	declaracao_funcao		{ $$ = $1; }
;

declaracao_procedimento:	TK_PROCEDURE identificador TK_LPAREN parametros_formais TK_RPAREN TK_PONTVIRG bloco_subrotinas	{ $$ = A_decProc_proc($2, $4, $7); }
						|	TK_PROCEDURE identificador TK_LPAREN TK_RPAREN TK_PONTVIRG bloco_subrotinas						{ $$ = A_decProc_proc($2, NULL, $6); }
;

declaracao_funcao:	TK_FUNCTION identificador TK_LPAREN parametros_formais TK_RPAREN TK_DOISPONTOS tipo TK_PONTVIRG bloco_subrotinas	{ $$ = A_decProc_func($2, $4, $9, $7); }
				|	TK_FUNCTION identificador TK_LPAREN TK_RPAREN TK_DOISPONTOS tipo TK_PONTVIRG bloco_subrotinas						{ $$ = A_decProc_func($2, NULL, $8, $6); }
;

bloco_subrotinas:	secao_declaracao_variaveis comando_composto 	{ $$ = A_blocoSub($1, $2); }
;


parametros_formais:	declaracao_parametros TK_PONTVIRG parametros_formais		{ $$ = A_decParamList($1, $3); }
				|	declaracao_parametros										{ $$ = A_decParamList($1, NULL); }
;

declaracao_parametros:	TK_VAR declaracao_parametros_op				{ $$ = $2; }
					|	declaracao_parametros_op					{ $$ = $1; }
;

declaracao_parametros_op: lista_identificadores TK_DOISPONTOS tipo 	{ $$ = A_decParam($1, $3); }
;


comando_composto:	TK_BEGIN comando_rec TK_END	{ $$ = $2; }
;

comando_rec:	comando TK_PONTVIRG comando_rec	{ $$ = A_cmdComp($1, $3); }
			|	comando	TK_PONTVIRG				{ $$ = A_cmdComp($1, NULL); }
;

comando:	atribuicao				{ $$ = $1; }	
		|   chamada_procedimento	{ $$ = $1; }
		|   condicional				{ $$ = $1; }
		|   repeticao				{ $$ = $1; }
		|   leitura					{ $$ = $1; }
		|   escrita					{ $$ = $1; }
		|   comando_composto		{ $$ = $1; }
;


atribuicao:	TK_IDENT TK_ATRIBUICAO expressao	{ $$ = A_cmd_atrib($3,$1); }
;

chamada_procedimento:	identificador TK_LPAREN lista_expressoes TK_RPAREN		{ $$ = A_cmd_chamProc($1, $3); }
				|		identificador TK_LPAREN TK_RPAREN						{ $$ = A_cmd_chamProc($1, NULL); }
;


condicional:	TK_IF expressao TK_THEN comando TK_ELSE comando	{ $$ = A_cmd_cond($2, $4, $6); }
			|	TK_IF expressao TK_THEN comando					{ $$ = A_cmd_cond($2, $4, NULL); }
;

repeticao:	TK_WHILE expressao TK_DO comando					{ $$ = A_cmd_loop($2, $4); }
;

leitura:	TK_READ TK_LPAREN lista_identificadores TK_RPAREN	{ $$ = A_cmd_read($3); }
;

escrita:	TK_WRITE TK_LPAREN lista_expressoes TK_RPAREN		{ $$ = A_cmd_write($3); }
;


lista_expressoes:	lista_expressoes TK_VIRGULA expressao		{ $$ = A_listExp($3, $1); }
				|	expressao									{ $$ = A_listExp($1, NULL); }
;


expressao:	expressao_simples									{ $$ = A_exp_binaria($1, -1, NULL); }
		|	expressao_simples relacao expressao_simples			{ $$ = A_exp_binaria($1, $2, $3); }
;


relacao:	TK_IGUAL			{ $$ = 00; }
		|   TK_DIFERENTE		{ $$ = 01; }
		|   TK_MENOR			{ $$ = 02; }
		|   TK_MENORIGUAL		{ $$ = 03; }
		|   TK_MAIOR			{ $$ = 04; }
		|   TK_MAIORIGUAL		{ $$ = 05; }
;      


expressao_simples:	expressao_simples or_op termo	{ $$ = A_exp_binaria($1, $2, $3); }
				|	termo							{ $$ = A_exp_binaria($1, -1, NULL); }
;

or_op:		TK_MAIS					{ $$ = 10; }
		|   TK_MENOS				{ $$ = 11; }
		|   TK_OR					{ $$ = 12; }
;


termo:		fator and_op termo		{ $$ = A_exp_binaria($1, $2, $3); }
		|	fator					{ $$ = A_exp_binaria($1, -1, NULL); }	// -1 equivale a NULL
;

and_op:		TK_MULT					{ $$ = 20; }
		|   TK_DIV					{ $$ = 21; }
		|   TK_AND					{ $$ = 22; }
;

fator:      variavel						{ $$ = A_exp_fator_variavel($1); }
		|	TK_NUM							{ $$ = A_exp_fator_int($1); }	
		|   logico							{ $$ = A_exp_fator_logico($1); }
		|   chamada_funcao					{ $$ = A_exp_fator_chamada_funcao($1); }
		|   TK_LPAREN expressao TK_RPAREN	{ $$ = A_exp_fator_expressao($2); }
		|   TK_NOT fator					{ $$ = $2; }
		|   TK_MENOS fator					{ $$ = $2; }
;


variavel:   identificador	{ $$ = A_var($1); }
;

logico:     TK_FALSE		{ $$ = 30; }
		|   TK_TRUE			{ $$ = 31; }
;

chamada_funcao:		identificador TK_LPAREN lista_expressoes TK_RPAREN	{ $$ = A_chamFunc($1, $3); }
				|	identificador TK_LPAREN TK_RPAREN					{ $$ = A_chamFunc($1, NULL); }
;

identificador: 		TK_IDENT	{ $$ = $1; }
;

%%