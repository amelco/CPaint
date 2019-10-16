 #include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERSION "0.1"
#define AUTHOR1 "Andre Herman Freire Bezerra"
#define EMAIL1  "amelco.herman@gmail.com"
#define AUTHOR2 "Marcell Santana de Deus"
#define EMAIL2  "marcellsantana@hotmail.com"

#define TAM_MAX_CMD 100         // tamanho maximo do comando (em caracteres)
#define NUM_MAX_PRM 20          // número máximo de parametros
#define INC_LINHAS 20           // incremento de linhas do arquivo (20 em 20)

// largua e altura padrao da imagem
#define LARG 50
#define ALT 50

// variáveis globais - serão utilizadas em praticamente todas as funções
char** comand_list;      // string contendo todas as linhas do 'arquivo'
int linha = 0;            // linha (posição do vetor) em que o 'arquivo' se encontra

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


/* funcoes graficas */
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
void list();


/*** funcoes do programa ***/

// Apresentação do programa
void msg_inicial() {
    printf("CPaint %s.\n", VERSION);
    printf("Densenvolvido por:\n  %s - %s\n  %s - %s\n\n", AUTHOR1, EMAIL1, AUTHOR2, EMAIL2);
    printf("Digite 'help' para ajuda\n\n");
}

// transforma comando de 1 string para um vetor de strings
//   recebe:  string com comando completo (comando)
//   retorna: vetor de string contendo o comando e seus parâmetros (cmd)
//            número de parametros (np)
void t_comando(char comando[TAM_MAX_CMD], char cmd[NUM_MAX_PRM][TAM_MAX_CMD], int* np) {
    int i = 0;
    int ic = 0, c = 0;

    while (comando[i] != '\0') {
        if (comando[i] == ' ') {
            ic++;
            c = 0;
        }
        else {
            cmd[ic][c] = comando[i];
            cmd[ic][c+1] = '\0';
            c++;
        }
        i++;
    }
    *np = ic;   
    // preenche todos as posiçoes restantes do vetor com a string "NULL"
    for (int i=ic+1; i<=NUM_MAX_PRM; i++) {
        strcpy(cmd[i], "NULL");
    }
}

// mostra comandos disponíveis e pequena documentação
void help() {
    printf("Ajuda do CPaint %s:\n\n", VERSION);
    printf("COMANDO [parâmetro_1 parâmetro_2 ...]\n\nCOMANDOS:\n");
    printf("image\tCria uma nova imagem\n\tParâmetros: [largura INT], [altura INT]\n");
    printf("color\tMuda a cor atual\n\tParâmetros: [vermelho INT], [verde INT], [azul INT]\n");
    printf("clear\tLimpa a imagem com a cor especificada\n\tParâmetros (opcional): [vermelho INT], [verde INT], [azul INT]\n");
    printf("rect\tDesenha um retângulo\n\tParâmetros: [x INT], [y INT], [largura INT], [altura INT]\n");
    printf("circle\tDesenha um círculo\n\tParâmetros: [x INT], [y INT], [raio INT]\n");
    printf("poligon\tDesenha um polígono fechado\n\tParâmetros: [x1 INT], [y1 INT], [x2 INT], [y2 INT] ... [xn INT], [yn INT]. (1 < n < 21)\n");
    printf("fill\tPinta área interna ou externa de um polígono\n\tParâmetros: [x INT], [y INT]\n");
    printf("save\tSalva arquivo de image\n\tParâmetro: [nome_do_arquivo TEXTO]\n");
    printf("open\tAbre um arquivo de imagem\n\tParâmetro: [nome_do_arquivo TEXTO]\n");
    printf("list\tMostra conteúdo do arquivo de imagem\n");
    printf("\n");
}

// interpretador de comandos
//   recebe: comando e seus parâmetros, se houver (cmd)
//           número de parâmetros (np)
void interpreta(int np, char cmd[NUM_MAX_PRM][TAM_MAX_CMD]) {
    char comando[TAM_MAX_CMD];

    strcpy(comando, cmd[0]);
    if (strcmp(comando, "quit") == 0) {
        printf("\nAté!\n\n");
        exit(1);
    } 
    else if (strcmp(comando, "help") == 0) {
        // printf("Help List\n");
        help();
    } 
    else if (strcmp(comando, "list") == 0) {
        list();
    }
    else if (strcmp(comando, "image") == 0) {
        int larg, alt;

        if (strcmp(cmd[1], "NULL") == 0) 
            larg = LARG;
        else 
            larg = atoi(cmd[1]);    // atoi() string to integer
        if (strcmp(cmd[2], "NULL") == 0) 
            alt = ALT;
        else 
            alt = atoi(cmd[2]);
        
        image(larg, alt);
    }
    else {
        printf("Comando inválido.\n");
    }
}

void image(int larg, int alt) {
    comand_list[0] = "P3";
    sprintf(comand_list[1], "%d %d", larg, alt);
    comand_list[2] = "255";
    if (linha < 2) linha = 2;
}

void list() {
    printf("\n");
    for (int i=0; i<=linha; i++) {
        printf("%3d: %s\n", i+1, comand_list[i]);
    }
    printf("\n");
}

int main() {
    comand_list = malloc(INC_LINHAS * sizeof(char*));      // primeiramente, aloca INC_LINHAS linhas. Adiciona + INC_LINHAS caso necessário.
    for (int i=0; i<INC_LINHAS; i++) {
        comand_list[i] = malloc(TAM_MAX_CMD * sizeof(char*));
    }
    
    image(50, 50);       // chama a função para definir um cabeçalho padrão (imagem 50 X 50)
    msg_inicial();

    while (1) {
        char comando[TAM_MAX_CMD];
        char cmd[NUM_MAX_PRM][TAM_MAX_CMD];
        int num_param = 0;

        printf(">> ");
        scanf(" %[^\n]", &comando);
        t_comando(comando, cmd, &num_param);
        interpreta(num_param, cmd);
    }
    return 0;
}