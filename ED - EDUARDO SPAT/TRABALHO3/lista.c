#include "lista.h"
#include <stdlib.h>


typedef struct _no {
  void* dado;
  struct _no* prox;
  struct _no* ant;
} No;

struct _lista {
  No* inicio;
  No* fim;
  int tamanho;
  int pos_percurso;
};

Lista lista_cria(void) {
  Lista self = malloc(sizeof(struct _lista));
  if (self == NULL) return NULL;
  self->inicio = NULL;
  self->fim = NULL;
  self->tamanho = 0;

  return self;
}

void lista_destroi(Lista self) {
  if (self != NULL) {
    No* atual = self->inicio;
    while (atual != NULL) {
      No* proximo = atual->prox;
      free(atual);
      atual = proximo;
    }
    free(self);
  }
}

int lista_nelem(Lista self) {
  if (self == NULL) return 0;
  return self->tamanho;
}

void *lista_elem_pos(Lista self, int pos) {
  if (self == NULL || pos < 0 || pos >= self->tamanho) return NULL;
  No* atual = self->inicio;
  for (int i = 0; i < pos; i++) {
    atual = atual->prox;
  }
  return atual->dado;
}

void lista_insere_pos(Lista self, void* dado, int pos) {
  if (self == NULL || pos < 0 || pos > self->tamanho) return;
  No* novo_no = malloc(sizeof(No));
  if (novo_no == NULL) return;
  novo_no->dado = dado;

  if (self->tamanho == 0) {
    // Inserção em lista vazia
    novo_no->prox = NULL;
    novo_no->ant = NULL;
    self->inicio = novo_no;
    self->fim = novo_no;
  } else if (pos == 0) {
    // Inserção no início da lista
    novo_no->prox = self->inicio;
    novo_no->ant = NULL;
    self->inicio->ant = novo_no;
    self->inicio = novo_no;
  } else if (pos == self->tamanho) {
    // Inserção no fim da lista
    novo_no->prox = NULL;
    novo_no->ant = self->fim;
    self->fim->prox = novo_no;
    self->fim = novo_no;
  } else {
    // Inserção no meio da lista
    No* atual = self->inicio;
    for (int i = 0; i < pos - 1; i++) {
      atual = atual->prox;
    }
    novo_no->prox = atual->prox;
    novo_no->ant = atual;
    atual->prox->ant = novo_no;
    atual->prox = novo_no;
  }

  self->tamanho++;
}

void lista_insere_inicio(Lista self, void* dado) {
  lista_insere_pos(self, dado, 0);
}

void lista_insere_fim(Lista self, void* dado) {
  lista_insere_pos(self, dado, self->tamanho);
}

void* lista_remove_pos(Lista self, int pos) {
  if (self == NULL || pos < 0 || pos >= self->tamanho) return NULL;
  No* no_removido;

  if (self->tamanho == 1) {
    // Remoção em lista com um único elemento
    no_removido = self->inicio;
    self->inicio = NULL;
    self->fim = NULL;
  } else if (pos == 0) {
    // Remoção do início da lista
    no_removido = self->inicio;
    self->inicio = no_removido->prox;
    self->inicio->ant = NULL;
  } else if (pos == self->tamanho - 1) {
    // Remoção do fim da lista
    no_removido = self->fim;
    self->fim = no_removido->ant;
    self->fim->prox = NULL;
  } else {
    // Remoção do meio da lista
    No* atual = self->inicio;
    for (int i = 0; i < pos; i++) {
      atual = atual->prox;
    }
    no_removido = atual;
    atual->ant->prox = atual->prox;
    atual->prox->ant = atual->ant;
  }

  void* dado = no_removido->dado;
  free(no_removido);
  self->tamanho--;
  return dado;
}

void* lista_remove_inicio(Lista self) {
  return lista_remove_pos(self, 0);
}

void* lista_remove_fim(Lista self) {
  return lista_remove_pos(self, self->tamanho - 1);
}

void* lista_proximo(Lista self) {
  if (self == NULL || self->tamanho == 0 || self->pos_percurso >= self->tamanho) return NULL;
  No* atual = self->inicio;
  for (int i = 0; i < self->pos_percurso; i++) {
    atual = atual->prox;
  }
  self->pos_percurso++;
  return atual->dado;
}

void* lista_percorre(Lista self) {
  if (self == NULL || self->tamanho == 0) return NULL;
  self->pos_percurso = 0;
  return lista_proximo(self);
}
