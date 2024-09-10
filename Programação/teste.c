#include <stdio.h>
#include <stdlib.h>
#include <string.h>

quant = 0;

typedef struct teste{
    struct teste *proxStruct;
    int info;
} tipoTeste;

typedef struct gerenciador{
    tipoTeste *primeirostruct;
    quant;
} tipoGerenciador;

void inicializa(tipoGerenciador *iniciar){
    iniciar->primeirostruct = NULL;
}

int main(){


}