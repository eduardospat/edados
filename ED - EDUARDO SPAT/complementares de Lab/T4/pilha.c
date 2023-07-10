#include "pilha.h"
#include "fila.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

pilha_Processos* pilha_Cria(void){
    pilha_Processos* pp = (pilha_Processos*) malloc(sizeof(pilha_Processos)); // Aloca mem?ria para a pilha

    if(pp == NULL){
        printf("[ERRO] Memoria insuficiente!\n");
    }

    pp->n = 0; // Inicializa o n?mero de elementos da pilha

    return pp;
}

void inserir_Dados_Pilha(pilha_Processos* pp, int id, int t_Cheg, int t_Exec, int status){
    if(pp->n == capacidade){
        printf("[ERRO] Pilha cheia!\n");
    }
    
    // Insere os dados na pilha
    pp->processos[pp->n ][0] = id; 
    pp->processos[pp->n][1] = t_Cheg;
    pp->processos[pp->n][2] = t_Exec;
    pp->processos[pp->n][3] = status;

    pp->n++; // Incrementa o numero de elementos da pilha
}

void mostrar_Dados_Pilha(pilha_Processos* pp){
    int i;

	printf("\n------------------ Pilha com usuarios -----------------------\n");

    if (pp->n == 0){
        printf("\nPILHA USUARIOS VAZIA!\n");
    }

    for(i = pp->n-1; i >= 0; i--){
        printf("ID: P%d\n", pp->processos[i][0]);
        printf("Tempo de chegada: %d\n", pp->processos[i][1]);
        printf("Tempo de execucao: %d\n", pp->processos[i][2]);
        printf("Status: Usuario\n");
        
        printf("\n---------------------------------------------\n");
    }
}

void esvaziar_Pilha(pilha_Processos* pp){
    if(pp->n == 0){
        printf("[ERRO] Pilha de usuarios vazia!");
        system("pause");
        system("cls");
    }
    
    pp->n = 0;
}
