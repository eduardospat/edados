#include "lista.h"
#include "arvore.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Arvore* buscar_Codigo_Arvore(Arvore* raiz, int codigo){ // Funcao que busca um codigo na arvore
    if(raiz == NULL){
        return NULL;
    } else {
        if(codigo < raiz->codigo){
            return buscar_Codigo_Arvore(raiz->esq, codigo);
        } else {
            if(codigo > raiz->codigo){
                return buscar_Codigo_Arvore(raiz->dir, codigo);
            } else {
                return raiz;
            }
        }
    }
}

Arvore* inserir_Dados_Arvore(Arvore* raiz, int codigo, char razaoSocial[50], char endereco[50]){ // Funcao que insere dados na arvore
    if(raiz == NULL){ // Arvore vazia
        Arvore* aux = (Arvore*) malloc (sizeof(Arvore));

        aux->codigo = codigo;
        strcpy(aux->razaoSocial, razaoSocial);
        strcpy(aux->endereco, endereco);
        aux->esq = NULL;
        aux->dir = NULL;

		system("cls");
    	printf("[AVISO] Dados inseridos com sucesso na arvore!\n");
    	system("pause");

        return aux;

    }else {
        if(codigo < raiz->codigo){ // Inserir na esquerda
            raiz->esq = inserir_Dados_Arvore(raiz->esq, codigo, razaoSocial, endereco);
        } else { // Inserir na direita
            raiz->dir = inserir_Dados_Arvore(raiz->dir, codigo, razaoSocial, endereco);
        }  
    }
    
    return raiz;
}

Arvore* remover_Dado_Arvore (Arvore** raiz, int codigo){ // Funcao que remove um dado da arvore
    if(*raiz == NULL){
        printf("[ERRO] Arvore vazia!\n");
        return NULL;
    } else {
        if(codigo < (*raiz)->codigo){
            (*raiz)->esq = remover_Dado_Arvore(&(*raiz)->esq, codigo);
        } else {
            if(codigo > (*raiz)->codigo){
                (*raiz)->dir = remover_Dado_Arvore(&(*raiz)->dir, codigo);
            } else {
                if((*raiz)->esq == NULL && (*raiz)->dir == NULL){ // Nao tem filhos
                    free(*raiz);
                    *raiz = NULL;
                } else {
                    if((*raiz)->esq == NULL){ // Tem filho na direita
                        Arvore* aux = *raiz;
                        *raiz = (*raiz)->dir;
                        free(aux);
                    } else {
                        if((*raiz)->dir == NULL){ // Tem filho na esquerda
                            Arvore* aux = *raiz;
                            *raiz = (*raiz)->esq;
                            free(aux);
                        } else { // Tem filho na esquerda e na direita
                            Arvore* aux = (*raiz)->esq;
                            while(aux->dir != NULL){
                                aux = aux->dir;
                            }
                            (*raiz)->codigo = aux->codigo;
                            strcpy((*raiz)->razaoSocial, aux->razaoSocial);
                            strcpy((*raiz)->endereco, aux->endereco);
                            aux->codigo = codigo;
                            (*raiz)->esq = remover_Dado_Arvore(&(*raiz)->esq, codigo);
                        }
                    }
                }
            }
        }
    }
    return *raiz;
}

void imprimir_Dados_Arvore(Arvore* raiz){ // Funcao que imprime os dados da arvore em ordem decrescente
	if(raiz != NULL){
        imprimir_Dados_Arvore(raiz->dir);     
        printf("Codigo da filial: %d\n", raiz->codigo);
        printf("Razao social: %s\n", raiz->razaoSocial);
        printf("Endereco: %s\n", raiz->endereco);
        imprimir_Dados_Arvore(raiz->esq);
        printf("-------------------------------------------------\n");
  	} 
}
