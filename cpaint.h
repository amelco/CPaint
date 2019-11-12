/*** funcoes do programa ***/
#ifndef cpaint_h
#define cpaint_h

#include "globals.h"

/// Inicialização.
/// Apenas inicializa variáveis com seus valores padrão.
void init();        // inicializa as variáveis

/// Mensagem inicial.
/// Mostra a tela de apresentação do programa.
void msg_inicial();

/// Traduz comando.
/// Transforma a string comando em um vetor de strings contendo o comando e seus argumentos.
/// @param[in]  comando  string com comando completo.
/// @param[out]  cmd      vetor de string contendo o comando e seus parâmetros.
/// @param[out] np       número de parametros.
void t_comando(char comando[TAM_MAX_CMD], char cmd[NUM_MAX_PRM][TAM_MAX_CMD], int* np);

/// Interpretador de comando.
/// Iterpreta o comando recebido e chama a função apropriada.
/// @param[in] np   número de parâmetros.
/// @param[in] cmd  comando e seus parâmetros (se houverem).
void interpreta(int np, char cmd[NUM_MAX_PRM][TAM_MAX_CMD]);

/// Ajuda.
/// Mostra os comandos possíveis de serem executados com uma breve descrição sobre eles.
void help();

/// Sair.
/// Sai do programa.
void quit();

/// Lê arquivo de entrada.
/// Lê um arquivo de entrada e interpreta seus comandos
/// @param[in] arquivo  nome do arquivo de entrada.
void le_arquivo(char arquivo[50]);

/// Imprime a matriz na tela.
/// Imprime a matriz que contém os pontos RGB na tela. É utilizada para debug do software.
/// Seu uso não deve ser feito pelo usuário final.
void print_matriz_tela();

/// Aloca imagem.
/// Aloca uma posição de memória destinada para armazenar a matriz de imagem.
/// @param[in] larg  largura da imagem.
/// @param[in] alt    altura da imagem.
void aloca_imagem(int larg, int alt);

/// Abre arquivo de imagem.
/// Abre um arquivo de imagem previamente criado para a edição.
/// @param[in] nome  nome do arquivo PPM.
void open(char nome[]);

#endif
