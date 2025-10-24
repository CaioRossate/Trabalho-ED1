#ifndef FILA_H
#define FILA_H

#include <stdlib.h> 

/**
 * @file fila.h
 * @brief Definições do TAD Fila (Queue) genérica, implementada com lista encadeada.
 *
 * @details
 * A Fila utiliza o princípio FIFO (First-In, First-Out).
 */

typedef void *FILA; // Tipo opaco para a Fila
typedef void *FORMA; // Tipo opaco para a forma genérica

/**
 * @brief Cria e inicializa uma nova Fila vazia.
 * @return Um ponteiro para a FILA criada.
 * @warning Encerra o programa com `exit(1)` se não for possível alocar memória.
 */
FILA criaFila();

/**
 * @brief Verifica se a Fila está vazia.
 * @param f A Fila a ser verificada.
 * @return 1 se a Fila estiver vazia, 0 caso contrário.
 */
int FilaVazia(FILA f);

/**
 * @brief Insere um novo elemento no final da Fila (fim).
 * @param f A Fila onde o elemento será inserido.
 * @param forma O ponteiro genérico (FORMA/void*) para o elemento (Ex: CIRCULO, RETANGULO).
 * @param tipo O caractere que representa o tipo do elemento ('c', 'r', 't', 'l').
 * @warning Encerra o programa se ocorrer falha na alocação de memória.
 */
void enfileira(FILA f, FORMA forma, char tipo);

/**
 * @brief Remove e retorna o elemento no início da Fila (início).
 * @param f A Fila da qual o elemento será removido.
 * @return O ponteiro (FORMA/void*) para o elemento removido. Retorna NULL se a Fila estiver vazia.
 */
FORMA desenfileira(FILA f);

/**
 * @brief Retorna o tipo do elemento que está no início da Fila (sem remover).
 * @param f A Fila a ser consultada.
 * @return O caractere ('c', 'r', 't', 'l') que representa o tipo do elemento no início. Retorna ' ' se vazia.
 */
char obtemTipoPrimeiroFila(FILA f);

/**
 * @brief Retorna o elemento que está no início da Fila (sem remover).
 * @param f A Fila a ser consultada.
 * @return O ponteiro (FORMA/void*) para o elemento no início. Retorna NULL se vazia.
 */
FORMA obtemPrimeiroFila(FILA f);

/**
 * @brief Libera toda a memória alocada para a Fila e seus nós.
 * @param f O TAD FILA a ser destruído.
 */
void destroiFila(FILA f);

/**
 * @brief Retorna um iterador para o primeiro nó da fila.
 * @param f A fila.
 * @return Ponteiro opaco para o primeiro nó ou NULL se vazia.
 */
void* obtemPrimeiroNoFila(FILA f);

/**
 * @brief Retorna o próximo nó do iterador.
 * @param no O nó atual.
 * @return Ponteiro opaco para o próximo nó ou NULL se fim.
 */
void* obtemProximoNoFila(void* no);

/**
 * @brief Retorna a forma armazenada em um nó.
 * @param no O nó.
 * @return Ponteiro para a FORMA.
 */
FORMA obtemFormaDoNo(void* no);

/**
 * @brief Retorna o tipo da forma armazenada em um nó.
 * @param no O nó.
 * @return O caractere do tipo ('c', 'r', 'l', 't').
 */
char obtemTipoDoNo(void* no);


#endif 