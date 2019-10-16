#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
#define INC_LINHAS 12   // incremento de linhas do arquivo


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
    cor** rgb;
} matriz;

// variáveis globais - serão utilizadas em praticamente todas as funções
char** comand_list;      // string contendo todas as linhas do 'arquivo'
int ultima_linha;        // número da ultima linha do arquivo
matriz* tela;
// char comand_list[INC_LINHAS][TAM_MAX_CMD];


/* funcoes graficas */
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


/*** funcoes do programa ***/
void update();      // atualiza 'arquivo'. Passa as informações da matriz tela para a matriz do arquivo. É chamada sempre que a matriz for alterada
void msg_inicial();
void t_comando(char comando[TAM_MAX_CMD], char cmd[NUM_MAX_PRM][TAM_MAX_CMD], int* np);
void help();
void interpreta(int np, char cmd[NUM_MAX_PRM][TAM_MAX_CMD]);
void quit();

/** funcoes debug **/
void print_matriz_tela() {
    for (int i=0; i<tela->larg; i++) {
        printf("|");
        for (int j=0; j<tela->alt; j++) {
            printf("%3d %3d %3d, ", tela->rgb[i][j].r, tela->rgb[i][j].g, tela->rgb[i][j].b);
        }
        printf("\b\b|\n");
    }

}

/*************************************************************************/

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
    printf("image\tCria uma nova imagem em branco\n\tParâmetros: [largura INT], [altura INT]\n");
    printf("color\tMuda a cor atual\n\tParâmetros: [vermelho INT], [verde INT], [azul INT]\n");
    printf("clear\tLimpa a imagem com a cor especificada\n\tParâmetros (opcional): [vermelho INT], [verde INT], [azul INT]\n");
    printf("rect\tDesenha um retângulo\n\tParâmetros: [x INT], [y INT], [largura INT], [altura INT]\n");
    printf("circle\tDesenha um círculo\n\tParâmetros: [x INT], [y INT], [raio INT]\n");
    printf("poligon\tDesenha um polígono fechado\n\tParâmetros: [x1 INT], [y1 INT], [x2 INT], [y2 INT] ... [xn INT], [yn INT]. (1 < n < 21)\n");
    printf("fill\tPinta área interna ou externa de um polígono\n\tParâmetros: [x INT], [y INT]\n");
    printf("save\tSalva arquivo de image\n\tParâmetro: [nome_do_arquivo TEXTO]\n");
    printf("open\tAbre um arquivo de imagem\n\tParâmetro: [nome_do_arquivo TEXTO]\n");
    printf("list\tMostra conteúdo do arquivo de imagem\n\tParâmetro (opcional): [remove_line_num BOOL]\n");
    printf("quit\tSai do programa\n");
    printf("\n");
}

// interpretador de comandos
//   recebe: comando e seus parâmetros, se houver (cmd)
//           número de parâmetros (np)
void interpreta(int np, char cmd[NUM_MAX_PRM][TAM_MAX_CMD]) {
    char comando[TAM_MAX_CMD];

    strcpy(comando, cmd[0]);
    if (strcmp(comando, "quit") == 0) {
        quit();
    } 
    else if (strcmp(comando, "help") == 0) {
        // printf("Help List\n");
        help();
    } 
    else if (strcmp(comando, "list") == 0) {
        bool line_num = true;
        if (strcmp(cmd[1],"NULL") != 0) line_num = false;
        list(line_num);
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
    else if (strcmp(comando, "clear") == 0) {
        cor c;
        if (strcmp(cmd[1], "NULL")==0 &&
            strcmp(cmd[2], "NULL")==0 &&
            strcmp(cmd[3], "NULL")==0 ) {
                strcpy(cmd[1], "0");
                strcpy(cmd[2], "0");
                strcpy(cmd[3], "0");
            }
        c.r = atoi(cmd[1]);
        c.g = atoi(cmd[2]);
        c.b = atoi(cmd[3]);
        clear(&c);
    }
    else {
        printf("Comando inválido.\n");
    }
}

// atualiza os dados do comand_list com o que está na matriz
void update() {
    int linha = 3;
    // printf("MAX.LINHAS: %d\n", INC_LINHAS);
    for (int i=0; i<tela->larg; i++) {
        for (int j=0; j<tela->alt; j++) {
            // printf("l %d: %d %d: %d %d %d\n", linha, i,j, tela->rgb[i][j].r, tela->rgb[i][j].g, tela->rgb[i][j].b);

            sprintf(comand_list[linha], "%d %d %d\n", tela->rgb[i][j].r, tela->rgb[i][j].g, tela->rgb[i][j].b);
            linha++;
        }
    }
    ultima_linha = linha-1;
}

/*************************************************************************/

// cria o cabeçalho da imagem
void image(int larg, int alt) {
    strcpy(comand_list[0], "P3\n");
    sprintf(comand_list[1], "%d %d\n", larg, alt);
    strcpy(comand_list[2], "255\n");
    ultima_linha = 2;
    cor branco;
    branco.r = 255;
    branco.g = 0;
    branco.b = 255;
    clear(&branco);
}

// mostra o conteudo da lista de comandos
void list(bool line_num) {
    printf("\n");
    for (int i=0; i<=ultima_linha; i++) {
        if (line_num) printf("%3d: ", i+1);
        printf("%s", comand_list[i]);
    }
    printf("\n");
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

// libera memoria alocada e sai do programa
void quit() {
    for (int i=0; i<LARG; i++) {
        free(tela->rgb[i]);
    }
    free(tela->rgb);
    free(tela);
    
    for (int i=0; i<INC_LINHAS; i++) {
        // printf("%d\n", i);
        free(comand_list[i]);
    }
    free(comand_list);  

    printf("\nAté!\n\n");
    exit(0);
}

int main() {
    
    /*** Inicialização ***/
    comand_list = malloc(INC_LINHAS * sizeof(char*));      // primeiramente, aloca INC_LINHAS linhas. Adiciona + INC_LINHAS caso necessário.
    for (int i=0; i<INC_LINHAS; i++) {
        // printf("%d\n", i);
        comand_list[i] = malloc(TAM_MAX_CMD * sizeof(char));
    }
    // inicializa ponteiro
    for (int i=0; i<LARG; i++) {
        for (int j=0; j<ALT; j++) {
            comand_list[i][j] = '\0';
        }
    }

    tela = malloc(sizeof(matriz));
    tela->larg = LARG;
    tela->alt = ALT;
    tela->rgb = malloc(LARG * sizeof(cor));
    for (int i=0; i<LARG; i++) {
        tela->rgb[i] = malloc(ALT * sizeof(cor));
    }
    // inicializa ponteiro
    for (int i=0; i<LARG; i++) {
        for (int j=0; j<ALT; j++) {
            tela->rgb[i][j].r = 0;
            tela->rgb[i][j].g = 0;
            tela->rgb[i][j].b = 0;
        }
    }
    
    cor cor_atual;
    cor_atual.r = 0;
    cor_atual.g = 0;
    cor_atual.b = 0;
    image(LARG, ALT);       // chama a função para definir um cabeçalho padrão
    
    /*** Início do programa ***/
    msg_inicial();

    while (1) {
        char comando[TAM_MAX_CMD];
        char cmd[NUM_MAX_PRM][TAM_MAX_CMD];
        int num_param = 0;

        printf(">> ");
        scanf(" %[^\n]", &comando);
        t_comando(comando, cmd, &num_param);
        interpreta(num_param, cmd);
        // print_matriz_tela();
    }
    
    // quit();
    return 0;
}