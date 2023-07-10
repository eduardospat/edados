#include "pilhaAux.h"
#include <stdio.h>
#include <stdlib.h>

pilha_Auxiliar* pilhaAux_Cria(void){
    pilha_Auxiliar* pa = (pilha_Auxiliar*) malloc(sizeof(pilha_Auxiliar)); // Aloca memoria para a pilha

    if(pa == NULL){
        printf("[ERRO] Memoria insuficiente!\n");
    }

    pa->n = 0; // Inicializa o numero de elementos da pilha

    return pa;
}

void inserir_Dados_PilhaAux(pilha_Auxiliar* pa, int id, int t_Cheg, int t_Exec, int status){
    if(pa->n == capacidade){
        printf("[ERRO] Pilha cheia!\n");
    }
    
    // Insere os dados na pilha
    pa->processos[pa->n ][0] = id; 
    pa->processos[pa->n][1] = t_Cheg;
    pa->processos[pa->n][2] = t_Exec;
    pa->processos[pa->n][3] = status;

    pa->n++; // Incrementa o numero de elementos da pilha
}

void esvaziar_PilhaAux(pilha_Auxiliar* pa){
    if(pa->n == 0){
        printf("[ERRO] Pilha de sistemas vazia!");
        system("pause");
        system("cls");
    }
    
    pa->n = 0; // Zera o numero de elementos da pilha
}

void mostrar_Dados_PilhaAux(pilha_Auxiliar* pa){
    int i;
    
    printf("\n------------------ Pilha com sistemas -----------------------\n");

    for(i = pa->n-1; i >= 0; i--){
        printf("ID: P%d\n", pa->processos[i][0]);
        printf("Tempo de chegada: %d\n", pa->processos[i][1]);
        printf("Tempo de execucao: %d\n", pa->processos[i][2]);
        
        if(pa->processos[i][3] == 1){
            printf("Status: Sistema\n");
        } else if(pa->processos[i][3] == 2){
            printf("Status: Usuario\n");
        }
        printf("\n---------------------------------------------------------\n");
        
    }
}
