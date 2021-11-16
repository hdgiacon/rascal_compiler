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
typedef struct A_Exp_ *A_Exp;
//exp binaria
typedef struct A_Atrib_ *A_Atrib;
typedef struct A_ChamProc_ *A_ChamProc;
typedef struct A_Cond_ *A_Cond;
typedef struct A_Loop_ *A_Loop;
typedef struct A_IO_ *A_IO;
typedef struct A_CmdComp_ *A_CmdComp;
typedef struct A_Cmd_ *A_Cmd;
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
A_Bloco A_bloco(A_LstDecVar _secDecVar, A_LstDecSub _secDecSub, A_CmdComp _cmdComp);
A_Identificador A_identificador(String _id);
A_ListaId A_listaId(String _id, A_ListaId _listaId);
A_Tipo A_tipo(A_Identificador _identificador);
A_DecVar A_decVar(String _id, String _tipo);
A_LstDecVar A_lstDecVar(A_DecVar _decVar, A_LstDecVar _lstDecVar);

A_LstDecVar concatLstDecVar(A_LstDecVar _lst1, A_LstDecVar _lst2);


A_Exp A_exp_fator_chamada_funcao(A_ChamFunc _chamadaFuncao);
A_Exp A_exp_fator_variavel(A_Var _variavel);
A_Exp A_exp_fator_expressao(A_Exp _expressao);

A_Exp A_exp_binaria(A_Exp _exp_esquerda, int _relacao, A_Exp _exp_direita);


// lista de expressoes
A_ListExp A_listExp(A_Exp _expressao, A_ListExp _lista_expressoes);


A_Atrib A_atrib(A_Exp _expressao);
A_ChamProc A_chamProc(A_Identificador _identificador, A_ListExp _lista_expressoes);

// ta certo isso?
A_Cond A_cond_c(A_Exp _expressao, A_Cmd _comando_1, A_Cmd _comando_2);
A_Cond A_cond_s(A_Exp _expressao, A_Cmd _comando_1);

A_Loop A_loop(A_Exp _expressao, A_Cmd _comando);

// ta certo isso?
A_IO A_io_read(A_ListaId _lista_identificadores);
A_IO A_io_write(A_ListExp _lista_expressoes);

// lista de comandos
A_CmdComp A_cmdComp(A_Cmd _comando, A_CmdComp _lista_comandos);

//A_Cmd A_cmd();    //vai ser esquema igual do fator? um pra cada

A_BlocoSub A_blocoSub(A_LstDecVar _secDecVar, A_CmdComp _cmdComp);
A_DecParam A_decParam(A_ListaId _lista_identificadores, A_Tipo _tipo);

// lista de declaração de parametros
A_DecParamList A_decParamList(A_DecParam _declaracao_parametros, A_DecParamList _lista_dec_parametros);

// ta certo isso?
A_DecProc A_decProc_proc(String _id, A_DecParamList _parametros_formais, A_BlocoSub _bloco);
A_DecProc A_decProc_func(String _id, A_DecParamList _parametros_formais, A_BlocoSub _bloco, A_Tipo _tipo);


struct A_Programa_ {
    String id;
    A_Bloco bloco;
};

struct A_Bloco_ {
    A_LstDecVar secDecVar;
    A_LstDecSub secDecSub;
    A_CmdComp cmdComp;
};

struct A_ListaId_ {
    String id;
    A_ListaId prox;
};

struct A_DecVar_ {
    String id;
    String tipo;
};

struct A_LstDecVar_ {
    A_DecVar decVar;
    A_LstDecVar prox;
};

struct A_Atrib_ {
    A_Exp expressao;
};

struct A_ChamProc_ {
    A_Identificador identificador; 
    A_ListExp lista_expressoes;
};

struct A_Loop_ {
    A_Exp expressao; 
    A_Cmd comando;
};



/* abstrata */
//struct A_Exp{

//};


// struct A_Fator{
//     struct A_Exp super;
//     A_Var variavel;
//     A_ChamFunc chamadaFuncao;
//     struct A_Exp expressao;
// };


enum tipo_expressao {
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

struct Exp_Binaria {
    A_Exp exp_esquerda;
    int relacao;
    A_Exp exp_direita;
};

struct A_Exp_ {
    enum tipo_expressao tipo;
    union {
        struct Exp_Fator fator;
        struct Exp_Binaria binaria; //serve pra exp simples e termo

        //struct Exp_Binaria simples; // so vai usar um campo (exp unaria)
        //struct Exp_Binaria termo;
    };
};


struct A_ListExp_ {
    A_Exp expressao; 
    A_ListExp prox;
};


// ta certo isso?
enum tipo_cond{
    TC_Sem_Else,
    TC_Com_else
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

struct A_Cond_ {
    enum tipo_cond tipo;
    union{
        struct Cond_C_Else _cond_c_else;
        struct Cond_S_Else _cond_s_else;
    };
};


// ta certo isso?
enum tipo_io{
    TI_READ,
    TI_WRITE
};

struct IO_Read{
    A_ListaId _lista_identificadores;
};

struct IO_Write{
    A_ListExp lista_expressoes;
};

struct A_IO_ {
    enum tipo_io tipo;
    union{
        struct IO_Read _io_read;
        struct IO_Write _io_write;
    };
};


struct A_CmdComp_ {
    A_Cmd comando; 
    A_CmdComp prox;
};

struct A_BlocoSub_ {
    A_LstDecVar secDecVar; 
    A_CmdComp cmdComp;
};

struct A_DecParam_ {
    A_ListaId lista_identificadores; 
    A_Tipo tipo;
};


struct A_DecParamList_ {
    A_DecParam declaracao_parametros; 
    A_DecParamList prox;
};


// ta certo isso?
enum tipo_decProc{
    TD_PROC,
    TD_FUNC
};

struct DecProc_Proc{
    String id;
    A_DecParamList parametros_formais; 
    A_BlocoSub bloco;
};

struct DecProc_Func{
    String id; 
    A_DecParamList parametros_formais; 
    A_BlocoSub bloco; 
    A_Tipo tipo;
};

struct A_DecProc_ {
    enum tipo_decProc tipo;
    union{
        struct DecProc_Proc _decProc_proc;
        struct DecProc_Func _decProc_func;
    };
};

#endif