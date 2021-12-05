#ifndef SEM_H
#define SEM_H

#include <stdbool.h>
#include "util.h"
#include "ast.h"
#include "tabelaSimbolos.h"

void analisaPrograma(A_Programa prog, String nome_programa);
void analisaBloco(A_Bloco bloco);
void analisaDecVars(A_LstDecVar secDecVar);
void analisaDecSubs(A_LstDecSub secDecSub);
String analisaChamFunc(A_ChamFunc chamFunc);
String analisaFator(struct Exp_Fator exp_fator);
String analisaExp(A_Exp expressao);
void analisaAtribuicao(struct A_atrib atribuicao);
void analisaChamProc(struct A_chamProc chamProc);
void analisaCondicional(struct A_cond cond);
void analisaLoop(struct A_loop loop);
void analisaLeitura(struct A_read read);
void analisaEscrita(struct A_write write);
void analisaCmd(A_Cmd comando);
void analisaCmdComp(A_Cmd comandos);

struct Symbol *esta_na_tabela(String simbolo);
bool simbolo_mesmo_escopo(String simbolo);
int num_pf(A_DecParamList lista_parametros);
int num_parametros(A_ListExp lista_parametros);
//bool analisaOrdemFunc(A_ChamFunc chamFunc);
//bool analisaOrdemProc(struct A_chamProc chamProc)
String buscar_tipo_var(String id);

#endif