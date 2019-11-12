/* funcoes graficas */
#ifndef drawing_h
#define drawing_h

#include "globals.h"

/// ### Cria área de desenho.
/// Cria um canvas de dimensôes *larg* e *alt*.
/// @param[in] larg  largura da imagem (eixo x).
/// @param[in] alt   altura  da imagem (eixo y).
/// ### Exemplo
/// ~~~~~~~~~~~~~~~~
/// image 640 480
/// ~~~~~~~~~~~~~~~~
void image(int larg, int alt);

/// ### Altera a cor.
/// Altera a cor atual do pincel.
/// @param[in] c  cor.
/// @note A cor é dada em RGB variando de 0 a 255.
/// ### Exemplo
/// ~~~~~~~~~~~~~~~~
/// color 255 120 98
/// ~~~~~~~~~~~~~~~~
void color(cor* c);

/// ### Limpa tela.
/// Limpa a tela com uma cor especificada.
/// @param[in] c  cor especificada.
/// @note     A cor é dada em RGB variando de 0 a 255.
/// @note     Caso não seja definida uma cor, a tela será preenchida com a cor preta.
/// ### Exemplo
/// ~~~~~~~~~~~~~~~~
/// clear 255 255 255
/// ~~~~~~~~~~~~~~~~
void clear(cor* c);

/// ### Desenha um ponto.
/// Desenha um ponto na tela nas coordenadas *x* e *y*.
/// @param[in] x  coordenada x.
/// @param[in] y  coordenada y.
/// ### Exemplo
/// ~~~~~~~~~~~~~~~~
/// point 5 25
/// ~~~~~~~~~~~~~~~~
void point(int x, int y);

/// ### Desenha uma linha.
/// Desenha uma linha na tela, de um ponto a outro.
/// @param[in] x1  coordenada x do ponto inicial.
/// @param[in] y1  coordenada y do ponto final.
/// @param[in] x2  coordenada x do ponto inicial.
/// @param[in] y2  coordenada y do ponto final.
/// ### Exemplo
/// ~~~~~~~~~~~~~~~~
/// line 2 2 6 6
/// ~~~~~~~~~~~~~~~~
void line(int x1, int y1, int x2, int y2);

/// ### Desenha um retângulo.
/// Desenha um retângulo na tela com o canto superior esquerdo na coordenadas x e y.
/// @param[in] x      coordenada x do início do retângulo.
/// @param[in] y      coordenada y do início do retângulo.
/// @param[in] tam_x  tamanho do retângulo na direção x.
/// @param[in] tam_y  tamanho do retângulo na direção y.
/// ### Exemplo
/// ~~~~~~~~~~~~~~~~
/// rect 3 4 25 35
/// ~~~~~~~~~~~~~~~~
void rect(int x, int y, int tam_x, int tam_y);

/// ### Desenha um círculo.
/// Desenha um círculo na tela com seu centro nas coordenadas x e y.
/// @param[in] x  coordenada x do centro do círculo.
/// @param[in] y  coordenada y do centro do círculo.
/// @param[in] r  raio do círculo
/// ### Exemplo
/// ~~~~~~~~~~~~~~~~
/// clear 10 10 50
/// ~~~~~~~~~~~~~~~~
void circle(int x, int y, int r);

/// ### Desenha um polígono.
/// Desenha um polígono de *n* lados na tela.
/// @param[in] n   número de lados do polígono.
/// @param[in] pts pontos que formarão o polígono.
/// @attention O polígono é automaticamente fechado, 
///  não sendo necessário especificar o último ponto igual ao primeiro.
/// ### Exemplo
/// ~~~~~~~~~~~~~~~~
/// polygon 3 10 10 12 5 14 10
/// ~~~~~~~~~~~~~~~~
void polygon(int n, ponto pts[n]);

/// ### Preencher.
/// Preenche uma área fechada da tela.
/// Utilizado quando se quer pintar a área de um polígono de uma determinada cor.
/// @param[in] x  coordenada x de onde se iniciará o preenchimento.
/// @param[in] y  coordenada y de onde se iniciará o preenchimento.
/// @param[in] r  componente vermelha da cor.
/// @param[in] g  componente verde    da cor.
/// @param[in] r  componente azul     da cor.
/// ### Exemplo
/// ~~~~~~~~~~~~~~~~
/// fill 2 2 255 0 0
/// ~~~~~~~~~~~~~~~~
void fill(int x, int y, int r, int g, int b, int rr, int gg, int bb);

/// ### Salva imagem.
/// Salva a imagem em um arquivo PPM.
/// @param[in] nome  nome do arquivo PPM.
/// ### Exemplo
/// ~~~~~~~~~~~~~~~~
/// save arte.ppm
/// ~~~~~~~~~~~~~~~~
void save(char nome[]);

/// ### Abre imagem.
/// Abre imagem PPM para continuar a edição.
/// @param[in] nome  nome do arquivo PPM.
/// ### Exemplo
/// ~~~~~~~~~~~~~~~~
/// open arte.ppm
/// ~~~~~~~~~~~~~~~~
void open(char nome[]);

/// ### Lista imagem.
/// Lista conteúdo do arquivo PPM.
/// @note Apesar de estar disponível ao usuário final, 
/// não há muita utilidade na utilização do comando.
/// ### Exemplo
/// ~~~~~~~~~~~~~~~~
/// list
/// ~~~~~~~~~~~~~~~~
void list();

/// ### Atualiza matriz de imagem.
/// Atualiza a matriz de imagem do programa para receber as alterações feitas pelos outros
/// comandos.
/// @note        Esta é uma função não disponível ao usuário final.
void update();      // atualiza 'arquivo'. Passa as informações da matriz tela para a matriz do arquivo. É chamada sempre que a matriz for alterada

#endif
