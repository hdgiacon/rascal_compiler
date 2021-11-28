#ifndef SEM_H
#define SEM_H

#include <stdbool.h>
#include "util.h"
#include "ast.h"

void analisaPrograma(A_programa prog);
void analisaBloco(A_Bloco bloco);
void analisaDecVars(A_lstDecVar secDecVar);
void analisaDecSubs(A_lstDecSub secDecSub);
void analisaCmdComp(A_Cmd comandos);
//String analisaChamFunc(A_ChamFunc chamFunc);
//String analisaFator(A_Exp exp_fator);
//void analisaAtribuicao(String id, A_Exp expressao);
//void analisaChamProc();
//void analisaCondicional();
//void analisaLoop();

bool esta_na_tabela(String simbolo);
bool variavel_mesmo_escopo(String simbolo);
int num_pf(A_DecParamList lista_parametros);
String buscar_tipo_var(String id);
String tipo_lado_dir(A_Exp expressao);

#endif