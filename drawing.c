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
    for (int i=0; i<tela->alt; i++) {
        for (int j=0; j<tela->larg; j++) {
            tela->rgb[i][j].r = c->r; 
            tela->rgb[i][j].g = c->g;
            tela->rgb[i][j].b = c->b;
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

void brush_width(int n) {
    espessura = n;
}

// desenha um ponto com a cor cor_atual
void point(int x, int y, bool isPoint) {
    if (x>=0 && x<tela->larg && y>=0 && y<tela->alt) {
        if (espessura == 1)
            tela->rgb[y][x] = cor_atual;
        else {
            for (int i=0; i<espessura; i++) {
                // eixos principais, cor cheia
                tela->rgb[y  ][x  ] = cor_atual;
                tela->rgb[y+i][x  ] = cor_atual;
                tela->rgb[y-i][x  ] = cor_atual;
                tela->rgb[y  ][x+i] = cor_atual;
                tela->rgb[y  ][x-i] = cor_atual;
                // eixos secundários, cor suavizada
                //cor suave = {(int)(cor_atual.r*1.2),(int)(cor_atual.g*1.2), (int)(cor_atual.b*1.2)};
                cor suave = {30, 30, 30};
                tela->rgb[y+i][x+i] = suave;
                tela->rgb[y+i][x-i] = suave;
                tela->rgb[y-i][x-i] = suave;
                tela->rgb[y-i][x+i] = suave;
            }
        }
        if (isPoint) update();
    }
}

// desenha uma reta entre 2 pontos
// http://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm#Line_equation
void line(int x0, int y0, int x1, int y1) {
 
  int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
  int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
  int err = (dx>dy ? dx : -dy)/2, e2;
 
  for(;;){
    point(x0,y0, false);
    if (x0==x1 && y0==y1) break;
    e2 = err;
    if (e2 >-dx) { err -= dy; x0 += sx; }
    if (e2 < dy) { err += dx; y0 += sy; }
  }
  update();
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
void polygon(int n, ponto pts[n]){
    int i = 1;
    ponto p1 = {pts[0].x, pts[0].y};
    // itera por todos os pontos desnhando as linhas
    do {
        //printf("i=%d\nx0: %d, y0: %d\nx1: %d, y1: %d\n\n", i, p1.x, p1.y, pts[i].x, pts[i].y);
        line(p1.x, p1.y, pts[i].x, pts[i].y);
        p1.x = pts[i].x;        // atualiza primeiro ponto da proxima linha
        p1.y = pts[i].y; 
        i++;
    } while (i<n);
    // desenha ultima linha (retornando para o primeiro ponto)
    //printf("i=%d\nx0: %d, y0: %d\nx1: %d, y1: %d\n\n", i, p1.x, p1.y, pts[0].x, pts[0].y);
    line(p1.x, p1.y, pts[0].x, pts[0].y);
}

void circle(int p, int q, int r) {
    int x=0, y=r, d;

    d = 3 - 2*r;

    while (x <= y) {
        point( x+p,   y+q, false);
        point(-x+p,  y+q , false);
        point(-x+p, -y+q , false);
        point( x+p,  -y+q, false);
        point( y+p,   x+q, false);
        point(-y+p,  x+q , false);
        point(-y+p, -x+q , false);
        point( y+p,  -x+q, false);

        //encontra localização do próximo pixel a ser escaneado
        if (d < 0) {
            d = d + 4*x + 6;
            x++;
        }
        else {
            d = d + 4*(x - y) + 10;
            x++;
            y--;
        }
    }
    update();
}

// mostra o conteudo da lista de comandos
void list() {
    for (int i=0; i<num_linhas; i++) {
        printf("%s", comand_list[i]);
    }
    printf("\n");
    printf("Cor atual: [%3d][%3d][%3d]\n", cor_atual.r, cor_atual.g, cor_atual.b);
    printf("Espessura do pincel: %d\n", espessura);
    printf("Tamanho da imagem: %d x %d\n\n", tela->larg, tela->alt);
}

// atualiza os dados do comand_list com o que está na matriz
void update() {
    int linha = 3;
    
    for (int i=0; i<tela->alt; i++) {
        for (int j=0; j<tela->larg; j++) {
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

void fill(int x, int y, int r, int g, int b) {
    int passo[4][2] = {
                        {-1, 0},
                        { 0,-1},
                        { 1, 0},
                        { 0, 1}
                    };
    
    // armazena cor do pixel que se deseja pintar (cor anterior)
    int rr = tela->rgb[x][y].r;
    int gg = tela->rgb[x][y].g;
    int bb = tela->rgb[x][y].b;

    contador++;
    
    // verifica se a cor do pixel atual é igual a cor anterior. Se sim, pinta com a cor desejada
    if (tela->rgb[y][x].r == rr && tela->rgb[y][x].g == gg && tela->rgb[y][x].b == bb) {
        point(x, y, false);
        // verifica os vizinhos de cima, baixo, esquerda e direita por cores iguais a anterior. Caso ache, chama a função novamente.
        for(int k = 0; k < 4; k++ ) {
            int l = x + passo[k][0];
            int c = y + passo[k][1];
    
            if ( 
                (l >= 0) && (l < tela->alt) && 
                (c >= 0) && (c < tela->larg) && 
                (tela->rgb[c][l].r == rr) && 
                (tela->rgb[c][l].g == gg) && 
                (tela->rgb[c][l].b == bb)
               ) {
                fill(l, c, r, g, b);
            }
        } 
    }
    update();
}
    
   
 
    
 
