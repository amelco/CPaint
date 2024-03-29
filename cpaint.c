#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpaint.h"
#include "drawing.h"
#include "globals.h"

void init() {
    isInit = true;          // é inicialização do programa
    foi_alocado = false;
    
    // define as constantes
    LARG = 60;
    ALT = 40;
    TAM_MAX_CMD = 100;
    NUM_MAX_PRM = 20;
    INC_LINHAS = 12;
    
    // inicializa variáveis
    contador = 0;
    modo_leitura = false;   // programa não está no modo leitura de arquivo 

    aloca_imagem(LARG, ALT);
    
    // preto
    cor_atual.r = 0;
    cor_atual.g = 0;
    cor_atual.b = 0;
    espessura = 1;

    image(LARG, ALT);       // chama a função para definir um cabeçalho padrão
    clear(&cor_atual);

    // branco
    cor_atual.r = 255;
    cor_atual.g = 255;
    cor_atual.b = 255;

    isInit = false;
}

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
    else if (strcmp(comando, "color") == 0) {
        if (strcmp(cmd[1], "NULL") == 0 || strcmp(cmd[2], "NULL") == 0 || strcmp(cmd[3], "NULL") == 0) {
            printf("Falta argumentos no comando. Veja ajuda.\n");
        } else {
            cor c;
            c.r = atoi(cmd[1]);
            c.g = atoi(cmd[2]);
            c.b = atoi(cmd[3]);
            color(&c);
            printf("Cor alterada\n");
        }
    }
    else if (strcmp(comando, "brush") == 0) {
        if (strcmp(cmd[1], "NULL") == 0 ) {
            printf("Falta argumentos no comando. Veja ajuda.\n");
        } else {
            int n;
            n = atoi(cmd[1]);
            brush_width(n);
            printf("Espessura do pincel alterada!\n");
        }
    }
    else if (strcmp(comando, "point") == 0) {
        if (strcmp(cmd[1], "NULL") == 0 || strcmp(cmd[2], "NULL") == 0) {
            printf("Falta argumentos no comando. Veja ajuda.\n");
        } else {
            int x = atoi(cmd[1]);
            int y = atoi(cmd[2]);
            point(x, y, true);
            //if (x>tela->larg || y>tela->alt) {
            //    printf("Ponto x ou y fora do canvas.\n");
            //    printf("Verifique o comando.\n");
            //} else {
            //    point(x, y, true);
            //}
        }
    }
    else if (strcmp(comando, "line") == 0) {
        if (strcmp(cmd[1], "NULL") == 0 || strcmp(cmd[2], "NULL") == 0 || strcmp(cmd[3], "NULL") == 0 || strcmp(cmd[4], "NULL") == 0) {
            printf("Falta argumentos no comando. Veja ajuda.\n");
        } else {
            int x1 = atoi(cmd[1]);
            int y1 = atoi(cmd[2]);
            int x2 = atoi(cmd[3]);
            int y2 = atoi(cmd[4]);
            line(x1, y1, x2, y2);
            //if (x1>tela->larg || y1>tela->alt || x2>tela->larg || y2>tela->alt ||
            //    x1<0          || y1<0         || x2<0          || y2<0           ) {
            //    printf("Pontos x ou y fora do canvas.\n");
            //    printf("Verifique o comando.\n");
            //} else {
            //    line(x1, y1, x2, y2);
            //}
        }
    }
    else if (strcmp(comando, "rect") == 0) {
        if (strcmp(cmd[1], "NULL") == 0 || strcmp(cmd[2], "NULL") == 0 || strcmp(cmd[3], "NULL") == 0 || strcmp(cmd[4], "NULL") == 0) {
            printf("Falta argumentos no comando. Veja ajuda.\n");
        } 
        else {
            int x  = atoi(cmd[1]);
            int y  = atoi(cmd[2]);
            int tx = atoi(cmd[3]);
            int ty = atoi(cmd[4]);
            rect(x, y, ty, tx);
            //if (x>tela->larg || y>tela->alt || x+tx>tela->larg || y+ty>tela->alt ||
            //    x<0          || y<0  ) {
            //    printf("x: %d y: %d\n", x, y);
            //    printf("x+tx: %d y+ty: %d\n", x+tx, y+ty);
            //    printf("larg: %d alt: %d\n", tela->larg, tela->alt);
            //    printf("Retângulo fora do canvas.\n");
            //    printf("Verifique o comando.\n");
            //} 
            //else {
            //    rect(x, y, ty, tx);
            //}
        }
    }
    else if (strcmp(comando, "source") == 0) {
        if (strcmp(cmd[1], "NULL") == 0) {
            printf("Falta argumentos no comando. Veja ajuda.\n");
        } 
        else {
            // le arquivo de comandos
            source(cmd[1]);
        }
    }
    else if (strcmp(comando, "polygon") == 0) {
        if (strcmp(cmd[1], "NULL") == 0 || strcmp(cmd[2], "NULL") == 0 || strcmp(cmd[3], "NULL") == 0 || strcmp(cmd[4], "NULL") == 0) {
            printf("Falta argumentos no comando. Veja ajuda.\n");
        } 
        else {
            int n = atoi(cmd[1]);  // número de lados do polígono
            ponto pts[n];   // Array com n pontos. Os 2 primeiros formam a primeira linha. As linhas
                            // seguintes tomam o ponto imediatamente anterior como sendo o ponto inicial.
            // adiciona os 2 primeiros pontos (1a linha)
            pts[0].x = atoi(cmd[2]);
            pts[0].y = atoi(cmd[3]);
            pts[1].x = atoi(cmd[4]);
            pts[1].y = atoi(cmd[5]);

            for (int i=6, ip=2; ip<n; i+=2, ip++) {    // O número de lados do polygono deve ser ultiplicado por dois
                                                        // pois cada lado (linha) é formado por dois pontos
                pts[ip].x = atoi(cmd[i]);
                pts[ip].y = atoi(cmd[i+1]);
                //printf("ip->%d  x: %d  y: %d\n", ip, pts[ip].x, pts[ip].y);
            }


            //int i=2;
            //int ip=0;
            //for (int i=0; i<n; i+=4) {
            //    pts[ip][0].x = atoi(cmd[i+2]);
            //    pts[ip][0].y = atoi(cmd[i+3]);
            //    pts[ip][1].x = atoi(cmd[i+4]);
            //    pts[ip][1].y = atoi(cmd[i+5]);
            //    ip++;
            //}
            polygon(n, pts);
        }
    }
    else if (strcmp(comando, "circle") == 0) {
        if (strcmp(cmd[1], "NULL") == 0 || strcmp(cmd[2], "NULL") == 0 || strcmp(cmd[3], "NULL") == 0) {
            printf("Falta argumentos no comando. Veja ajuda.\n");
        } else {
            int x = atoi(cmd[1]);
            int y = atoi(cmd[2]);
            int r = atoi(cmd[3]);
            circle(x, y, r);
        }
    }
    else if (strcmp(comando, "save") == 0) {
        if (strcmp(cmd[1], "NULL") == 0) {
            printf("Falta argumentos no comando. Veja ajuda.\n");
        } else {
            save(cmd[1]);
        }
    }
    else if(strcmp(comando, "open") == 0) {
        if (strcmp(cmd[1], "NULL") == 0) {
            printf("Falta argumentos no comando. Veja ajuda.\n");
        } else {
            open(cmd[1]);
        }
    }
    else if(strcmp(comando,"fill") == 0){
        if(strcmp(cmd[1], "NULL") == 0 || strcmp(cmd[2], "NULL") == 0) {
            printf("Falta argumentos no comando. Veja ajuda.\n");
        }
        else{
            int x  = atoi(cmd[1]);
            int y  = atoi(cmd[2]);
            int r = cor_atual.r;
            int g = cor_atual.g;
            int b = cor_atual.b;

            fill(x, y, r, g, b);
            }
                     
    }
    
    else if(strcmp(comando,"copy") == 0){
        if(strcmp(cmd[1], "NULL") == 0 || strcmp(cmd[2], "NULL") == 0 || strcmp(cmd[3], "NULL") == 0 || strcmp(cmd[4], "NULL") == 0) {
            printf("Falta argumentos no comando. Veja ajuda.\n");
        }
        else{
            int x  = atoi(cmd[1]);
            int y  = atoi(cmd[2]);
            int tam_x = atoi(cmd[3]);
            int tam_y = atoi(cmd[4]);
            aloca_imcopy(tela->larg, tela->alt);   
            copy(x,y,tam_x,tam_y);
            }                
    }
    
    else if(strcmp(comando,"cut") == 0){
        if(strcmp(cmd[1], "NULL") == 0 || strcmp(cmd[2], "NULL") == 0 || strcmp(cmd[3], "NULL") == 0 || strcmp(cmd[4], "NULL") == 0) {
            printf("Falta argumentos no comando. Veja ajuda.\n");
        }
        else{
            int x  = atoi(cmd[1]);
            int y  = atoi(cmd[2]);
            int tam_x = atoi(cmd[3]);
            int tam_y = atoi(cmd[4]);
            aloca_imcopy(tela->larg, tela->alt);   
            cut(x,y,tam_x,tam_y);
            }                
    }

    else if(strcmp(comando,"paste") == 0){
        if(strcmp(cmd[1], "NULL") == 0 || strcmp(cmd[2], "NULL") == 0) {
            printf("Falta argumentos no comando. Veja ajuda.\n");
        }
        else{
            int x  = atoi(cmd[1]);
            int y  = atoi(cmd[2]);  
            paste(x,y);
            }                
    }

    else {
        printf("Comando inválido.\n");
    }
}

