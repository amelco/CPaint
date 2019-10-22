#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "drawing.h"
#include "globals.h"
#include "cpaint.h"

// cria o cabeçalho da imagem
// realoca matriz tela e command list
void image(int larg, int alt) {
    // num_linhas = larg*alt + 3;
    aloca_imagem(larg, alt);
    strcpy(comand_list[0], "P3\n");
    sprintf(comand_list[1], "%d %d\n", larg, alt);
    strcpy(comand_list[2], "255\n");
    clear(&cor_atual);
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

// muda a cor atual
void color(cor* c) {
    cor_atual.r = c->r;
    cor_atual.g = c->g;
    cor_atual.b = c->b;
}

void point(int x, int y) {
    tela->rgb[x][y] = cor_atual;
    update();
}

// mostra o conteudo da lista de comandos
void list() {
    // printf("total: %d\n", num_linhas);
    for (int i=0; i<num_linhas; i++) {
        // printf("%d\n", i);
        printf("%s", comand_list[i]);
    }
    printf("\n");
}

// atualiza os dados do comand_list com o que está na matriz
void update() {
    int linha = 3;
    
    for (int i=0; i<tela->larg; i++) {
        for (int j=0; j<tela->alt; j++) {
            // printf("l %d: %d %d: %d %d %d\n", linha, i,j, tela->rgb[i][j].r, tela->rgb[i][j].g, tela->rgb[i][j].b);
            sprintf(comand_list[linha], "%d %d %d\n", tela->rgb[i][j].r, tela->rgb[i][j].g, tela->rgb[i][j].b);
            linha++;
        }
    }
}
