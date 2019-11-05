#include <allegro5/color.h>
#include <allegro5/display.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "globals.h"
#include "drawing.h"
#include "cpaint.h"


int main() {
    /*** Inicialização ***/
    g_is_init = True;          // é inicialização do programa
    g_modo_leitura = False;   // programa não está no modo leitura de arquivo 

    aloca_imagem(LARG, ALT);
    
    // preto
    g_cor_atual.r = 0;
    g_cor_atual.g = 0;
    g_cor_atual.b = 0;

    image(LARG, ALT);       // chama a função para definir um cabeçalho padrão
    clear(&g_cor_atual);

    // branco
    g_cor_atual.r = 255;
    g_cor_atual.g = 255;
    g_cor_atual.b = 255;
    
    g_cmd_n = 0;

    g_is_init = False;
    
    /*** Início do programa ***/
    msg_inicial();
    
    // inicializa janela gráfica
    init_allegro(g_tela->larg, g_tela->alt);
    while (1) {
        char comando[TAM_MAX_CMD];
        char cmd[NUM_MAX_PRM][TAM_MAX_CMD];
        int num_param = 0;

        printf(">> ");
        if (g_modo_leitura) {
            if (cmd_i > g_cmd_tot) {
                g_modo_leitura = False;
                fclose(g_arq_ent);
                cmd_i = 0;
                printf("\b\b\b");
                continue;
            }
            else {
                fscanf(g_arq_ent, " %[^\n]", &comando);
                cmd_i++;
                printf("%s\n", comando);
            }
        } 
        else {
            scanf(" %[^\n]", &comando);
        }
        t_comando(comando, cmd, &num_param);
        interpreta(num_param, cmd);
        desenha();
    }
    
    return 0;
}
