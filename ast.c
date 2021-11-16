#include <stdlib.h>
#include "ast.h"

A_Programa A_programa(String _id, A_Bloco _bloco){
    A_Programa programa = malloc(sizeof(*programa));
    programa->id = _id;
    programa->bloco = _bloco;
    return programa;
}

A_Bloco A_bloco(A_LstDecVar _secDecVar, A_LstDecSub _secDecSub, A_CmdComp _cmdComp){
    A_Bloco bloco = malloc(sizeof(*bloco));
    bloco->secDecVar = _secDecVar;
    bloco->secDecSub = _secDecSub;
    bloco->cmdComp = _cmdComp;
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
    no->fator.tipo = TF_Var;
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
    no->binaria.exp_esquerda = _exp_esquerda;
    no->binaria.relacao = _relacao;
    no->binaria.exp_direita = _exp_direita;
    return no;
}



A_ListExp A_listExp(A_Exp _expressao, A_ListExp _lista_expressoes){
    A_ListExp no = malloc(sizeof(*no));
    no->expressao = _expressao;
    no->prox = _lista_expressoes;
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



A_Cond A_cond_c(A_Exp _expressao, A_Cmd _comando_1, A_Cmd _comando_2){
    A_Cond cond = malloc(sizeof(*cond));
    cond->tipo = TC_Com_else;
    cond->_cond_c_else.expressao = _expressao;
    cond->_cond_c_else.comando_1 = _comando_1;
    cond->_cond_c_else.comando_2 = _comando_2;
}

A_Cond A_cond_s(A_Exp _expressao, A_Cmd _comando_1){
    A_Cond cond = malloc(sizeof(*cond));
    cond->tipo = TC_Sem_Else;
    cond->_cond_s_else.expressao = _expressao;
    cond->_cond_s_else.comando_1 = _comando_1;
}

A_IO A_io_read(A_ListaId _lista_identificadores){
    A_IO io = malloc(sizeof(*io));
    io->tipo = TI_READ;
    io->_io_read._lista_identificadores = _lista_identificadores;
}

A_IO A_io_write(A_ListExp _lista_expressoes){  //trocar para lista de expressoes
    A_IO io = malloc(sizeof(*io));
    io->tipo = TI_WRITE;
    io->_io_write.lista_expressoes = _lista_expressoes;
}



A_CmdComp A_cmdComp(A_Cmd _comando, A_CmdComp _lista_comandos){
    A_CmdComp no = malloc(sizeof(*no));
    no->comando = _comando;
    no->prox = _lista_comandos;
    return no;
}


A_BlocoSub A_blocoSub(A_LstDecVar _secDecVar, A_CmdComp _cmdComp){
    A_BlocoSub blocoSub = malloc(sizeof(*blocoSub));
    blocoSub->secDecVar = _secDecVar;
    blocoSub->cmdComp = _cmdComp;
}

A_DecParam A_decParam(A_ListaId _lista_identificadores, A_Tipo _tipo){
    A_DecParam decParam = malloc(sizeof(*decParam));
    decParam->lista_identificadores = _lista_identificadores;
    decParam->tipo = _tipo;
}


A_DecParamList A_decParamList(A_DecParam _declaracao_parametros, A_DecParamList _lista_dec_parametros){
    A_DecParamList no = malloc(sizeof(*no));
    no->declaracao_parametros = _declaracao_parametros;
    no->prox = _lista_dec_parametros;
    return no;
}


A_DecProc A_decProc_proc(String _id, A_DecParamList _parametros_formais, A_BlocoSub _bloco){
    A_DecProc decProc = malloc(sizeof(*decProc));
    decProc->tipo = TD_PROC;
    decProc->_decProc_proc.id = _id;
    decProc->_decProc_proc.parametros_formais = _parametros_formais;
    decProc->_decProc_proc.bloco = _bloco;
}

A_DecProc A_decProc_func(String _id, A_DecParamList _parametros_formais, A_BlocoSub _bloco, A_Tipo _tipo){
    A_DecProc decProc = malloc(sizeof(*decProc));
    decProc->tipo = TD_FUNC;
    decProc->_decProc_func.id = _id;
    decProc->_decProc_func.parametros_formais = _parametros_formais;
    decProc->_decProc_func.bloco = _bloco;
    decProc->_decProc_func.tipo = _tipo;
}