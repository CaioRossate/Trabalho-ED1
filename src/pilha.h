#ifndef PILHA_H
#define PILHA_H

#include <stdlib.h> 

/**
 * @file pilha.h
 * @brief Definições do TAD Pilha (Stack) genérica, implementada com lista encadeada.
 *
 * @details
 * A Pilha utiliza o princípio LIFO (Last-In, First-Out) e é capaz de armazenar 
 * ponteiros genéricos para qualquer forma geométrica, juntamente com o seu tipo.
 */

typedef void *PILHA; // Tipo opaco para a Pilha
typedef void *FORMA; // Tipo opaco para a forma genérica

/**
 * @brief Cria e inicializa uma nova Pilha vazia.
 * @return Um ponteiro para a PILHA criada.
 * @warning Encerra o programa com `exit(1)` se não for possível alocar memória.
 */
PILHA criaPilha();

/**
 * @brief Verifica se a Pilha está vazia.
 * @param p A Pilha a ser verificada.
 * @return 1 se a Pilha estiver vazia, 0 caso contrário.
 */
int PilhaVazia(PILHA p);

/**
 * @brief Insere um novo elemento no topo da Pilha (operação PUSH).
 * @param p A Pilha onde o elemento será inserido.
 * @param forma O ponteiro genérico (FORMA/void*) para o elemento (Ex: CIRCULO, RETANGULO).
 * @param tipo O caractere que representa o tipo do elemento ('c', 'r', 't', 'l').
 * @warning Encerra o programa se ocorrer falha na alocação de memória.
 */
void empilha(PILHA p, FORMA forma, char tipo);

/**
 * @brief Remove e retorna o elemento no topo da Pilha (operação POP).
 * @param p A Pilha da qual o elemento será removido.
 * @return O ponteiro (FORMA/void*) para o elemento removido. Retorna NULL se a Pilha estiver vazia.
 */
FORMA desempilha(PILHA p);

/**
 * @brief Retorna o tipo do elemento que está no topo da Pilha (sem remover).
 * @param p A Pilha a ser consultada.
 * @return O caractere ('c', 'r', 't', 'l') que representa o tipo do elemento no topo. Retorna ' ' se vazia.
 */
char obtemTipoTopoPilha(PILHA p);

/**
 * @brief Retorna o elemento que está no topo da Pilha (sem remover).
 * @param p A Pilha a ser consultada.
 * @return O ponteiro (FORMA/void*) para o elemento no topo. Retorna NULL se vazia.
 */
FORMA obtemTopoPilha(PILHA p);

/**
 * @brief Libera toda a memória alocada para a Pilha e seus nós.
 * @param p O TAD PILHA a ser destruído.
 */
void destroiPilha(PILHA p);

#endif 