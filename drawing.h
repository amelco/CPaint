/* funcoes graficas */
#ifndef drawing_h
#define drawing_h


// define o tipo booleano
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
void color(cor* c);
void clear(cor* c);
void rect(int x, int y, int tam_x, int tam_y);
void circle(int x, int y, int r);
void poligon();     // Ainda nao sei como implementar essa assinatura. Provavelmente função recursiva.
void fill(int x, int y);
void save(char* arq);
void open(char* arq);
void list(bool line_num);
void update();      // atualiza 'arquivo'. Passa as informações da matriz tela para a matriz do arquivo. É chamada sempre que a matriz for alterada

#endif