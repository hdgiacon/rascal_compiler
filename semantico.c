#include "semantico.h"

#define _NUL_S_ "_NUL_" // null para string
#define _NUL_I_ -1      // null para inteiro

int escopo_atual = 0;

/* tabela (pilha) de simbolos */
struct symbol *top = NULL;

/* verifica se um simbolo esta na tabela */
bool esta_na_tabela(String simbolo){
    //procurar na pilha
    struct symbol *temp;
    temp = top;
    while(temp != NULL){
        if(simbolo == temp->simbolo){
            //se estiver presente
            return true;
        }
        temp = temp->prox;
    }
    return false;
}

bool variavel_mesmo_escopo(String simbolo){
    struct symbol *temp;
    temp = top;
    while(temp != NULL){
        if(simbolo == temp->simbolo && temp->infos.escopo == escopo_atual){
            return true;
        }
    }

    return false;
}


// //Verificar se está na tabela de simbolos e no escopo atual
// bool verifica_tabela_escopo(variavel){
//     if(esta_na_tabela(variavel)){
//         if(mesmo_escopo(variavel)){
//             //tudo ok
//             return true;
//         }
//     }
//     else{
//         printf("Erro: Variavel nao declarada no atual contexto"); //colocar a variavel em um %s aqui
//     }

//     return false;

// }

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
    while(secDecVar != NULL){
        top = push(top,secDecVar->decVar->id,"VS",0,0,0,"aaa",secDecVar->decVar->tipo,"ttt",0,0);
        secDecVar = secDecVar->prox;
    }
}

/* numero de parametros formais */
int num_pf(A_DecParamList lista_parametros){
    int cont = 0;
    while(lista_parametros != NULL){
        cont++;
        lista_parametros = lista_parametros->prox;
    }
    return cont;
}

/* buscar tipo da variavel pelo nome na tabela de simbolos */
String buscar_tipo_var(String _id){
    struct symbol *temp;
    temp = top;
    while(temp != NULL){
        if(temp->simbolo == _id){
            return temp->infos.type.t_normal;
        }
        temp = temp->prox;
    }
    return _NUL_S_;
}


void analisaDecSubs(A_lstDecSub secDecSub){
    // mandar pra pilha todos os elementos A_lstDecSub

    escopo_atual++;
    
    while(secDecSub != NULL){
        if(secDecSub->decProc.tipo == TD_PROC){
            // para procedimento
            top = push(
                secDecSub->decProc._decProc_proc.id,
                "PROC",
                0,
                0,
                0,
                "aaa",
                "ooo",
                "eee",
                num_pf(secDecSub->decProc._decProc_proc.parametros_formais),
                0
            );
            // analise do corpo do procedimento
        }
        else{
            // para funcao
            top = push(
                secDecSub->decProc._decProc_func.id,
                "FUNC",
                0,
                0,
                0,
                "aaa".
                "ooo",
                secDecSub->decProc._decProc_func.tipo,
                num_pf(secDecSub->decProc._decProc_func.parametros_formais),
                0
            );
            // analise do corpo da função
        }
        
        secDecSub = secDecSub->prox;
    }

    escopo_atual--;
}

// analise que envolve expressão:
//  -> precisa analisar de forma recursiva 
//  -> se for uma expressão binaria, então chama a recursão
//  -> se for um dos casos do fator, então fazer a analise 
//  -> a recursão acaba quando não há mais expressões binarias

String analiseChamFunc(A_ChamFunc _chamFunc){

}

String analiseFator(A_Exp exp_fator){
    A_Exp fatores = exp_fator;
    switch(fatores->fator.tipo){
        case TF_Var:
            return buscar_tipo_var(fatores->fator.variavel->id);
            //break;
        case TF_Num:
            return "integer";
            //break;
        case TF_Logico: // neste caso faz o que?
            break;
        case TF_ChamFunc:
            return analiseChamFunc(fatores->fator.chamadaFuncao);
            //break;
        case TF_Exp:    // neste caso faz o que?
            break;
    }
}

String tipo_lado_dir(A_Exp _expressao){
    A_Exp expressoes = _expressao;
    switch(expressoes->tipo){
        case TE_Fator:
            analiseFator(expressoes->fator);
            break;
        case TE_Exp_Binaria:
            // chamar a recursão
            //expressoes = tipo_lado_dir(expressoes); // seria isso?
            break;
    }
    // onde fica o return dessa função?
}

void analisaAtribuicao(String _id, A_Exp _expressao){

    //verficiar se a variavel esta na tabela de simbolos e no escopo atual
    if(esta_na_tabela(_id) && variavel_mesmo_escopo(_id)){
        //verificar se o tipo dos dois lados da atribuição é o mesmo
        if(buscar_tipo_var(_id) == tipo_lado_dir(_expressao)){

        }
        
    }
    
}
// arrumar o parametro
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
                analisaAtribuicao(comando->A_atrib.id, comando->A_atrib.expressao);
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