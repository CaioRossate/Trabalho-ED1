#include "qry.h"
#include "lancador.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "intersecao.h"
#include "util_forma.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TAM_LINHA_MAX 512
#define MAX_LANCADORES 100
#define MAX_CARREGADORES 100

typedef struct {
    int totalInstrucoes;
    int totalDisparos;
    int totalEsmagados;
    int totalClonados;
    float pontuacaoTotal;
} Estatisticas;

static LANCADOR lancadores[MAX_LANCADORES] = {NULL};
static PILHA carregadores[MAX_CARREGADORES] = {NULL};

void limpaLancadores() {
    for (int i = 0; i < MAX_LANCADORES; i++) {
        if (lancadores[i] != NULL) {
            destroiLancador(lancadores[i]);
            lancadores[i] = NULL;
        }
    }
}

void limpaCarregadores() {
    for (int i = 0; i < MAX_CARREGADORES; i++) {
        if (carregadores[i] != NULL) {
            destroiPilha(carregadores[i]);
            carregadores[i] = NULL;
        }
    }
}

FORMA clonarForma(FORMA forma, char tipo, int novoID) {
    if (tipo == 'c') {
        CIRCULO c = (CIRCULO)forma;
        return cria_circulo(novoID, getXCirculo(c), getYCirculo(c), getRaioCirculo(c), getCorBCirculo(c), getCorPCirculo(c));
    }
    else if (tipo == 'r') {
        RETANGULO r = (RETANGULO)forma;
        return cria_retangulo(novoID, getXRetangulo(r), getYRetangulo(r), getLarguraRetangulo(r), getAlturaRetangulo(r), getCorBRetangulo(r), getCorPRetangulo(r));
    }
    else if (tipo == 'l') {
        LINHA l = (LINHA)forma;
        return criaLinha(novoID, getX1Linha(l), getY1Linha(l),getX2Linha(l), getY2Linha(l), getCorLinha(l));
    }
    else if (tipo == 't') {
        TEXTO t = (TEXTO)forma;
        return cria_texto(novoID, getXTexto(t), getYTexto(t), getAncoraTexto(t), getCorBTexto(t), getCorPTexto(t), getTxtoTexto(t), getFontFamilyTexto(t), getFontWeightTexto(t), getFontSizeTexto(t));
    }
    return NULL;
}

void cmd_pd(int id, float x, float y, FILE *txt) {
    if (id >= 0 && id < MAX_LANCADORES) {
        if (lancadores[id] != NULL) {
            destroiLancador(lancadores[id]);
        }
        lancadores[id] = criaLancador(id, x, y);
        
        if (txt) {
            fprintf(txt, "[PD] Disparador %d posicionado em (%.2f, %.2f)\n\n", id, x, y);
        }
    }
}

void cmd_lc(int idCarreg, int n, FILA chao, FILE *txt) {
    if (idCarreg < 0 || idCarreg >= MAX_CARREGADORES) return;
    
    if (carregadores[idCarreg] == NULL) {
        carregadores[idCarreg] = criaPilha();
    }
    
    if (txt) {
        fprintf(txt, "[LC] Carregando %d formas no carregador %d\n", n, idCarreg);
    }
    
    int carregadas = 0;
    for (int i = 0; i < n && !FilaVazia(chao); i++) {
        char tipo = obtemTipoPrimeiroFila(chao);
        FORMA forma = desenfileira(chao);
        
        if (forma != NULL) {
            empilha(carregadores[idCarreg], forma, tipo);
            carregadas++;
            
            if (txt) {
                fprintf(txt, "  - Forma tipo '%c' carregada\n", tipo);
            }
        }
    }
    
    if (txt) {
        fprintf(txt, "Total: %d formas carregadas\n\n", carregadas);
    }
}

void cmd_atch(int idDisp, int idEsq, int idDir, FILE *txt) {
    if (idDisp < 0 || idDisp >= MAX_LANCADORES || lancadores[idDisp] == NULL) {
        
        return;
    }
    
    LANCADOR l = lancadores[idDisp];
    if (carregadores[idEsq] == NULL){
        carregadores[idEsq] = criaPilha();
    }

    if (carregadores[idDir] == NULL){
        carregadores[idDir] = criaPilha();
    }

    if (idEsq >= 0 && idEsq < MAX_CARREGADORES) {
        associaCarregadorLancador(l, carregadores[idEsq], 'e');
    }
    
    if (idDir >= 0 && idDir < MAX_CARREGADORES) {
        associaCarregadorLancador(l, carregadores[idDir], 'd');
    }
    
    if (txt) {
        fprintf(txt, "[ATCH] Carregadores %d (esquerda) e %d (direita) associados ao disparador %d\n\n", idEsq, idDir, idDisp);
    }
}

