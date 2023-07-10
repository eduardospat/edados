#ifndef FILA_H
#define FILA_H
#include "pilha.h"
#define capacidade 4

typedef struct{
    int processos[capacidade][4];
    int inicio;
    int quantidade;
} fila_Processos;

void ordenar_Fila(fila_Processos* fp);

fila_Processos* fila_Cria(void);
void inserir_Dados_Fila(fila_Processos* fp, int id, int t_Cheg, int t_Exec, int status);
void mostrar_Dados_Fila(fila_Processos* fp);
void esvaziar_Fila(fila_Processos* fp);
int* remover_Dados_Fila(fila_Processos* fp);

#endif
