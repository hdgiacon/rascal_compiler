#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabelaSimbolos.h"

//struct symbol *top = NULL;

struct symbol *push(struct symbol *top, String _simbolo, String _categoria, int _escopo, int _pr_var_simples, int _pr_param_formal, String _pr_procedimento, String _tipo_normal, String _tipo_procedimento, int _numero_parametros, int _tipo_chamada){
    struct symbol *s_ptr = malloc(sizeof(struct symbol));
    //strcpy(s_ptr->simbolo,_simbolo);
    s_ptr->simbolo = _simbolo;
    //strcpy(s_ptr->categoria, _categoria);
    s_ptr->categoria = _categoria;
    s_ptr->infos.escopo = _escopo;
    s_ptr->infos.pr.variavel_simples = _pr_var_simples;
    s_ptr->infos.pr.parametro_formal = _pr_param_formal;
    //strcpy(s_ptr->infos.pr.procedimento, _pr_procedimento);
    s_ptr->infos.pr.procedimento = _pr_procedimento;
    //strcpy(s_ptr->infos.type.t_normal, _tipo_normal);
    s_ptr->infos.type.t_normal = _tipo_normal;
    //strcpy(s_ptr->infos.type.t_proc.t_procedimento, _tipo_procedimento);
    s_ptr->infos.type.t_proc.t_procedimento = _tipo_procedimento;
    s_ptr->infos.type.t_proc.numero_parametros = _numero_parametros;
    s_ptr->infos.type.t_proc.tipo_chamada = _tipo_chamada;
    s_ptr->prox = top;
    top = s_ptr;
    return top;
}

struct symbol *pop(struct symbol *top){
    if (top == NULL){
        printf("\n\nStack is empty ");
    }
    else{
        struct symbol *temp;
        temp = top;
        top = top->prox;
        //printf("\n\n%d deleted", temp->data);
        free(temp);
    }
    return top;
}

void display(struct symbol *top)
{
    struct symbol *temp;
    temp = top;
    while (temp != NULL)
    {
        printf("\n %s | %s | %d | %d | %d | %s | %s | %s | %d | %d \n", temp->simbolo, temp->categoria, 
                    temp->infos.escopo, temp->infos.pr.variavel_simples, temp->infos.pr.parametro_formal,
                            temp->infos.pr.procedimento, temp->infos.type.t_normal,
                                 temp->infos.type.t_proc.t_procedimento, temp->infos.type.t_proc.numero_parametros, temp->infos.type.t_proc.tipo_chamada);
        temp = temp->prox;
    }
}




//int main(){
//    top = push(top, "z","VS",0,0,1,"ac","int","as",0,0);
//    display(top);
//}