// abre arquivo de entrada
void source(char arquivo[50]) {
    modo_leitura = true;
    arq_ent = fopen(arquivo, "r");
    if (arq_ent == NULL) {                  // verifica se arquivo existe
        printf("Arquivo não existe\n");
        modo_leitura = false;
        cmd_i = -1;
    }
}

void aloca_imagem(int larg, int alt) {
    int new_num_linhas = larg * alt + 3;
    if (isInit) {
        // aloca command_list
        comand_list = (char**)malloc(new_num_linhas * sizeof(char*));
        for (int i=0; i<new_num_linhas; i++) {
            comand_list[i] = (char*)malloc(TAM_MAX_CMD * sizeof(char));
        }
        // inicializa ponteiro
        for (int i=0; i<new_num_linhas; i++) {
            for (int j=0; j<TAM_MAX_CMD; j++) {
                comand_list[i][j] = '\0';
            }
        }
        // aloca matriz tela
        tela = (matriz*)malloc(sizeof(matriz));
        tela->larg = larg;
        tela->alt = alt;
        tela->rgb = (cor**)malloc(alt * sizeof(cor*));
        for (int i=0; i<alt; i++) {
            tela->rgb[i] = (cor*)malloc(larg * sizeof(cor));
        }
        // inicializa ponteiro
        for (int i=0; i<alt; i++) {
            for (int j=0; j<larg; j++) {
                tela->rgb[i][j].r = 0;
                tela->rgb[i][j].g = 0;
                tela->rgb[i][j].b = 0;
            }
        }
    } else {
        /*** Realoca memória ***/
        comand_list = (char**)realloc(comand_list, new_num_linhas * sizeof(char*));
        for (int i=0; i<new_num_linhas; i++) {
            comand_list[i] = (char*)malloc(TAM_MAX_CMD * sizeof(char));
        }
        // inicializa ponteiro não incializados anteriormente
        for (int i=tela->larg * tela->alt + 3; i<new_num_linhas; i++) {
            for (int j=0; j<TAM_MAX_CMD; j++) {
                comand_list[i][j] = '\0';
            }
        }
        // realoca matriz tela
        tela->rgb = (cor**)realloc(tela->rgb, alt * sizeof(cor*));
        for (int i=0; i<alt; i++) {
            tela->rgb[i] = (cor*)malloc(larg * sizeof(cor));
        }
        // inicializa ponteiro
        for (int i=tela->alt; i<alt; i++) {
            for (int j=tela->larg; j<larg; j++) {
                tela->rgb[i][j].r = 0;
                tela->rgb[i][j].g = 0;
                tela->rgb[i][j].b = 0;
            }
        }
        tela->larg = larg;
        tela->alt = alt;
    }
    num_linhas = new_num_linhas;
}

