#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "drawing.h"
#include "globals.h"

// cria o cabeçalho da imagem
// realoca matriz tela e command list
void image(int larg, int alt) {
    num_linhas = larg*alt + 3;
    
    strcpy(comand_list[0], "P3\n");
    sprintf(comand_list[1], "%d %d\n", larg, alt);
    strcpy(comand_list[2], "255\n");
    // ultima_linha = 2;

    // clear(&cor_atual);
}

// limpa a tela com uma cor especificada
void clear(cor* c) {
    for (int i=0; i<tela->larg; i++) {
        for (int j=0; j<tela->alt; j++) {
            // printf("%d\n", tela->rgb[i][j].r);
            tela->rgb[i][j].r = c->r; 
            tela->rgb[i][j].g = c->g;
            tela->rgb[i][j].b = c->b;
            // printf("%d %d: %d %d %d\n", i,j, tela->rgb[i][j].r, tela->rgb[i][j].g, tela->rgb[i][j].b);
        }
    }
    update();
}

// mostra o conteudo da lista de comandos
void list() {
    printf("%d\n", num_linhas);
    for (int i=0; i<num_linhas; i++) {
        printf("%s", comand_list[i]);
    }
    printf("\n");
}

// atualiza os dados do comand_list com o que está na matriz
void update() {
    int linha = 3;
    // printf("MAX.LINHAS: %d\n", INC_LINHAS);
    for (int i=0; i<tela->larg; i++) {
        for (int j=0; j<tela->alt; j++) {
            // printf("l %d: %d %d: %d %d %d\n", linha, i,j, tela->rgb[i][j].r, tela->rgb[i][j].g, tela->rgb[i][j].b);
            sprintf(comand_list[linha], "%d %d %d\n", tela->rgb[i][j].r, tela->rgb[i][j].g, tela->rgb[i][j].b);
            linha++;
        }
    }
    // ultima_linha = linha-1;
}