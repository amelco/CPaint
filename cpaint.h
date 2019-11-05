/*** funcoes do programa ***/
#ifndef cpaint_h
#define cpaint_h

#include "globals.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

void msg_inicial();
void t_comando(char comando[TAM_MAX_CMD], char cmd[NUM_MAX_PRM][TAM_MAX_CMD], int* np);
void interpreta(int np, char cmd[NUM_MAX_PRM][TAM_MAX_CMD]);
void help();
void quit();
void le_arquivo(char arquivo[50]);
void print_matriz_g_tela(); // para debug
void aloca_imagem(int larg, int alt);
void d_open(char nome[]);
void desenha();

/* ALLEGRO STUFF */

void init_allegro();

ALLEGRO_TIMER* timer;
ALLEGRO_EVENT_QUEUE* queue;
ALLEGRO_DISPLAY* disp;
ALLEGRO_FONT* font;

#endif
