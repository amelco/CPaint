#include <stdio.h>
#include <string.h>

#include "drawing.h"
#include "globals.h"

// cria o cabeçalho da imagem
void image(int larg, int alt) {
    strcpy(comand_list[0], "P3\n");
    sprintf(comand_list[1], "%d %d\n", larg, alt);
    strcpy(comand_list[2], "255\n");
    ultima_linha = 2;
    cor branco;
    branco.r = 255;
    branco.g = 0;
    branco.b = 255;
    clear(&branco);
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
void list(bool line_num) {
    printf("\n");
    for (int i=0; i<=ultima_linha; i++) {
        if (line_num) printf("%3d: ", i+1);
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
    ultima_linha = linha-1;
}