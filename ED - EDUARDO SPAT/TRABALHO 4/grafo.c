#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include "grafo.h"
#include "lerArquivos.h"
#include "funcoes.h"

#define MAX_ARESTAS 150
typedef struct local Local;
typedef struct caminho Caminho;
typedef struct listaLocais ListaLocais;
typedef struct listaCaminhos ListaCaminhos;
typedef struct _grafo Grafo;

Grafo* g_cria(int n, bool orientado) {
    Grafo* grafo = malloc(sizeof(Grafo));
    if (grafo == NULL) {
        // Tratar falha na alocação de memória
        return NULL;
    }
    grafo->local = malloc(n * sizeof(Local));
    if (grafo->local == NULL) {
        // Tratar falha na alocação de memória
        free(grafo);
        return NULL;
    }
    grafo->numLocais = n;
    grafo->orientado = orientado;
    // Inicializar cada vértice com NULL
    for (int i = 0; i < n; i++) {
        grafo->local[i] = NULL;
    }
    return grafo;
}

void g_destroi(Grafo* self) {
    if (self == NULL) {
        return;
    }
    // Liberar memória dos vértices
    for (int i = 0; i < self->numLocais; i++) {
        if (self->local[i] != NULL) {
            free(self->local[i]->identificacao);
            free(self->local[i]);
        }
    }
    // libera memória do array de locais/vertices
    free(self->local);
    // libera memória da estrutura do grafo
    free(self);
}

int g_nvertices(Grafo* self) {
    if (self == NULL) {
        return 0;
    }
    return self->numLocais;
}

void g_ins_aresta(Grafo* self, int origem, int destino, float distancia) {
    if (self == NULL || origem < 0 || origem >= self->numLocais || destino < 0 || destino >= self->numLocais) {
        // Tratar caso de grafo inválido ou índices fora dos limites
        return;
    }

    // Criar caminho
    Caminho* caminho = &(self->caminho[self->consultaArestasIndex]);
    caminho->origem = self->local[origem]->identificacao;
    caminho->destino = self->local[destino]->identificacao;
    caminho->distancia = distancia;

    // Incrementar índice de consulta
    self->consultaArestasIndex++;
}

void g_rem_aresta(Grafo* grafo, int origem, int destino) { 
    if (grafo == NULL || origem < 0 || origem >= grafo->numLocais || destino < 0 || destino >= grafo->numLocais) {
        // Tratar caso de grafo inválido ou índices fora dos limites
        return;
    }
    // Percorrer caminhos para encontrar a aresta
    for (int i = 0; i < grafo->consultaArestasIndex; i++) {
        Caminho* caminho = &(grafo->caminho[i]);
        if (strcmp(caminho->origem, grafo->local[origem]->identificacao) == 0 && strcmp(caminho->destino, grafo->local[destino]->identificacao) == 0) {
            // Remover a aresta substituindo-a pela última
            *caminho = grafo->caminho[grafo->consultaArestasIndex - 1];
            // Decrementar o índice de consulta
            grafo->consultaArestasIndex--;
            return;
        }
    }
}

void g_arestas(Grafo* grafo) {
    if (grafo == NULL) {
        // Tratar caso de grafo inválido
        return;
    }
    grafo->origemConsultaArestas = -1; 
    grafo->consultaArestasIndex = 0; 
}

void g_arestas_que_partem(Grafo* grafo, int origem) {
    if (grafo == NULL || origem < 0 || origem >= grafo->numLocais) {
        // Tratar caso de grafo inválido ou vértice de origem inválido
        return;
    }
    grafo->origemConsultaArestas = origem;
    grafo->consultaArestasIndex = 0;
}

bool g_proxima_aresta(Grafo* grafo, char** origem, char** destino, double* distancia) {

    if (grafo == NULL || grafo->origemConsultaArestas == -1 || grafo->consultaArestasIndex >= MAX_ARESTAS) {
        // Tratar caso de grafo inválido ou consulta não iniciada
        return false;
    }
    Caminho* caminho = &(grafo->caminho[grafo->consultaArestasIndex]);
    // Verificar se a origem da aresta coincide com a origem da consulta
    if (strcmp(caminho->origem, grafo->local[grafo->origemConsultaArestas]->identificacao) != 0) {
        // Se não coincidir, não é uma aresta que parte da origem da consulta
        return false;
    }
    // Preencher as informações da aresta
    if (origem != NULL) {
        *origem = caminho->origem;
    }
    if (destino != NULL) {
        *destino = caminho->destino;
    }
    if (distancia != NULL) {
        *distancia = caminho->distancia;
    }

    // Incrementar o índice de consulta
    grafo->consultaArestasIndex++;

    return true;
}