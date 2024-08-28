#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>
#include <math.h>
#include "grafo.h"
#include "lerArquivos.h"
#include "dijkstra.h"

int* dijkstra (Grafo grafo, int origem) {
    int numVertices = g_nvertices(grafo);
    int* check = (int*)malloc(numVertices * sizeof(int));
    int* prev = (int*)malloc(numVertices * sizeof(int));
    float* distancia = (float*)malloc(numVertices * sizeof(float));

    for (int i = 0; i < numVertices; i++) {
        check[i] = 0;
        prev[i] = 0;
        distancia[i] = INT_MAX;
    }
    distancia[origem] = 0;

    for (int i = 0; i < numVertices; i++) {
        float minimo = INT_MAX;
        int atual = -1;
        for (int j = 0; j < numVertices; j++) {
            if (check[j] == 0 && distancia[j] < minimo) {
                minimo = distancia[j];
                atual = j;
            }
        }
        if (atual == -1) break;
        check[atual] = 1;
        for (int j = 0; j < numVertices; j++) {
            float peso = g_dist(grafo, atual, j);

            if (peso > 0 && distancia[atual] + peso < distancia[j]) {
                distancia[j] = distancia[atual] + peso;
                prev[j] = atual;
            }
        }

    }
    free(distancia);
    free(check);
    return prev;
}

void coords_iden(FILE *arquivo, double latitude, double longitude, const char *identificacao) {
    fprintf(arquivo, "%lf,%lf(%s)", latitude, longitude, identificacao);
}

void coords(FILE *arquivo, double latitude, double longitude) {
    fprintf(arquivo, "%lf,%lf ", latitude, longitude);
}

void imprime_inicio(int indice, listavertices lista_locais, char *nomeArquivoSaida) {
    FILE *arquivo = fopen(nomeArquivoSaida, "w");
    double latitude = lat(lista_locais, indice);
    double longitude = lon(lista_locais, indice);
    char *identificacao = identifica(lista_locais, indice);
    fprintf(arquivo, "[map]\n");
    fprintf (arquivo, "%lf,%lf(%s);", latitude, longitude, identificacao);
    fprintf(arquivo, "\n");
    fclose(arquivo);
}

void imprime_fim(int indice, listavertices lista_locais, char *nomeArquivoSaida) {
    FILE *arquivo = fopen(nomeArquivoSaida, "a");
    double latitude = lat(lista_locais, indice);
    double longitude = lon(lista_locais, indice);
    char *identificacao = identifica(lista_locais, indice);
    fprintf(arquivo, ";");
    fprintf(arquivo, "\n");
    coords_iden(arquivo, latitude, longitude, identificacao);
    fprintf(arquivo, "\n[/map]");
    fclose(arquivo);
}

void imprimeCaminho(int* prev, int destino, listavertices lista_locais, char *nomeArquivoSaida) {
    if (prev[destino] == 0) {
        return;
    }
    FILE *arquivo = fopen(nomeArquivoSaida, "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    imprimeCaminho(prev, prev[destino], lista_locais, nomeArquivoSaida);

    double latitude = lat(lista_locais, destino);
    double longitude = lon(lista_locais, destino);
    coords (arquivo, latitude, longitude);

    fclose(arquivo);
}

void menor_caminho(Grafo grafo, listavertices lista_locais) {
    int nVis = 0;
    int* listaVisitas = lerVisitas(&nVis, "visita.csv", lista_locais);
    char* nomeArquivoSaida = "resultado.txt";
    FILE* arquivo = fopen("resultado.txt", "a");

    int* prev;
    int nvertices = g_nvertices(grafo);

    imprime_inicio(listaVisitas[0], lista_locais, nomeArquivoSaida);
    for (int i = 0; i < nVis - 1; i++) {
        prev = dijkstra(grafo, listaVisitas[i]);
        imprimeCaminho(prev, listaVisitas[i + 1], lista_locais, nomeArquivoSaida);
    }
    imprime_fim(listaVisitas[nVis - 1], lista_locais, nomeArquivoSaida);

    fclose(arquivo);
    free(listaVisitas);
}

