#ifndef PILHA_H 
#define PILHA_H
#define capacidade 4

typedef struct{
    int n; // Numero de elementos na pilha
    int processos[capacidade][4];
} pilha_Processos;

pilha_Processos* pilha_Cria(void);
void inserir_Dados_Pilha(pilha_Processos* pp, int id, int t_Cheg, int t_Exec, int status);
void mostrar_Dados_Pilha(pilha_Processos* pp);
void esvaziar_Pilha(pilha_Processos* pp);
 
#endif
