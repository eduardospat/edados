#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "funcoes.h"
#include "grafo.h"
#include "lerArquivos.h"

int contarLocais(ListaLocais* listaLocais) {
    int count = 0;
    ListaLocais* atual = listaLocais;
    while (atual != NULL) {
        count++;
        atual = atual->prox;
    }
    return count;
}

void lerLocais(ListaLocais** listaLocais, const char* nomeArquivoLocais) {
    FILE* arquivo = fopen(nomeArquivoLocais, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivoLocais);
        return;
    }

    char linha[150];
    int indice = 0;
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (linha[0] != '\n' && linha[0] != '#') {
            char* token = strtok(linha, ",");
            if (token == NULL) {
                continue;  // Ignorar linhas inválidas sem identificação
            }
            char* identificacao = strdup(token);

            token = strtok(NULL, ",");
            if (token == NULL) {
                free(identificacao);
                continue;  // Ignorar linhas inválidas sem latitude
            }
            double latitude = atof(token);

            token = strtok(NULL, ",");
            if (token == NULL) {
                free(identificacao);
                continue;  // Ignorar linhas inválidas sem longitude
            }
            double longitude = atof(token);

            // Cria um novo local
            Local* local = (Local*)malloc(sizeof(Local));
            local->identificacao = identificacao;
            local->latitude = latitude;
            local->longitude = longitude;
            local->indice = indice;

            // Adiciona o local à lista
            ListaLocais* novoNo = (ListaLocais*)malloc(sizeof(ListaLocais));
            novoNo->local = local;
            novoNo->prox = NULL;

            if (*listaLocais == NULL) {
                *listaLocais = novoNo;
            } else {
                ListaLocais* ultimo = *listaLocais;
                while (ultimo->prox != NULL) {
                    ultimo = ultimo->prox;
                }
                ultimo->prox = novoNo;
            }

            indice++;
        }
    }

    fclose(arquivo);
}

void lerCaminhos(ListaCaminhos** listaCaminhos, const char* nomeArquivoCaminhos, ListaLocais* listaLocais) {
    FILE* arquivo = fopen(nomeArquivoCaminhos, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivoCaminhos);
        return;
    }
    char linha[100];
    char* origem = (char*)malloc(10 * sizeof(char));
    char* destino = (char*)malloc(10 * sizeof(char));

    fgets(linha, sizeof(linha), arquivo);

    while ((fscanf(arquivo,"%s\n", linha)) != -1) {

        int indicevirgula = strchr(linha, ',') - linha; 

        origem = strncpy(origem, linha, indicevirgula);
        origem [indicevirgula] = '\0'; // Adiciona o caractere nulo no final da string
        destino = strncpy(destino, linha + indicevirgula + 1, strlen(linha) - indicevirgula);


        Caminho* novoCaminho = (Caminho*)malloc(sizeof(Caminho));
        
        novoCaminho->origem = (char*)malloc(4 * sizeof(char));
        novoCaminho->destino = (char*)malloc(4 * sizeof(char));
        
        strncpy(novoCaminho->origem, origem, 4);
        strncpy(novoCaminho->destino, destino, 4);
        
        // Calcular a distância em metros
        novoCaminho->distancia = 0.0;
        calcular_Distancia(novoCaminho, listaLocais);

        ListaCaminhos* novoNo = (ListaCaminhos*)malloc(sizeof(ListaCaminhos));
        novoNo->caminho = novoCaminho;
        novoNo->prox = NULL;

        if (*listaCaminhos == NULL) {
            *listaCaminhos = novoNo;
        } else {
            ListaCaminhos* ultimo = *listaCaminhos;
            while (ultimo->prox != NULL) {
                ultimo = ultimo->prox;
            }
            ultimo->prox = novoNo;
        }
    }
    fclose(arquivo);
}

void lerLocaisAVisitar(ListaLocaisAVisitar** listaLocaisAVisitar, const char* nomeArquivoVisita) {
    FILE* arquivo = fopen(nomeArquivoVisita, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivoVisita);
        return;
    }

    char linha[100];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (linha[0] != '\n' && linha[0] != '#') {
            char* token = strtok(linha, "\n");
            char* identificacao = strdup(token);

            LocaisAVisitar* localAVisitar = (LocaisAVisitar*)malloc(sizeof(LocaisAVisitar));
            localAVisitar->identificacao = identificacao;

            ListaLocaisAVisitar* novoNo = (ListaLocaisAVisitar*)malloc(sizeof(ListaLocaisAVisitar));
            novoNo->localAVisitar = localAVisitar;
            novoNo->prox = NULL;

            if (*listaLocaisAVisitar == NULL) {
                *listaLocaisAVisitar = novoNo;
            } else {
                ListaLocaisAVisitar* ultimo = *listaLocaisAVisitar;
                while (ultimo->prox != NULL) {
                    ultimo = ultimo->prox;
                }
                ultimo->prox = novoNo;
            }
        }
    }

    fclose(arquivo);
}

