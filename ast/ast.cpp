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
class A_IO{

};

// A_ListExp
    // lista_expressoes

class A_ListExp{
    A_Exp expressao;
    //lista_expressoes

    A_ListExp(A_Exp _expressao){
        expressao = _expressao;
    }

};


// A_Exp
    // expressao expressao_simples
class A_Exp{

};


// A_ListTermo
    // termo_rec

class A_ListTermo{
    A_Fator fator;
    //termo_rec

    A_ListTermo(A_Fator _fator){
        fator = _fator;
        //termo rec
    }
};
// A_Termo
    // termo

class A_Termo{
    A_Fator fator;
    //termo_rec

    A_Termo(A_Fator _fator){
        fator = _fator;
    }
};

// A_Fator
    // fator
class A_Fator{
    public:
        A_Var variavel;
        A_ChamFunc chamadaFuncao;
        A_Exp expressao;
        //fator

        A_Fator(A_Var _variavel, A_ChamFunc _chamadaFuncao, A_Exp _expressao){
            variavel = _variavel;
            chamadaFuncao = _chamadaFuncao;
            expressao = _expressao;
            //fator
        }

};



// A_Var
    // variavel
class A_Var{
    public:
        A_identificador identificador;
        A_ChamFunc chamadaFuncao;


        A_Var(A_identificador _identificador, A_ChamFunc _chamadaFuncao){
            identificador = _identificador;
            chamadaFuncao = _chamadaFuncao;
        }

};


// A_ChamFunc
    // chamada_funcao
class A_ChamFunc{
    public:
        A_identificador identificador;

        A_ChamFunc(A_identificador _identificador){
            identificador = _identificador;
        }

};


class A_identificador{
    public:
        string identificador;

        A_identificador(string _identificador){
            identificador = _identificador;
        }

};
