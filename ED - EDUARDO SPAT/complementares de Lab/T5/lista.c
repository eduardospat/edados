#include "arvore.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void preencher_Dados_Lista(Lista** lista, Arvore** raiz){ // Funcao para preencher os dados da lista
    if(raiz == NULL){ // Arvore vazia
        printf("[ERRO] Nao existem filiais castradas, nao e possivel cadastrar um funcionario!\n");
        system("pause");
        return;
    } else {
        Lista* novo = (Lista*) malloc (sizeof(Lista));
        if(novo == NULL){
            printf("[ERRO] Memoria insuficiente!\n");
            return;
			system("pause");
        }

        Arvore* aux;
        int cpf;
        char nome[50];
        int salario;
        int codigo;

        printf ("Digite o CPF do funcionario: ");
        scanf ("%d", &cpf);

        setbuf(stdin, NULL);
        printf ("Digite o nome do funcionario: ");
        fgets (nome, 50, stdin);
        nome[strcspn(nome, "\n")] = '\0';

        printf ("Digite o salario do funcionario: ");
        scanf ("%d", &salario);

        printf("Digite o codigo da empresa do funcionario: ");
        scanf("%d", &codigo);

        aux = buscar_Codigo_Arvore(*raiz, codigo);

        if(aux == NULL){
            printf("[ERRO] Codigo nao encontrado!\n");
            system("pause");
            return;
        } else {
            novo->cod_Filial = aux;
        }

        novo->cpf = cpf;
        strcpy(novo->nome, nome);
        novo->salario = salario;

        novo->prox = *lista;
        *lista = novo;

        system("cls");
        printf("[AVISO] Dados inseridos com sucesso na lista!\n");
        system("pause");
    }
}   

Lista* remover_Dado_Codigo(Lista** lista, int codigo){ // Funcao que remove um dado da lista pelo codigo da filial desfeita
    Lista* aux;
    Lista* remover = NULL;

    if (*lista == NULL) {
        printf("[ERRO] Lista vazia!\n");
        return NULL;
    } else {
        if ((*lista)->cod_Filial->codigo == codigo) { // Se o codigo da filial for igual ao codigo da filial desfeita
            remover = *lista;
            *lista = remover->prox;
            free(remover); // Liberar memoria do funcionario demitido

        } else {
            aux = *lista;
            while (aux->prox != NULL && aux->prox->cod_Filial->codigo != codigo) {
                aux = aux->prox;
            }
            if (aux->prox == NULL) {
                return NULL;
            } else {
                remover = aux->prox;
                aux->prox = remover->prox;
                free(remover); // Liberar memoria do funcionario demitido
            }
        }
    }
    return remover;
}

Lista* remover_Dado_CPF(Lista** lista, int cpf) {
    Lista* aux;
    Lista* remover = NULL;

    if (*lista == NULL) {
        printf("[ERRO] Lista vazia!\n");
        return NULL;
    } else {
        if ((*lista)->cpf == cpf) {
            remover = *lista;
            *lista = remover->prox;
            free(remover); // Liberar mem�ria do funcion�rio demitido
        } else {
            aux = *lista;
            while (aux->prox != NULL && aux->prox->cpf != cpf) {
                aux = aux->prox;
            }
            if (aux->prox == NULL) {
                printf("[ERRO] CPF nao encontrado!\n");
                return NULL;
            } else {
                remover = aux->prox;
                aux->prox = remover->prox;
                free(remover); // Liberar mem�ria do funcion�rio demitido
            }
        }
    }

    return remover;
}

void imprimir_Dados_Lista(Lista* lista){
    const Lista* aux = lista;

    if(aux == NULL){
        printf("[ERRO] Lista vazia!\n");

    }else{
        printf("     Funcionarios cadastrados:\n");

        while(aux != NULL){ 
            printf("--------------------------------------------------------\n");
            printf("CPF: %d\n", aux->cpf);
            printf("Nome: %s\n", aux->nome);
            printf("Salario: %d\n", aux->salario);
            printf("Nome da empresa que esta vinculado: %s\n", aux->cod_Filial->razaoSocial);

            aux = aux->prox;
        }
    }
}


