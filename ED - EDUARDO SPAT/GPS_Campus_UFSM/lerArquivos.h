#ifndef LERARQUIVOS_H
#define LERARQUIVOS_H

#include "grafo.h"

typedef struct vertices *vertices;
typedef struct listavertices *listavertices;
typedef struct arestas *arestas;
typedef struct listaarestas *listaarestas;

listavertices lerLocais(listavertices lista, const char* nomeArquivo);
double calcula_Distancia(int origem, int destino, listavertices listaV);
listaarestas lerArestas(listaarestas listaA, const char* nomeArquivo, listavertices listaV);
int* lerVisitas(int* nVis, const char* nomeArquivoVisitas, const listavertices vertices);
void preencherGrafo (Grafo grafo, listaarestas listaA, listavertices listaV);
int numV(listavertices listaV);
double lon (listavertices listaV, int indice);
double lat (listavertices listaV, int indice);
char* identifica (listavertices listaV, int indice);
    
#endif