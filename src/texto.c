#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "texto.h"

typedef struct {
    int id;
    float x, y;
    char ancora;
    char *corB;
    char *corP;
    char *txto;
    char *ffamily;
    char *fweight;
    char *fsize;
} texto;

TEXTO cria_texto(int id, float x, float y, char ancora, char* corB, char* corP, char* txto, char* ffamily, char* fweight, char* fsize) {
    texto *t = (texto*) malloc(sizeof(texto));
    if (t == NULL) {
        printf("Erro ao alocar memória para TEXTO.\n");
        exit(1);
    }

    t->id = id;
    t->x = x;
    t->y = y;
    t->ancora = ancora;

    t->corB = malloc(strlen(corB) + 1);
    strcpy(t->corB, corB);

    t->corP = malloc(strlen(corP) + 1);
    strcpy(t->corP, corP);

    t->txto = malloc(strlen(txto) + 1);
    strcpy(t->txto, txto);

    t->ffamily = malloc(strlen(ffamily) + 1);
    strcpy(t->ffamily, ffamily);

    t->fweight = malloc(strlen(fweight) + 1);
    strcpy(t->fweight, fweight);

    t->fsize = malloc(strlen(fsize) + 1);
    strcpy(t->fsize, fsize);

    return t;
}

int getIDTexto(TEXTO t) { return ((texto*)t)->id; }
float getXTexto(TEXTO t) { return ((texto*)t)->x; }
float getYTexto(TEXTO t) { return ((texto*)t)->y; }
char getAncoraTexto(TEXTO t) { return ((texto*)t)->ancora; }
char* getCorBTexto(TEXTO t) { return ((texto*)t)->corB; }
char* getCorPTexto(TEXTO t) { return ((texto*)t)->corP; }
char* getTxtoTexto(TEXTO t) { return ((texto*)t)->txto; }
char* getFontFamilyTexto(TEXTO t) { return ((texto*)t)->ffamily; }
char* getFontWeightTexto(TEXTO t) { return ((texto*)t)->fweight; }
char* getFontSizeTexto(TEXTO t) { return ((texto*)t)->fsize; }

float getAreaTexto(TEXTO t) {
    return 20.0 * strlen(((texto*)t)->txto);
}

void setIDTexto(TEXTO t, int id) { ((texto*)t)->id = id; }
void setXTexto(TEXTO t, float x) { ((texto*)t)->x = x; }
void setYTexto(TEXTO t, float y) { ((texto*)t)->y = y; }
void setAncoraTexto(TEXTO t, char a) { ((texto*)t)->ancora = a; }

void setCorBTexto(TEXTO t, char* corB) {
    texto* tx = (texto*)t;
    free(tx->corB);
    tx->corB = malloc(strlen(corB) + 1);
    strcpy(tx->corB, corB);
}

void setCorPTexto(TEXTO t, char* corP) {
    texto* tx = (texto*)t;
    free(tx->corP);
    tx->corP = malloc(strlen(corP) + 1);
    strcpy(tx->corP, corP);
}

void setTxtoTexto(TEXTO t, char* conteudo) {
    texto* tx = (texto*)t;
    free(tx->txto);
    tx->txto = malloc(strlen(conteudo) + 1);
    strcpy(tx->txto, conteudo);
}

void setFontFamilyTexto(TEXTO t, char* ffamily) {
    texto* tx = (texto*)t;
    free(tx->ffamily);
    tx->ffamily = malloc(strlen(ffamily) + 1);
    strcpy(tx->ffamily, ffamily);
}

void setFontWeightTexto(TEXTO t, char* fweight) {
    texto* tx = (texto*)t;
    free(tx->fweight);
    tx->fweight = malloc(strlen(fweight) + 1);
    strcpy(tx->fweight, fweight);
}

void setFontSizeTexto(TEXTO t, char* fsize) {
    texto* tx = (texto*)t;
    free(tx->fsize);
    tx->fsize = malloc(strlen(fsize) + 1);
    strcpy(tx->fsize, fsize);
}

void liberaTexto(TEXTO t) {
    texto* tx = (texto*)t;
    free(tx->corB);
    free(tx->corP);
    free(tx->txto);
    free(tx->ffamily);
    free(tx->fweight);
    free(tx->fsize);
    free(tx);
}
