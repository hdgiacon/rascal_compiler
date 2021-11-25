#include "semantico.h"
#include "ast.h"

void analisaPrograma(A_programa prog){
    //instalar simbolo na tabela de simbolos
    analisaBloco();
}

void analisaBloco(A_Bloco bloco){
    analisaDecVars(bloco->secDecVar);
    analisaDecSubs(bloco->secDecSub);
    analisaCmdComp(bloco->cmdComp);
}

void analisaDecVars(A_lstDecVar secDecVar){
    // mandar pra pilha todos os elementos A_lstDecVar
}

void analisaDecSubs(A_lstDecSub secDecSub){
    // mandar pra pilha todos os elementos A_lstDecSub
}

void analisaAtribuicao(A_cmd_atrib atribuicao){
    //verficiar se a variavel esta na tabela de simbolos e no escopo atual
    //verificar se o tipo dos dois lados da atribuição é o mesmo
}

void analisaChamProc(A_cmd_chamProc chamProc){
    // verficiar se a chamada de procedimento esta na tabela de simbolos e no escopo atual
    // verificar se o numero de parametros na chamada equivale ao numero da declaração na pilha
    // verificar se os argumentos estão na mesma ordem da declaração do procedimento (pilha)
}

void analisaCondicional(A_cmd_cond condicional){
    //a expressão condicional deve ser valida e resultar em algum valor do tipo logico
}

void analisaLoop(A_cmd_loop loop){
    //a expressão condicional deve ser valida e resultar em algum valor do tipo logico
}

void analisaCmdComp(A_Cmd comandos){
    A_Cmd comando = comandos;
    while(comando->A_cmdComp.prox != NULL){
        switch(comando->tipo){
            case TC_ATRIB:
                analisaAtribuicao(A_cmd_atrib atribuicao);
                break;
            case TC_CHAMPROC:
                analisaChamProc(A_cmd_chamProc chamProc);
                break;
            case TC_COND:
                analisaCondicional(A_cmd_cond condicional);
                break;
            case TC_LOOP:
                analisaLoop(A_cmd_loop loop);
                break;
            case TC_LEITURA:
                break
            case TC_ESCRITA:
                break;
            case TC_CMDCOMP:
                // incremento da lista de comando compostos
                // comando = comando->A_cmdComp.prox;
                break;
        }
    }
}