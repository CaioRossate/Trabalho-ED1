#ifndef LANCADOR_H
#define LANCADOR_H

#include <stdlib.h>
#include "pilha.h" 

/**
 * @file lancador.h
 * @brief TAD Lançador (Disparador) - controle central do jogo.
 *
 * @details
 * O Lançador gerencia dois carregadores (pilhas esquerda e direita),
 * uma posição de disparo, e é responsável pela mecânica de rotação
 * e disparo de formas na arena.
 */

typedef void *LANCADOR;
typedef void *FORMA;

/**
 * @brief Cria e inicializa um novo Lançador.
 * @param id Identificador único do lançador.
 * @param x Coordenada X da posição do lançador.
 * @param y Coordenada Y da posição do lançador.
 * @return Ponteiro para o LANCADOR criado.
 */
LANCADOR criaLancador(int id, float x, float y);

/**
 * @brief Libera toda a memória alocada pelo Lançador.
 * @param l Ponteiro para o TAD LANCADOR a ser destruído.
 * @details Destrói as pilhas internas e a forma em posição de disparo.
 */
void destroiLancador(LANCADOR l);

/**
 * @brief Adiciona uma forma a um dos carregadores do lançador.
 * @param l Ponteiro para o TAD LANCADOR.
 * @param carregador Caractere indicando o carregador ('e' = esquerda, 'd' = direita).
 * @param forma Ponteiro para a FORMA a ser carregada.
 * @param tipo Caractere representando o tipo da forma ('c', 'r', 't', 'l').
 */
void carregaFormaLancador(LANCADOR l, char carregador, FORMA forma, char tipo);

/**
 * @brief Associa uma pilha (carregador externo) ao lançador.
 * @param l Ponteiro para o TAD LANCADOR.
 * @param carregador PILHA a ser associada (transfere todas as formas).
 * @param lado Caractere indicando o lado ('e' = esquerda, 'd' = direita).
 * @details Transfere todas as formas da pilha externa para a pilha interna do lançador.
 */
void associaCarregadorLancador(LANCADOR l, PILHA carregador, char lado);

/**
 * @brief Move forma do topo da pilha direita para posição de disparo (botão direito).
 * @param l Ponteiro para o TAD LANCADOR.
 * @details Se houver forma em disparo, ela é movida para a pilha esquerda.
 */
void selecionaCargaDireita(LANCADOR l);

/**
 * @brief Move forma do topo da pilha esquerda para posição de disparo (botão esquerdo).
 * @param l Ponteiro para o TAD LANCADOR.
 * @details Se houver forma em disparo, ela é movida para a pilha direita.
 */
void selecionaCargaEsquerda(LANCADOR l);

/**
 * @brief Retorna a forma que está em posição de disparo (sem remover).
 * @param l Ponteiro para o TAD LANCADOR.
 * @return Ponteiro para a FORMA em disparo ou NULL se vazia.
 */
FORMA obtemFormaDisparo(LANCADOR l);

/**
 * @brief Retorna o tipo da forma em posição de disparo.
 * @param l Ponteiro para o TAD LANCADOR.
 * @return Caractere do tipo da forma ou ' ' se vazia.
 */
char obtemTipoFormaDisparo(LANCADOR l);

/**
 * @brief Remove e retorna a forma da posição de disparo (efetua o disparo).
 * @param l Ponteiro para o TAD LANCADOR.
 * @return Ponteiro para a FORMA disparada ou NULL se vazia.
 */
FORMA disparaForma(LANCADOR l);

/**
 * @brief Retorna a coordenada X do lançador.
 * @param l Ponteiro para o TAD LANCADOR.
 * @return Coordenada X da posição do lançador.
 */
float obtemXLancador(LANCADOR l);

/**
 * @brief Retorna a coordenada Y do lançador.
 * @param l Ponteiro para o TAD LANCADOR.
 * @return Coordenada Y da posição do lançador.
 */
float obtemYLancador(LANCADOR l);

/**
 * @brief Retorna a pilha interna de um dos carregadores do lançador.
 * @param l Ponteiro para o TAD LANCADOR.
 * @param lado Caractere indicando o lado ('e' = esquerda, 'd' = direita).
 * @return Ponteiro para a PILHA interna ou NULL se inválido.
 */
PILHA obtemCarregadorLancador(LANCADOR l, char lado);

#endif