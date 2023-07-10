#include "lista.h"
#include "arvore.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remover_Funcionarios_Codigo(Lista** lista, int codigo){ // Funcao que remove todos os funcionarios de uma filial
    Lista *aux = *lista;
    
    while(aux != NULL){
        Lista* removido = remover_Dado_Codigo(lista, codigo);
        aux = aux->prox;
    }
}

void digitar_Dados_Arvore(Arvore** raiz){ // Funcao que digita os dados da arvore
    int codigo;
    char razaoSocial[50];
    char endereco[50];

    printf("Digite o codigo da empresa: ");
    scanf("%d", &codigo);

    setbuf(stdin, NULL);
    printf("Digite a razao social da empresa: ");
    fgets(razaoSocial, 50, stdin);
	razaoSocial[strcspn(razaoSocial, "\n")] = '\0';

    setbuf(stdin, NULL);
    printf("Digite o endereco da empresa: ");
    fgets(endereco, 50, stdin);
    endereco[strcspn(endereco, "\n")] = '\0';

    *raiz = inserir_Dados_Arvore(*raiz, codigo, razaoSocial, endereco);
}

void menu_Relatorios(Lista* lista, Arvore* raiz){ // Funcao que imprime os menus de relatorios
    int opcao;

    do{
        printf("    | Menu de relatorios\n");
        printf("----|-------------------------------\n");
        printf("    | 1 - Listar filiais\n");
        printf("    | 2 - Listar funcionarios\n");
        printf("    | 3 - Voltar ao menu principal\n    |\n");
        printf("    | Digite a opcao desejada: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                system("cls");

                imprimir_Dados_Arvore(raiz);

                system("pause");
                system("cls");

                break;

            case 2:
                system("cls");

                imprimir_Dados_Lista(lista);

                system("pause");
                system("cls");

                break;

            case 3:
                system("cls");
                break;

            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while(opcao != 3);
}

void menu_Cadastros(Lista** lista, Arvore** raiz){ // Funcao que imprime os menus de cadastros
    int opcao, cpf, codigo;

    do{
		system("cls");
        printf("    | Menu de cadastros\n");
        printf("----|-------------------------------\n");
        printf("    | 1 - Cadastrar filial\n");
        printf("    | 2 - Desfazer filial\n");
        printf("    | 3 - Cadastrar funcionario\n");
        printf("    | 4 - Demitir funcionario\n");
        printf("    | 5 - Voltar ao menu principal\n    |\n");
        printf("    | Digite a opcao desejada: ");
        scanf("%d", &opcao);

        switch(opcao){

            case 1: // Cadastrar filial
                system("cls");

                digitar_Dados_Arvore(raiz);

                system("cls");
                break;

            case 2: // Desfazer filial               
                system("cls");
                printf("Digite o codigo da filial que deseja desfazer: ");
                scanf("%d", &codigo);

                remover_Funcionarios_Codigo(lista, codigo);
                Arvore* removido_arvore = remover_Dado_Arvore(raiz, codigo);
                    
                system("pause");
                system("cls");
                break;
                
            case 3: // Cadastrar funcionario
            	system("cls");

                preencher_Dados_Lista(lista, raiz);

                system("cls");
                break;

            case 4: // Demitir funcionario
                system("cls");
                printf("Digite o CPF do funcionario que deseja demitir: ");
                scanf("%d", &cpf);

                Lista* removido_lista = remover_Dado_CPF(lista, cpf);

                if(removido_lista != NULL){
                    printf("[AVISO] Funcionario de CPF %d removido com sucesso!\n", cpf);
                }
                system("pause");
                system("cls");
                break;

            case 5: // Voltar ao menu principal
                system("cls");
                break;

            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while(opcao != 5);
}

int main(){
    Arvore* raiz = NULL;
    Lista* lista = NULL;
    int opcao;

    do{
        printf("    | Sistema de gerenciamento de funcionarios\n");
        printf("----|----------------------------------------------\n");
        printf("    | 1 - Menu de cadastro\n");
        printf("    | 2 - Menu de relatorios\n");
        printf("    | 3 - Sair\n    |\n");
        printf("    | Digite a opcao desejada: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                system("cls");
                menu_Cadastros(&lista, &raiz);
                break;

            case 2:
                system("cls");
                menu_Relatorios(lista, raiz);
                break;

            case 3:
                system("cls");
                break;

            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while(opcao != 3);

    printf("[AVISO] Programa encerrado!\n");
}


