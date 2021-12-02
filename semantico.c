#include <string.h>
#include "semantico.h"

#define _NUL_S_ "_NUL_" // null para string
#define _NUL_I_ -1      // null para inteiro

int escopo_atual = 0;

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
            0,  // para esses 3 0's: como funciona posição relativa?
            0,
            0,
            secDecVar->decVar->tipo,
            _NUL_S_,
            _NUL_I_,
            0   // como funciona o tipo de chamada?
        );
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
        if(secDecSub->decProc.tipo == TD_PROC){
            /* procedimento */
            top = push(
                secDecSub->decProc._decProc_proc.id,
                "PROC",
                0, 
                0,  // para esses 3 0's abaixo: como funciona posição relativa?
                0,
                0,
                _NUL_S_,
                _NUL_S_,
                num_pf(secDecSub->decProc._decProc_proc.parametros_formais),
                0   // como funciona o tipo de chamada?
            );
            // analise do corpo do procedimento
        }
        else{
            /* função */
            top = push(
                secDecSub->decProc._decProc_func.id,
                "FUNC",
                0,
                0,
                0,
                0,
                _NUL_S_,
                secDecSub->decProc.tipo,
                num_pf(secDecSub->decProc._decProc_func.parametros_formais),
                0
            );
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

bool analisaOrdemFunc(A_ChamFunc chamFunc, ){

}

String analisaChamFunc(A_ChamFunc _chamFunc){
    struct Symbol *funcao = esta_na_tabela(_chamFunc->id);

    // verficiar se a chamada de procedimento esta na tabela de simbolos e no escopo atual
    if((funcao != NULL) && simbolo_mesmo_escopo(_chamFunc->id)){
        // verificar se o numero de parametros na chamada equivale ao numero da declaração na pilha
        if(num_parametros(_chamFunc->lista_expressoes) == funcao->infos.type.t_sub.numero_parametros){
            // verificar se os argumentos estão na mesma ordem da declaração do procedimento (pilha)
            if(analisaOrdemFunc()){
                // buguei aqui
            }
            else{
                // mensagem de erro
            }
        }
        else{
            // mensagem de erro
        }
    }
    else{
        // mensagem de erro
    }
}

String analisaFator(A_Exp exp_fator){
    A_Exp fatores = exp_fator;

    switch(fatores->fator.tipo){
        case TF_Var:
            // codigo mepa
            return buscar_tipo_var(fatores->fator.variavel->id);
        case TF_Num:
            // codigo mepa
            return "integer";
        case TF_Logico: 
            // codigo mepa
            return "boolean";
        case TF_ChamFunc:
            return analisaChamFunc(fatores->fator.chamadaFuncao);
        case TF_Exp:
            return analisaExp(fatores->fator.expressao);
    }
}

String analisaExp(A_Exp _expressao){
    A_Exp expressoes = _expressao;

    String tipoEsq;
    String tipoDir;

    switch(expressoes->tipo){
        case TE_Fator:
            analisaFator(expressoes->fator);
            break;
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
                        // mensagem de erro
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
                        // mensagem de erro
                    }
            }
    }
}

void analisaAtribuicao(struct A_atrib atribuicao){
    struct Symbol *variavel = esta_na_tabela(atribuicao.id);

    //verficiar se a variavel esta na tabela de simbolos e no escopo atual
    if((variavel != NULL) && simbolo_mesmo_escopo(atribuicao.id)){      
        
        //verificar se o tipo dos dois lados da atribuição é o mesmo
        if(strcmp(buscar_tipo_var(atribuicao.id),analisaExp(atribuicao.expressao)) == 0){

        }
        else{
            // mensagem de erro
        }
    }
    else{
        // mensagem de erro
    }
}

void analisaChamProc(struct A_chamProc champroc){
    // verficiar se a chamada de procedimento esta na tabela de simbolos e no escopo atual
    if(simbolo_mesmo_escopo(champroc.identificador)){
        // verificar se o numero de parametros na chamada equivale ao numero da declaração na pilha
            // verificar se os argumentos estão na mesma ordem da declaração do procedimento (pilha)
    }
    else{
        // mensagem de erro
    }
}

void analisaCondicional(struct A_cond cond){
    //a expressão condicional deve ser valida e resultar em algum valor do tipo logico
    if(strcmp(analisaExp(cond.expressao),"boolean") == 0){

    }
    else{
        // mensagem de erro
    }
}

void analisaLoop(struct A_loop loop){
    //a expressão condicional deve ser valida e resultar em algum valor do tipo logico
    if(strcmp(analisaExp(loop.expressao),"boolean") == 0){

    }
    else{
        // mensagem de erro
    }
}

void analisaLeitura(struct A_read read){
    struct A_read aux_read = read;

    while(aux_read._lista_identificadores != NULL){
        if(esta_na_tabela(aux_read._lista_identificadores->id) != NULL){

        }
        else{
            // mensagem de erro
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
            analisaCmdComp(comando->A_cmdComp);
            break;
    }
}

void analisaCmdComp(A_cmdComp comandos){
    A_cmdComp cmd = comandos;

    while(cmd != NULL){
        analisaCmd(cmd->comando);
        cmd = cmd->prox;
    }
}