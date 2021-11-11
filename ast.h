#ifndef AST_H
#define AST_H

#include "util.h"

typedef struct A_Programa *A_Programa;
typedef struct A_Bloco *A_Bloco;
typedef struct A_LstDecSub *A_LstDecSub;
typedef struct A_LstDecVar *A_LstDecVar;
typedef struct A_CmdComp *A_CmdComp;
typedef struct A_Identificador *A_Identificador;
typedef struct A_ListaId *A_ListaId;
typedef struct A_Tipo *A_Tipo;
typedef struct A_DecVar *A_DecVar;
typedef struct A_LstDecVar *A_LstDecVar;
//exp
//exp binaria
typedef struct A_Atrib *A_Atrib;
typedef struct A_ChamProc *A_ChamProc;
typedef struct A_Cond *A_Cond;
typedef struct A_Loop *A_Loop;
typedef struct A_IO *A_IO;
typedef struct A_CmdComp *A_CmdComp;
typedef struct A_CMD *A_Cmd;
typedef struct A_BlocoSub *A_BlocoSub;
typedef struct A_DecParam *A_DecParam;
typedef struct A_DecParamList *A_DecParamList;
typedef struct A_DecProc *A_DecProc;
typedef struct A_LstDecSub *A_LstDecSub;
typedef struct A_Bloco *A_Bloco;
typedef struct A_Programa *A_Programa;
typedef struct A_ListExp *A_ListExp;
typedef struct A_ChamFunc *A_ChamFunc;
typedef struct A_Var *A_Var;
//fator
//exp simples
//termo

A_Programa A_programa(String id, A_Bloco bloco);
A_Bloco A_bloco(A_LstDecSub secDecSub, A_LstDecVar secDecVar, A_CmdComp cmdComp);
A_Identificador A_identificador(String id);
//A_ListaId A_ListaId()
A_Tipo A_tipo(A_Identificador identificador);
//A_DecVar A_decVar()
A_LstDecVar A_lstDecVar(A_DecVar decVar);
//expressao binaria
//A_Atrib 
//A_ChamProc
//cond
//loop
//IO
A_CmdComp A_cmdComp(A_Cmd cmd);
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



#endif