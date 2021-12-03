#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "semantico.h"

#define _NUL_S_ "_NUL_" // null para string
#define _NUL_I_ -1      // null para inteiro

//extern char *nome_prog;   // nome do arquivo pra passar no fopen

int escopo_atual = 0;

int posicao_relativa_0 = 0;
int posicao_relativa_1 = 0;
int posicao_relativa_pf = -4;

/* tabela (pilha) de simbolos */
struct Symbol *top = NULL;


/* verifica se um simbolo esta na tabela e o retorna*/
struct Symbol *esta_na_tabela(String simbolo){
    struct Symbol *temp;
    temp = top;
    while(temp != NULL){
        if(simbolo == temp->simbolo){
            return temp;
        }
        temp = temp->prox;
    }
    return NULL;
}

bool simbolo_mesmo_escopo(String simbolo){
    struct Symbol *temp;
    temp = top;
    while(temp != NULL){
        if(simbolo == temp->simbolo && temp->infos.escopo == escopo_atual){
            return true;
        }
    }
    return false;
}


void analisaPrograma(A_Programa prog){
    analisaBloco(prog->bloco);
}

void analisaBloco(A_Bloco bloco){
    analisaDecVars(bloco->secDecVar);
    analisaDecSubs(bloco->secDecSub);
    analisaCmdComp(bloco->cmdComp);
}

void analisaDecVars(A_LstDecVar _secDecVar){
    // mandar pra pilha todos os elementos A_lstDecVar
    A_LstDecVar secDecVar = _secDecVar;

    while(secDecVar != NULL){
        top = push(
            top,
            secDecVar->decVar->id,
            "VS",
            escopo_atual,
            (escopo_atual == 0) ? posicao_relativa_0 : posicao_relativa_1,
            _NUL_I_,
            _NUL_S_,        // aqui é string: R01, o que seria isso?
            secDecVar->decVar->tipo,
            _NUL_S_,
            _NUL_I_,
            _NUL_I_
        );

        (escopo_atual == 0) ? posicao_relativa_0++ : posicao_relativa_1++;
        secDecVar = secDecVar->prox;
    }
}

/* numero de parametros formais */
int num_pf(A_DecParamList lista_parametros){
    A_DecParamList decParamList = lista_parametros;
    int cont = 0;
    
    while(decParamList != NULL){
        cont++;
        decParamList = decParamList->prox;
    }
    return cont;
}

/* buscar tipo da variavel pelo nome na tabela de simbolos */
String buscar_tipo_var(String _id){
    struct Symbol *temp;
    temp = top;
    while(temp != NULL){
        if(temp->simbolo == _id){
            return temp->infos.type.t_normal;
        }
        temp = temp->prox;
    }
    return _NUL_S_; // variavel não foi encontrada
}


void analisaDecSubs(A_LstDecSub _secDecSub){
    // mandar pra pilha todos os elementos A_lstDecSub
    A_LstDecSub secDecSub = _secDecSub;

    escopo_atual = 1;
    
    while(secDecSub != NULL){
        if(secDecSub->decProc->tipo == TD_PROC){
            /* parametro formal */
            A_DecParamList param_formais = secDecSub->decProc->_decProc_proc.parametros_formais;
            while(param_formais != NULL){
                /* lista de identificadores dentro de parametros formais */
                A_ListaId var_param = param_formais->declaracao_parametros->lista_identificadores;
                while(var_param != NULL){
                    top = push(
                        top,
                        var_param->id,
                        "PF",
                        1,
                        _NUL_I_,
                        posicao_relativa_pf,
                        _NUL_S_,    //mesma coisa aqui: R01?
                        param_formais->declaracao_parametros->tipo,
                        _NUL_S_,
                        _NUL_I_,
                        _NUL_I_
                    );

                    posicao_relativa_pf--;
                    var_param = var_param->prox;
                }

                param_formais = param_formais->prox;
            }
            /* procedimento */
            top = push(
                top,
                secDecSub->decProc->_decProc_proc.id,
                "PROC",
                escopo_atual, 
                _NUL_I_,
                _NUL_I_,
                _NUL_S_,   //posicao_relativa_1, mesma coisa R01?
                _NUL_S_,
                _NUL_S_,
                num_pf(secDecSub->decProc->_decProc_proc.parametros_formais),
                0
            );

            posicao_relativa_1++;

            // analise do corpo do procedimento
        }
        else{
            /* parametro formal */
            A_DecParamList parametros_formais = secDecSub->decProc->_decProc_func.parametros_formais;
            while(parametros_formais != NULL){
                /* lista de identificadores dentro de parametros formais */
                A_ListaId var_parametros = parametros_formais->declaracao_parametros->lista_identificadores;
                while(var_parametros != NULL){
                    top = push(
                        top,
                        var_parametros->id,
                        "PF",
                        1,
                        _NUL_I_,
                        posicao_relativa_pf,
                        _NUL_S_,    // mesma coisa aqui R01???
                        parametros_formais->declaracao_parametros->tipo,
                        _NUL_S_,
                        _NUL_I_,
                        _NUL_I_                       
                    );

                    var_parametros = var_parametros->prox;
                }

                parametros_formais = parametros_formais->prox;
            }
            /* função */
            top = push(
                top,
                secDecSub->decProc->_decProc_func.id,
                "FUNC",
                escopo_atual,   
                _NUL_I_,
                _NUL_I_,
                _NUL_S_,     //posicao_relativa_1          mesma coisa aqui R01?
                _NUL_S_,
                secDecSub->decProc->_decProc_func.tipo,
                num_pf(secDecSub->decProc->_decProc_func.parametros_formais),
                0
            );

            posicao_relativa_1++;

            // analise do corpo da função
        }
        
        secDecSub = secDecSub->prox;
    }

    escopo_atual = 0;
}

