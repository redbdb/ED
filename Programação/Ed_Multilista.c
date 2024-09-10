#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aluno{
    char Nome[25];
    char ID[5];
    struct aluno *ProxAluno;
}tipoAluno;

typedef struct dis{
    char Materia[25];
    char ID[4];
    int quant;
    struct dis *ProxDis;
    struct aluno *Aluno;
}tipoDisciplina;

typedef struct gerenciador{//struct "cabeca" para gerenciamento
    tipoDisciplina *inicio;
    int quant;
}tipoEntrada;

void inicializa(tipoEntrada *gerenciador){
    gerenciador->inicio = NULL;
    gerenciador->quant = 0; 
}

int criarDisciplina(tipoEntrada *gerenciador, char disciplina[25], char id[4]){
    tipoDisciplina *novaDisciplina = (tipoDisciplina*)malloc(sizeof(tipoDisciplina));
    if(novaDisciplina == NULL)
        return 0;
    if(gerenciador->inicio == NULL){
        gerenciador->inicio = novaDisciplina;
        novaDisciplina->ProxDis = NULL;
    } else{
        novaDisciplina->ProxDis = gerenciador->inicio;
        gerenciador->inicio = novaDisciplina;
        novaDisciplina->Aluno = NULL;
    }
    strcpy(novaDisciplina->Materia, disciplina);
    strcpy(novaDisciplina->ID, id);
    novaDisciplina->Aluno = NULL;
    gerenciador->quant++;
    gerenciador->inicio->quant = 0;
    return 1;
}

int matricularAluno(tipoEntrada *gerenciador, char iddisciplina[4], char nome[25], char idaluno[5]){
    tipoAluno *novoAluno = (tipoAluno*)malloc(sizeof(tipoAluno));
    tipoDisciplina *Atual = gerenciador->inicio;
    if(novoAluno == NULL)
        return 0;
    while(strcmp(Atual->ID, iddisciplina) != 0){
        if(Atual->ProxDis == NULL){
            printf("\nNao existe disciplina com esse id.");
            return 0;
        }
        Atual = Atual->ProxDis;
    }
    if(Atual->Aluno == NULL){
        novoAluno->ProxAluno = NULL;
    }else{
        novoAluno->ProxAluno = Atual->Aluno;
        Atual->Aluno = novoAluno;
    }
    Atual->Aluno = novoAluno;
    strcpy(novoAluno->ID, idaluno);
    strcpy(novoAluno->Nome, nome);
    Atual->quant++;
    return 1;
}

int exibeDisciplinas(tipoEntrada *gerenciador){
    if(gerenciador->inicio == NULL){
        printf("\nNão existem disciplinas registradas.");
        return 0;
    }
    tipoDisciplina *AtualDisciplina = gerenciador->inicio;
    tipoAluno *AtualAluno = AtualDisciplina->Aluno;
    printf("Lista de disciplinas: \n");
    do{
        printf("%s - %s ------- quantidade de alunos: %d\n", AtualDisciplina->ID, AtualDisciplina->Materia, AtualDisciplina->quant);
        while(AtualAluno != NULL){
            printf("--->%s - %s\n", AtualAluno->ID, AtualAluno->Nome);
            AtualAluno = AtualAluno->ProxAluno;
        }
        AtualDisciplina = AtualDisciplina->ProxDis;
    }while(AtualDisciplina != NULL);
    return 1;
}

int removerAluno(tipoEntrada *gerenciador, char idaluno[5], char iddisciplina[4]){
    tipoDisciplina *AtualDisciplina = gerenciador->inicio;
    tipoAluno *AtualAluno, *AnteriorAluno;
    while (strcmp(iddisciplina,AtualDisciplina->ID) != 0 ){
        if(AtualDisciplina->ProxDis == NULL){
            printf("\nNão existem disciplinas com esse ID.");
            return 0;
        }
        AtualDisciplina = AtualDisciplina->ProxDis;
    }
    AnteriorAluno = AtualDisciplina->Aluno;
    if(strcmp(idaluno, AnteriorAluno->ID) == 0){
        AtualDisciplina->Aluno = AnteriorAluno->ProxAluno;
        free(AnteriorAluno);
    }else{
        if(AnteriorAluno->ProxAluno == NULL){
            printf("\nNão existe aluno com esse ID.");
            return 0;
        }
        AtualAluno = AnteriorAluno->ProxAluno;
        while(strcmp(AtualAluno->ID,idaluno) != 0){
            if(AtualAluno->ProxAluno == NULL){
                printf("\nNão existe aluno com esse ID.");
                return 0;
            }
            AtualAluno = AtualAluno->ProxAluno;
            AnteriorAluno = AnteriorAluno->ProxAluno;
        }
        AnteriorAluno->ProxAluno = AtualAluno->ProxAluno;
        free(AtualAluno);
    }
    AtualDisciplina->quant--;
    return 1;
}

int main(){
    tipoEntrada Gerenciador;
    inicializa(&Gerenciador);
    int op;
    char Nome[25];
    char IDDisciplina[4];
    char IDAluno[5];
    do{
        printf("\n1 - Criar disciplina \n2 - Matricular aluno \n3 - Remover aluno \n4 - Lista de disciplinas \n5 - encerrar\n");
        scanf("%d", &op);
        switch (op){
            case 1:
                printf("\nInsira o nome da disciplina a ser inserida: ");
                scanf("%s", Nome);
                printf("\nInsira o ID da disciplina a ser inserida(3 digitos): ");
                scanf("%s", IDDisciplina);
                criarDisciplina(&Gerenciador, Nome, IDDisciplina);
                break;

            case 2:
                if (Gerenciador.inicio == NULL){
                    printf("\nNão existem disciplinas para matricular alunos.");
                    break;
                }
                printf("\nInsira o nome do aluno matriculado: ");
                scanf("%s", Nome);
                printf("\nInsira o ID do aluno a ser matriculado(4 digitos): ");
                scanf("%s",IDAluno);
                printf("\nInsira o ID da disciplina em que o aluno será matriculado(3 digitos): ");
                scanf("%s", IDDisciplina);
                matricularAluno(&Gerenciador, IDDisciplina, Nome, IDAluno);
                break;

            case 3:
            if (Gerenciador.inicio == NULL){
                    printf("\nNão existem disciplinas para remover alunos.");
                    break;
                }
                printf("\nInsira o ID do aluno a ser removido(4 digitos): ");
                scanf("%s", IDAluno);
                printf("\nInsira o ID da disciplina em que o aluno será removido(3 digitos): ");
                scanf("%s", IDDisciplina);
                removerAluno(&Gerenciador, IDAluno, IDDisciplina);
                break;

            case 4:
                exibeDisciplinas(&Gerenciador);
                break;

            case 5:
                break;
                
            default:
                printf("\noperador invalido.");
                break;
        }
    }while(op!=5);
    return 0;
}