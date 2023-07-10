#ifndef ARVORE_H
#define ARVORE_H
#include "lista.h"

typedef struct lista Lista;

typedef struct arvore{
    int codigo;
    char razaoSocial[50];
    char endereco[50];

    struct arvore* esq;
    struct arvore* dir;
} Arvore;

Arvore* buscar_Codigo_Arvore(Arvore* raiz, int codigo);
Arvore* inserir_Dados_Arvore(Arvore* raiz, int codigo, char razaoSocial[50], char endereco[50]);
Arvore* remover_Dado_Arvore(Arvore** raiz, int codigo);
void imprimir_Dados_Arvore(Arvore* raiz);

#endif // ARVORE_H

