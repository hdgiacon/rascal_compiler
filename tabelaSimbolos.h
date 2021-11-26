#ifndef STACK_H
#define STACK_H


struct posicao_relativa{
    int variavel_simples;   
    int parametro_formal;   
    char procedimento[10];   
};

struct tipo_proc{
    char t_procedimento[10];
    int tipo_chamada;    // 1 = parametro ou 0 = referencia
    int numero_parametros;
};

struct tipo{
    char t_normal[10];  // vs, pf
    struct tipo_proc t_proc;
};

struct info{
    int escopo;
    struct posicao_relativa pr;
    struct tipo type;
};

struct symbol{
    char simbolo[10];
    char categoria[10];  // VS, PF, PROC
    struct info infos;
    struct symbol *prox;
};

    
void push(struct symbol *top,char _simbolo[], char _categoria[], int _escopo, int _pr_var_simples,
             int _pr_param_formal, char _pr_procedimento[], 
                char _tipo_normal[], char _tipo_procedimento[], int _numero_parametros, int _tipo_chamada);
void pop(struct symbol *top);
void display(struct symbol *top);


#endif