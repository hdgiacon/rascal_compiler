#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct posicao_relativa{
    int variavel_simples;   
    int parametro_formal;   
    char procedimento[4];   
};

struct tipo_proc{
    char t_procedimento[4];
    int tipo_chamada;    // 1 = parametro ou 0 = referencia
    int numero_parametros;
};

struct tipo{
    char t_normal[4];  // vs, pf
    struct tipo_proc t_proc;
};

struct info{
    int escopo;
    struct posicao_relativa pr;
    struct tipo type;
};

struct symbol{
    char simbolo;
    char categoria[5];  // VS, PF, PROC
    struct info infos;

    struct symbol *prox;
};

struct symbol *top = NULL;

void push(int);
void pop();

/*
int main(){
    int n, ch;

    do{
        printf("\n\nStack Menu\n1. Push \n2. Pop\n3. Display\n0. Exit");
        printf("\nEnter Choice 0-3? : ");
        scanf("%d", &ch);
        switch (ch){
            case 1:
                printf("\nEnter number ");
                scanf("%d", &n);
                push(n);
                break;
            case 2:
                pop();
                break;
        }
    } while (ch != 0);
}
*/

void push(char _simbolo, char _categoria, int _escopo, int _pr_var_simples, int _pr_param_formal, char _pr_procedimento, int _tipo_normal, char _tipo_procedimento){
    struct symbol *s_ptr = malloc(sizeof(struct symbol));
    s_ptr->simbolo = _simbolo;
    s_ptr->categoria = _categoria;  // str_cpy
    s_ptr->infos.escopo = _escopo;
    s_ptr->infos.pr.variavel_simples = _pr_var_simples;
    s_ptr->infos.pr.parametro_formal = _pr_param_formal;
    s_ptr->infos.pr.procedimento = _pr_procedimento;    // str_cpy
    s_ptr->infos.type.t_normal = _tipo_normal;
    s_ptr->infos.type.t_proc = _tipo_procedimento;  // str_cpy

    s_ptr->prox = top;
    top = s_ptr;
}

void pop(){
    if (top == NULL){
        printf("\n\nStack is empty ");
    }
    else{
        struct node *temp;
        temp = top;
        top = top->next;
        printf("\n\n%d deleted", temp->data);
        free(temp);
    }
}