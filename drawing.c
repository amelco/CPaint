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

// desenha um poligono
//   entradas: n   -> número de lados
//             pts -> vetor de par de pontos iniciais e finais 
void poligon(int n, ponto pts[n][2]){
    int i;
    ponto p_ini;
    p_ini.x = pts[0][0].x;
    p_ini.y = pts[0][0].y;
    
    printf("POLIGON\n");
    for (i=0; i<n/4; i++) {
        printf("i=%d\n", i);
        line(pts[i][0].x, pts[i][0].y, pts[i][1].x, pts[i][1].y);
        printf("%d %d %d %d\n", pts[i][0].x, pts[i][0].y, pts[i][1].x, pts[i][1].y);
    }
    printf("pts[%d][1].x = %d; p_ini.x = %d\n pts[%d][1].y = %d; p_ini.y = %d\n",
            i-1, pts[i-1][1].x, p_ini.x, i-1, pts[i-1][1].y, p_ini.y);
    // checa se o ultimoo ponto é igual ao primeiro
    //  se não for, traca uma linha para fechar o poligono
    if (pts[i-1][1].x != p_ini.x && pts[i-1][1].y != p_ini.y) {
        line(pts[i-1][1].x, pts[i-1][1].y, p_ini.x, p_ini.y);
    }
}

// mostra o conteudo da lista de comandos
void list() {
    for (int i=0; i<num_linhas; i++) {
        printf("%s", comand_list[i]);
    }
    printf("\n");
    printf("Cor atual: [%3d][%3d][%3d]\n\n", cor_atual.r, cor_atual.g, cor_atual.b);
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
void open(char nome[]){
    FILE* arquivo;
    arquivo = fopen(nome, "r");

    int nlin, ncol;
    char str1[TAM_MAX_CMD];
    char str2[TAM_MAX_CMD];
    char dum[TAM_MAX_CMD];
    
    fgets(str1,TAM_MAX_CMD,arquivo);
    fscanf(arquivo, "%d %d", &nlin, &ncol);
    fgets(str2,TAM_MAX_CMD,arquivo);
    
    char Linha[nlin*ncol+3][TAM_MAX_CMD];
    char scol[TAM_MAX_CMD];
    char slin[TAM_MAX_CMD];
    
    sprintf(scol,"%d", ncol);
    sprintf(slin,"%d", nlin);

    strcpy(Linha[0], str1);
    sprintf(Linha[1],"%s %s", slin, scol);
    strcpy(Linha[2], str2);
    
    
    for (int i = 3; i < nlin*ncol+3; i++) {
        fgets(Linha[i],TAM_MAX_CMD,arquivo);
    }

    aloca_imagem(ncol, nlin);
    
    for (int i = 0; i < nlin*ncol+3; i++) {
        strcpy(comand_list[i], Linha[i]);
    }

    fseek( arquivo, 0, SEEK_SET);
    fgets(dum,TAM_MAX_CMD,arquivo); //Dummy read
    fgets(dum,TAM_MAX_CMD,arquivo);
    fgets(dum,TAM_MAX_CMD,arquivo);

    for (int i = 0; i < nlin; i++) {
        for (int j = 0; j < ncol; j++) {
            fscanf(arquivo, "%d %d %d", &tela->rgb[i][j].r, &tela->rgb[i][j].g, &tela->rgb[i][j].b);
        }
    }

    fclose(arquivo);
}


void save (char nome[]) {
    FILE* arq;
    arq = fopen(nome, "w");

    for (int i=0; i<num_linhas; i++) {
        //printf("%s", comand_list[i]);
        fprintf(arq, "%s", comand_list[i]);
    }
    fclose(arq);
    printf("Arquivo salvo!\n");
}

int fill(int x, int y, int r, int g, int b, int rr, int gg, int bb) {
 
    int passo[8][2] = {{-1,0},{0,-1},{0,1},{1,0},{1,1},{-1,1},{1,-1},{-1,-1}};
    if(tela->rgb[x][y].r == rr && tela->rgb[x][y].g == gg && tela->rgb[x][y].b == bb) {
        tela->rgb[x][y].r = r;
        tela->rgb[x][y].g = g;
        tela->rgb[x][y].b = b;
    
        for(int k = 0; k < 8; k++ )
        {
            int l = x + passo[k][0];
            int c = y + passo[k][1];
    
            if((l >= 0) && (l < tela->alt) && (c >= 0) && (c < tela->larg))
                fill(l, c, r, g, b, rr, gg, bb);
        } 
    }
    else{
        return 0;
    }
    update();
}
    
   
 
    
 
