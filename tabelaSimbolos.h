#ifndef STACK_H
#define STACK_H

#include "util.h"

struct posicao_relativa{
    int variavel_simples;   
    int parametro_formal;   
    String procedimento;   
};

struct tipo_proc{
    String t_procedimento;
    int tipo_chamada;    // 1 = parametro ou 0 = referencia
    int numero_parametros;
};

struct tipo{
    String t_normal;  // vs, pf
    struct tipo_proc t_proc;
};

struct info{
    int escopo;
    struct posicao_relativa pr;
    struct tipo type;
};

struct symbol{
    String simbolo;
    String categoria;  // VS, PF, PROC
    struct info infos;
    struct symbol *prox;
};

    
struct symbol *push(struct symbol *top, String _simbolo, String _categoria, int _escopo, int _pr_var_simples,
            int _pr_param_formal, String _pr_procedimento, 
                String _tipo_normal, String _tipo_procedimento, int _numero_parametros, int _tipo_chamada);

struct symbol *pop(struct symbol *top);

void display(struct symbol *top);


#endif