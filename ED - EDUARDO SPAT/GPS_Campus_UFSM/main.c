#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "lerArquivos.h"
#include "dijkstra.h"

int main(){
    listavertices lista_locais = NULL;
    listaarestas listaA = NULL;
    Grafo self = NULL;

    const char* nomeArquivoLocais = "locais.csv";
    const char* nomeArquivoCaminhos = "caminhos.csv";

    lista_locais = lerLocais(lista_locais, nomeArquivoLocais);
    listaA = lerArestas(listaA, nomeArquivoCaminhos, lista_locais);

    int nVertices = numV(lista_locais);

    self = g_cria(nVertices, false);

    preencherGrafo(self, listaA, lista_locais);

    menor_caminho(self, lista_locais);

    g_destroi(self);
    free(lista_locais);
    free(listaA);
}