void cmd_shft(int idDisp, char lado, int n, FILE *txt) {
    if (idDisp < 0 || idDisp >= MAX_LANCADORES || lancadores[idDisp] == NULL) {
        if (txt) fprintf(txt, "[SHFT] ERRO: Disparador %d não existe\n\n", idDisp);
        return;
    }
    
    LANCADOR l = lancadores[idDisp];
    
    if (txt) {
        fprintf(txt, "[SHFT] Disparador %d: Botão '%c' pressionado %d vezes\n", idDisp, lado, n);
    }
    
    for (int i = 0; i < n; i++) {
        if (lado == 'e' || lado == 'E') {
            selecionaCargaDireita(l);
        } else if (lado == 'd' || lado == 'D') {
            selecionaCargaEsquerda(l);
        }
    }
    
    FORMA formaAtual = obtemFormaDisparo(l);
    char tipoAtual = obtemTipoFormaDisparo(l);
    
    if (txt) {
        if (formaAtual != NULL) {
            fprintf(txt, "Forma em posição de disparo: tipo '%c'\n\n", tipoAtual);
        } else {
            fprintf(txt, "Posição de disparo vazia\n\n");
        }
    }
}

void cmd_dsp(int idDisp, float dx, float dy, FILA arena, FILE *txt, Estatisticas *stats, char vi, FILA chao) { 
    if (idDisp < 0 || idDisp >= MAX_LANCADORES || lancadores[idDisp] == NULL) {
        if (txt) fprintf(txt, "[DSP] ERRO: Disparador %d não existe\n\n", idDisp);
        return;
    }
    
    LANCADOR l = lancadores[idDisp];
    char tipo = obtemTipoFormaDisparo(l);
    FORMA forma = disparaForma(l);
    
    if (forma == NULL) {
        if (txt) fprintf(txt, "[DSP] Nenhuma forma para disparar\n\n");
        return;
    }
    
    float xLancador = obtemXLancador(l);
    float yLancador = obtemYLancador(l);

    moveForma(forma, tipo, dx + xLancador, dy + yLancador);
    enfileira(arena, forma, tipo);
    
    if (vi == 'v') {
        LINHA linhaX = criaLinha(0, xLancador, yLancador + dy, xLancador + dx, yLancador + dy, "#FF0000");

        LINHA linhaY = criaLinha(0, xLancador + dx, yLancador, xLancador + dx, yLancador + dy, "#FF0000");

        enfileira(chao, linhaX, 'l');
        enfileira(chao, linhaY, 'l');
      }

    stats->totalDisparos++;
    
    if (txt) {
        fprintf(txt, "[DSP] Disparo realizado do disparador %d\n", idDisp);
        fprintf(txt, "Tipo: '%c', Deslocamento: (%.2f, %.2f)\n\n", tipo, dx, dy);
    }

}

void cmd_rjd(int idDisp, char lado, float dx, float dy, float ix, float iy, FILA arena, FILE *txt, Estatisticas *stats){
    if (idDisp < 0 || idDisp >= MAX_LANCADORES || lancadores[idDisp] == NULL) {
        if (txt) fprintf(txt, "[RJD] ERRO: Disparador %d não existe\n\n", idDisp);
        return;
    }
    
    LANCADOR l = lancadores[idDisp];
    
    PILHA p = lado == 'e' ? obtemCarregadorLancador(l, 'd') : obtemCarregadorLancador(l, 'e');
    int i = 1;
    
    while(!PilhaVazia(p) ){
        char tipo = obtemTipoTopoPilha(p);
        FORMA forma = desempilha(p);
        
        float xLancador = obtemXLancador(l);
        float yLancador = obtemYLancador(l);
        
        moveForma(forma, tipo, dx + xLancador + i * ix, dy + yLancador + i * iy);
        enfileira(arena, forma, tipo);
        
        stats->totalDisparos++;
        i++;
        if (txt) {
            fprintf(txt, "[RJD] Disparo realizado do disparador %d pelo lado '%c'\n", idDisp, lado);
            fprintf(txt, "Tipo: '%c', Deslocamento: (%.2f, %.2f)\n\n", tipo, dx, dy);
        }
    }
}

