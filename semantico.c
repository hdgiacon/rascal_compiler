#include <string.h>
#include "semantico.h"

#define _NUL_S_ "_NUL_" // null para string
#define _NUL_I_ -1      // null para inteiro

int escopo_atual = 0;

/* tabela (pilha) de simbolos */
struct Symbol *top = NULL;


/* verifica se um simbolo esta na tabela */
bool esta_na_tabela(String simbolo){
    struct Symbol *temp;
    temp = top;
    while(temp != NULL){
        if(simbolo == temp->simbolo){
            return true;
        }
        temp = temp->prox;
    }
    return false;
}

bool variavel_mesmo_escopo(String simbolo){
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
    //instalar simbolo na tabela de simbolos
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
    return _NUL_S_;
}


void analisaDecSubs(A_LstDecSub _secDecSub){
    // mandar pra pilha todos os elementos A_lstDecSub
    A_LstDecSub secDecSub = _secDecSub;

    escopo_atual = 1;
    
    while(secDecSub != NULL){
        if(secDecSub->decProc.tipo == TD_PROC){
            // procedimento
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
            // função
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

String analiseChamFunc(A_ChamFunc _chamFunc){

}

String analiseFator(A_Exp exp_fator){
    A_Exp fatores = exp_fator;

    switch(fatores->fator.tipo){
        case TF_Var:

            return buscar_tipo_var(fatores->fator.variavel->id);
        case TF_Num:
            // codigo mepa
            return "integer";
        case TF_Logico: 
            // codigo mepa
            return "boolean";
        case TF_ChamFunc:
            return analiseChamFunc(fatores->fator.chamadaFuncao);
        case TF_Exp:
            return analiseExp(farores->fator.exp);  // conferir esse parametro pra ver se ta certo
            break;
    }
}

String analiseExp(A_Exp _expressao){
    A_Exp expressoes = _expressao;

    String tipoEsq;
    String tipoDir;

    switch(expressoes->tipo){
        case TE_Fator:
            analiseFator(expressoes->fator);
            break;
        case TE_Exp_Binaria:
            // chamar a recursão
            tipoEsq = analiseExp(expressoes->binaria.exp_esquerda);
            tipoDir = analiseExp(expressoes->binaria.exp_direita);

            if(verificar se é aritmetico ou elacional && tipoEsq == tipoDir){ // strcmp, usar switch pra cada tipo numerico de operador
                // return do tipo
            }
            else if(verificar se é logico ou = ou <> && tipoEsq == tipoDir){    // comparação de String é por strcmp
                // return do tipo
            }
            else{
                // erro tipo
            }
    }
}

void analisaAtribuicao(struct A_atrib atribuicao){

    //verficiar se a variavel esta na tabela de simbolos e no escopo atual
    if(esta_na_tabela(_id) && variavel_mesmo_escopo(_id)){      
        //verificar se o tipo dos dois lados da atribuição é o mesmo

        if(buscar_tipo_var(_id) == analiseExp(_expressao)){ // trocar aqui pra seguir o parametro

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

void analisaCmd(A_Cmd comando){
    switch(comando->tipo){
        case TC_ATRIB:
            analisaAtribuicao(comando->A_atrib);
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