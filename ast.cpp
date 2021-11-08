// codigo de ast
#include "ast.h"
#include <string>
#include <iostream>
using namespace std;

// A_Exp
    // expressao expressao_simples
A_Exp::A_Exp(){

};

A_Identificador::A_Identificador(string _id){
    this->id = _id;
};

A_ListaId::A_ListaId(A_Identificador* _id_add){
    this->lista_identificadores.push_back(_id_add);
};

A_Tipo::A_Tipo(A_Identificador* _identificador){
    this->identificador = _identificador;
};

A_DecVar::A_DecVar(A_ListaId* _listaIdentificadores, A_Tipo* _tipo){
    this->listaIdentificadores = _listaIdentificadores;
    this->tipo = _tipo;
};

A_LstDecVar::A_LstDecVar(A_DecVar* _decVar){
    this->decVar = _decVar;
};


A_Exp_Binaria::A_Exp_Binaria(A_Exp* _exp_esquerda, int _relacao, A_Exp* _exp_direita){
    this->exp_direita = _exp_esquerda;
    this->relacao = _relacao;
    this->exp_direita = _exp_direita;
};

A_Exp_Binaria::A_Exp_Binaria(A_Exp* _exp_esquerda){
    this->exp_direita = _exp_esquerda;
};


A_Cmd::A_Cmd(A_Atrib* _atribuicao, A_ChamProc* _chamada_procedimento, A_Cond* _condicional, A_Loop* _repeticao, A_IO* _io, A_CmdComp* _comando_composto){
    this->atribuicao = _atribuicao;
    this->chamada_procedimento = _chamada_procedimento;
    this->condicional = _condicional;
    this->repeticao = _repeticao;
    this->io = _io;
    this->comando_composto = _comando_composto;
};

A_CmdComp::A_CmdComp(A_Cmd* _cmd){
    this->cmd = _cmd;
};

A_BlocoSub::A_BlocoSub(A_LstDecVar* _secDecVar, A_CmdComp* _cmdComp){
    this->secDecVar = _secDecVar;
    this->cmdComp = _cmdComp;
};

A_DecParamList::A_DecParamList(A_DecParam* _declaracao_parametros_add){
    this->lista_declaracao_parametros.push_back(_declaracao_parametros_add);
};


// construtor de procedimento
A_DecProc::A_DecProc(A_Identificador* _identificador, A_DecParamList* _parametros_formais, A_BlocoSub* _bloco_sub){
    this->identificador = _identificador;
    this->parametros_formais = _parametros_formais;
    this->bloco = _bloco_sub;
};

// construtor de função
A_DecProc::A_DecProc(A_Identificador* _identificador, A_DecParamList* _parametros_formais, A_BlocoSub* _bloco_sub, A_Tipo* _tipo){
    this->identificador = _identificador;
    this->parametros_formais = _parametros_formais;
    this->bloco = _bloco_sub;
    this->tipo = _tipo;
};


A_LstDecSub::A_LstDecSub(A_DecProc* _decProc){
    this->decProc = _decProc;
};

A_LstDecSub::A_LstDecSub(A_DecProc* _decFunc){
    this->decFunc = _decFunc;
};


A_Bloco::A_Bloco(A_LstDecSub* _secDecSub, A_LstDecVar* _secDecVar, A_CmdComp* _cmdComp){
    this->secDecSub = _secDecSub;
    this->secDecVar = _secDecVar;
    this->cmdComp = _cmdComp;
};

A_Programa::A_Programa(string _id, A_Bloco* _bloco){
    this->id = _id;
    this->bloco = _bloco;
};

A_DecParam::A_DecParam(A_ListaId* _lista_identificadores, A_Tipo* _tipo){
    this->lista_identificadores = _lista_identificadores;
    this->tipo = _tipo;
};
    
A_Atrib::A_Atrib(A_Exp* _expressao){
    this->expressao = _expressao;
};


A_ChamProc::A_ChamProc(A_Identificador* _identificador, A_ListExp* _lista_expressoes){
    this->identificador = _identificador;
    this->lista_expressoes = _lista_expressoes;
};

A_ChamProc::A_ChamProc(A_Identificador* _identificador){
    this->identificador = _identificador;
};


A_Cond::A_Cond(A_Exp* _expressao, A_Cmd* _comando_1, A_Cmd* _comando_2){
    this->expressao = _expressao;
    this->comando_1 = _comando_1;
    this->comando_2 = _comando_2;
};

A_Cond::A_Cond(A_Exp* _expressao, A_Cmd* _comando_1){
    this->expressao = _expressao;
    this->comando_1 = _comando_1;
}


A_Loop::A_Loop(A_Exp* _expressao, A_Cmd* _comando){
    this->expressao = _expressao;
    this->comando = _comando;
};


A_IO::A_IO(A_ListaId* _lista_identificadores){
    this->lista_identificadores = _lista_identificadores;
};

A_IO::A_IO(A_Exp_Binaria* _expressao_add){
    this->lista_expressoes.push_back(_expressao_add);
};


A_ListExp::A_ListExp(A_Exp* _expressao_add){
    this->lista_expressoes.push_back(_expressao_add);
};

A_ChamFunc::A_ChamFunc(A_Identificador* _identificador, A_ListExp* _lista_expressoes){
    this->identificador = _identificador;
    this->lista_expressoes = _lista_expressoes;
};

A_Var::A_Var(A_Identificador* _identificador, A_ChamFunc* _chamadaFuncao){
    this->identificador = _identificador;
    this->chamadaFuncao = _chamadaFuncao;
};


A_Fator::A_Fator(A_Var* _variavel){
    this->variavel = _variavel;
};

A_Fator::A_Fator(A_ChamFunc* _chamadaFuncao){
    this->chamadaFuncao = _chamadaFuncao;
}

A_Fator::A_Fator(A_Exp* _expressao){
    this->expressao = _expressao;
}


A_Exp_Simples::A_Exp_Simples(A_Exp* _exp_esquerda, int _relacao, A_Exp* _exp_direita){
    this->exp_esquerda = _exp_esquerda;
    this->relacao = _relacao;
    this->exp_direita = _exp_direita;
}

A_Termo::A_Termo(A_Exp* _exp_esquerda, int _relacao, A_Exp* _exp_direita){
    this->exp_esquerda = _exp_esquerda;
    this->relacao = _relacao;
    this->exp_direita = _exp_direita;
};

/*
int main(){
    A_Identificador teste1 = A_Identificador("a");
    cout << teste1.id;

    A_ListaId teste2 = A_ListaId(&teste1);
    cout << teste2.identificador->id;
}
*/