void cmd_calc(FILA arena, FILA chao, FILE *txt, Estatisticas *stats) {
    if (txt) {
        fprintf(txt, "\n========================================\n");
        fprintf(txt, "[CALC] Processando arena\n");
        fprintf(txt, "========================================\n");
    }
    
    float areaEsmagadaRound = 0.0;
    int maxID = 100000;
    
    while (!FilaVazia(arena)) {
        char tipoI = obtemTipoPrimeiroFila(arena);
        FORMA formaI = desenfileira(arena);
        
        if (FilaVazia(arena)) {
            enfileira(chao, formaI, tipoI);
            break;
        }
        
        char tipoJ = obtemTipoPrimeiroFila(arena);
        FORMA formaJ = desenfileira(arena);
        
        float areaI = obterAreaForma(formaI, tipoI);
        float areaJ = obterAreaForma(formaJ, tipoJ);
        
        bool intersecta = verificaIntersecao(formaI, tipoI, formaJ, tipoJ);
        fprintf(txt, "Verificando interseção entre formas '%d' e '%d': %s\n", obtemIDforma(formaI, tipoI), obtemIDforma(formaJ, tipoJ), intersecta ? "SIM" : "NÃO");
        if (intersecta) {
            if (areaI < areaJ) {
                if (txt) {
                    fprintf(txt, "ESMAGAMENTO: Forma '%c' (área %.2f) esmagada por '%c' (área %.2f)\n", tipoI, areaI, tipoJ, areaJ);
                }
                
                areaEsmagadaRound += areaI;
                stats->totalEsmagados++;

                TEXTO asterisco = cria_texto(-1, obtemXforma(formaI, tipoI), obtemYforma(formaI, tipoI), 'm', "red", "red", "*", "sans-serif", "normal", "16");
                destroiForma(formaI, tipoI);
                enfileira(chao, formaJ, tipoJ);
                enfileira(chao, asterisco, 't');
            }
            else if (areaI > areaJ) {
                if (txt) {
                    fprintf(txt, "MUDANÇA DE COR: Forma '%c' muda cor de '%c'\n", tipoI, tipoJ);
                }
                
                char corParaAplicar[20];
                
                // Determina qual cor usar baseado no tipo de I
                if (tipoI == 'c') {
                    // I é CÍRCULO: usa cor de preenchimento
                    strncpy(corParaAplicar, getCorPCirculo((CIRCULO)formaI), sizeof(corParaAplicar)-1);
                    corParaAplicar[sizeof(corParaAplicar)-1] = '\0';
                    
                    if (txt) {
                        fprintf(txt, "  Círculo: usando cor de preenchimento '%s'\n", corParaAplicar);
                    }
                }
                else if (tipoI == 'r') {
                    strncpy(corParaAplicar, getCorPRetangulo((RETANGULO)formaI), sizeof(corParaAplicar)-1);
                    corParaAplicar[sizeof(corParaAplicar)-1] = '\0';
                    
                    if (txt) {
                        fprintf(txt, "  Retângulo: usando cor de preenchimento '%s'\n", corParaAplicar);
                    }
                }
                else if (tipoI == 'l') {
                    char *corLinha = getCorLinha((LINHA)formaI);
                    obterCorComplementar(corLinha, corParaAplicar);
                    
                    if (txt) {
                        fprintf(txt, "  Linha: cor original '%s' -> complementar '%s'\n", corLinha, corParaAplicar);
                    }
                }
                else if (tipoI == 't') {
                    strncpy(corParaAplicar, getCorPTexto((TEXTO)formaI), sizeof(corParaAplicar)-1);
                    corParaAplicar[sizeof(corParaAplicar)-1] = '\0';
                    
                    if (txt) {
                        fprintf(txt, "  Texto: usando cor de preenchimento '%s'\n", corParaAplicar);
                    }
                }
                else {
                    strcpy(corParaAplicar, "#000000");
                }
                
                if (tipoJ == 'c') {
                    setCorBCirculo((CIRCULO)formaJ, corParaAplicar);
                } 
                else if (tipoJ == 'r') {
                    setCorBRetangulo((RETANGULO)formaJ, corParaAplicar);
                } 
                else if (tipoJ == 'l') {
                    definirCorLinha((LINHA)formaJ, corParaAplicar);
                } 
                else if (tipoJ == 't') {
                    setCorBTexto((TEXTO)formaJ, corParaAplicar);
                }
                
                if (txt) {
                    fprintf(txt, "  Nova cor de borda de J: '%s'\n", corParaAplicar);
                }
                
                enfileira(chao, formaI, tipoI);
                enfileira(chao, formaJ, tipoJ);
                
                maxID++;
                FORMA clone = clonarForma(formaI, tipoI, maxID);
                if (clone != NULL) {
                    enfileira(chao, clone, tipoI);
                    stats->totalClonados++;
                    if (txt) fprintf(txt, "Clone criado (ID: %d)\n", maxID);
                }
            }
        } else {
            enfileira(chao, formaI, tipoI);
            enfileira(chao, formaJ, tipoJ);
        }
    }
    
    stats->pontuacaoTotal += areaEsmagadaRound;
    
    if (txt) {
        fprintf(txt, "Área esmagada neste round: %.2f\n", areaEsmagadaRound);
        fprintf(txt, "========================================\n\n");
    }
}

