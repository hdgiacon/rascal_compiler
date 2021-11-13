#ifndef AST_H
#define AST_H

#include "util.h"

typedef struct A_Programa_ *A_Programa;
typedef struct A_Bloco_ *A_Bloco;
typedef struct A_LstDecSub_ *A_LstDecSub;
typedef struct A_LstDecVar_ *A_LstDecVar;
typedef struct A_CmdComp_ *A_CmdComp;
typedef struct A_Identificador_ *A_Identificador;
typedef struct A_ListaId_ *A_ListaId;
typedef struct A_Tipo_ *A_Tipo;
typedef struct A_DecVar_ *A_DecVar;
typedef struct A_LstDecVar_ *A_LstDecVar;
//exp
typedef struct A_Exp *A_Exp;
//exp binaria
typedef struct A_Atrib_ *A_Atrib;
typedef struct A_ChamProc_ *A_ChamProc;
typedef struct A_Cond_ *A_Cond;
typedef struct A_Loop_ *A_Loop;
typedef struct A_IO_ *A_IO;
typedef struct A_CmdComp_ *A_CmdComp;
typedef struct A_CMD_ *A_Cmd;
typedef struct A_BlocoSub_ *A_BlocoSub;
typedef struct A_DecParam_ *A_DecParam;
typedef struct A_DecParamList_ *A_DecParamList;
typedef struct A_DecProc_ *A_DecProc;
typedef struct A_LstDecSub_ *A_LstDecSub;
typedef struct A_Bloco_ *A_Bloco;
typedef struct A_Programa_ *A_Programa;
typedef struct A_ListExp_ *A_ListExp;
typedef struct A_ChamFunc_ *A_ChamFunc;
typedef struct A_Var_ *A_Var;
//fator
//exp simples
//termo

A_Programa A_programa(String _id, A_Bloco _bloco);
A_Bloco A_bloco(A_LstDecSub _secDecSub, A_LstDecVar _secDecVar, A_CmdComp _cmdComp);
A_Identificador A_identificador(String _id);
A_ListaId A_listaId(String _id, A_ListaId _listaId);
A_Tipo A_tipo(A_Identificador _identificador);
A_DecVar A_decVar(String _id, String _tipo);
A_LstDecVar A_lstDecVar(A_DecVar _decVar, A_LstDecVar _lstDecVar);

// precisa de typedef aqui?
A_Exp A_exp_fator_chamada_funcao(A_ChamFunc _chamadaFuncao);
A_Exp A_exp_fator_variavel(A_Var _variavel);
A_Exp A_exp_fator_expressao(A_Exp _expressao);

A_Exp A_exp_binaria(A_Exp _exp_esquerda, int _relacao, A_Exp _exp_direita);


A_Atrib A_atrib(A_Exp _expressao);
A_ChamProc A_chamProc(A_Identificador _identificador, A_ListExp _lista_expressoes);

// ta certo isso? precisa de typedef aqui?
A_Cond A_cond_c(A_Exp expressao, A_Cmd comando_1, A_Cmd comando_2);
A_Cond A_cond_s(A_Exp expressao, A_Cmd comando_1);

A_Loop A_loop(A_Exp _expressao, A_Cmd _comando);

//A_IO A_io() //mesmo esquema do fator

//A_CmdComp A_cmdComp(A_Cmd* cmd);    //lista de comandos?

//A_Cmd A_cmd();    //vai ser esquema igual do fator, um pra cada

A_BlocoSub A_blocoSub(A_LstDecVar _secDecVar, A_CmdComp _cmdComp);
A_DecParam A_decParam(A_ListaId _lista_identificadores, A_Tipo _tipo);

//A_DecParamList A_decParamList();    //esquema de lista

//A_DecProc A_decProc();  //esquema do fator


struct A_Programa {
    String id;
    A_Bloco bloco;
};

struct A_Bloco {
    A_LstDecSub secDecSub;
    A_LstDecVar secDecVar;
    A_CmdComp cmdComp;
};

struct A_ListaId{
    String id;
    A_listaId prox;
};

struct A_DecVar{
    String id;
    String tipo;
};

struct A_LstDecVar{
    A_DecVar decVar;
    A_LstDecVar prox;
};

struct A_Atrib{
    A_Exp expressao;
};

struct A_ChamProc{
    A_Identificador identificador; 
    A_ListExp lista_expressoes;
};

struct A_Loop{
    A_Exp expressao; 
    A_Cmd comando;
};



/* abstrata */
struct A_Exp{

};


// struct A_Fator{
//     struct A_Exp super;
//     A_Var variavel;
//     A_ChamFunc chamadaFuncao;
//     struct A_Exp expressao;
// };


enum tipo_expressao{
    TE_Fator,
    //TE_Exp_Simples,
    //TE_Termo,
    TE_Exp_Binaria
};

enum tipo_fator{
    TF_Var,
    TF_ChamFunc,
    TF_Exp
};


struct Exp_Fator {
    enum tipo_fator tipo;
    union{
        A_Var variavel;
        A_ChamFunc chamadaFuncao;
        A_Exp expressao;
    };  
};

struct Exp_Binaria{
    A_Exp exp_esquerda;
    int relacao;
    A_Exp exp_direita;
};

struct A_Exp{
    enum tipo_expressao tipo;
    union {
        struct Exp_Fator fator;
        struct Exp_Binaria binaria; //serve pra exp simples e termo

        //struct Exp_Binaria simples; // so vai usar um campo (exp unaria)
        //struct Exp_Binaria termo;
    };
};


// ta certo isso?
enum tipo_cond{
    TI_Sem_Else;
    TI_Com_else;
};

struct Cond_C_Else{
    A_Exp expressao;
    A_Cmd comando_1;
    A_Cmd comando_2;
};

struct Cond_S_Else{
    A_Exp expressao;
    A_Cmd comando_1;
};

struct A_Cond{
    enum tipo_if tipo;
    union{
        struct Cond_C_Else _cond_c_else;
        struct Cond_S_Else _cond_s_else;
    };
};


#endif