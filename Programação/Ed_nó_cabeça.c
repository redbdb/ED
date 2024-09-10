#include <stdio.h>
#include <stdlib.h>

typedef struct no{
int dado;
struct no *proxNo;
}tipoNo;

typedef struct listaGerenciada{
  tipoNo *inicio;
  tipoNo *fim;
  int quant;
  }tipoLista;

void inicializa(tipoLista *lista){
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->quant = 0;
}

int insereListaVazia(tipoLista *lista, int valor){
    tipoNo *novoNo = (tipoNo*) malloc(sizeof(tipoNo));
    if(novoNo == NULL)
        return 0;
    novoNo->dado = valor;
    novoNo->proxNo = NULL;
    lista->inicio = novoNo;
    lista->fim = novoNo;
    lista->quant++;
    return 1;
}

int insereNaFrente(tipoLista *lista, int valor){
    tipoNo *novoNo;
    if(lista->inicio == NULL)
        insereListaVazia(lista ,valor);
    else{
        novoNo = (tipoNo*)malloc(sizeof(tipoNo));
        if(novoNo==NULL)
            return 0;
        novoNo->dado = valor;
        novoNo->proxNo = lista->inicio;
        lista->inicio = novoNo; 
        lista->quant++;  
    }
    return 1;
}

int exibeLista(tipoLista *lista){
    tipoNo *atual;  
    if(lista->inicio == NULL)
        return 0;
    atual = lista->inicio;
    printf("\nLista encadeada: ");
    while(atual !=NULL){
        printf("%8d",atual->dado);
        atual = atual->proxNo;
    }
    return 1;
}

int DestroiLista(tipoLista *lista){
    tipoNo *atual, *prox;
    atual = lista->inicio;
    prox = lista->inicio->proxNo;
    do{
        free(atual);
        atual = prox;
        prox = prox->proxNo;
    } while (atual!=NULL);
    return 0;
}

int DestroiInicio(tipoLista *lista){
    tipoNo *var;
    if(lista->inicio == NULL){
        return 1;
    }
    var = lista->inicio;
    lista->inicio = lista->inicio->proxNo;
    free(var);
    lista->quant--;
    return 0;
}

int DestroiFim(tipoLista *lista){
    lista->fim = lista->inicio;
    int i;
    for( i = 2; i < lista->quant; i++){
        lista->fim = lista->fim->proxNo;
    }
    free(lista->fim->proxNo);
    lista->fim->proxNo = NULL;
    lista->quant--;
    return 0;
}

int ProcuraIndice(tipoLista *lista, int valor){
    tipoNo *atual = lista->inicio;
    int indice = 0;
    while (indice < lista->quant && atual->dado!=valor){
        atual = atual->proxNo;
        indice++;
    }
    return indice;
}

int DestroiIndice(tipoLista *lista, int indice){
    tipoNo *anterior, *excluido;
    int i;
    if(lista->inicio==NULL)
        return 0;    
    if(indice == 0)
        DestroiInicio(lista);
    else if (indice == lista->quant - 1)
        DestroiFim(lista);
    else{
        anterior = lista->inicio;
        excluido = anterior->proxNo;
        for(i = 1; i < indice; i++){
            anterior = anterior->proxNo;
            excluido = excluido->proxNo;    
        }
        anterior->proxNo = excluido->proxNo;
        free(excluido);
        lista->quant--;
    }
    return 0;
}

int InsereIndice(tipoLista *lista, int indice, int valor){
    tipoNo *NovoNo, *atual;
    NovoNo = (tipoNo*)malloc(sizeof(tipoNo));
    int i;
    if(indice > lista->quant+1){
        printf("Indice invalido \n");
        return 0;
    }
    if(indice == 0)
        insereNaFrente(lista, valor);
    else if(indice == lista->quant){
        lista->fim->proxNo = NovoNo;
        NovoNo->proxNo = NULL;
        NovoNo->dado = valor;
        lista->fim = lista->fim->proxNo;
        lista->quant++;
    } else{
        atual = lista->inicio;
        for(i = 0; i < indice-1; i++){
            atual = atual->proxNo;
        }
        NovoNo->dado = valor;
        NovoNo->proxNo = atual->proxNo;
        atual->proxNo = NovoNo;
        lista->quant++;
    }
    return 0;
}

int main(){
    tipoLista lista;
    inicializa(&lista);
    int leitor, op, busca;
    do {
        printf("\n 1 - Insere elemento \n 2 - Exibe lista \n 3 - Destroi valor no inicio \n 4 - Destroi valor no fim \n 5 - Procurar indice de valor \n 6 - Destroi valor no indice dado \n 7 - Insere em indice dado \n 8 - Destruir lista e encerrar \n");
        scanf("%d", &op);
        switch (op){
            case 1:
                printf("Digite um elemento: ");
                scanf("%d",&leitor);
                int resp = insereNaFrente(&lista, leitor);
                if(!resp)
                    printf("Memoria nao alocada!");
                printf("Elemento guardado: %d",lista.inicio->dado);
            break;

            case 2: 
                exibeLista(&lista);
            break;

            case 3:
                DestroiInicio(&lista);
            break;

            case 4:
                DestroiFim(&lista);
            break;

            case 5:
                printf("\nInsira o valor procurado: \n");
                scanf("%d", &busca);
                printf("\nO indice de %d eh %d\n", busca, ProcuraIndice(&lista, busca));
            break;

            case 6:
                printf("\n Insira o indice a ser excluido: \n");
                scanf("%d", &busca);
                DestroiIndice(&lista, busca);
                printf("\nValor excluido\n");
            break;

            case 7:
                printf("Digite um elemento: ");
                scanf("%d",&leitor);
                printf("\n Insira o indice a ser inserido: \n");
                scanf("%d", &busca);
                InsereIndice(&lista, busca, leitor);
                printf("\nValor inserido\n");
            break;

            case 8:
                DestroiLista(&lista);
            break;

            default:
                printf("\n Valor invalido \n");
            break;
        }
    } while (op!=8);
return 0;
}