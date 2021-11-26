#include "semantico.h"
#include "ast.h"
#include <stdbool.h>

int escopo_atual = 0;

//chamar a tabela aqui pra ficar global


bool esta_na_tabela(variavel){
    //procurar na pilha
    //se estiver presente
        return true;
    //senão
        return false;
}

bool mesmo_escopo(){
    //logica ...
    return true
    return false;
}


//Verificar se está na tabela de simbolos e no escopo atual
bool verifica_tabela_escopo(variavel){
    //talvez jogar essa verificação em uma função separada visto q aparecerá em mais de um nó
    if(esta_na_tabela(variavel)){
        if(mesmo_escopo(variavel)){
            //tudo ok
            return true;
        }
    }
    else{
        printf("Erro: Variavel nao declarada no atual contexto"); //colocar a variavel em um %s aqui
    }

    return false;

}

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
    
    if(verifica_tabela_escopo(atribuicao)){
        //verificar se o tipo dos dois lados da atribuição é o mesmo
    }
    
}

void analisaChamProc(A_cmd_chamProc chamProc){
    // verficiar se a chamada de procedimento esta na tabela de simbolos e no escopo atual
    if(verifica_tabela_escopo(chamProc)){

    }
    
    // verificar se o numero de parametros na chamada equivale ao numero da declaração na pilha
    // verificar se os argumentos estão na mesma ordem da declaração do procedimento (pilha)
}

void analisaCondicional(A_cmd_cond condicional){
    //a expressão condicional deve ser valida e resultar em algum valor do tipo logico



    //Verificar se é valida -> verificar se retorna boolean
    //Verificar se a condicional resulta em boolean
    // checar se a expressão possui operadores relacionais ou logicos -> unico jeito de resultar boolean
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
                break;
            case TC_ESCRITA:
                break;
            case TC_CMDCOMP:
                // incremento da lista de comando compostos
                // comando = comando->A_cmdComp.prox;
                break;
        }
    }
}