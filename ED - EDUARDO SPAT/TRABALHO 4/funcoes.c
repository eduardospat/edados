#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "lerArquivos.h"
#include "grafo.h"

typedef struct local Local;
typedef struct caminho Caminho;
typedef struct listaLocais ListaLocais;
typedef struct listaCaminhos ListaCaminhos;
typedef struct _grafo;

#define PI 3.14159265358979323846
#define RAIO_DA_TERRA 6371.0 // Raio médio da Terra em quilômetros

void calcular_Distancia(Caminho* caminho, ListaLocais* listaLocais) {
    ListaLocais* aux = listaLocais;
    double calcDistancia = 0.0;
    double lat1, lon1, lat2, lon2;
    lat1 = lon1 = lat2 = lon2 = 0.0;

    while (aux != NULL) { // coordenadas dos locais de origem e destino
        if (strcmp(caminho->origem, aux->local->identificacao) == 0) {
            lat1 = aux->local->latitude;
            lon1 = aux->local->longitude;
        }
        if (strcmp(caminho->destino, aux->local->identificacao) == 0) {
            lat2 = aux->local->latitude;
            lon2 = aux->local->longitude;

        }
        aux = aux->prox;
    }

    // coordenadas de graus para radianos
    double lat1Rad = lat1 * PI / 180.0;
    double lon1Rad = lon1 * PI / 180.0;
    double lat2Rad = lat2 * PI / 180.0;
    double lon2Rad = lon2 * PI / 180.0;
    
    // diferença entre as latitudes e longitudes
    double dLat = lat2Rad - lat1Rad;
    double dLon = lon2Rad - lon1Rad;
    
    // fórmula de Haversine
    double a = sin(dLat / 2) * sin(dLat / 2) + cos(lat1Rad) * cos(lat2Rad) * sin(dLon / 2) * sin(dLon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double distanciaMetros = RAIO_DA_TERRA * c;
    
    calcDistancia = distanciaMetros * 1000;
    
    caminho->distancia = calcDistancia;
}

double g_distancia_aresta(Grafo* self, int origem, int destino) {
    // Verificar se o grafo é válido
    if (self == NULL || origem < 0 || origem >= self->numLocais || destino < 0 || destino >= self->numLocais) {
        // Tratar caso de grafo inválido ou índices fora dos limites
        return -1.0; // Valor de distância inválido
    }

    // Verificar se a consulta de arestas foi iniciada
    if (self->origemConsultaArestas == -1) {
        return -1.0; // Valor de distância inválido
    }

    // Verificar se os vértices de origem e destino estão dentro do intervalo de consulta de arestas
    if (origem != self->origemConsultaArestas || destino < self->consultaArestasIndex || destino >= self->numLocais) {
        return -1.0; // Valor de distância inválido
    }

    // Procurar a distância da aresta no array de caminhos
    for (int i = self->consultaArestasIndex; i < self->numLocais; i++) {
        Caminho* caminho = &(self->caminho[i]);
        if (strcmp(caminho->origem, self->local[origem]->identificacao) == 0 &&
            strcmp(caminho->destino, self->local[destino]->identificacao) == 0) {
            return caminho->distancia; // Retorna a distância da aresta encontrada
        }
    }

    return -1.0; // Valor de distância inválido (aresta não encontrada)
}

bool g_existe_aresta(Grafo* self, int origem, int destino) {
    // Verificar se o grafo é válido
    if (self == NULL || origem < 0 || origem >= self->numLocais || destino < 0 || destino >= self->numLocais) {
        // Tratar caso de grafo inválido ou índices fora dos limites
        return false;
    }

    // Verificar se a consulta de arestas foi iniciada
    if (self->origemConsultaArestas == -1) {
        return false;
    }

    // Verificar se os vértices de origem e destino estão dentro do intervalo de consulta de arestas
    if (origem != self->origemConsultaArestas || destino < self->consultaArestasIndex || destino >= self->numLocais) {
        return false;
    }

    // Verificar a existência da aresta no array de caminhos
    for (int i = self->consultaArestasIndex; i < self->numLocais; i++) {
        Caminho* caminho = &(self->caminho[i]);
        if (strcmp(caminho->origem, self->local[origem]->identificacao) == 0 &&
            strcmp(caminho->destino, self->local[destino]->identificacao) == 0) {
            return true; // Aresta encontrada
        }
    }

    return false; // Aresta não encontrada
}

void g_caminho_mais_curto(Grafo* self, int origem, int destino) { // Algoritmo de Dijkstra
    if (self == NULL || origem < 0 || origem >= self->numLocais || destino < 0 || destino >= self->numLocais) {
        // Tratar caso de grafo inválido ou índices fora dos limites
        return;
    }

    int numVertices = self->numLocais;

    // Aloca e inicializa os arrays de distâncias e visitados
    double* distancias = malloc(numVertices * sizeof(double));
    bool* visitados = malloc(numVertices * sizeof(bool));
    int* antecessores = malloc(numVertices * sizeof(int));

    if (distancias == NULL || visitados == NULL || antecessores == NULL) {
        // Trata falha na alocação de memória
        free(distancias);
        free(visitados);
        free(antecessores);
        return;
    }

    // Inicializa as distâncias como infinito e os visitados como falso
    for (int i = 0; i < numVertices; i++) {
        distancias[i] = DBL_MAX;
        visitados[i] = false;
        antecessores[i] = -1;
    }

    // Define a distância da origem como 0
    distancias[origem] = 0.0;

    // Encontra o caminho mais curto
    for (int i = 0; i < numVertices - 1; i++) {
        // Encontra o vértice com a menor distância ainda não visitado
        int verticeMinDist = -1;
        double minDist = DBL_MAX;
        for (int j = 0; j < numVertices; j++) {
            if (!visitados[j] && distancias[j] < minDist) {
                verticeMinDist = j;
                minDist = distancias[j];
            }
        }

        // Marca o vértice como visitado
        visitados[verticeMinDist] = true;

        // Atualiza as distâncias dos vértices adjacentes não visitados
        for (int j = 0; j < numVertices; j++) {
            if (!visitados[j] && g_existe_aresta(self, verticeMinDist, j)) {
                double pesoAresta = g_distancia_aresta(self, verticeMinDist, j);
                double dist = distancias[verticeMinDist] + pesoAresta;
                if (dist < distancias[j]) {
                    distancias[j] = dist;
                    antecessores[j] = verticeMinDist;
                }
            }
        }
    }
    // Libera a memória alocada
    free(distancias);
    free(visitados);
    free(antecessores);
}

// essa funcao deveria preencher os dados do grafo
void preencherGrafo(Grafo* grafo, ListaLocais* listaLocais, ListaCaminhos* listaCaminhos){ 
    int verticeorigem, verticedestino; // variaveis para armazenar os vertices de origem e destino

    while(listaCaminhos != NULL){ // Enquanto a lista de caminhos nao for vazia
        verticeorigem = verticedestino = -1; // inicializa as variaveis com -1

        ListaLocais* temp = listaLocais; // cria uma lista temporaria para percorrer a lista de locais
        while(temp != NULL){ 
            if(strcmp(listaCaminhos->caminho->origem, temp->local->identificacao) == 0){ 
                verticeorigem = temp->local->indice;
            }
            if(strcmp(listaCaminhos->caminho->destino, temp->local->identificacao) == 0){ // Se o nome do vertice for igual ao nome do destino
                verticedestino = temp->local->indice;
            }
            temp = temp->prox;
        }
        if(verticeorigem != -1 && verticedestino != -1) g_ins_aresta(grafo, verticeorigem, verticedestino, listaCaminhos->caminho->distancia); // Insere o peso da aresta na matriz do grafo

        listaCaminhos = listaCaminhos->prox;
    }
}

int obterIndiceLocal(ListaLocais* listaLocais, const char* identificacao) {
    ListaLocais* listaLocaisAtual = listaLocais;
    while (listaLocaisAtual != NULL) {
        if (strcmp(listaLocaisAtual->local->identificacao, identificacao) == 0) {
            return listaLocaisAtual->local->indice;
        }
        listaLocaisAtual = listaLocaisAtual->prox;
    }
    return -1; // Local não encontrado
}