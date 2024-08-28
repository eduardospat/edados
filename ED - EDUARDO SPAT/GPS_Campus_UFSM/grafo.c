#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

struct _grafo {
    float mat_arestas[MAX_VERTICES][MAX_VERTICES];
    bool orientado;
    int nvertices;
    int narestas;
    int arestas_visitadas;

    double prox_A;
    bool conf;
    int conf_type;
    int prox_O;
    int prox_D;
};

// aloca e inicializa um grafo com n vértices
// o grafo pode ser orientado ou não (afeta o processamento das arestas)
// retorna um ponteiro para o grafo alocado
Grafo g_cria(int n, bool orientado){
    Grafo self = (Grafo) malloc(sizeof(struct _grafo));
    if (self == NULL) {
        return NULL;
    }
    self->nvertices = n;
    self->orientado = orientado;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; ++j) {
            self->mat_arestas[i][j] = 0;
        }
    }
    self -> narestas = 0;
    self -> arestas_visitadas = 0;
    self -> prox_A = 0.0;
    self -> conf = false;
    int conf_type = -1;
    self -> prox_O = 0;
    self -> prox_D = 0;

    return self;
}

// libera a memória usada pelo grafo
void g_destroi(Grafo self){
    free(self);
}// 

// retorna o número de vértices do grafo
int g_nvertices(Grafo self){
    return self->nvertices;
}

// insere uma aresta no grafo (ou altera o peso de uma aresta já existente)
void g_ins_aresta(Grafo self, int origem, int destino, float peso){
    self->mat_arestas[origem][destino] = peso;
    self->narestas++;
    if (!self->orientado) {
        self->mat_arestas[destino][origem] = peso;
        self->narestas++;
    }
}

// remove uma aresta do grafo
void g_rem_aresta(Grafo self, int origem, int destino){
    self->mat_arestas[origem][destino] = 0;
    if (!self->orientado) {
        self->mat_arestas[destino][origem] = 0;
    }
}

// inicia uma consulta a arestas do grafo.
// as próximas chamadas a g_proxima_aresta devem retornar cada aresta do grafo
void g_arestas(Grafo self){
    if (self == NULL)
    return;

    self->arestas_visitadas = 0;
    self -> prox_A = 0.0;
    self -> conf = true;
    self -> conf_type = 0;
    self -> prox_O = 0;
    self -> prox_D = 0;
}
// inicia uma consulta a arestas do grafo.
// as próximas chamadas à g_proxima_aresta devem retornar cada aresta do grafo que parte do vértice origem
void g_arestas_que_partem(Grafo self, int origem){
    if (self == NULL)
    return;
    self->arestas_visitadas = 0;
    self -> prox_A = self -> mat_arestas[origem][0];
    self -> conf = true;
    self -> conf_type = 1;
    self -> prox_O = origem;
    self -> prox_D = 0;
}

// retorna os dados sobre a próxima aresta de uma consulta
// retorna true se ok ou false se não tem mais arestas ou se não foi iniciada uma consulta
// cada ponteiro pode ser NULL, para o caso de não se estar interessado na informação associada
// não se deve inserir ou remover arestas no grafo com uma consulta em andamento
bool g_proxima_aresta(Grafo self, int *origem, int *destino, float *peso){
    if (self == NULL)
    return false;

    if (self -> conf == false)
    return false;

    if (self -> conf_type == 0) {
        if (self -> arestas_visitadas == self -> narestas) {
            self -> conf = false;   
            return false;
        }
        for (int i = self -> prox_O; i < self -> nvertices; i++) {
            for (int j = self -> prox_D; j < self -> nvertices; j++) {
                if (self -> mat_arestas[i][j] != 0.0) {
                    self -> arestas_visitadas++;
                    self -> prox_O = i;
                    self -> prox_D = j + 1;
                    *origem = i;
                    *destino = j;
                    *peso = self -> mat_arestas[i][j];
                    self -> prox_A = self -> mat_arestas[i][j+1];
                    return true;
                }
            }
            self -> prox_D = 0;
        }
    } else if (self -> conf_type == 1) {
        if (self -> arestas_visitadas == self -> nvertices) {
            self -> conf = false;
            return false;
        }
        for (int j = self -> prox_D; j < self -> nvertices; j++) {
            if (self -> mat_arestas[self -> prox_O][self -> prox_D] != 0.0) {
                self -> arestas_visitadas++;
                self -> prox_D++;
                *origem = self -> prox_O;
                *destino = j;
                *peso = self -> mat_arestas[self -> prox_O][self -> prox_D];
                self -> prox_A = self -> mat_arestas[self -> prox_O][self -> prox_D];
                return true;
            }
            self -> prox_D++;
        }
        self -> conf = false;
        self -> arestas_visitadas = 0;
        self -> conf_type = -1;
        return false;
    }
    return false;
}

float g_dist(Grafo self, int origem, int destino) {
    if (self == NULL)
        return 0.0;
    return self->mat_arestas[origem][destino];
}