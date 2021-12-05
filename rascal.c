#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "semantico.h"
#include "bison.tab.h"

A_Programa absyn_root;

/* Compilar:
   $ make
   
   Executar:
   $ ./compilador arquivo.ras
*/

int main(int argc, char** argv){
    FILE* fp;
    extern FILE* yyin;

    String nome_prog = argv[0]; // nome do arquivo pra passar no fopen

    // antes de dar make verificar os imports, ver se tem repetido

    if(argc < 2 || argc > 2){
        fprintf(stderr, "Erro: número inválido de parâmetros\n");
        fprintf(stderr, "Uso: compilador <arquivo>\n");
        return EXIT_FAILURE;
    }

    fp = fopen(argv[1], "r");
    if(fp == NULL){
        printf("Erro: não foi possível ler o arquivo '%s'\n", argv[1]);
        return EXIT_FAILURE;
    }

    yyin = fp;
    if(yyparse() == 0){
        fprintf(stderr, "\nSucesso sintatico!\n\n");
        
        analisaPrograma(absyn_root, nome_prog);
    } 
    else{
        fprintf(stderr, "\nAnálise com erros sintaticos!");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}