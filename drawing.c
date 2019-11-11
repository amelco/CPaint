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
    tela->rgb[y][x] = cor_atual;

    // debug
    //printf("%p => %ld bits\n", 
    //        &tela->rgb[y][x], 
    //        (long int)&tela->rgb[y][x] - end_ant);
    //end_ant = (long int)&tela->rgb[y][x];

    update();
}

// desenha uma reta entre 2 pontos
//retirado de: http://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm#Line_equation
void linha_oct(int x0, int y0, int x1, int y1, char o) {
    int dx, dy, xi, yi, x, y, D;

    dx = x1 - x0;
    dy = y1 - y0;
    
    if (o == 'b') { // baixa declividade (anda mais no eixo x)
        // anda uma unidade no eixo y a cada iteração
        yi = 1;
        if (dy < 0) {
            // declividade negativa
            yi = -1;
            dy = -dy;
        }
        D = 2*dy - dx;
        y = y0;
        for (x = x0; x<=x1; x++) {
            // loop de x0 a x1
            point(x, y);
            if (D > 0) {
                y = y + yi;
                D = D - 2*dx;
            }
            D = D + 2*dy;
        }
    }
    else {         //alta declividade (anda mais no eixo y)
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

// desenha uma linha
//   entradas: coordenadas dos pontos inicial (0) e final (1)
void line(int x0, int y0, int x1, int y1) {
    if (abs(y1 - y0) < abs(x1 - x0)) { 
        // distancia a se percorrer no eixo X é maior
        if (x0 >  x1) linha_oct(x1, y1, x0, y0, 'b');  // ponto inicial à direita do ponto final
        else          linha_oct(x0, y0, x1, y1, 'b');  // ponto inicial à esquerda do ponto final
    } 
    else {  
        // distancia a se percorrer no eixo Y é maior
        if (y0 >  y1) linha_oct(x1, y1, x0, y0, 'a');  // ponto inicial abaixo do ponto final
        else          linha_oct(x0, y0, x1, y1, 'a');  // ponto inicial acima do ponto final
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
void polygon(int n, ponto pts[n]){
    int i = 1;
    ponto p1 = {pts[0].x, pts[0].y};
    // itera por todos os pontos desnhando as linhas
    do {
        printf("i=%d\nx0: %d, y0: %d\nx1: %d, y1: %d\n\n", i, p1.x, p1.y, pts[i].x, pts[i].y);
        line(p1.x, p1.y, pts[i].x, pts[i].y);
        p1.x = pts[i].x;        // atualiza primeiro ponto da proxima linha
        p1.y = pts[i].y; 
        i++;
    } while (i<n);
    // desenha ultima linha (retornando para o primeiro ponto)
    printf("i=%d\nx0: %d, y0: %d\nx1: %d, y1: %d\n\n", i, p1.x, p1.y, pts[0].x, pts[0].y);
    line(p1.x, p1.y, pts[0].x, pts[0].y);
}

void circle(int p, int q, int r) {
    int x=0, y=r, d;

    d = 3 - 2*r;

    while (x <= y) {
        point( x+p,   y+q);
        point(-x+p,  y+q );
        point(-x+p, -y+q );
        point( x+p,  -y+q);
        point( y+p,   x+q);
        point(-y+p,  x+q );
        point(-y+p, -x+q );
        point( y+p,  -x+q);

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

void fill(int x, int y, int r, int g, int b, int rr, int gg, int bb) {
    //int passo[8][2] = {{-1,0},{0,-1},{0,1},{1,0},{1,1},{-1,1},{1,-1},{-1,-1}};
    int passo[8][2] = {{-1,0},{0,-1},{0,1},{1,0}};
    contador++;
    //printf("fill: %d\n", contador);
    if(tela->rgb[x][y].r == rr && tela->rgb[x][y].g == gg && tela->rgb[x][y].b == bb) {
        tela->rgb[x][y].r = r;
        tela->rgb[x][y].g = g;
        tela->rgb[x][y].b = b;
    
        //for(int k = 0; k < 8; k++ )
        for(int k = 0; k < 4; k++ )
        {
            int l = x + passo[k][0];
            int c = y + passo[k][1];
    
            if((l >= 0) && (l < tela->alt) && (c >= 0) && (c < tela->larg) && (tela->rgb[l][c].r == rr) && (tela->rgb[l][c].g == gg) && (tela->rgb[l][c].b == bb))
                fill(l, c, r, g, b, rr, gg, bb);
        } 
    }
    update();
}
    
   
 
    
 
