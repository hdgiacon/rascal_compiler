#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "semantico.h"

#define _NUL_S_ "_NUL_S_" // null para string
#define _NUL_I_ -1      // null para inteiro
int null_vet[1] = {0};  // null para vetor

// fazer uma string gigante ou matriz de strings pra cada codigo mepa
// caso haja erro nao usar essa string
// se for tudo bem, andar nessa string e gerar o arquivo da MEPA

bool possui_erros = false;

int escopo_atual = 0;

int posicao_relativa_0 = 0;
int posicao_relativa_1 = 0;
int posicao_relativa_pf = -4;

int posicao_relativa_sub = 0;
char aux_char[3];

int aux_vet_tipos[20];
int index_vet_tipos = 0;

/* tabela (pilha) de simbolos */
struct Symbol *top = NULL;


/* verifica se um simbolo esta na tabela e o retorna*/
struct Symbol *esta_na_tabela(String simbolo){
    struct Symbol *temp;
    temp = top;
    while(temp != NULL){
        if(strcmp(simbolo,temp->simbolo) == 0){
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
        if((strcmp(simbolo,temp->simbolo) == 0) && temp->infos.escopo == escopo_atual){
            return true;
        }
        temp = temp->prox;
    }
    return false;
}


void analisaPrograma(A_Programa prog, String nome_programa){
    analisaBloco(prog->bloco);

    // chamar a função de gerar o codigo MEPA aqui
}

void analisaBloco(A_Bloco bloco){
    analisaDecVars(bloco->secDecVar);
    analisaDecSubs(bloco->secDecSub);
    analisaCmdComp(bloco->cmdComp);
}

void analisaDecVars(A_LstDecVar _secDecVar){
    // mandar pra pilha todos os elementos A_lstDecVar
    A_LstDecVar secDecVar = _secDecVar;

    // secDecVar ta certo, tem só x e Y la, ja conferi

    while(secDecVar != NULL){
        top = push(
            top,
            secDecVar->decVar->id,
            "VS",
            escopo_atual,
            (escopo_atual == 0) ? posicao_relativa_0 : posicao_relativa_1,
            _NUL_I_,
            _NUL_S_,
            secDecVar->decVar->tipo,
            _NUL_S_,
            _NUL_I_,
            _NUL_I_,
            null_vet,
            0
        );

        (escopo_atual == 0) ? posicao_relativa_0++ : posicao_relativa_1++;
        secDecVar = secDecVar->prox;
    }
    //display(top); //as variaveis estao na tabela de simbolos
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
        if(strcmp(temp->simbolo,_id) == 0){
            return temp->infos.type.t_normal;
        }
        temp = temp->prox;
    }
    return _NUL_S_; // variavel não foi encontrada
}


void analisaDecSubs(A_LstDecSub _secDecSub){
    // mandar pra pilha todos os elementos A_lstDecSub
    A_LstDecSub secDecSub = _secDecSub;

    int k;

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
                        _NUL_S_,
                        param_formais->declaracao_parametros->tipo,
                        _NUL_S_,
                        _NUL_I_,
                        _NUL_I_,
                        null_vet,
                        0
                    );

                    aux_vet_tipos[index_vet_tipos] = (strcmp(param_formais->declaracao_parametros->tipo,"integer") == 0) ? 1 : 0;
                    index_vet_tipos++;

                    posicao_relativa_pf--;
                    var_param = var_param->prox;
                }

                param_formais = param_formais->prox;
            }
            /* procedimento */
            sprintf(aux_char, "%d", posicao_relativa_sub);
            top = push(
                top,
                secDecSub->decProc->_decProc_proc.id,
                "PROC",
                escopo_atual, 
                _NUL_I_,
                _NUL_I_,
                strcat(aux_char,"R"),
                _NUL_S_,
                _NUL_S_,
                num_pf(secDecSub->decProc->_decProc_proc.parametros_formais),
                0,
                aux_vet_tipos,
                index_vet_tipos
            );

            // talvez seja preciso zerar o vetor de tipos

            index_vet_tipos = 0;

            posicao_relativa_1++;
            posicao_relativa_sub++;

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
                        _NUL_S_,
                        parametros_formais->declaracao_parametros->tipo,
                        _NUL_S_,
                        _NUL_I_,
                        _NUL_I_,
                        null_vet,
                        0              
                    );

                    aux_vet_tipos[index_vet_tipos] = (strcmp(parametros_formais->declaracao_parametros->tipo,"integer") == 0) ? 1 : 0;
                    index_vet_tipos++;

                    posicao_relativa_pf--;
                    var_parametros = var_parametros->prox;
                }

                parametros_formais = parametros_formais->prox;
            }
            /* função */
            sprintf(aux_char, "%d", posicao_relativa_sub);
            top = push(
                top,
                secDecSub->decProc->_decProc_func.id,
                "FUNC",
                escopo_atual,   
                _NUL_I_,
                _NUL_I_,
                strcat(aux_char,"R"),
                _NUL_S_,
                secDecSub->decProc->_decProc_func.tipo,
                num_pf(secDecSub->decProc->_decProc_func.parametros_formais),
                0,
                aux_vet_tipos,
                index_vet_tipos
            );

            // talvez seja preciso zerar o vetor de tipos

            index_vet_tipos = 0;

            posicao_relativa_1++;
            posicao_relativa_sub++;

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

