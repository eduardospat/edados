#ifndef LISTA_H
#define LISTA_H
#include "arvore.h"

typedef struct arvore Arvore;

typedef struct lista{
    int cpf;
    char nome[50];
    int salario;

    Arvore* cod_Filial;

    struct lista* prox;
} Lista;

void preencher_Dados_Lista(Lista** lista, Arvore** raiz);
Lista* buscar_Dado_CPF(Lista* lista, int cpf);
Lista* remover_Dado_Codigo(Lista** lista, int codigo);
Lista* remover_Dado_CPF(Lista** lista, int cpf);
void imprimir_Dados_Lista(Lista* lista);
#endif // LISTA_H