// analise que envolve expressão:
//  -> precisa analisar de forma recursiva 
//  -> se for uma expressão binaria, então chama a recursão
//  -> se for um dos casos do fator, então fazer a analise 
//  -> a recursão acaba quando não há mais expressões binarias

int num_parametros(A_ListExp lista_parametros){
    A_ListExp lista = lista_parametros;
    int cont = 0;

    while(lista != NULL){
        cont++;
        lista = lista->prox;
    }

    return cont;
}

bool analisaOrdemFunc(A_ChamFunc chamFunc){

}

String analisaChamFunc(A_ChamFunc _chamFunc){
    struct Symbol *funcao = esta_na_tabela(_chamFunc->id);

    // verficar se a chamada de procedimento esta na tabela de simbolos e no escopo atual
    if((funcao != NULL) && simbolo_mesmo_escopo(_chamFunc->id)){
        // verificar se o numero de parametros na chamada equivale ao numero da declaração na pilha
        if(num_parametros(_chamFunc->lista_expressoes) == funcao->infos.type.t_sub.numero_parametros){
            // verificar se os argumentos estão na mesma ordem da declaração do procedimento (pilha)
            //if(analisaOrdemFunc()){
                // buguei aqui ---------------
            //}
            //else{
            //    fprintf(stderr, "");
            //}
        }
        else{
            fprintf(stderr, "Número incorreto de parâmetros na função %s \n\n", _chamFunc->id);
        }
    }
    else{
        fprintf(stderr, "Função %s não está declarada \n\n", _chamFunc->id);
    }

    return _NUL_S_; // talvez isso de problema
}

String analisaFator(struct Exp_Fator exp_fator){
    struct Exp_Fator fatores = exp_fator;

    switch(fatores.tipo){
        case TF_Var:
            // codigo mepa
            return buscar_tipo_var(fatores.variavel->id);
        case TF_Num:
            // codigo mepa
            return "integer";
        case TF_Logico: 
            // codigo mepa
            return "boolean";
        case TF_ChamFunc:
            return analisaChamFunc(fatores.chamadaFuncao);
        case TF_Exp:
            return analisaExp(fatores.expressao);
    }
}

String analisaExp(A_Exp _expressao){
    A_Exp expressoes = _expressao;

    String tipoEsq;
    String tipoDir;

    switch(expressoes->tipo){
        case TE_Fator:
            return analisaFator(expressoes->fator);
        case TE_Exp_Binaria:
            tipoEsq = analisaExp(expressoes->binaria.exp_esquerda);
            tipoDir = analisaExp(expressoes->binaria.exp_direita);

            switch(expressoes->binaria.relacao){
                /* operadores aritmeticos */
                case 10:
                case 11:
                case 20:
                case 21:
                    if(strcmp(tipoEsq,tipoDir) == 0){
                        return "integer";
                    }
                    else{
                        fprintf(stderr, "Tipo incorreto, esperado tipo integer (inteiro) \n\n");
                        return "integer";   // só pro programa continuar e mostrar mais erros se houver
                    }
                /* operadores relacionais */
                case 00:
                case 01:
                case 02:
                case 03:
                case 04:
                case 05:
                /* operadores logicos */
                case 12:
                case 22:
                    if(strcmp(tipoEsq,tipoDir) == 0){
                        return "boolean";
                    }
                    else{
                        fprintf(stderr, "Tipo incorreto, esperado tipo boolean (booleano) \n\n");
                        return "boolean";
                    }
            }
    }
}

