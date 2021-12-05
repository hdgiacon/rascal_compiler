#include <stdio.h>
#include <stdlib.h>
#include "tabelaSimbolos.h"

//struct Symbol *top = NULL;
// adicionar um parametro pra lista de tipos dos parametros
/* adiciona na tabela de simbolos */
struct Symbol *push(struct Symbol *top, String _simbolo, String _categoria, int _escopo, int _pr_var_simples, int _pr_param_formal, String _pr_subrotina, String _tipo_normal, String _tipo_funcao, int _numero_parametros, int _tipo_chamada, int _tipos_parametros[], int tam_list){
    struct Symbol *s_ptr = malloc(sizeof(struct Symbol));
    int k;

    s_ptr->simbolo = _simbolo;
    s_ptr->categoria = _categoria;
    s_ptr->infos.escopo = _escopo;
    s_ptr->infos.pr.variavel_simples = _pr_var_simples;
    s_ptr->infos.pr.parametro_formal = _pr_param_formal;
    s_ptr->infos.pr.subrotina = _pr_subrotina;
    s_ptr->infos.type.t_normal = _tipo_normal;
    s_ptr->infos.type.t_sub.t_funcao = _tipo_funcao;
    s_ptr->infos.type.t_sub.numero_parametros = _numero_parametros;
    s_ptr->infos.type.t_sub.tipo_chamada = _tipo_chamada;
    
    for(k=0;k<tam_list;k++){
        s_ptr->tipos_parametros[k] = _tipos_parametros[k];      // 1 = integer, 0 = boolean
    }

    s_ptr->tam_list_param = tam_list;
    s_ptr->prox = top;
    top = s_ptr;
    return top;
}

/* remove da tabela de simbolos */
struct Symbol *pop(struct Symbol *top){
    if (top == NULL){
        printf("\n\nStack is empty ");
    }
    else{
        struct Symbol *temp;
        temp = top;
        top = top->prox;
        free(temp);
    }
    return top;
}

/* mostra a tabela de simbolos */
void display(struct Symbol *top){
    struct Symbol *temp;
    temp = top;
    while (temp != NULL){
        printf("\n %s | %s | %d | %d | %d | %s | %s | %s | %d | %d | $ | %d | \n", temp->simbolo, temp->categoria, 
                    temp->infos.escopo, temp->infos.pr.variavel_simples, temp->infos.pr.parametro_formal,
                            temp->infos.pr.subrotina, temp->infos.type.t_normal,
                                temp->infos.type.t_sub.t_funcao, temp->infos.type.t_sub.numero_parametros, 
                                    temp->infos.type.t_sub.tipo_chamada, temp->tam_list_param);
        temp = temp->prox;
    }
    printf("\n\n");
}



/*
int main(){
    top = push(top, "z","VS",0,0,1,"ac","int","as",0,0);
    top = push(top, "z","VS",0,0,1,"ac","int","as",0,0);
    top = pop(top);
    top = push(top, "z","VS",0,0,1,"ac","int","as",0,0);
    top = pop(top);
    top = push(top, "z","VS",0,0,1,"ac","int","as",0,0);
    display(top);
}
*/