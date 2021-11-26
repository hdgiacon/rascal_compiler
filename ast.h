#ifndef AST_H
#define AST_H

#include "util.h"

typedef struct A_Programa_ *A_Programa;
typedef struct A_Bloco_ *A_Bloco;
typedef struct A_LstDecSub_ *A_LstDecSub;
typedef struct A_LstDecVar_ *A_LstDecVar;
typedef struct A_ListaId_ *A_ListaId;
typedef struct A_DecVar_ *A_DecVar;
typedef struct A_LstDecVar_ *A_LstDecVar;
typedef struct A_Exp_ *A_Exp;
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

A_Programa A_programa(String _id, A_Bloco _bloco);
A_Bloco A_bloco(A_LstDecVar _secDecVar, A_LstDecSub _secDecSub, A_Cmd _cmdComp);
A_ListaId A_listaId(String _id, A_ListaId _listaId);
A_DecVar A_decVar(String _id, String _tipo);
A_LstDecVar A_lstDecVar(A_DecVar _decVar, A_LstDecVar _lstDecVar);

A_LstDecVar concatLstDecVar(A_LstDecVar _lst1, A_LstDecVar _lst2);

A_LstDecSub A_lstDecSub(A_DecProc _decProc, A_LstDecSub _lstDecSub);


A_Exp A_exp_fator_chamada_funcao(A_ChamFunc _chamadaFuncao);
A_Exp A_exp_fator_variavel(A_Var _variavel);
A_Exp A_exp_fator_int(int _num);
A_Exp A_exp_fator_logico(int _logico);
A_Exp A_exp_fator_expressao(A_Exp _expressao);

A_Exp A_exp_binaria(A_Exp _exp_esquerda, int _relacao, A_Exp _exp_direita);

A_ListExp A_listExp(A_Exp _expressao, A_ListExp _lista_expressoes);

A_Cmd A_cmd_atrib(A_Exp _expressao);
A_Cmd A_cmd_chamProc(String _identificador, A_ListExp _lista_expressoes);
A_Cmd A_cmd_cond(A_Exp _expressao, A_Cmd _comando_1, A_Cmd _comando_2);
A_Cmd A_cmd_loop(A_Exp _expressao, A_Cmd _comando);
A_Cmd A_cmd_read(A_ListaId _lista_identificadores);
A_Cmd A_cmd_write(A_ListExp _lista_expressoes);

A_Cmd A_cmdComp(A_Cmd _comando, A_Cmd _lista_comandos);

A_BlocoSub A_blocoSub(A_LstDecVar _secDecVar, A_Cmd _cmdComp);
A_DecParam A_decParam(A_ListaId _lista_identificadores, String _tipo);

A_DecParamList A_decParamList(A_DecParam _declaracao_parametros, A_DecParamList _lista_dec_parametros);

A_DecProc A_decProc_proc(String _id, A_DecParamList _parametros_formais, A_BlocoSub _bloco);
A_DecProc A_decProc_func(String _id, A_DecParamList _parametros_formais, A_BlocoSub _bloco, String _tipo);

A_ChamFunc A_chamFunc(String _id, A_ListExp _lista_expressoes);
A_Var A_var(String _id);


struct A_Programa_ {
    String id;
    A_Bloco bloco;
};

struct A_Bloco_ {
    A_LstDecVar secDecVar;
    A_LstDecSub secDecSub;
    A_Cmd cmdComp;
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

struct A_LstDecSub_ {
    A_DecProc decProc;
    A_LstDecSub prox;
};

enum tipo_expressao {
    TE_Fator,
    TE_Exp_Binaria
};

enum tipo_fator{
    TF_Var,
    TF_Num,
    TF_Logico,
    TF_ChamFunc,
    TF_Exp
};


struct Exp_Fator {
    enum tipo_fator tipo;
    union{
        A_Var variavel;
        int num;
        int logico;
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
        struct Exp_Binaria binaria; 
    };
};


struct A_ListExp_ {
    A_Exp expressao; 
    A_ListExp prox;
};

struct A_atrib {
    A_Exp expressao;
};

struct A_chamProc {
    String identificador; 
    A_ListExp lista_expressoes;
};

struct A_cond {
    A_Exp expressao;
    A_Cmd comando_1;
    A_Cmd comando_2;
};

struct A_loop {
    A_Exp expressao; 
    A_Cmd comando;
};

struct A_read {
    A_ListaId _lista_identificadores;
};

struct A_write {
    A_ListExp lista_expressoes;
};


struct A_cmdComp {
    A_Cmd comando; 
    A_Cmd prox;
};

enum tipo_cmd{
    TC_ATRIB,
    TC_CHAMPROC,
    TC_COND,
    TC_LOOP,
    TC_LEITURA,
    TC_ESCRITA,
    TC_CMDCOMP
};

struct A_Cmd_ {
    enum tipo_cmd tipo;
    union{
        struct A_atrib A_atrib;
        struct A_chamProc A_chamProc;
        struct A_cond A_cond;
        struct A_loop A_loop;
        struct A_read A_io_read;
        struct A_write A_io_write;
        struct A_cmdComp A_cmdComp;
    };
};


struct A_BlocoSub_ {
    A_LstDecVar secDecVar; 
    A_Cmd cmdComp;
};

struct A_DecParam_ {
    A_ListaId lista_identificadores; 
    String tipo;
};


struct A_DecParamList_ {
    A_DecParam declaracao_parametros; 
    A_DecParamList prox;
};

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
    String tipo;
};

struct A_DecProc_ {
    enum tipo_decProc tipo;
    union{
        struct DecProc_Proc _decProc_proc;
        struct DecProc_Func _decProc_func;
    };
};

struct A_ChamFunc_ {
    String id; 
    A_ListExp lista_expressoes;
};

struct A_Var_ {
    String id; 
};

#endif