#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "grafo.h"
#include "lerArquivos.h"

int* dijkstra(Grafo grafo, int origem);
void coords_iden(FILE *arquivo, double latitude, double longitude, const char *identificacao);
void coords(FILE *arquivo, double latitude, double longitude);
void imprime_inicio(int indice, listavertices lista_locais, char *nomeArquivoSaida);
void imprime_fim(int indice, listavertices lista_locais, char *nomeArquivoSaida);
void imprimeCaminho(int* prev, int destino, listavertices lista_locais, char *nomeArquivoSaida);
void menor_caminho(Grafo grafo, listavertices lista_locais);

#endif