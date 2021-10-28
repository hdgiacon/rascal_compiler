// codigo de ast
#include "ast.h"
#include <string>
#include <iostream>
using namespace std;

A_Identificador::A_Identificador(string _id){
    this->id = _id;
};


// A_ListaId
    // lista_identificadores
A_ListaId::A_ListaId(A_Identificador* _identificador){
    this->identificador = _identificador;
};

/*
int main(){
    A_Identificador teste1("a");
    cout << teste1.identificador;

    A_ListaId teste2(teste1("b"));
    cout << teste2.identificador.id;
}
*/


// A_tipo
    // tipo
A_Tipo::A_Tipo(A_Identificador* _identificador){
    this->identificador = _identificador;
};


// A_DecVar
    // declaracao_variaveis
A_DecVar::A_DecVar(A_ListaId* _listaIdentificadores, A_Tipo* _tipo){
    this->listaIdentificadores = _listaIdentificadores;
    this->tipo = _tipo;
};


A_LstDecVar::A_LstDecVar(A_DecVar* _decVar){
    this->decVar = _decVar;
};


// A_Cmd        //aqui chama outras classes implementadas
    // comando
A_Cmd::A_Cmd(){

};


A_CmdComp::A_CmdComp(A_Cmd* _cmd){
    this->cmd = _cmd;
};


A_BlocoSub::A_BlocoSub(A_LstDecVar* _secDecVar, A_CmdComp* _cmdComp){
    this->secDecVar = _secDecVar;
    this->cmdComp = _cmdComp;
};


// A_DecParamList   //isso ta chegando em declaração de parametros, que ja esta feito
    // parametros_formais
A_DecParamList::A_DecParamList(){
  //por hora vazia  
};


// A_DecProc
    // declaracao_procedimento declaracao_funcao
A_DecProc::A_DecProc(A_Identificador* _identificador, A_DecParamList* _parametros_formais, A_BlocoSub* _bloco){
    // construtor de procedimento
    this->identificador = _identificador;
    this->parametros_formais = _parametros_formais;
    this->bloco = _bloco;
};

A_DecProc::A_DecProc(A_Identificador* _identificador, A_DecParamList* _parametros_formais, A_BlocoSub* _bloco, A_Tipo* _tipo){
    // construtor de função
    this->identificador = _identificador;
    this->parametros_formais = _parametros_formais;
    this->bloco = _bloco;
    this->tipo = _tipo;
};


A_LstDecSub::A_LstDecSub(A_DecProc* _decProc, A_DecProc* _decFunc){
    this->decProc = _decProc;
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


// A_DecParam
    // declaracao_parametros

A_DecParam::A_DecParam(A_ListaId* _lista_identificadores, A_Tipo* _tipo){
    this->lista_identificadores = _lista_identificadores;
    this->tipo = _tipo;
};
    

// A_CmdList    // mesma coisa aqui
    // comando_rec
A_CmdList::A_CmdList(){

};


// A_Atrib      // chama atribuição
    // atribuicao
A_Atrib::A_Atrib(){

};


// A_ChamProc       // chamada de procedimento op precisa ser criada uma classe?
    // chamada_procedimento
A_ChamProc::A_ChamProc(){

};


// A_Exp
    // expressao expressao_simples
A_Exp::A_Exp(){

};


// A_Cond
    // condicional
A_Cond::A_Cond(A_Exp* _expressao, A_Cmd* _comando_1, A_Cmd* _comando_2){
    this->expressao = _expressao;
    this->comando_1 = _comando_1;
    this->comando_2 = _comando_2;
};

A_Cond::A_Cond(A_Exp* _expressao, A_Cmd* _comando_1){
    this->expressao = _expressao;
    this->comando_1 = _comando_1;
}


// A_Loop
    // repeticao

A_Loop::A_Loop(A_Exp* _expressao, A_Cmd* _comando){
    this->expressao = _expressao;
    this->comando = _comando;
};


// A_IO
    // leitura escrita
A_IO::A_IO(){

};


// A_ListExp
    // lista_expressoes
A_ListExp::A_ListExp(A_Exp* _expressao){
    this->expressao = _expressao;
};


// A_ChamFunc
    // chamada_funcao
A_ChamFunc::A_ChamFunc(A_Identificador* _identificador){
    this->identificador = _identificador;
};


// A_Var
    // variavel
A_Var::A_Var(A_Identificador* _identificador, A_ChamFunc* _chamadaFuncao){
    this->identificador = _identificador;
    this->chamadaFuncao = _chamadaFuncao;
};


// A_Fator
    // fator
A_Fator::A_Fator(A_Var* _variavel, A_ChamFunc* _chamadaFuncao, A_Exp* _expressao){
    this->variavel = _variavel;
    this->chamadaFuncao = _chamadaFuncao;
    this->expressao = _expressao;
    //fator
};


// A_ListTermo
    // termo_rec
A_ListTermo::A_ListTermo(A_Fator* _fator){
    this->fator = _fator;
};


// A_Termo
    // termo
A_Termo::A_Termo(A_Fator* _fator){
    this->fator = _fator;
};
