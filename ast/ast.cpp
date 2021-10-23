// codigo de ast

#include <string>


class A_Programa{
    public:
        string id;
        A_Bloco bloco;

        A_Programa(string _id, A_Bloco _bloco){
            id = _id;
            bloco = _bloco;
        }


};


class A_Bloco{
    public:
        A_LstDecSub secDecSub;
        A_LstDecVar secDecVar;
        A_CmdComp cmdComp;

        A_Bloco(A_LstDecSub _secDecSub, A_LstDecVar _secDecVar, A_CmdComp _cmdComp){
            secDecSub = _secDecSub;
            secDecVar = _secDecVar;
            cmdComp = _cmdComp;
        }
};


class A_LstDecSub{
    public:
        A_DecProc decProc;
        A_DecProc decFunc;

        A_LstDecSub(A_DecProc _decProc, A_DecProc _decFunc){
            decProc = _decProc;
            decFunc = _decFunc;
        }
};


class A_LstDecVar{
    public:
        A_DecVar decVar;

        A_LstDecVar(A_DecVar _decVar){
            decVar = _decVar;
        }
};


class A_CmdComp{
    public:
        A_Cmd cmd;

        A_CmdComp(A_Cmd _cmd){
            cmd = _cmd;
        }
};


// A_DecVar
    // declaracao_variaveis

class A_decVar{
    public:
        A_listaId listaIdentificadores;
        A_tipo tipo;

        A_decVar(A_listaId _listaIdentificadores, A_tipo _tipo){
            listaIdentificadores = _listaIdentificadores;
            tipo = _tipo;
        }

};

// A_ListaId
    // lista_identificadores

class A_listaId{
    public:
        A_identificador indentificador;
        // A_listaId lista_identificadores

        a_listaId(A_identificador _indentificador){
            identificador = _identificador;

        }

};

// A_tipo
    // tipo

class A_tipo{
    public:
        A_identificador identificador;

        A_tipo(A_identificador _identificador){
            identificador = _identificador;
        }
};

// A_DecProc
    // declaracao_procedimento declaracao_funcao

// A_DecParam
    // declaracao_parametros
    

// A_DecParamList
    // parametros_formais


// A_Cmd
    // comando


// A_CmdList
    // comando_rec


// A_Atrib
    // atribuicao


// A_ChamProc
    // chamada_procedimento


// A_Cond
    // condicional


// A_Loop
    // repeticao


// A_IO
    // leitura escrita


// A_ListExp
    // lista_expressoes


// A_Exp
    // expressao expressao_simples


// A_ListTermo
    // termo_rec


// A_Termo
    // termo


// A_Fator
    // fator


// A_Var
    // variavel


// A_ChamFunc
    // chamada_funcao

