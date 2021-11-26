#include <stdlib.h>
#include "ast.h"

A_Programa A_programa(String _id, A_Bloco _bloco){
    A_Programa programa = malloc(sizeof(*programa));
    programa->id = _id;
    programa->bloco = _bloco;
    return programa;
}

A_Bloco A_bloco(A_LstDecVar _secDecVar, A_LstDecSub _secDecSub, A_Cmd _cmdComp){
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
    return decVar;
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
    A_Exp no = malloc(sizeof(*no));
    no->tipo = TE_Fator;
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

A_Exp A_exp_fator_int(int _num){
    A_Exp no = malloc(sizeof(*no));
    no->tipo = TE_Fator;
    no->fator.num = _num;
    return no;
}

A_Exp A_exp_fator_logico(int _logico){
    A_Exp no = malloc(sizeof(*no));
    no->tipo = TE_Fator;
    no->fator.logico = _logico;
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


A_BlocoSub A_blocoSub(A_LstDecVar _secDecVar, A_Cmd _cmdComp){
    A_BlocoSub blocoSub = malloc(sizeof(*blocoSub));
    blocoSub->secDecVar = _secDecVar;
    blocoSub->cmdComp = _cmdComp;
    return blocoSub;
}

A_DecParam A_decParam(A_ListaId _lista_identificadores, String _tipo){
    A_DecParam decParam = malloc(sizeof(*decParam));
    decParam->lista_identificadores = _lista_identificadores;
    decParam->tipo = _tipo;
    return decParam;
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
    return decProc;
}

A_DecProc A_decProc_func(String _id, A_DecParamList _parametros_formais, A_BlocoSub _bloco, String _tipo){
    A_DecProc decProc = malloc(sizeof(*decProc));
    decProc->tipo = TD_FUNC;
    decProc->_decProc_func.id = _id;
    decProc->_decProc_func.parametros_formais = _parametros_formais;
    decProc->_decProc_func.bloco = _bloco;
    decProc->_decProc_func.tipo = _tipo;
    return decProc;
}




A_Cmd A_cmd_atrib(A_Exp _expressao){
    A_Cmd atrib = malloc(sizeof(*atrib));
    atrib->tipo = TC_ATRIB;
    atrib->A_atrib.expressao = _expressao;
    return atrib;
}

A_Cmd A_cmd_chamProc(String _identificador, A_ListExp _lista_expressoes){
    A_Cmd chamProc = malloc(sizeof(*chamProc));
    chamProc->tipo = TC_CHAMPROC;
    chamProc->A_chamProc.identificador = _identificador;
    chamProc->A_chamProc.lista_expressoes = _lista_expressoes;
    return chamProc;
}

A_Cmd A_cmd_cond(A_Exp _expressao, A_Cmd _comando_1, A_Cmd _comando_2){
    A_Cmd cond = malloc(sizeof(*cond));
    cond->tipo = TC_COND;
    cond->A_cond.expressao = _expressao;
    cond->A_cond.comando_1 = _comando_1;
    cond->A_cond.comando_2 = _comando_2;
    return cond;
}

A_Cmd A_cmd_loop(A_Exp _expressao, A_Cmd _comando){
    A_Cmd loop = malloc(sizeof(*loop));
    loop->tipo = TC_LOOP;
    loop->A_loop.expressao = _expressao;
    loop->A_loop.comando = _comando;
    return loop;
}

A_Cmd A_cmd_read(A_ListaId _lista_identificadores){
    A_Cmd io = malloc(sizeof(*io));
    io->tipo = TC_LEITURA;
    io->A_io_read._lista_identificadores = _lista_identificadores;
    return io;
}

A_Cmd A_cmd_write(A_ListExp _lista_expressoes){
    A_Cmd io = malloc(sizeof(*io));
    io->tipo = TC_ESCRITA;
    io->A_io_write.lista_expressoes = _lista_expressoes;
    return io;
}


A_Cmd A_cmdComp(A_Cmd _comando, A_Cmd _lista_comandos){
    A_Cmd no = malloc(sizeof(*no));
    no->tipo = TC_CMDCOMP;
    no->A_cmdComp.comando = _comando;
    no->A_cmdComp.prox = _lista_comandos;
    return no;
}

A_ChamFunc A_chamFunc(String _id, A_ListExp _lista_expressoes){
    A_ChamFunc chamFunc = malloc(sizeof(*chamFunc));
    chamFunc->id = _id;
    chamFunc->lista_expressoes = _lista_expressoes;
    return chamFunc;
}

A_Var A_var(String _id){
    A_Var var = malloc(sizeof(*var));
    var->id = _id;
    return var;
}

A_LstDecSub A_lstDecSub(A_DecProc _decProc, A_LstDecSub _lstDecSub){
    A_LstDecSub lstDecSub = malloc(sizeof(*lstDecSub));
    lstDecSub->decProc = _decProc;
    lstDecSub->prox = _lstDecSub;
    return lstDecSub;
}