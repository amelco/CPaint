#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "globals.h"
#include "drawing.h"
#include "cpaint.h"


int main() {
    
    /*** Inicialização ***/
    num_linhas = LARG * ALT + 3;
    comand_list = malloc(num_linhas * sizeof(char*));      // primeiramente, aloca INC_LINHAS linhas. Adiciona + INC_LINHAS caso necessário.
    for (int i=0; i<num_linhas; i++) {
        printf("%d\n", i);
        comand_list[i] = malloc(TAM_MAX_CMD * sizeof(char));
    }
    // inicializa ponteiro
    for (int i=0; i<LARG; i++) {
        for (int j=0; j<ALT; j++) {
            comand_list[i][j] = '\0';
        }
    }

    tela = malloc(sizeof(matriz));
    tela->larg = LARG;
    tela->alt = ALT;
    tela->rgb = malloc(LARG * sizeof(cor));
    for (int i=0; i<LARG; i++) {
        tela->rgb[i] = malloc(ALT * sizeof(cor));
    }
    // inicializa ponteiro
    for (int i=0; i<LARG; i++) {
        for (int j=0; j<ALT; j++) {
            tela->rgb[i][j].r = 0;
            tela->rgb[i][j].g = 0;
            tela->rgb[i][j].b = 0;
        }
    }
    
    cor_atual.r = 0;
    cor_atual.g = 0;
    cor_atual.b = 0;
    image(LARG, ALT);       // chama a função para definir um cabeçalho padrão
    clear(&cor_atual);
    
    /*** Início do programa ***/
    msg_inicial();
    
    while (1) {
        char comando[TAM_MAX_CMD];
        char cmd[NUM_MAX_PRM][TAM_MAX_CMD];
        int num_param = 0;

        printf(">> ");
        scanf(" %[^\n]", &comando);
        t_comando(comando, cmd, &num_param);
        interpreta(num_param, cmd);
        // print_matriz_tela();
    }
    
    // quit();
    return 0;
}