void analisaAtribuicao(struct A_atrib atribuicao){
    struct Symbol *simbolo = esta_na_tabela(atribuicao.id);
    String tipo_lado_esq;
    String tipo_lado_dir;

    //verficiar se o simbolo esta na tabela de simbolos e no escopo atual
    if((simbolo != NULL) && simbolo_mesmo_escopo(atribuicao.id)){      
        
        //verificar se o tipo dos dois lados da atribuição é o mesmo
        tipo_lado_esq = buscar_tipo_var(atribuicao.id);
        tipo_lado_dir = analisaExp(atribuicao.expressao);
        if(strcmp(tipo_lado_esq,tipo_lado_dir) == 0){

        }
        else{
            fprintf(stderr, "Tipo %s incorreto, esperado tipo %s para %s \n\n", tipo_lado_dir, tipo_lado_esq, atribuicao.id);
        }
    }
    else{
        fprintf(stderr, "Simbolo %s não declarado \n\n", atribuicao.id);
    }
}

bool analisaOrdemProc(struct A_chamProc chamProc){

}

void analisaChamProc(struct A_chamProc chamProc){
    struct Symbol *procedimento = esta_na_tabela(chamProc.identificador);

    // verficar se a chamada de procedimento esta na tabela de simbolos e no escopo atual
    if((procedimento != NULL) && simbolo_mesmo_escopo(chamProc.identificador)){
        // verificar se o numero de parametros na chamada equivale ao numero da declaração na pilha
        if(num_parametros(chamProc.lista_expressoes) == procedimento->infos.type.t_sub.numero_parametros){
            // verificar se os argumentos estão na mesma ordem da declaração do procedimento (pilha)

            //buguei igual com função ---------------
        }
        else{
            fprintf(stderr, "Número incorreto de parâmetros no procedimento %s \n\n", chamProc.identificador);
        }
    }
    else{
        fprintf(stderr, "Procedimento %s não está declarado \n\n", chamProc.identificador);
    }
}

void analisaCondicional(struct A_cond cond){
    //a expressão condicional deve ser valida e resultar em algum valor do tipo logico
    String tipo_exp = analisaExp(cond.expressao);
    if(strcmp(tipo_exp,"boolean") == 0){

    }
    else{
        fprintf(stderr, "Valor booleano esperado, expressão condicional resultou em %s \n\n", tipo_exp);
    }
}

void analisaLoop(struct A_loop loop){
    //a expressão condicional deve ser valida e resultar em algum valor do tipo logico
    String tipo_loop = analisaExp(loop.expressao);
    if(strcmp(tipo_loop,"boolean") == 0){

    }
    else{
        fprintf(stderr, "Valor booleano esperado, expressão condicional resultou em %s \n\n", tipo_loop);
    }
}

void analisaLeitura(struct A_read read){
    struct A_read aux_read = read;

    while(aux_read._lista_identificadores != NULL){
        if(esta_na_tabela(aux_read._lista_identificadores->id) != NULL){

        }
        else{
            fprintf(stderr, "Simbolo %s não declarado \n\n", aux_read._lista_identificadores->id);
        }

        aux_read._lista_identificadores = aux_read._lista_identificadores->prox;
    }
}

void analisaEscrita(struct A_write write){
    struct A_write aux_write = write;
    String ret_exp;

    while(aux_write.lista_expressoes != NULL){
        ret_exp = analisaExp(aux_write.lista_expressoes->expressao);

        aux_write.lista_expressoes = aux_write.lista_expressoes->prox;
    }
}

void analisaCmd(A_Cmd comando){
    switch(comando->tipo){
        case TC_ATRIB:
            analisaAtribuicao(comando->A_atrib);
            break;
        case TC_CHAMPROC:
            analisaChamProc(comando->A_chamProc);
            break;
        case TC_COND:
            analisaCondicional(comando->A_cond);
            break;
        case TC_LOOP:
            analisaLoop(comando->A_loop);
            break;
        case TC_LEITURA:
            analisaLeitura(comando->A_io_read);
            break;
        case TC_ESCRITA:
            analisaEscrita(comando->A_io_write);
            break;
        case TC_CMDCOMP:
            analisaCmdComp(comando->A_cmdComp.comando);
            break;
    }
}

void analisaCmdComp(A_Cmd comandos){
    A_Cmd cmd = comandos;

    while(cmd != NULL){
        analisaCmd(cmd->A_cmdComp.comando);
        cmd = cmd->A_cmdComp.prox;
    }
}