#ifndef QRY_H
#define QRY_H

#include <stdio.h>
#include "fila.h"

/**
 * @file qry.h
 * @brief Módulo de processamento de arquivos .qry.
 * 
 * @details
 * Este módulo processa comandos de consulta e manipulação das formas,
 * incluindo posicionamento de disparadores, carregamento, disparos e
 * cálculo de colisões.
 */

/**
 * @brief Processa um arquivo .qry executando os comandos sequencialmente.
 * @param pathQry Caminho completo para o arquivo .qry.
 * @param pathTxt Caminho completo para o arquivo de texto de saída (.txt).
 * @param chao FILA contendo as formas disponíveis no chão.
 */
void processarQry(const char *pathQry, const char *pathTxt, FILA chao);

#endif