bool analisaOrdemFunc(A_ChamFunc chamFunc, struct Symbol *funcao_tabela){
    A_ListExp lista_param = chamFunc->lista_expressoes;
    int tam_vet_param = 0;

    while(lista_param != NULL){
        if(strcmp(analisaExp(lista_param->expressao),(funcao_tabela->tipos_parametros[tam_vet_param] == 1) ? "integer" : "boolean") != 0){
            return false;
        }

        tam_vet_param++;
        lista_param = lista_param->prox;
    }
    return true;
}

String analisaChamFunc(A_ChamFunc _chamFunc){
    struct Symbol *funcao = esta_na_tabela(_chamFunc->id);

    // verficar se a chamada de procedimento esta na tabela de simbolos e no escopo atual
    if((funcao != NULL) && simbolo_mesmo_escopo(_chamFunc->id)){
        // verificar se o numero de parametros na chamada equivale ao numero da declaração na pilha
        if(num_parametros(_chamFunc->lista_expressoes) == funcao->infos.type.t_sub.numero_parametros){
            // verificar se os argumentos estão na mesma ordem da declaração do procedimento (pilha)
            if(analisaOrdemFunc(_chamFunc, funcao)){
                return funcao->infos.type.t_sub.t_funcao;
            }
            else{
                fprintf(stderr, "Os argumentos passados não estão na ordem da declaração da função %s \n\n", _chamFunc->id);
                possui_erros = true;
            }
        }
        else{
            fprintf(stderr, "Número incorreto de parâmetros na função %s \n\n", _chamFunc->id);
            possui_erros = true;
        }
    }
    else{
        fprintf(stderr, "Função %s não está declarada \n\n", _chamFunc->id);
        possui_erros = true;
    }

    return _NUL_S_; // talvez isso de problema
}

String analisaFator(struct Exp_Fator exp_fator){
    struct Exp_Fator fatores = exp_fator;
    printf("\n3\n");
    printf("\ntipo exp: %d\n", (int)fatores.tipo);
    switch(fatores.tipo){
        case TF_Var:
            // codigo mepa
            return buscar_tipo_var(fatores.variavel->id);
        case TF_Num:
            printf("\nnumero: %i\n", exp_fator.num);
            // codigo mepa
            return "integer";
        case TF_Logico: 
            // codigo mepa
            return "boolean";
        case TF_ChamFunc:
            return analisaChamFunc(fatores.chamadaFuncao);
        //default:
        case TF_Exp:
            return analisaExp(fatores.expressao);
    }
}
int contiii = 1;
String analisaExp(A_Exp _expressao){
    A_Exp expressoes = _expressao;

    String tipoEsq;
    String tipoDir;

    //printf("\ntipo exp: %d\n", (int)expressoes->tipo);

    switch(expressoes->tipo){
        case TE_Fator:
            printf("\n-->%i\n", contiii);
            return analisaFator(expressoes->fator);
        case TE_Exp_Binaria:
            printf("\n->%i\n", contiii);
            printf("\nrelacao: %i\n", expressoes->binaria.relacao);     // -1 é quando é uma expressão unaria
            contiii++;
            
            tipoEsq = analisaExp(expressoes->binaria.exp_esquerda);
            printf("\ntipoEsq: %s\n\n", tipoEsq);
            tipoDir = analisaExp(expressoes->binaria.exp_direita);  // ta dando problema aqui
            // qualquer coisa feita com expressoes->binaria.exp_direita ta dando problema

            // nao chegou aqui ainda, so vai passar aqui depois da ultima recursão
            printf("\ntipoEsq: %s\n", tipoEsq);
            printf("tipoDir: %s\n", tipoDir);

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
                        possui_erros = true;
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
                        possui_erros = true;
                        return "boolean";
                    }
            }
    }
}

