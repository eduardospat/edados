#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "grafo.h"
#include "lerArquivos.h"

#define PI 3.14159265358979323846
#define RAIO 6371.0

struct vertices {
    int indice;
    char* identificacao;
    double latitude;
    double longitude;
};

struct listavertices {
    struct vertices* local;
    struct listavertices* prox;
};

struct arestas {
    int origem;
    int destino;
    double distancia;
};

struct listaarestas {
    struct arestas* aresta;
    struct listaarestas* prox;
};

listavertices lerLocais(listavertices lista, const char* nomeArquivoLocais) {

    vertices novoVer = NULL;
    listavertices novoNo = NULL;
    listavertices ultimoNo = NULL;

    FILE* arquivo = fopen(nomeArquivoLocais, "r");

    char linha[100];
    int indice = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
    if (linha[0] == '#') {
        continue;  
    }
        char* identificacao = strtok(linha, ",");
        char* latitude = strtok(NULL, ",");
        char* longitude = strtok(NULL, ",");

        double lat = strtod (latitude, NULL);
        double lon = strtod (longitude, NULL);

        novoVer = malloc(sizeof(struct vertices));
        novoVer -> indice = indice;
        novoVer -> identificacao = strdup(identificacao);
        novoVer -> latitude = lat;
        novoVer -> longitude = lon;

        if (lista == NULL) {
            lista = malloc(sizeof(struct listavertices));
            lista -> local = novoVer;
            lista -> prox = NULL;
            ultimoNo = lista;
        } else {
            novoNo = malloc(sizeof(struct listavertices));
            novoNo -> local = novoVer;
            novoNo -> prox = NULL;
            ultimoNo -> prox = novoNo;
            ultimoNo = novoNo;
        }
        indice++;
    }
    fclose (arquivo);
    return lista;
}

double calcula_Distancia(int origem, int destino, listavertices listaV){
    listavertices atual = listaV;
    double lat1, lon1, lat2, lon2;
    lat1 = lon1 = lat2 = lon2 = 0.0;

    while (atual != NULL) {
        if (atual->local->indice == origem) {
            lat1 = atual->local->latitude;
            lon1 = atual->local->longitude;
        }
        if (atual->local->indice == destino) {
            lat2 = atual->local->latitude;
            lon2 = atual->local->longitude;
        }
        atual = atual->prox;
    }

    double lat1Rad = lat1 * PI / 180.0;
    double lon1Rad = lon1 * PI / 180.0;
    double lat2Rad = lat2 * PI / 180.0;
    double lon2Rad = lon2 * PI / 180.0;
    
    double dLat = lat2Rad - lat1Rad;
    double dLon = lon2Rad - lon1Rad;
    
    double a = sin(dLat / 2) * sin(dLat / 2) + cos(lat1Rad) * cos(lat2Rad) * sin(dLon / 2) * sin(dLon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double distanciaMetros = RAIO * c;
    
    double calcDistancia = distanciaMetros * 1000;
    
    return calcDistancia;
}

listaarestas lerArestas(listaarestas listaA, const char* nomeArquivoCaminhos, listavertices listaV) {

    FILE* arquivo = fopen(nomeArquivoCaminhos, "r");
    char linha[100];
    int indiceOri = -1;
    int indiceDest = -1;
    while (fgets(linha, sizeof(linha), arquivo)) {
        if (linha[0] == '#') {
            continue;  
        }
        char* charOri = strtok(linha, ",");
        char* charDest = strtok(NULL, ",");

        charOri[strcspn(charOri, "\r\n")] = '\0';
        charDest[strcspn(charDest, "\r\n")] = '\0';

        indiceOri = -1;
        indiceDest = -1;

        listavertices atual = listaV;
        while (atual != NULL) {
            if (strcmp(atual->local->identificacao, charOri) == 0) {
                indiceOri = atual->local->indice;
            }
            if (strcmp(atual->local->identificacao, charDest) == 0) {
                indiceDest = atual->local->indice;
            }
            if (indiceOri != -1 && indiceDest != -1) {
                break;
            }
            atual = atual->prox;
        }
        if (indiceOri != -1 && indiceDest != -1) {
            arestas novaAresta = (arestas)malloc(sizeof(struct arestas));
            novaAresta->origem = indiceOri;
            novaAresta->destino = indiceDest;
            novaAresta->distancia = calcula_Distancia(indiceOri, indiceDest, listaV);
    
            listaarestas novoNo = (listaarestas)malloc(sizeof(struct listaarestas));
            novoNo->aresta = novaAresta;
            novoNo->prox = NULL;

            if (listaA == NULL) {
                listaA = novoNo;
            } else {
                listaarestas auxiliar = listaA;
                while (auxiliar->prox != NULL)
                    auxiliar = auxiliar->prox;
                auxiliar->prox = novoNo;
            }
        }
    }
    fclose(arquivo);
    return listaA;
}

int* lerVisitas(int* nVis, const char* nomeArquivoVisitas, const listavertices vertices){
    FILE* arquivo = fopen(nomeArquivoVisitas, "r");
    char linha[10];
    int p = 10;
    int n = 0;
    int* visitas = (int*)malloc(p * sizeof(int));
    while (fgets(linha, sizeof(linha), arquivo)) {
        if (linha[0] == '#') {
            continue;  
        }
        linha [strcspn (linha, "\r\n")] = '\0';
        char* charVis = strtok(linha, "\n");
        listavertices atual = vertices;
        while (atual != NULL) {
            if (strcmp(atual->local->identificacao, charVis) == 0) {
                visitas[n++] = atual->local->indice;
            if (n >= p) {
                p *= 2;
                int* novoVis = (int*) realloc(visitas, p * sizeof(int));
                if (novoVis == NULL) {
                    fclose (arquivo);
                    free(visitas);
                    return NULL;
                }
                visitas = novoVis;
            }
                break;
            }
        atual = atual->prox;
        }
    }
    fclose(arquivo);
    *nVis = n;
    return visitas;
}

void preencherGrafo (Grafo grafo, listaarestas listaA, listavertices listaV) {
    listaarestas atual = listaA;
    while (atual != NULL) {
        g_ins_aresta(grafo, atual->aresta->origem, atual->aresta->destino, atual->aresta->distancia);
        atual = atual->prox;
    }
}

int numV(listavertices listaV) {
    int numVertices = 0;
    listavertices atual = listaV;
    while (atual != NULL) {
        numVertices++;
        atual = atual->prox;
    }
    return numVertices;
}

double lat (listavertices listaV, int indice) {
    listavertices atual = listaV;
    while (atual != NULL) {
        if (atual->local->indice == indice) {
            return atual->local->latitude;
        }
        atual = atual->prox;
    }
    return 0.0;
}

double lon (listavertices listaV, int indice) {
    listavertices atual = listaV;
    while (atual != NULL) {
        if (atual->local->indice == indice) {
            return atual->local->longitude;
        }
        atual = atual->prox;
    }
    return 0.0;
}

char* identifica (listavertices listaV, int indice) {
    listavertices atual = listaV;
    while (atual != NULL) {
        if (atual->local->indice == indice) {
            return atual->local->identificacao;
        }
        atual = atual->prox;
    }
    return NULL;
}

