/*** funcoes do programa ***/
#ifndef cpaint_h
#define cpaint_h

#include "globals.h"

void msg_inicial();
void t_comando(char comando[TAM_MAX_CMD], char cmd[NUM_MAX_PRM][TAM_MAX_CMD], int* np);
void interpreta(int np, char cmd[NUM_MAX_PRM][TAM_MAX_CMD]);
void help();
void quit();
void le_arquivo(char arquivo[50]);
void print_matriz_tela(); // para debug
void aloca_imagem(int larg, int alt);

#endif
