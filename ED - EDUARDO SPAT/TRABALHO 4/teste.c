#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lerArquivos.h" // Inclua o arquivo de cabeçalho que contém as definições das estruturas e funções

#define MAX_VERTICES 100

void imprimirLocais(ListaLocais* listaLocais) {
    ListaLocais* atual = listaLocais;
    while (atual != NULL) {
        printf(" %s, ", atual->local->identificacao);
        printf("%.5f, ", atual->local->latitude);
        printf("%.5f\n", atual->local->longitude);
        atual = atual->prox;
    }
    printf("\n");
}

void imprimirCaminhos(ListaCaminhos* listaCaminhos) {
    ListaCaminhos* atual = listaCaminhos;
    while (atual != NULL) {
        printf("%s, ", atual->caminho->origem);
        printf("%s, ", atual->caminho->destino);
        printf("%.lf metros\n", atual->caminho->distancia);
        atual = atual->prox;
    }
}

int main() {
    ListaLocais* listaLocais = NULL;
    ListaCaminhos* listaCaminhos = NULL;
    ListaLocais* listaLocaisAVisitar = NULL;

    const char* nomeArquivoLocais = "locais.csv";
    const char* nomeArquivoCaminhos = "caminhos.csv";

    lerLocais(&listaLocais, nomeArquivoLocais);
    lerCaminhos(&listaCaminhos, nomeArquivoCaminhos, listaLocais);

    printf("Locais lidos:\n");
    imprimirLocais(listaLocais);

    printf("Caminhos lidos:\n");
    imprimirCaminhos(listaCaminhos);
    system("pause");
    printf("Pressione qualquer tecla para encerrar o programa...\n");
    getchar();

    // Criar o grafo e preencher com os dados
    Grafo* grafo = g_cria(MAX_VERTICES, false);

    // A PARTIR DAQUI NAO CONSEGUI FAZER FUNCIONAR 100%

    preencherGrafo(&grafo, &listaLocais, &listaCaminhos);
    // Consultar os caminhos do grafo
    g_arestas(grafo);

    encontrarCaminhoMaisCurto(&grafo, &listaLocaisAVisitar, "saida.txt"); // Encontrar o caminho mais curto

    g_destroi(grafo);
    liberarListaLocais(&listaLocais);
    liberarListaCaminhos(&listaCaminhos);

    return 0;
}