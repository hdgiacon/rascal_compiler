// codigo de ast

#include <string>
#include <iostream>
using namespace std;


class A_Identificador{
    public:
        string id;
        A_Identificador(string _id);
};


class A_ListaId{
    public:
        A_Identificador* identificador;
        // A_listaId lista_identificadores

        A_ListaId(A_Identificador* _identificador);
};

class A_Tipo{
    public:
        A_Identificador* identificador;

        A_Tipo(A_Identificador* _identificador);
};

class A_DecVar{
    public:
        A_ListaId* listaIdentificadores;
        A_Tipo* tipo;

        A_DecVar(A_ListaId* _listaIdentificadores, A_Tipo* _tipo);
};

class A_LstDecVar{
    public:
        A_DecVar* decVar;

        A_LstDecVar(A_DecVar* _decVar);
};

class A_Cmd{
    public:
        A_Atrib* atribuicao;
        A_ChamProc* chamada_procedimento;
        A_Cond* condicional;
        A_Loop* repeticao;
        A_IO* io;
        A_CmdComp* comando_composto;

        A_Cmd(A_Atrib* _atribuicao, A_ChamProc* _chamada_procedimento, A_Cond* _condicional, A_Loop* _repeticao, A_IO* _io, A_CmdComp* _comando_composto);
};

class A_CmdComp{
    public:
        A_Cmd* cmd;

        A_CmdComp(A_Cmd* _cmd);
};

class A_BlocoSub{
    public:
        A_LstDecVar* secDecVar;
        A_CmdComp* cmdComp;

        A_BlocoSub(A_LstDecVar* _secDecVar, A_CmdComp* _cmdComp);
};

class A_DecParamList{
    public:
        // precisa de lista

        A_DecParamList();
};

class A_DecProc{
    public:
        A_Identificador* identificador;
        A_DecParamList* parametros_formais;
        A_BlocoSub* bloco;

        A_Tipo* tipo;

        // construtor de procedimento
        A_DecProc(A_Identificador* _identificador, A_DecParamList* _parametros_formais, A_BlocoSub* _bloco);

        // construtor de função
        A_DecProc(A_Identificador* _identificador, A_DecParamList* _parametros_formais, A_BlocoSub* _bloco, A_Tipo* _tipo);
};

class A_LstDecSub{
    public:
        A_DecProc* decProc;
        A_DecProc* decFunc;

        A_LstDecSub(A_DecProc* _decProc, A_DecProc* _decFunc);
};

class A_Bloco{
    public:
        A_LstDecSub* secDecSub;
        A_LstDecVar* secDecVar;
        A_CmdComp* cmdComp;

        A_Bloco(A_LstDecSub* _secDecSub, A_LstDecVar* _secDecVar, A_CmdComp* _cmdComp);
};

class A_Programa{
    public:
        string id;
        A_Bloco* bloco;

        A_Programa(string _id, A_Bloco* _bloco);
};

class A_DecParam{
    public:
        A_ListaId* lista_identificadores;
        A_Tipo* tipo;

        A_DecParam(A_ListaId* _lista_identificadores, A_Tipo* _tipo);
};

//class A_CmdList{
//    public:
//        A_CmdList();
//};

class A_Atrib{
    public:
        A_Exp* expressao;

        A_Atrib(A_Exp* _expressao);
};

class A_ChamProc{
    public:
        A_Identificador* identificador;
        // lista expressões

        A_ChamProc(A_Identificador* _identificador);
};

class A_Exp{
    public:
        // precisa de lista

        A_Exp();
};

class A_Cond{
    public:
        A_Exp* expressao;
        A_Cmd* comando_1;
        A_Cmd* comando_2;

        // com else
        A_Cond(A_Exp* _expressao, A_Cmd* _comando_1, A_Cmd* _comando_2);

        // sem else
        A_Cond(A_Exp* _expressao, A_Cmd* _comando_1);
};

class A_Loop{
    public:
        A_Exp* expressao;
        A_Cmd* comando;

        A_Loop(A_Exp* _expressao, A_Cmd* _comando);
};

class A_IO{
    public:
        // lista de identificações
        // lista de expressoes

        A_IO();
};

class A_ListExp{
    public:
        A_Exp* expressao;
        //lista_expressoes

        A_ListExp(A_Exp* _expressao);
};

class A_ChamFunc{
    public:
        A_Identificador* identificador;

        A_ChamFunc(A_Identificador* _identificador);
};

class A_Var{
    public:
        A_Identificador* identificador;
        A_ChamFunc* chamadaFuncao;

        A_Var(A_Identificador* _identificador, A_ChamFunc* _chamadaFuncao);
};

class A_Fator{
    public:
        A_Var* variavel;
        A_ChamFunc* chamadaFuncao;
        A_Exp* expressao;

        A_Fator(A_Var* _variavel, A_ChamFunc* _chamadaFuncao, A_Exp* _expressao);
};

class A_ListTermo{
    A_Fator* fator;
    //precisa de lista

    A_ListTermo(A_Fator* _fator);
};

class A_Termo{
    A_Fator* fator;
    //precisa de lista

    A_Termo(A_Fator* _fator);
};