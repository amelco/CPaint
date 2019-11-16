/*** variáveis globais ***/
#ifndef globals_h
#define globals_h

#include <stdio.h>

#define VERSION "0.1"
#define AUTHOR1 "Andre Herman Freire Bezerra"
#define EMAIL1  "amelco.herman@gmail.com"
#define AUTHOR2 "Marcell Santana de Deus"
#define EMAIL2  "marcellsantana@hotmail.com"

// largua e altura padrao da imagem
unsigned short int LARG;
unsigned short int ALT;

unsigned short int TAM_MAX_CMD;         // tamanho maximo do comando (em caracteres)
unsigned short int NUM_MAX_PRM;          // número máximo de parametros
unsigned short int INC_LINHAS;           // incremento de linhas do arquivo

/// Define o tipo booleano.
typedef enum bool_t {
    false=0,
    true
} bool;

/// Define tipo "cor" com os valores de vermelho (r), verde (g) e azul (b)
typedef struct cor_t {
    int r;
    int g;
    int b;
 } cor;

/// Struct tela com a matriz de cores (ex. tela->rgb[0][0].r = 255; tela->rgb[0][0].g = 0; tela->rgb[0][0].b = 0; )
typedef struct matriz_t {
    int larg;
    int alt;
    cor** rgb;
} matriz;

/// Define o tipo ponto, contendo as coordenadas x e y.
typedef struct ponto_t {
    int x;
    int y;
} ponto;

// variáveis globais - serão utilizadas em praticamente todas as funções
char** comand_list;         // string contendo todas as linhas do 'arquivo'
int num_linhas;             // número de linhas do arquivo (larg * alt)
matriz* tela;

cor cor_atual;              // cor atual do pincel
int espessura;              // espessura do pincel (largura do traço)

bool isInit;
bool modo_leitura;          // modo leitura de arquivo (sem interação do usuário)
FILE* arq_ent;
int cmd_tot;                // numero total de comandos do arquivo de entrada (deve estar na primeira linha do arquivo)
int cmd_i;    // comando atual do cursor de leitura do arquivo

// debug
int contador;
long int end_ant;

#endif
