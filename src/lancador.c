#include <stdio.h>
#include <stdlib.h>
#include "lancador.h"
#include "fila.h"
#include "pilha.h"
#include "util_forma.h"

typedef struct {
    int id;
    float x, y;
    PILHA carregadorEsquerda, carregadorDireita;

    FORMA formaDisparo;
    char tipoDisparo; 
} Lancador;


LANCADOR criaLancador(int id, float x, float y) {
    Lancador *l = (Lancador*)malloc(sizeof(Lancador));
    if (l == NULL) {
        fprintf(stderr, "ERRO: Falha ao alocar memória para o Lancador.\n");
        exit(1);
    }

    l->id = id;
    l->x = x;
    l->y = y;

    l->carregadorEsquerda = NULL;
    l->carregadorDireita = NULL; 
    l->formaDisparo = NULL;
    l->tipoDisparo = ' ';

    return l;
}

void destroiLancador(LANCADOR l) {
    Lancador *lancador = (Lancador*)l;
    
    if (lancador != NULL) {
        
        if (lancador->formaDisparo != NULL) {
             destroiForma(lancador->formaDisparo, lancador->tipoDisparo);
        }
        free(lancador);
    }
}

void carregaFormaLancador(LANCADOR l, char carregador, FORMA forma, char tipo) {
    Lancador *lancador = (Lancador*)l;

    if (carregador == 'e') {
        empilha(lancador->carregadorEsquerda, forma, tipo);
    } else if (carregador == 'd') {
        empilha(lancador->carregadorDireita, forma, tipo);
    } else {
        fprintf(stderr, "AVISO: Carregador '%c' inválido. Forma ignorada.\n", carregador);
    }
}

void selecionaCargaDireita(LANCADOR l) {
    Lancador *lancador = (Lancador*)l;
    if (lancador->formaDisparo != NULL) {
        empilha(lancador->carregadorEsquerda, lancador->formaDisparo, lancador->tipoDisparo);
        lancador->formaDisparo = NULL;
        lancador->tipoDisparo = ' ';
    }
    if (PilhaVazia(lancador->carregadorDireita)) {
        return; 
    }
    lancador->tipoDisparo = obtemTipoTopoPilha(lancador->carregadorDireita);
    lancador->formaDisparo = desempilha(lancador->carregadorDireita);
}

void selecionaCargaEsquerda(LANCADOR l) {
    Lancador *lancador = (Lancador*)l;

    if (lancador->formaDisparo != NULL) {
        empilha(lancador->carregadorDireita, lancador->formaDisparo, lancador->tipoDisparo);
        lancador->formaDisparo = NULL;
        lancador->tipoDisparo = ' ';
    }
    
    if (PilhaVazia(lancador->carregadorEsquerda)) {
        return; 
    }

    lancador->tipoDisparo = obtemTipoTopoPilha(lancador->carregadorEsquerda);
    lancador->formaDisparo = desempilha(lancador->carregadorEsquerda);
}


FORMA obtemFormaDisparo(LANCADOR l) {
    Lancador *lancador = (Lancador*)l;
    return lancador->formaDisparo;
}

char obtemTipoFormaDisparo(LANCADOR l) {
    Lancador *lancador = (Lancador*)l;
    return lancador->tipoDisparo;
}

FORMA disparaForma(LANCADOR l) {
    Lancador *lancador = (Lancador*)l;
    FORMA formaDisparada = lancador->formaDisparo;
    lancador->formaDisparo = NULL;
    lancador->tipoDisparo = ' '; 

    return formaDisparada;
}

float obtemXLancador(LANCADOR l) {
    Lancador *lancador = (Lancador*)l;
    return lancador->x;
}

float obtemYLancador(LANCADOR l) {
    Lancador *lancador = (Lancador*)l;
    return lancador->y;
}

void associaCarregadorLancador(LANCADOR l, PILHA carregador, char lado){
    Lancador *lancador = (Lancador*)l;
    if (lado == 'e') {
        lancador->carregadorEsquerda = carregador;
    } else if (lado == 'd') {
        lancador->carregadorDireita = carregador;
    } else {
        fprintf(stderr, "AVISO: Lado '%c' inválido para associação de carregador. Associação ignorada.\n", lado);
    }
}

PILHA obtemCarregadorLancador(LANCADOR l, char lado){
    Lancador *lancador = (Lancador*)l;
    if (lado == 'e') {
        return lancador->carregadorEsquerda;
    } else if (lado == 'd') {
        return lancador->carregadorDireita;
    } else {
        fprintf(stderr, "AVISO: Lado '%c' inválido para obtenção de carregador. Retornando NULL.\n", lado);
        return NULL;
    }
}
