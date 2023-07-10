#ifndef FUNCOES_H
#define FUNCOES_H

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

typedef struct local Local;
typedef struct caminho Caminho;
typedef struct listaLocais ListaLocais;
typedef struct listaCaminhos ListaCaminhos;
typedef struct _grafo Grafo;

#define PI 3.14159265358979323846
#define RAIO_DA_TERRA 6371.0 // Raio médio da Terra em quilômetros

void calcular_Distancia(Caminho* caminho, ListaLocais* listaLocais);

double g_distancia_aresta(Grafo* self, int origem, int destino);

bool g_existe_aresta(Grafo* self, int origem, int destino);

void g_caminho_mais_curto(Grafo* self, int origem, int destino);

void preencherGrafo(Grafo* grafo, ListaLocais* listaLocais, ListaCaminhos* listaCaminhos);

int obterIndiceLocal(ListaLocais* listaLocais, const char* identificacao);


#endif