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
//retirado de: http://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm#Line_equation
void linha_oct(int x0, int y0, int x1, int y1, char o) {
    int dx, dy, xi, yi, x, y, D;

    dx = x1 - x0;
    dy = y1 - y0;
    
    if (o == 'b') { // baixo
        yi = 1;
        if (dy < 0) {
            yi = -1;
            dy = -dy;
        }
        D = 2*dy - dx;
        y = y0;
        for (x = x0; x<=x1; x++) {
            point(x, y);
            if (D > 0) {
                y = y + yi;
                D = D - 2*dx;
            }
            D = D + 2*dy;
        }
    }
    else {         //alto
        xi = 1;
        if (dx < 0) {
            xi = -1;
            dx = -dx;
        }
        D = 2*dx - dy;
        x = x0;
        for (y = y0; y<=y1; y++) {
            point(x, y);
            if (D > 0) {
                x = x + xi;
                D = D - 2*dy;
            }
            D = D + 2*dx;
        }
    }
}

void line(int x0, int y0, int x1, int y1) {
    if (abs(y1 - y0) < abs(x1 - x0)) {
        if (x0 >  x1) linha_oct(x1, y1, x0, y0, 'b');
        else          linha_oct(x0, y0, x1, y1, 'b');
    } else {
        if (y0 >  y1) linha_oct(x1, y1, x0, y0, 'a');
        else          linha_oct(x0, y0, x1, y1, 'a');
    }
}

void rect(int x, int y, int tam_x, int tam_y) {
   line(x        , y        , x + tam_x, y        );
   line(x + tam_x, y        , x + tam_x, y + tam_y);
   line(x + tam_x, y + tam_y, x        , y + tam_y);
   line(x        , y + tam_y, x        , y        );
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
