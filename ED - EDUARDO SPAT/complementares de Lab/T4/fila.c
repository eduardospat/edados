#include "pilha.h"
#include "fila.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void ordenar_Fila(fila_Processos* fp){ // Ordena a fila de acordo com o tempo de chegada
    int i, j, aux[capacidade];

    for(i = 0; i < capacidade; i++){
        for(j = i + 1; j < capacidade; j++){
            if(fp->processos[i][1] > fp->processos[j][1]){ // Compara o tempo de chegada
                aux[0] = fp->processos[i][0];
                aux[1] = fp->processos[i][1];
                aux[2] = fp->processos[i][2];
                aux[3] = fp->processos[i][3];

                fp->processos[i][0] = fp->processos[j][0];
                fp->processos[i][1] = fp->processos[j][1];
                fp->processos[i][2] = fp->processos[j][2];
                fp->processos[i][3] = fp->processos[j][3];

                fp->processos[j][0] = aux[0];
                fp->processos[j][1] = aux[1];
                fp->processos[j][2] = aux[2];
                fp->processos[j][3] = aux[3];
            }
        }
    }
}

fila_Processos* fila_Cria(void){ // Cria a fila
    fila_Processos* fp = (fila_Processos*) malloc(sizeof(fila_Processos));

    if(fp == NULL){
        printf("[ERRO] Memoria insuficiente!\n");
    }

    fp->quantidade = 0; // Inicializa o n?mero de elementos da fila
    fp->inicio = 0; // Inicializa o in?cio da fila

    return fp;
}

void inserir_Dados_Fila(fila_Processos* fp, int id, int t_Cheg, int t_Exec, int status){ // Insere os dados na fila
    if(fp->quantidade == capacidade){
        printf("[ERRO] Fila cheia!\n");
    }

    int posicao = (fp->inicio + fp->quantidade) % capacidade; // Calcula a posicao do elemento na fila

    fp->processos[posicao][0] = id;
    fp->processos[posicao][1] = t_Cheg;
    fp->processos[posicao][2] = t_Exec;
    fp->processos[posicao][3] = status;

    fp->quantidade++;
}

void mostrar_Dados_Fila(fila_Processos* fp){ // Mostra os dados da fila
    int i;	
    
    if(fp->quantidade == 0){
		printf("[ERRO] Fila vazia!");
		system("pause");
		system("cls");
	}
	
	printf("\n------------------ Fila com processos -----------------------\n");
    
	for(i = fp->inicio; i < fp->quantidade; i++){ // Percorre a fila
        printf("ID: P%d\n", fp->processos[i][0]);
        printf("Tempo de chegada: %d\n", fp->processos[i][1]);
        printf("Tempo de execucao: %d\n", fp->processos[i][2]);
        if(fp->processos[i][3] == 1){
            printf("Status: Sistema\n");
        } else if(fp->processos[i][3] == 2){
            printf("Status: Usuario\n");
        }
        printf("\n-----------------------------------------------\n");
    }
}

void esvaziar_Fila(fila_Processos* fp){ // Esvazia a fila
	if(fp->quantidade == 0){
		printf("[ERRO] Fila vazia!");
		system("pause");
		system("cls");
	}
	
	fp->inicio = 0;
	fp->quantidade = 0;
}

int* remover_Dado_Fila(fila_Processos* fp){ // Remove um dado da fila
    if(fp->quantidade == 0){
        printf("[ERRO] Fila vazia!\n");
    }

    int* aux = (int*) malloc(4 * sizeof(int)); // Aloca memoria para o vetor auxiliar

    if(aux == NULL){
        printf("[ERRO] Memoria insuficiente!\n");
    }

    aux[0] = fp->processos[fp->inicio][0];
    aux[1] = fp->processos[fp->inicio][1];
    aux[2] = fp->processos[fp->inicio][2];
    aux[3] = fp->processos[fp->inicio][3];

    fp->inicio = (fp->inicio + 1) % capacidade; // Calcula o novo inicio da fila
    fp->quantidade--; // Decrementa o numero de elementos da fila

    return aux;
}
