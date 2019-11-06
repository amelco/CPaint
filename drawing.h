/* funcoes graficas */
#ifndef drawing_h
#define drawing_h

#include "globals.h"

// por equanto, todas as funções retornam void até que se decida o contrário
void image(int larg, int alt);
void color(cor* c);
void clear(cor* c);
void point(int x, int y);
void line(int x1, int y1, int x2, int y2);
void rect(int x, int y, int tam_x, int tam_y);
void circle(int x, int y, int r);
void poligon(int n, ponto pts[n][2]);
void fill(int x, int y, int r, int g, int b, int rr, int gg, int bb);
void save(char nome[]);
void open(char nome[]);
void list();
void update();      // atualiza 'arquivo'. Passa as informações da matriz tela para a matriz do arquivo. É chamada sempre que a matriz for alterada

#endif
