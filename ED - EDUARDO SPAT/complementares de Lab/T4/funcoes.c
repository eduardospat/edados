#include "funcoes.h"
#include "pilha.h"
#include "pilhaAux.h"
#include "fila.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void enviar_Usuario_Fila(fila_Processos* fp, pilha_Processos* pilha){ // Envia os processos de usuario para a fila
    int i = 0;
    int id, t_Cheg, t_Exec;
    
    
    for(i = 0; i < capacidade; i++){
        if(pilha->processos[i][3] == 2){ // Se o processo for de usuario, envia para a fila
        	id = pilha->processos[i][0];
        	t_Cheg = pilha->processos[i][1];
        	t_Exec = pilha->processos[i][2]; 
        	
            inserir_Dados_Fila(fp, id, t_Cheg, t_Exec, 2); // Insere os dados na fila
        }
    }
}

void enviar_Sistema_Fila(fila_Processos* fp, pilha_Auxiliar* pilhaAux){ // Envia os processos de sistema para a fila
    int i = 0;
    int id, t_Cheg, t_Exec;
    
    
    for(i = 0; i < capacidade; i++){
        if(pilhaAux->processos[i][3] == 1){ // Se o processo for de sistema, envia para a fila
        	id = pilhaAux->processos[i][0];
        	t_Cheg = pilhaAux->processos[i][1];
        	t_Exec = pilhaAux->processos[i][2]; 
        	
            inserir_Dados_Fila(fp, id, t_Cheg, t_Exec, 1); // Insere os dados na fila
        }
    }
}

int verifica_Existe_Sistema(fila_Processos* fila){ // Verifica se existe um processo de sistema na fila
    int i, teste = 0;
    
    for(i = 0; i < capacidade; i++){
        if(fila->processos[i][3] == 1){ // Se existir um processo de sistema na fila, retorna 1
            teste = 1;

            break;
        }
    }
    return teste;
}

void enviar_Usuarios_Pilha(fila_Processos* fila, pilha_Processos* pilha){ // Envia os processos de usu?rio para a pilha
    int i = 0;
    int id, t_Cheg, t_Exec;
    
    
    for(i = 0; i < capacidade; i++){
        if(fila->processos[i][3] == 2){ // Se o processo for de usuario, envia para a pilha
        	id = fila->processos[i][0];
        	t_Cheg = fila->processos[i][1];
        	t_Exec = fila->processos[i][2]; 
        	
            inserir_Dados_Pilha(pilha, id, t_Cheg, t_Exec, 2); // Insere os dados na pilha
        }
    }
}

void enviar_Sistema_PilhaAux(fila_Processos* fila, pilha_Auxiliar* pilhaAux){ // Envia os processos de sistema para a pilha
    int i = 0;
    int id, t_Cheg, t_Exec;
    
    
    for(i = 0; i < capacidade; i++){
        if(fila->processos[i][3] == 1){ // Se o processo for de sistema, envia para a pilha
        	id = fila->processos[i][0];
        	t_Cheg = fila->processos[i][1];
        	t_Exec = fila->processos[i][2]; 
        	
            inserir_Dados_PilhaAux(pilhaAux, id, t_Cheg, t_Exec, 1); // Insere os dados na pilha
        }
    }
}

void digitar_Dados(fila_Processos* fp, int t_Padrao){ // Digita os dados do processo
    int id, t_Cheg, t_Exec;
    int status;
    char statusChar[10];

    printf("Digite o id do processo: ");
    scanf("%d", &id);

    printf("Digite o tempo de chegada do processo: ");
    scanf("%d", &t_Cheg);

    printf("Digite o tempo de execucao do processo: ");
    scanf("%d", &t_Exec);

    setbuf(stdin, NULL);
    printf("Digite o status do processo: ");
    fgets(statusChar, 10, stdin);
    statusChar[strcspn(statusChar, "\n")] = '\0'; // Remove o caractere de nova linha

    if(strcmp(statusChar, "sistema") == 0){
        status = 1;
    }
    else if(strcmp(statusChar, "usuario") == 0){
        status = 2;
    }

    inserir_Dados_Fila(fp, id, t_Cheg, t_Exec, status); // Insere os dados na fila
}
