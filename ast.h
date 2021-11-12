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

A_Programa A_programa(String id, A_Bloco bloco);
A_Bloco A_bloco(A_LstDecSub secDecSub, A_LstDecVar secDecVar, A_CmdComp cmdComp);
A_Identificador A_identificador(String id);
A_ListaId A_listaId(String id, A_ListaId listaId);
A_Tipo A_tipo(A_Identificador identificador);
A_DecVar A_decVar(String id, String tipo);
A_LstDecVar A_lstDecVar(A_DecVar decVar, A_LstDecVar lstDecVar);


//expressao binaria
//A_Atrib 
//A_ChamProc
//cond
//loop
//IO
//A_CmdComp A_cmdComp(A_Cmd cmd);
//cmd
//A_BlocoSub
//A_DecParam
//A_DecParamList
//A_Decproc


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

#endif