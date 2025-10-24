#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
#include "util_forma.h"

typedef struct No {
    FORMA elemento;
    char tipo_elemento;
    struct No *prox;
} No;


typedef struct {
    No *inicio; 
    No *fim;
} Fila;


FILA criaFila() {
    Fila *f = (Fila*) malloc(sizeof(Fila));
    if (f == NULL) {
        fprintf(stderr, "ERRO: Falha ao alocar memória para a Fila.\n");
        exit(1);
    }
    f->inicio = NULL;
    f->fim = NULL;
    return f;
}

int FilaVazia(FILA f) {
    Fila *fila = (Fila*)f;
    return fila->inicio == NULL;
}

void enfileira(FILA f, FORMA forma, char tipo) {
    Fila *fila = (Fila*)f;

    No *novo = (No*) malloc(sizeof(No));
    if (novo == NULL) {
        fprintf(stderr, "ERRO: Falha ao alocar memória para o nó da Fila.\n");
        exit(1);
    }

    novo->elemento = forma;
    novo->tipo_elemento = tipo;
    novo->prox = NULL;

    if (FilaVazia(f)) {
        
        fila->inicio = novo;
    } else {
        
        fila->fim->prox = novo;
    }
    
    fila->fim = novo;
}

FORMA desenfileira(FILA f) {
    Fila *fila = (Fila*)f;
    FORMA elemento = NULL;

    if (FilaVazia(f)) {
        return NULL;
    }

    No *removido = fila->inicio;
    elemento = removido->elemento;
    
    fila->inicio = removido->prox;
    
    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }

    free(removido);
    return elemento;
}

FORMA obtemPrimeiroFila(FILA f) {
    Fila *fila = (Fila*)f;

    if (FilaVazia(f)) {
        return NULL;
    }
    return fila->inicio->elemento;
}

char obtemTipoPrimeiroFila(FILA f) {
    Fila *fila = (Fila*)f;

    if (FilaVazia(f)) {
        return ' '; 
    }
    return fila->inicio->tipo_elemento;
}


void destroiFila(FILA f) {
    Fila *fila = (Fila*)f;
    No *atual = fila->inicio;
    No *proximo;

    while (atual != NULL) {
        proximo = atual->prox;
        if (atual->elemento != NULL) {
            destroiForma(atual->elemento, atual->tipo_elemento);
        }
        free(atual);
        atual = proximo;
    }
    free(fila);
}

void* obtemPrimeiroNoFila(FILA f) {
    Fila *fila = (Fila*)f;
    if (fila == NULL) return NULL;
    return (void*)fila->inicio;
}

void* obtemProximoNoFila(void* no) {
    if (no == NULL) return NULL;
    No *n = (No*)no;
    return (void*)n->prox;
}

FORMA obtemFormaDoNo(void* no) {
    if (no == NULL) return NULL;
    No *n = (No*)no;
    return n->elemento;
}

char obtemTipoDoNo(void* no) {
    if (no == NULL) return ' ';
    No *n = (No*)no;
    return n->tipo_elemento;
}