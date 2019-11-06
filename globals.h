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
#define LARG 8
#define ALT 8

#define TAM_MAX_CMD 100         // tamanho maximo do comando (em caracteres)
#define NUM_MAX_PRM 20          // número máximo de parametros
#define INC_LINHAS 12           // incremento de linhas do arquivo

/* define o tipo booleano */
typedef enum bool_t {
    False=0,
    True
} d_bool;

// define tipo "cor" com os valores de vermelho (r), verde (g) e azul (b)
typedef struct cor_t {
    int r;
    int g;
    int b;
 } cor;

// struct g_tela com a matriz de cores (ex. g_tela->rgb[0][0].r = 255; g_tela->rgb[0][0].g = 0; g_tela->rgb[0][0].b = 0; )
typedef struct matriz_t {
    int larg;
    int alt;
    struct cor_t** rgb;
} matriz;

typedef struct ponto_t {
    int x;
    int y;
} ponto;

/* variáveis globais - serão utilizadas em praticamente todas as funções */
char** g_ppm_command_list;                  // string contendo todas as linhas do 'arquivo'
char g_gfx_command_list[100][TAM_MAX_CMD];  // string contendo comandos do allegro
int g_cmd_n;                                // número do comando atual
int g_num_linhas;                           // número de linhas do arquivo (larg * alt)
matriz* g_tela;
cor g_cor_atual;
d_bool g_is_init;
d_bool g_modo_leitura;                      // modo leitura de arquivo (sem interação do usuário)
FILE* g_arq_ent;
int g_cmd_tot;                              // numero total de comandos do arquivo de entrada (deve estar na primeira linha do arquivo)
int cmd_i;                                  // comando atual do cursor de leitura do arquivo

float g_escala_x;
float g_escala_y;

#endif
