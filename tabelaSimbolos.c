#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabelaSimbolos.h"


symbol *top = NULL;

void push(char _simbolo, char _categoria[], int _escopo, int _pr_var_simples, int _pr_param_formal, char _pr_procedimento[], char _tipo_normal[], char _tipo_procedimento[]){
    symbol *s_ptr = malloc(sizeof(symbol));
    s_ptr->simbolo = _simbolo;
    strcpy(s_ptr->categoria, _categoria);
    //s_ptr->categoria = _categoria;  // str_cpy
    s_ptr->infos.escopo = _escopo;
    s_ptr->infos.pr.variavel_simples = _pr_var_simples;
    s_ptr->infos.pr.parametro_formal = _pr_param_formal;
    strcpy(s_ptr->infos.pr.procedimento, _pr_procedimento);
    //s_ptr->infos.pr.procedimento = _pr_procedimento;    // str_cpy
    s_ptr->infos.type.t_normal = _tipo_normal;
    strcpy(s_ptr->infos.type.t_proc, _tipo_procedimento);
    //s_ptr->infos.type.t_proc = _tipo_procedimento;  // str_cpy

    s_ptr->prox = top;
    top = s_ptr;
}

void pop(){
    if (top == NULL){
        printf("\n\nStack is empty ");
    }
    else{
        symbol *temp;
        temp = top;
        top = top->prox;
        //printf("\n\n%d deleted", temp->data);
        free(temp);
    }
}

void display()
{
    symbol *temp;
    temp = top;
    while (temp != NULL)
    {
        printf("\n %c | %s | %d | %d | %d | %s | %s | %s | \n", temp->symbol, temp->categoria, 
                    temp->infos.escopo, temp->infos.pr.variavel_simples, temp->infos.pr.parametro_formal,
                            temp->infos.pr.procedimento, temp->infos.type.t_normal,
                                 temp->infos.type.t_proc);
        temp = temp->prox;
    }
}




int main(){
    push('z',"VS",0,0,NULL,NULL,"int",NULL);
    display();
}