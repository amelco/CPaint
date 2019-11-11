#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpaint.h"
#include "drawing.h"
#include "globals.h"

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
        bool line_num = true;
        if (strcmp(cmd[1],"NULL") != 0) line_num = false;
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
    else if (strcmp(comando, "point") == 0) {
        if (strcmp(cmd[1], "NULL") == 0 || strcmp(cmd[2], "NULL") == 0) {
            printf("Falta argumentos no comando. Veja ajuda.\n");
        } else {
            int x = atoi(cmd[1]);
            int y = atoi(cmd[2]);
            if (x>tela->larg || y>tela->alt) {
                printf("Ponto x ou y fora do canvas.\n");
                printf("Verifique o comando.\n");
            } else {
                point(x, y);
            }
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
            if (x1>tela->larg || y1>tela->alt || x2>tela->larg || y2>tela->alt ||
                x1<0          || y1<0         || x2<0          || y2<0           ) {
                printf("Pontos x ou y fora do canvas.\n");
                printf("Verifique o comando.\n");
            } else {
                line(x1, y1, x2, y2);
            }
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
            if (x>tela->larg || y>tela->alt || x+tx>tela->larg || y+ty>tela->alt ||
                x<0          || y<0  ) {
                printf("x: %d y: %d\n", x, y);
                printf("x+tx: %d y+ty: %d\n", x+tx, y+ty);
                printf("larg: %d alt: %d\n", tela->larg, tela->alt);
                printf("Retângulo fora do canvas.\n");
                printf("Verifique o comando.\n");
            } 
            else {
                rect(x, y, ty, tx);
            }
        }
    }
    else if (strcmp(comando, "source") == 0) {
        if (strcmp(cmd[1], "NULL") == 0) {
            printf("Falta argumentos no comando. Veja ajuda.\n");
        } 
        else {
            // le arquivo de comandos
            le_arquivo(cmd[1]);
        }
    }
    else if (strcmp(comando, "poligon") == 0) {
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

            for (int i=6, ip=2; ip<n; i+=2, ip++) {    // O número de lados do poligono deve ser ultiplicado por dois
                                                        // pois cada lado (linha) é formado por dois pontos
                pts[ip].x = atoi(cmd[i]);
                pts[ip].y = atoi(cmd[i+1]);
                printf("ip->%d  x: %d  y: %d\n", ip, pts[ip].x, pts[ip].y);
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
            poligon(n, pts);
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
            int rr = tela->rgb[x][y].r;
            int gg = tela->rgb[x][y].g;
            int bb = tela->rgb[x][y].b;

            fill(x, y, r, g, b, rr, gg, bb);
            }
                     
    }
    
    else {
        printf("Comando inválido.\n");
    }
}

// abre arquivo de entrada
void le_arquivo(char arquivo[50]) {
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
        for (int i=0; i<larg; i++) {
            for (int j=0; j<alt; j++) {
                comand_list[i][j] = '\0';
            }
        }
        // aloca matriz tela
        tela = (matriz*)malloc(sizeof(matriz));
        tela->larg = larg;
        tela->alt = alt;
        tela->rgb = (cor**)malloc(larg * sizeof(cor*));
        for (int i=0; i<larg; i++) {
            tela->rgb[i] = (cor*)malloc(alt * sizeof(cor));
        }
        // inicializa ponteiro
        for (int i=0; i<larg; i++) {
            for (int j=0; j<alt; j++) {
                tela->rgb[i][j].r = 0;
                tela->rgb[i][j].g = 0;
                tela->rgb[i][j].b = 0;
            }
        }
    } else {
        /*** Realoca memória ***/
        //char** pointer;
        //pointer = (char**)realloc(comand_list, new_num_linhas * sizeof(char*));
        //if (pointer == NULL) printf("ERRO");
        //comand_list = pointer;
        comand_list = (char**)realloc(comand_list, new_num_linhas * sizeof(char*));
        for (int i=0; i<new_num_linhas; i++) {
            comand_list[i] = (char*)malloc(TAM_MAX_CMD * sizeof(char));
        }
        // inicializa ponteiro
        for (int i=tela->larg; i<larg; i++) {
            for (int j=tela->alt; j<alt; j++) {
                comand_list[i][j] = '\0';
            }
        }
        // aloca matriz tela
        tela->rgb = (cor**)realloc(tela->rgb, larg * sizeof(cor*));
        for (int i=0; i<larg; i++) {
            tela->rgb[i] = (cor*)malloc(alt * sizeof(cor));
        }
        // inicializa ponteiro
        for (int i=tela->larg; i<larg; i++) {
            for (int j=tela->alt; j<alt; j++) {
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

// mostra comandos disponíveis e pequena documentação
void help() {
    printf("Ajuda do CPaint %s:\n\n", VERSION);
    printf("COMANDO [parâmetro_1 parâmetro_2 ...]\n\nCOMANDOS:\n");
    printf("image\tCria uma nova imagem em branco\n\tParâmetros: [largura INT], [altura INT]\n");
    printf("color\tMuda a cor atual\n\tParâmetros: [vermelho INT], [verde INT], [azul INT]\n");
    printf("clear\tLimpa a imagem com a cor especificada\n\tParâmetros (opcional): [vermelho INT], [verde INT], [azul INT]\n");
    printf("rect\tDesenha um retângulo\n\tParâmetros: [x INT], [y INT], [largura INT], [altura INT]\n");
    printf("circle\tDesenha um círculo\n\tParâmetros: [x INT], [y INT], [raio INT]\n");
    printf("poligon\tDesenha um polígono fechado\n\tParâmetros: [n INT] [x1 INT], [y1 INT], [x2 INT], [y2 INT] ... [xn INT], [yn INT]. (1 < n < 21)\n");
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
    for (int i=0; i<tela->larg; i++) {
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
    for (int i=0; i<tela->larg; i++) {
        printf("|");
        for (int j=0; j<tela->alt; j++) {
            printf("%3d %3d %3d, ", tela->rgb[i][j].r, tela->rgb[i][j].g, tela->rgb[i][j].b);
        }
        printf("\b\b|\n");
    }

}
