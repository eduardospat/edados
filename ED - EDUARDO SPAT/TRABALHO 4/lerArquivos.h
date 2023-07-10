#ifndef LERARQUIVOS_H
#define LERARQUIVOS_H
#include "grafo.h"

typedef struct _grafo Grafo;
typedef struct caminho Caminho;

typedef struct local {
    char* identificacao;
    double latitude;
    double longitude;
    int indice;
} Local;

typedef struct listaLocais {
    Local* local;
    struct listaLocais* prox;
    struct listaLocais* ant;

} ListaLocais;

typedef struct listaCaminhos {
    Caminho* caminho;
    Local* localAtual;
    struct listaCaminhos* prox;
    struct listaCaminhos* ant;
    struct listaCaminhos* caminhoAtual;
} ListaCaminhos;

typedef struct locaisAVisitar {
    char* identificacao;
} LocaisAVisitar;

typedef struct listaLocaisAVisitar {
    Local* localAVisitar;
    struct listaLocaisAVisitar* prox;
    struct listaLocaisAVisitar* ant;
} ListaLocaisAVisitar;


void lerLocais(ListaLocais** listaLocais, const char* nomeArquivo);
void lerCaminhos(ListaCaminhos** listaCaminhos, const char* nomeArquivoCaminhos, ListaLocais* listaLocais);
void lerLocaisAVisitar(ListaLocaisAVisitar** listaLocaisAVisitar, const char* nomeArquivo);
Grafo* lerArquivoCSV(const char* nomeArquivoLocais, const char* nomeArquivoCaminhos);
void gerarArquivoSaida(const char* nomeArquivo, ListaLocaisAVisitar* listaLocaisAVisitar, ListaCaminhos* g_caminho_mais_curto);
void encontrarCaminhoMaisCurto(Grafo* grafo, ListaLocaisAVisitar* listaLocaisAVisitar, const char* nomeArquivoSaida);
void liberarListaLocais(ListaLocais* lista);
void liberarListaCaminhos(ListaCaminhos* lista);
void liberarListaLocaisAVisitar(ListaLocaisAVisitar* lista);
int contarLocais(ListaLocais* listaLocais);

#endif