Grafo* lerArquivosCSV(const char* nomeArquivoLocais, const char* nomeArquivoCaminhos) {
    // Criar o grafo
    Grafo* grafo = NULL;

    // Ler os locais do arquivo e inseri-los no grafo
    ListaLocais* listaLocais = NULL;
    lerLocais(&listaLocais, nomeArquivoLocais);

    // Contar o número de locais lidos
    int numLocais = contarLocais(listaLocais);

    // Criar o grafo com o número de locais
    grafo = g_cria(numLocais, false);
    if (grafo == NULL) {
        // Tratar erro na criação do grafo
        return NULL;
    }

    // Inserir os locais no grafo
    int indiceLocal = 0;
    ListaLocais* atual = listaLocais;
    while (atual != NULL) {
        grafo->local[indiceLocal] = atual->local;
        indiceLocal++;
        atual = atual->prox;
    }

    // Liberar a memória da lista de locais
    liberarListaLocais(&listaLocais);

    // Ler as conexões entre os locais do arquivo e inseri-las no grafo
    ListaCaminhos* listaCaminhos = NULL;
    // Ler os caminhos do arquivo
    lerCaminhos(&listaCaminhos, nomeArquivoCaminhos, listaLocais);


    // Percorrer a lista de caminhos e inserir as arestas no grafo
    ListaCaminhos* atualCaminho = listaCaminhos;
    while (atualCaminho != NULL) {
        int indiceOrigem = obterIndiceLocal(grafo, atualCaminho->caminho->origem);
        int indiceDestino = obterIndiceLocal(grafo, atualCaminho->caminho->destino);

        if (indiceOrigem != -1 && indiceDestino != -1) {
            g_ins_aresta(grafo, indiceOrigem, indiceDestino, atualCaminho->caminho->distancia);
        }

        atualCaminho = atualCaminho->prox;
    }

    // Liberar a memória da lista de caminhos
    liberarListaCaminhos(&listaCaminhos);

    return grafo;
}

void gerarArquivoSaida(const char* nomeArquivoSaida, ListaLocaisAVisitar* listaLocaisAVisitar, ListaCaminhos* g_caminho_mais_curto) {
    FILE* arquivo = fopen(nomeArquivoSaida, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de saída\n");
        return;
    }

    // Escreve o cabeçalho
    fprintf(arquivo, "[map]\n");

    ListaCaminhos* caminhoAtual = g_caminho_mais_curto;

    // Escreve o local inicial em coordenadas
    fprintf(arquivo, "%.6f,%.6f(%s)\n", listaLocaisAVisitar->localAVisitar->latitude, listaLocaisAVisitar->localAVisitar->longitude, listaLocaisAVisitar->localAVisitar->identificacao);

    // Percorre os caminhos mais curtos e os locais a visitar
    while (caminhoAtual != NULL && listaLocaisAVisitar != NULL) {
        // Escreve o caminho até o próximo local
        fprintf(arquivo, "%.6f,%.6f(%s)\n", caminhoAtual->localAtual->latitude, caminhoAtual->localAtual->longitude, listaLocaisAVisitar->localAVisitar->identificacao);
        // Avança para o próximo local a visitar
        listaLocaisAVisitar = listaLocaisAVisitar->prox;

        // Verifica se ainda há locais a visitar
        if (listaLocaisAVisitar != NULL) {
            // Escreve o próximo local
            fprintf(arquivo, "%.6f,%.6f(%s)\n", caminhoAtual->localAtual->latitude, caminhoAtual->localAtual->longitude, listaLocaisAVisitar->localAVisitar->identificacao);
        }

        // Avança para o próximo caminho mais curto
        caminhoAtual = caminhoAtual->prox;
    }

    // Escreve o rodapé
    fprintf(arquivo, "[/map]\n");

    fclose(arquivo);
}

void encontrarCaminhoMaisCurto(Grafo* grafo, ListaLocaisAVisitar* listaLocaisAVisitar, const char* nomeArquivoSaida) {
    // Obtenha o local inicial e o local final com base na lista de locais a visitar
    Local* localInicial = listaLocaisAVisitar->localAVisitar;
    Local* localFinal = listaLocaisAVisitar->prox->localAVisitar;

    // Verifique se os locais de origem e destino são válidos
    if (localInicial == NULL || localFinal == NULL) {
        printf("Erro: Locais de origem ou destino inválidos.\n");
        return;
    }

    // Obtenha os índices dos locais de origem e destino
    int indiceLocalInicial = obterIndiceLocal(grafo, localInicial->identificacao);
    int indiceLocalFinal = obterIndiceLocal(grafo, localFinal->identificacao);

    // Verifique se os índices são válidos
    if (indiceLocalInicial == -1 || indiceLocalFinal == -1) {
        printf("Erro: Locais de origem ou destino inválidos.\n");
        return;
    }
    // caminho mais curto usando os índices dos locais
    g_caminho_mais_curto(grafo, indiceLocalInicial, indiceLocalFinal);
    // gerar o arquivo de saída com as informações do caminho mais curto
    gerarArquivoSaida(nomeArquivoSaida, listaLocaisAVisitar, grafo);
}

void liberarListaLocais(ListaLocais* lista) {
    ListaLocais* atual = lista;
    while (atual != NULL) {
        ListaLocais* prox = atual->prox;
        free(atual->local->identificacao);
        free(atual->local);
        free(atual);
        atual = prox;
    }
}

void liberarListaCaminhos(ListaCaminhos* lista) {
    ListaCaminhos* atual = lista;
    while (atual != NULL) {
        ListaCaminhos* prox = atual->prox;
        free(atual->caminho->origem);
        free(atual->caminho->destino);
        free(atual->caminho);
        free(atual);
        atual = prox;
    }
}

void liberarListaLocaisAVisitar(ListaLocaisAVisitar* lista) {
    ListaLocaisAVisitar* atual = lista;
    while (atual != NULL) {
        ListaLocaisAVisitar* prox = atual->prox;
        free(atual->localAVisitar->identificacao);
        free(atual->localAVisitar);
        free(atual);
        atual = prox;
    }
}