#include <allegro5/display.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

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
        bool line_num = True;
        if (strcmp(cmd[1],"NULL") != 0) line_num = False;
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
            if (x>g_tela->larg || y>g_tela->alt) {
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
            if (x1>g_tela->larg || y1>g_tela->alt || x2>g_tela->larg || y2>g_tela->alt ||
                x1<0          || y1<0         || x2<0          || y2<0           ) {
                printf("Pontos x ou y fora do canvas.\n");
                printf("Verifique o comando.\n");
            } else {
                line(x1, y1, x2, y2);
                adiciona_comando_gfx(cmd);
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
            if (x>g_tela->larg || y>g_tela->alt || x+tx>g_tela->larg || y+ty>g_tela->alt ||
                x<0          || y<0  ) {
                printf("x: %d y: %d\n", x, y);
                printf("x+tx: %d y+ty: %d\n", x+tx, y+ty);
                printf("larg: %d alt: %d\n", g_tela->larg, g_tela->alt);
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
            int n = atoi(cmd[1]) * 4;
            ponto pts[n][2];
            int i=2;
            int ip=0;
            for (int i=0; i<n; i+=4) {
                pts[ip][0].x = atoi(cmd[i+2]);
                pts[ip][0].y = atoi(cmd[i+3]);
                pts[ip][1].x = atoi(cmd[i+4]);
                pts[ip][1].y = atoi(cmd[i+5]);
                ip++;
            }
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
            d_open(cmd[1]);
        }
    }
    else {
        printf("Comando inválido.\n");
    }
}

// abre arquivo de entrada
void le_arquivo(char arquivo[50]) {
    g_modo_leitura = True;
    g_arq_ent = fopen(arquivo, "r");
    if (g_arq_ent == NULL) {                  // verifica se arquivo existe
        printf("Arquivo não existe\n");
        g_modo_leitura = False;
        cmd_i = -1;
    }
    else {
        fscanf(g_arq_ent, "%d", &g_cmd_tot);    // armazena o numero total de comandos
        cmd_i = 1;                          // inicializa o numero do comando a ser lido do arquivo de entrada
    };
}

void aloca_imagem(int larg, int alt) {
    int new_g_num_linhas = larg * alt + 3;
    if (g_is_init) {
        // aloca command_list
        g_ppm_command_list = malloc(new_g_num_linhas * sizeof(char*));
        for (int i=0; i<new_g_num_linhas; i++) {
            g_ppm_command_list[i] = malloc(TAM_MAX_CMD * sizeof(char));
        }
        // inicializa ponteiro
        for (int i=0; i<larg; i++) {
            for (int j=0; j<alt; j++) {
                g_ppm_command_list[i][j] = '\0';
            }
        }
        // aloca matriz g_tela
        g_tela = malloc(sizeof(matriz));
        g_tela->larg = larg;
        g_tela->alt = alt;
        g_tela->rgb = malloc(larg * sizeof(cor));
        for (int i=0; i<larg; i++) {
            g_tela->rgb[i] = malloc(alt * sizeof(cor));
        }
        // inicializa ponteiro
        for (int i=0; i<larg; i++) {
            for (int j=0; j<alt; j++) {
                g_tela->rgb[i][j].r = 0;
                g_tela->rgb[i][j].g = 0;
                g_tela->rgb[i][j].b = 0;
            }
        }
    } else {
        /*** Realoca memória ***/
        g_ppm_command_list = realloc(g_ppm_command_list, new_g_num_linhas * sizeof(char*));
        for (int i=0; i<new_g_num_linhas; i++) {
            // printf("realloc linha=%d\n", i);
            g_ppm_command_list[i] = malloc(TAM_MAX_CMD * sizeof(char));
        }
        // inicializa ponteiro
        for (int i=g_tela->larg; i<larg; i++) {
            for (int j=g_tela->alt; j<alt; j++) {
                g_ppm_command_list[i][j] = '\0';
            }
        }
        // aloca matriz g_tela
        // g_tela = realloc(g_tela, sizeof(matriz));
        g_tela->rgb = realloc(g_tela->rgb, larg * sizeof(cor));
        for (int i=0; i<larg; i++) {
            g_tela->rgb[i] = malloc(alt * sizeof(cor));
        }
        // inicializa ponteiro
        for (int i=g_tela->larg; i<larg; i++) {
            for (int j=g_tela->alt; j<alt; j++) {
                g_tela->rgb[i][j].r = 0;
                g_tela->rgb[i][j].g = 0;
                g_tela->rgb[i][j].b = 0;
            }
        }
        g_tela->larg = larg;
        g_tela->alt = alt;
    }
    g_num_linhas = new_g_num_linhas;
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
    printf("source\tLê comandos de um arquivo\n\tParâmetro: [nome_do_arquivo.in TEXTO]\n");
    printf("quit\tSai do programa\n");
    printf("\n");
}

// libera memoria alocada e sai do programa
void quit() {
    int n = g_tela->alt * g_tela->larg;
    for (int i=0; i<g_tela->larg; i++) {
        free(g_tela->rgb[i]);
    }
    free(g_tela->rgb);
    free(g_tela);
    
    for (int i=0; i<n; i++) {
        // printf("%d\n", i);
        free(g_ppm_command_list[i]);
    }
    free(g_ppm_command_list);  

    al_destroy_display(disp);

    printf("\nAté!\n\n");
    exit(0);
}

/** funcoes debug **/
void print_matriz_g_tela() {
    for (int i=0; i<g_tela->larg; i++) {
        printf("|");
        for (int j=0; j<g_tela->alt; j++) {
            printf("%3d %3d %3d, ", g_tela->rgb[i][j].r, g_tela->rgb[i][j].g, g_tela->rgb[i][j].b);
        }
        printf("\b\b|\n");
    }

}

// Funcao de inicializacao de partes do allegro. 
// Sai do programa com messagem de erro se inicialização falhar
// entrada: teste -> função a inicializar
//          description -> string com descriçao da função a inicializar
void must_init(bool test, const char *descricao)
{
    if (test) return;

    printf("Não foi possível inicializar %s\n", descricao);
    exit(1);
}

// Inicializa janela gráfica
// Tamanho: 640 x 480. 
// TODO: Escalonar desenhos.
void init_allegro(int larg, int alt) {
    int res_x = 640;
    int res_y = 480;
    g_escala_x = res_x/larg;
    g_escala_y = res_y/alt;

    must_init(al_init(), " allegro");
    must_init(al_install_keyboard(), "teclado");
    timer = al_create_timer(1.0 / 30.0);
    must_init(timer, "timer");

    queue = al_create_event_queue();
    must_init(queue, "queue");

    disp = al_create_display(res_x, res_y);
    must_init(disp, "display");

    font = al_create_builtin_font();
    must_init(font, "font");

    must_init(al_init_primitives_addon(), "primitives addon");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    bool done = False;
    bool redraw = True;
    ALLEGRO_EVENT event;
    
    al_start_timer(timer);
}

// percorre a lista de comandos e executa os comandos do cpaint
// traduzidos para o allegro
void desenha() {

}

// adiciona comando à lista de comandos do allegro
void adiciona_comando_gfx(char comando[NUM_MAX_PRM][TAM_MAX_CMD]) {
    if (strcmp(comando[1],"line") == 0) {
        //g_ppm_command_list[g_mmd_n] = 
    }
    g_cmd_n++;
}