void aloca_imcopy(int larg, int alt) {
    if (!foi_alocado) {
       // aloca matriz tela
            imcopy = (matriz*)malloc(sizeof(matriz));
            imcopy->larg = larg;
            imcopy->alt = alt;
            imcopy->rgb = (cor**)malloc(alt * sizeof(cor*));
            for (int i=0; i<alt; i++) {
                imcopy->rgb[i] = (cor*)malloc(larg * sizeof(cor));
            }
            // inicializa ponteiro
            for (int i=0; i<alt; i++) {
                for (int j=0; j<larg; j++) {
                    imcopy->rgb[i][j].r = 0;
                    imcopy->rgb[i][j].g = 0;
                    imcopy->rgb[i][j].b = 0;
                }
            }
            foi_alocado = true;
    }   
}

// mostra comandos disponíveis e pequena documentação
void help() {
    printf("Ajuda do CPaint %s:\n\n", VERSION);
    printf("COMANDO [parâmetro_1 parâmetro_2 ...]\n\nCOMANDOS:\n");
    printf("image\tCria uma nova imagem em branco\n\tParâmetros: [largura INT], [altura INT]\n");
    printf("color\tMuda a cor atual\n\tParâmetros: [vermelho INT], [verde INT], [azul INT]\n");
    printf("brush\tMuda a espessura do pincel\n\tParâmetros: [espessura INT]\n");
    printf("clear\tLimpa a imagem com a cor especificada\n\tParâmetros (opcional): [vermelho INT], [verde INT], [azul INT]\n");
    printf("rect\tDesenha um retângulo\n\tParâmetros: [x INT], [y INT], [largura INT], [altura INT]\n");
    printf("circle\tDesenha um círculo\n\tParâmetros: [x INT], [y INT], [raio INT]\n");
    printf("polygon\tDesenha um polígono fechado\n\tParâmetros: [n INT] [x1 INT], [y1 INT], [x2 INT], [y2 INT] ... [xn INT], [yn INT]. (1 < n < 21)\n");
    printf("fill\tPinta área interna ou externa de um polígono\n\tParâmetros: [x INT], [y INT]\n");
    printf("save\tSalva arquivo de image\n\tParâmetro: [nome_do_arquivo TEXTO]\n");
    printf("open\tAbre um arquivo de imagem\n\tParâmetro: [nome_do_arquivo TEXTO]\n");
    printf("list\tMostra conteúdo do arquivo de imagem\n\tParâmetro (opcional): [remove_line_num BOOL]\n");
    printf("source\tLê comandos de um arquivo\n\tParâmetro: [nome_do_arquivo.in TEXTO]\n\t\tOBS.: O arquivo deve obrigatoriamente ter 'quit' como ultimo comando.\n");
    printf("quit\tSai do programa\n");
    printf("\n");
}

// libera memoria alocada e sai do programa
void quit() {
    int n = tela->alt * tela->larg + 3;
    for (int i=0; i<tela->alt; i++) {
        free(tela->rgb[i]);
    }
    free(tela->rgb);
    free(tela);
    
    for (int i=0; i<n; i++) {
        // printf("%d\n", i);
        free(comand_list[i]);
    }
    free(comand_list);  
    if (modo_leitura) {
        modo_leitura = false;
        fclose(arq_ent);
    }

    printf("\nAté!\n\n");
    exit(0);
}

/** funcoes debug **/
void print_matriz_tela() {
    for (int i=0; i<tela->alt; i++) {
        printf("|");
        for (int j=0; j<tela->larg; j++) {
            printf("%3d %3d %3d, ", tela->rgb[i][j].r, tela->rgb[i][j].g, tela->rgb[i][j].b);
        }
        printf("\b\b|\n");
    }

}
