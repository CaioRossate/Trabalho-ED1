#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"
#include "util_forma.h"

typedef struct No {
    FORMA elemento;
    char tipo_elemento; 
    struct No *prox;
} No;

typedef struct {
    No *topo; 
} Pilha;


PILHA criaPilha() {
    Pilha *p = (Pilha*) malloc(sizeof(Pilha));
    if (p == NULL) {
        fprintf(stderr, "ERRO: Falha ao alocar memória para a Pilha.\n");
        exit(1);
    }
    p->topo = NULL;
    return p;
}

int PilhaVazia(PILHA p) {
    Pilha *pilha = (Pilha*)p;
    return pilha->topo == NULL;
}

void empilha(PILHA p, FORMA forma, char tipo) {
    Pilha *pilha = (Pilha*)p;

    No *novo = (No*) malloc(sizeof(No));
    if (novo == NULL) {
        fprintf(stderr, "ERRO: Falha ao alocar memória para o nó da Pilha.\n");
        exit(1);
    }

    novo->elemento = forma;
    novo->tipo_elemento = tipo;
    
    novo->prox = pilha->topo; 
    
    pilha->topo = novo;
}

FORMA desempilha(PILHA p) {
    Pilha *pilha = (Pilha*)p;
    FORMA elemento = NULL;

    if (PilhaVazia(p)) {
        return NULL; 
    }

    No *removido = pilha->topo;
    elemento = removido->elemento;
    
    pilha->topo = removido->prox; 

    free(removido);
    return elemento;
}

FORMA obtemTopoPilha(PILHA p) {
    Pilha *pilha = (Pilha*)p;

    if (PilhaVazia(p)) {
        return NULL;
    }
    return pilha->topo->elemento;
}

char obtemTipoTopoPilha(PILHA p) {
    Pilha *pilha = (Pilha*)p;

    if (PilhaVazia(p)) {
        return ' '; 
    }
    return pilha->topo->tipo_elemento;
}


void destroiPilha(PILHA p) {
    Pilha *pilha = (Pilha*)p;
    No *atual = pilha->topo;
    No *proximo;

    while (atual != NULL) {
        proximo = atual->prox;
        if (atual->elemento != NULL) {
            destroiForma(atual->elemento, atual->tipo_elemento);
        }
        free(atual);
        atual = proximo;
    }
    free(pilha);
}