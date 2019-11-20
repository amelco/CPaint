/*** funcoes do programa ***/
#ifndef cpaint_h
#define cpaint_h

#include "globals.h"

/// ### Inicialização.
/// Inicializa variáveis com valores padrão.
/// @note É executado apenas quando o programa inicia.
/// @note        Esta é uma função não disponível ao usuário final.
void init();        // inicializa as variáveis

/// ### Mensagem inicial.
/// Mostra a tela de apresentação do programa.
/// @note        Esta é uma função não disponível ao usuário final.
void msg_inicial();

/// ### Traduz comando.
/// Transforma a string comando em um vetor de strings contendo o comando e seus argumentos.
/// @param[in]  comando  string com comando completo.
/// @param[out]  cmd      vetor de string contendo o comando e seus parâmetros.
/// @param[out] np       número de parametros.
/// @note        Esta é uma função não disponível ao usuário final.
// @attention   Alguma coisa para se atentar
// @warning     Algum aviso
void t_comando(char comando[TAM_MAX_CMD], char cmd[NUM_MAX_PRM][TAM_MAX_CMD], int* np);

/// ### Interpretador de comando.
/// Iterpreta o comando recebido e chama a função apropriada.
/// @param[in] np   número de parâmetros.
/// @param[in] cmd  comando e seus parâmetros (se houverem).
/// @note        Esta é uma função não disponível ao usuário final.
void interpreta(int np, char cmd[NUM_MAX_PRM][TAM_MAX_CMD]);

/// ### Ajuda.
/// Mostra os comandos possíveis de serem executados com uma breve descrição sobre eles.
void help();

/// ### Sair.
/// Sai do programa.
void quit();

/// ### Lê arquivo de entrada.
/// Lê um arquivo de entrada e interpreta seus comandos
/// @param[in]   arquivo  nome do arquivo de entrada.
/// @attention   O último comando presente no arquivo de entrada deve **obrigatoriamente** ser `quit`.
/// @note        Esta é uma função não disponível ao usuário final.
void le_arquivo(char arquivo[50]);

/// ### Imprime a matriz na tela.
/// Imprime a matriz que contém os pontos RGB na tela. É utilizada para debug do software.
/// @see Chamada pela função source()
/// @note        Esta é uma função não disponível ao usuário finala.
void print_matriz_tela();

/// ### Aloca imagem.
/// Aloca uma posição de memória destinada para armazenar a matriz de imagem.
/// @param[in] larg  largura da imagem.
/// @param[in] alt    altura da imagem.
/// @note Chamada pela função image()
/// ### Exemplo
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
/// image 640 480
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
void aloca_imagem(int larg, int alt);

/// ### Aloca imagem a ser copiada.
/// Aloca uma posição de memória destinada para armazenar a matriz da imagem a ser copiada.
/// @param[in] larg  largura da imagem.
/// @param[in] alt    altura da imagem.
void aloca_imcopy(int larg, int alt);

/// ### Abre arquivo de imagem.
/// Abre um arquivo de imagem previamente criado para a edição.
/// @param[in] nome  nome do arquivo PPM.
void open(char nome[]);

#endif
