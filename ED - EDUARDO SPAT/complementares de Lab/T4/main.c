#include "pilha.h"
#include "pilhaAux.h"
#include "fila.h"
#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define capacidade 4

void processar_Fila(fila_Processos* fp, pilha_Auxiliar* pa, int t_Padrao){
    int id, t_Cheg, t_Exec, status;

    while(fp->quantidade > 0){
        if(fp->processos[fp->inicio][2] > t_Padrao){
            fp->processos[fp->inicio][2] -= t_Padrao;
			
			printf("Processo P%d realizado por %d segundos, tempo restante: %d\n",fp->processos[fp->inicio][0], t_Padrao, fp->processos[fp->inicio][2]);
			
            id = fp->processos[fp->inicio][0];
            t_Cheg = fp->processos[fp->inicio][1];
            t_Exec = fp->processos[fp->inicio][2];
            status = fp->processos[fp->inicio][3];
            remover_Dado_Fila(fp);

            inserir_Dados_Fila(fp, id, t_Cheg, t_Exec, status);
        } else {
            id = fp->processos[fp->inicio][0];
            t_Cheg = fp->processos[fp->inicio][1];
            t_Exec = fp->processos[fp->inicio][2];
            status = fp->processos[fp->inicio][3];
            remover_Dado_Fila(fp);
            // processo "id" realizado por "tempo de execucao" com sucesso
            printf("Processo P%d realizado por %ds com sucesso!\n", fp->processos[fp->inicio][0], fp->processos[fp->inicio][2]);
        }

        system("pause");
        system("cls");
    }
}

void inicializa_Funcoes(fila_Processos* fila, pilha_Processos* pilha, pilha_Auxiliar* pilhaAux, int t_Padrao){ // Inicializa as funcoes
    int i;
    int teste = 0;

    for(i = 0; i < capacidade; i++){
    	system("cls");
    	
    	printf("-------------------- Cadastro de processos ------------------------\n");
        digitar_Dados(fila, t_Padrao);
    }

    teste = verifica_Existe_Sistema(fila);
    //ordenar_Fila(fila);

    if(teste == 1){
    	system("cls");
        printf("[AVISO] Existe um processo de sistema na fila, ele sera executado primeiramente!\n");
        system("pause");
		system("cls");
    
        enviar_Usuarios_Pilha(fila, pilha);
        enviar_Sistema_PilhaAux(fila, pilhaAux);
        
        esvaziar_Fila(fila);
        enviar_Sistema_Fila(fila, pilhaAux);
        esvaziar_PilhaAux(pilhaAux);

        mostrar_Dados_Pilha(pilha);
        system("pause");
        system("cls");

        processar_Fila(fila, pilhaAux, t_Padrao);
        system("pause");
        system("cls");
    
    }

    enviar_Usuario_Fila(fila, pilha);
    esvaziar_Pilha(pilha);
    mostrar_Dados_Pilha(pilha);
    system("pause");
    system("cls");

    processar_Fila(fila, pilhaAux, t_Padrao);
    system("pause");
    system("cls");

    printf("[AVISO] Todos os processos foram executados com sucesso!\n");
}

int main(){
    int t_Padrao;

    fila_Processos* fila = fila_Cria();
    pilha_Processos* pilha = pilha_Cria();
    pilha_Auxiliar* pilhaAux = pilhaAux_Cria();

    printf("Digite o tempo padrao: ");
    scanf("%d", &t_Padrao);

    inicializa_Funcoes(fila, pilha, pilhaAux, t_Padrao);
}
