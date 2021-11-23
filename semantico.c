#include "semantico.h"

void analisaPrograma(A_programa prog){
    //instalar simbolo na tabela de simbolos
    analisaBloco();
}

void analisaBloco(A_Bloco bloco){
    analisaDecVars(bloco->secDecVar);
    analisaDecSubs(bloco->secDecSub);
    analisaCmdComp(bloco->cmdComp);
}

void analisaCmdComp(A_LstCmd comandos){
    A_Cmd comando = comandos;
    while(comando != NULL){
        switch(comando.categoria){
            case CMD_IF:
                analisaCondicional(comando);
                break;
        }
    }
}