#ifndef PILHAAUX_H 
#define PILHAAUX_H
#define capacidade 4

typedef struct{
    int n; // Numero de elementos na pilha
    int processos[capacidade][4];
} pilha_Auxiliar;

pilha_Auxiliar* pilhaAux_Cria(void);
void inserir_Dados_PilhaAux(pilha_Auxiliar* pa, int id, int t_Cheg, int t_Exec, int status);
void esvaziar_PilhaAux(pilha_Auxiliar* pa);
void mostrar_Dados_PilhaAux(pilha_Auxiliar* pa);
 
#endif
