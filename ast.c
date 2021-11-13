#include <stdlib.h>
#include "ast.h"

A_Programa A_programa(String _id, A_Bloco _bloco){
    A_Programa programa = malloc(sizeof(*programa));
    programa->id = _id;
    programa->bloco = _bloco;
    return programa;
}

A_Bloco A_bloco(A_LstDecVar _secDecVar, A_LstDecSub _secDecSub, A_CmdComp _cmdComp){
    A_Bloco A_bloco = malloc(sizeof(*bloco));
    bloco->secDecSub = _secDecSub;
    bloco->secDecVar = _secDecVar;
    bloco->cmdcomp = _cmdComp;
    return bloco;
}

A_ListaId A_listaId(String _id, A_ListaId _listaId){
    A_ListaId no = malloc(sizeof(*no));
    no->id = _id;
    no->prox = _listaId;
    return no;
}

A_DecVar A_decVar(String _id, String _tipo){
    A_DecVar decVar = malloc(sizeof(*decVar));
    decVar->id = _id;
    decVar->tipo = _tipo;
}

A_LstDecVar A_lstDecVar(A_DecVar _decVar, A_LstDecVar _lstDecVar){
    A_LstDecVar no = malloc(sizeof(*no));
    no->decVar = _decVar;
    no->prox = _lstDecVar;
    return no;
}

A_LstDecVar concatLstDecVar(A_LstDecVar _lst1, A_LstDecVar _lst2){
    A_LstDecVar lstConcat = _lst1;
    if(_lst1 != NULL){
        while(_lst1->prox != NULL){
            _lst1 = _lst1->prox;
        }
        _lst1->prox = _lst2;
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
    return no;
}

A_Exp A_exp_fator_variavel(A_Var _variavel){
    A_Exp no = malloc(sizeof(*no));
    no->tipo = TE_Fator;
    no->fator.tipo = RF_Var;
    no->fator.variavel = _variavel;
    return no;
}

A_Exp A_exp_fator_expressao(A_Exp _expressao){
    A_Exp no = malloc(sizeof(*no));
    no->tipo = TE_Fator;
    no->fator.tipo = TF_Exp;
    no->fator.expressao = _expressao;
    return no;
}

A_Exp A_exp_binaria(A_Exp _exp_esquerda, int _relacao, A_Exp _exp_direita){
    A_Exp no = malloc(sizeof(*no));
    no->tipo = TE_Exp_Binaria;
    no->binaria = TE_Exp_Binaria;
    no->binaria.exp_esquerda = _exp_esquerda;
    no->binaria.relacao = _relacao;
    no->binaria.exp_direita = _exp_direita;
    return no;
}

A_Atrib A_atrib(A_Exp _expressao){
    A_Atrib atrib = malloc(sizeof(*atrib));
    atrib->expressao = _expressao;
    return atrib;
}

A_ChamProc A_chamProc(A_Identificador _identificador, A_ListExp _lista_expressoes){
    A_ChamProc chamProc = malloc(sizeof(*chamProc));
    chamProc->identificador = _identificador;
    chamProc->lista_expressoes = _lista_expressoes;
    return chamProc;
}

A_Loop A_loop(A_Exp _expressao, A_Cmd _comando){
    A_Loop loop = malloc(sizeof(*loop));
    loop->expressao = _expressao;
    loop->comando = _comando;
    return loop;
}

