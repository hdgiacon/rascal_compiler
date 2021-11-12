#include <stdlib.h>
#include "ast.h"

A_Programa A_programa(String id, A_Bloco bloco){
    A_Programa programa = malloc(sizeof(*programa));
    programa->id = id;
    programa->bloco = bloco;
    return programa;
}

A_Bloco A_bloco(A_LstDecVar secDecVar, A_LstDecSub secDecSub, A_CmdComp cmdComp){
    A_Bloco A_bloco = malloc(sizeof(*bloco));
    bloco->secDecSub = secDecSub;
    bloco->secDecVar = secDecVar;
    bloco->cmdcomp = cmdComp;
    return bloco;
}

A_ListaId A_listaId(String id, A_ListaId listaId){
    A_ListaId no = malloc(sizeof(*no));
    no->id = id;
    no->prox = listaId;
    return no;
}

A_DecVar A_decVar(String id, String tipo){
    A_DecVar decVar = malloc(sizeof(*decVar));
    decVar->id = id;
    decVar->tipo = tipo;
}

A_LstDecVar A_lstDecVar(A_DecVar decVar, A_LstDecVar lstDecVar){
    A_LstDecVar no = malloc(sizeof(*no));
    no->decVar = decVar;
    no->prox = lstDecVar;
    return no;
}

A_LstDecVar concatLstDecVar(A_LstDecVar lst1, A_LstDecVar lst2){
    A_LstDecVar lstConcat = lst1;
    if(lst1 != NULL){
        while(lst1->prox != NULL){
            lst1 = lst1->prox;
        }
        lst1->prox = lst2;
    }
    return lstConcat;
}


A_Exp A_exp_fator_chamada_funcao(A_ChamFunc _chamadaFuncao){
    //dar um malloc q nem 33
    A_Exp no = malloc(sizeof(*no));
    no->tipo = TE_Fator;
    //no->fator = (struct Exp_Fator){.tipo = TF_ChamFunc, .chamadaFuncao = chamadaFuncao}; // se precisar de mais argumentos
    no->fator.tipo = TF_ChamFunc;
    no->fator.chamadaFuncao = _chamadaFuncao;
}