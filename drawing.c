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

// desenha um ponto com a cor cor_atual
void point(int x, int y) {
    tela->rgb[x][y] = cor_atual;
    update();
}

// desenha uma reta entre 2 pontos
//   retirado de: https://www.thecrazyprogrammer.com/2017/01/dda-line-drawing-algorithm-c-c.html
void line(int x1, int y1, int x2, int y2) {
    float dx, dy, step, x, y;
    
    dx = abs(x2 - x1);
    dy = abs(y2 - y1);
    //printf("%d %d\n", dx, dy);
    if (dx>=dy) step = dx;
    else step = dy;
    dx = dx/step;
    dy = dy/step;
    x = x1;
    y = y1;
    
    int i = 0;
    while(i<=step) {
        //printf("%d %d %d %d\n", i, step, x, y);
        point(x, y);
        x+=dx;
        y+=dy;
        i++;
    }
}

// mostra o conteudo da lista de comandos
void list() {
    printf("Cor atual: [%3d][%3d][%3d]\n\n", cor_atual.r, cor_atual.g, cor_atual.b);
    for (int i=0; i<num_linhas; i++) {
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

void save (char nome[]) {
    FILE* arq;
    arq = fopen(nome, "w");

    for (int i=0; i<num_linhas; i++) {
        printf("%s", comand_list[i]);
        fprintf(arq, "%s", comand_list[i]);
    }
    fclose(arq);
}