void processarQry(const char *pathQry, const char *pathTxt, FILA chao) {
    FILE *qryFile = fopen(pathQry, "r");
    if (qryFile == NULL) {
        fprintf(stderr, "ERRO: Não foi possível abrir %s\n", pathQry);
        return;
    }

    FILE *txtFile = NULL;
    if (pathTxt != NULL && pathTxt[0] != '\0') {
        txtFile = fopen(pathTxt, "w");
        if (txtFile == NULL) {
            fprintf(stderr, "ERRO: Não foi possível criar %s\n", pathTxt);
            fclose(qryFile);
            return;
        }

        FILA arena = criaFila();
        Estatisticas stats = {0, 0, 0, 0, 0.0};
        
        char linha[TAM_LINHA_MAX];
        
        while (fgets(linha, TAM_LINHA_MAX, qryFile) != NULL) {
            size_t len = strlen(linha);
            if (len > 0 && linha[len - 1] == '\n') {
                linha[len - 1] = '\0';
            }
            
            if (linha[0] == '\0' || linha[0] == '#') {
                continue;
            }
            
            char comando[10];
            sscanf(linha, "%9s", comando);
            
            stats.totalInstrucoes++;
            
            if (strcmp(comando, "pd") == 0) {
                int id;
                float x, y;
                sscanf(linha, "pd %d %f %f", &id, &x, &y);
                cmd_pd(id, x, y, txtFile);
            }
            else if (strcmp(comando, "lc") == 0) {
                int idCarreg, n;
                sscanf(linha, "lc %d %d", &idCarreg, &n);
                cmd_lc(idCarreg, n, chao, txtFile);
            }
            else if (strcmp(comando, "atch") == 0) {
                int idDisp, idEsq, idDir;
                sscanf(linha, "atch %d %d %d", &idDisp, &idEsq, &idDir);
                cmd_atch(idDisp, idEsq, idDir, txtFile);
            }
            else if (strcmp(comando, "shft") == 0) {
                int idDisp, n;
                char lado;
                sscanf(linha, "shft %d %c %d", &idDisp, &lado, &n);
                cmd_shft(idDisp, lado, n, txtFile);
            }
            else if (strcmp(comando, "dsp") == 0) {
                int idDisp;
                float dx, dy;
                char vi;
                sscanf(linha, "dsp %d %f %f %c", &idDisp, &dx, &dy, &vi);
                cmd_dsp(idDisp, dx, dy, arena, txtFile, &stats, vi, chao);
            }
            else if (strcmp(comando, "rjd") == 0) {
                int idDisp;
                char lado;
                float dx, dy, ix, iy;
                sscanf(linha, "rjd %d %c %f %f %f %f", &idDisp, &lado, &dx, &dy, &ix, &iy);
                cmd_rjd(idDisp, lado, dx, dy, ix, iy, arena, txtFile, &stats);
            }
            else if (strcmp(comando, "calc") == 0) {
                cmd_calc(arena, chao, txtFile, &stats);
            }
        }
        
        if (txtFile) {
            fprintf(txtFile, "\n========== ESTATÍSTICAS FINAIS ==========\n");
            fprintf(txtFile, "Pontuação Total: %.2f\n", stats.pontuacaoTotal);
            fprintf(txtFile, "Instruções Executadas: %d\n", stats.totalInstrucoes);
            fprintf(txtFile, "Total de Disparos: %d\n", stats.totalDisparos);
            fprintf(txtFile, "Formas Esmagadas: %d\n", stats.totalEsmagados);
            fprintf(txtFile, "Formas Clonadas: %d\n", stats.totalClonados);
            fprintf(txtFile, "=========================================\n");
        }
        
        limpaLancadores();
        limpaCarregadores();
        destroiFila(arena);
        
        fclose(qryFile);
        if (txtFile) fclose(txtFile);
    }
}