void analisaAtribuicao(struct A_atrib atribuicao){
    struct Symbol *simbolo = esta_na_tabela(atribuicao.id);

    //printf("Simbolo %s esta na tabela\n", simbolo->simbolo);

    String tipo_lado_esq;
    String tipo_lado_dir;

    //verficiar se o simbolo esta na tabela de simbolos e no escopo atual
    if((simbolo != NULL) && simbolo_mesmo_escopo(atribuicao.id)){      
        //verificar se o tipo dos dois lados da atribuição é o mesmo
        tipo_lado_esq = buscar_tipo_var(atribuicao.id); // ate aqui de boa
        tipo_lado_dir = analisaExp(atribuicao.expressao);
        if(strcmp(tipo_lado_esq,tipo_lado_dir) == 0){

        }
        else{
            fprintf(stderr, "Tipo %s incorreto, esperado tipo %s para %s \n\n", tipo_lado_dir, tipo_lado_esq, atribuicao.id);
            possui_erros = true;
        }
    }
    else{
        fprintf(stderr, "Simbolo %s não declarado \n\n", atribuicao.id);
        possui_erros = true;
    }
}

bool analisaOrdemProc(struct A_chamProc chamProc, struct Symbol *proc_tabela){
    A_ListExp lista_param = chamProc.lista_expressoes;
    int tam_vet_param = 0;

    while(lista_param != NULL){
        if(strcmp(analisaExp(lista_param->expressao),(proc_tabela->tipos_parametros[tam_vet_param] == 1) ? "integer" : "boolean") != 0){
            return false;
        }

        tam_vet_param++;
        lista_param = lista_param->prox;
    }
    return true;
}

void analisaChamProc(struct A_chamProc chamProc){
    struct Symbol *procedimento = esta_na_tabela(chamProc.identificador);

    // verficar se a chamada de procedimento esta na tabela de simbolos e no escopo atual
    if((procedimento != NULL) && simbolo_mesmo_escopo(chamProc.identificador)){
        // verificar se o numero de parametros na chamada equivale ao numero da declaração na pilha
        if(num_parametros(chamProc.lista_expressoes) == procedimento->infos.type.t_sub.numero_parametros){
            // verificar se os argumentos estão na mesma ordem da declaração do procedimento (pilha)
            if(analisaOrdemProc(chamProc,procedimento)){
                // codigo mepa
            }
            else{
                fprintf(stderr, "Os argumentos passados não estão na ordem da declaração do procedimento %s \n\n", chamProc.identificador);
                possui_erros = true;
            }
        }
        else{
            fprintf(stderr, "Número incorreto de parâmetros no procedimento %s \n\n", chamProc.identificador);
            possui_erros = true;
        }
    }
    else{
        fprintf(stderr, "Procedimento %s não está declarado \n\n", chamProc.identificador);
        possui_erros = true;
    }
}

void analisaCondicional(struct A_cond cond){
    //a expressão condicional deve ser valida e resultar em algum valor do tipo logico
    String tipo_exp = analisaExp(cond.expressao);
    if(strcmp(tipo_exp,"boolean") == 0){

    }
    else{
        fprintf(stderr, "Valor booleano esperado, expressão condicional resultou em %s \n\n", tipo_exp);
        possui_erros = true;
    }
}

void analisaLoop(struct A_loop loop){
    //a expressão condicional deve ser valida e resultar em algum valor do tipo logico
    String tipo_loop = analisaExp(loop.expressao);
    if(strcmp(tipo_loop,"boolean") == 0){

    }
    else{
        fprintf(stderr, "Valor booleano esperado, expressão condicional resultou em %s \n\n", tipo_loop);
        possui_erros = true;
    }
}

void analisaLeitura(struct A_read read){
    struct A_read aux_read = read;

    while(aux_read._lista_identificadores != NULL){
        if(esta_na_tabela(aux_read._lista_identificadores->id) != NULL){

        }
        else{
            fprintf(stderr, "Simbolo %s não declarado \n\n", aux_read._lista_identificadores->id);
            possui_erros = true;
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

void gerarArquivoMepa(bool _possui_erros, String nome_programa){
    if(_possui_erros){
        fprintf(stderr, "O programa %s possui erros de compilação \n\n", nome_programa);
    }
    else{
        //mandar os codigos mepa pra arquivos
    }
}