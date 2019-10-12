#include <stdio.h>

typedef enum bool_t {
    false=0,
    true
} bool;

// define tipo "cor" com os valores de vermelho (r), verde (g) e azul (b)
typedef struct cor_t {
    int r;
    int g;
    int b;
 } cor;

// por equanto, todas as funções retornam void até que se decida o contrário
void image(int larg, int alt);
void color(cor c);
void clear(cor c);
void rect(int x, int y, int tam_x, int tam_y);
void circle(int x, int y, int r);
void poligon();     // Ainda nao sei como implementar essa assinatura
void fill(int x, int y);
void save(char* arq);
void open(char* arq);

int main() {
    
    return 0;
}