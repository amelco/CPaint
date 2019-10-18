/*** variáveis globais ***/
#ifndef globals_h
#define globals_h


#define VERSION "0.1"
#define AUTHOR1 "Andre Herman Freire Bezerra"
#define EMAIL1  "amelco.herman@gmail.com"
#define AUTHOR2 "Marcell Santana de Deus"
#define EMAIL2  "marcellsantana@hotmail.com"

// largua e altura padrao da imagem
#define LARG 3
#define ALT 3

#define TAM_MAX_CMD 100         // tamanho maximo do comando (em caracteres)
#define NUM_MAX_PRM 20          // número máximo de parametros
#define INC_LINHAS 12           // incremento de linhas do arquivo

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

// struct tela com a matriz de cores (ex. tela->rgb[0][0].r = 255; tela->rgb[0][0].g = 0; tela->rgb[0][0].b = 0; )
typedef struct matriz_t {
    int larg;
    int alt;
    struct cor_t** rgb;
} matriz;

// variáveis globais - serão utilizadas em praticamente todas as funções
char** comand_list;      // string contendo todas as linhas do 'arquivo'
int ultima_linha;        // número da ultima linha do arquivo
matriz* tela;
cor cor_atual;

#endif