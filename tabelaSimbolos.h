#ifndef STACK_H
#define STACK_H

typedef struct posicao_relativa_ *posicao_relativa;
typedef struct tipo_proc_ *tipo_proc;
typedef struct tipo_ *tipo;
typedef struct info_ *info;
typedef struct symbol_ *symbol;



struct posicao_relativa_{
    int variavel_simples;   
    int parametro_formal;   
    char procedimento[4];   
};

struct tipo_proc_{
    char t_procedimento[4];
    int tipo_chamada;    // 1 = parametro ou 0 = referencia
    int numero_parametros;
};

struct tipo_{
    char t_normal[4];  // vs, pf
    tipo_proc t_proc;
};

struct info_{
    int escopo;
    posicao_relativa pr;
    tipo type;
};

struct symbol_{
    char simbolo;
    char categoria[5];  // VS, PF, PROC
    info infos;
    symbol *prox;
};

    
void push(char _simbolo, char _categoria[], int _escopo, int _pr_var_simples,
             int _pr_param_formal, char _pr_procedimento[], 
                char _tipo_normal[], char _tipo_procedimento[]);
void pop();


#endif