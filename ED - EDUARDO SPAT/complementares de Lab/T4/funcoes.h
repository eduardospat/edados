#ifndef FUNCOES_H
#define FUNCOES_H
#define capacidade 4

#include "pilha.h"
#include "pilhaAux.h"
#include "fila.h"

void enviar_Usuario_Fila(fila_Processos* fp, pilha_Processos* pilha); // Envia os processos de usuario para a fila
void enviar_Sistema_Fila(fila_Processos* fp, pilha_Auxiliar* pilhaAux); // Envia os processos de sistema para a fila
int verifica_Existe_Sistema(fila_Processos* fila); // Verifica se existe um processo de sistema na fila
void enviar_Usuarios_Pilha(fila_Processos* fila, pilha_Processos* pilha); // Envia os processos de usuario para a pilha
void enviar_Sistema_PilhaAux(fila_Processos* fila, pilha_Auxiliar* pilhaAux); // Envia os processos de sistema para a pilha
void digitar_Dados(fila_Processos* fp, int t_Padrao); // Digita os dados do processo

#endif
