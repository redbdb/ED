#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//programa recebe senhas de uma fila, o operador pode adicionar mais senhas na fila, atender aproxima senha e exibir a fila de senhas. o máximo da fila foi predefinido para 20
int Max = 20, Inicio = 0, Fim = 0;

void insere(int Array[Max], int Var){
    printf("\nSenha %d inserida a fila", Var);
    Array[Fim++ % Max] = Var;
}

void remover(int Array[Max]){
    printf("\nChamando senha numero %d", Array[Inicio%Max]);
    Inicio++;
}

void exibe(int Array[Max]){
    int i;
    if(Inicio == Fim){
        printf("\nFila vazia");
        return;
    }
    printf("\nSenhas em espera: ");
    for(i = Inicio; i != Fim; i++){
        printf("\n%d ", Array[i%Max]);
    }
}

int main(){
    int Senhas[Max], op = 1, var;
    printf("-----Fila de senhas-----");
    while(op != 4){
        printf("\n1 - Inserir nova senha na fila \n2 - Chamar proxima senha \n3 - Exibir fila \n4 - Encerrar\n");
        scanf("%d", &op);
        switch (op){
            case 1:
                if(Inicio%Max == Fim%Max && Inicio != Fim){
                    printf("Fila cheia");
                break;
                }
                printf("\nDigite a senha inserida na fila: ");
                scanf("%d", &var);
                insere(Senhas, var);
            break;
    
            case 2:
            if(Inicio == Fim){
                printf("Fila vazia.");
                break;
            }
                remover(Senhas);
            break;

            case 3:
                exibe(Senhas);
            break;

            case 4:
            break;

            default:
                printf("\nOperador invalido.");
            break;
        }
    }
    return 0;
}