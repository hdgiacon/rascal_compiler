#ifndef STACK_H
#define STACK_H

#include "util.h"

struct posicao_relativa{
    int variavel_simples;   
    int parametro_formal;   
    String subrotina;   
};

struct tipo_sub{
    String t_funcao;        // procedimento nao tem tipo
    int tipo_chamada;       // 1 = parametro ou 0 = referencia
    int numero_parametros;
};

struct tipo{
    String t_normal;  // vs, pf
    struct tipo_sub t_sub;
};

struct info{
    int escopo;
    struct posicao_relativa pr;
    struct tipo type;
};

struct Symbol{
    String simbolo;
    String categoria;  // VS, PF, PROC, FUNC
    struct info infos;
    struct Symbol *prox;
};

    
struct Symbol *push(struct Symbol *top, String _simbolo, String _categoria, int _escopo, int _pr_var_simples,
            int _pr_param_formal, String _pr_subrotina, 
                String _tipo_normal, String _tipo_procedimento, int _numero_parametros, int _tipo_chamada);

struct Symbol *pop(struct Symbol *top);

void display(struct Symbol *top);


#endif