#ifndef SEM_H
#define SEM_H

void analisaPrograma(A_programa prog);
void analisaBloco(A_Bloco bloco);
void analisaDecVars(A_Bloco secDecVar);
void analisaDecSubs(A_Bloco secDecSub);
void analisaCmdComp(A_Bloco cmdComp);


//no tocante a comando
void analisaAtribuicao();
void analisaChamadaProcedimento();
void analisaChamadaFuncao();
void analisaCondicional();
void analisaRepeticao();
void analisaLeitura();
void analisaEscrita();

#endif