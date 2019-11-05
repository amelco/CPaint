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
    isInit = True;          // é inicialização do programa
    modo_leitura = False;   // programa não está no modo leitura de arquivo 

    aloca_imagem(LARG, ALT);
    
    // preto
    cor_atual.r = 0;
    cor_atual.g = 0;
    cor_atual.b = 0;

    image(LARG, ALT);       // chama a função para definir um cabeçalho padrão
    clear(&cor_atual);

    // branco
    cor_atual.r = 255;
    cor_atual.g = 255;
    cor_atual.b = 255;
    
    cmd_n = 0;

    isInit = False;
    
    /*** Início do programa ***/
    msg_inicial();
    
    // inicializa janela gráfica
    init_allegro(tela->larg, tela->alt);
    while (1) {
        char comando[TAM_MAX_CMD];
        char cmd[NUM_MAX_PRM][TAM_MAX_CMD];
        int num_param = 0;

        printf(">> ");
        if (modo_leitura) {
            if (cmd_i > cmd_tot) {
                modo_leitura = False;
                fclose(arq_ent);
                cmd_i = 0;
                printf("\b\b\b");
                continue;
            }
            else {
                fscanf(arq_ent, " %[^\n]", &comando);
                cmd_i++;
                printf("%s\n", comando);
            }
        } 
        else {
            scanf(" %[^\n]", &comando);
            //todo: adiciona comando na lista de comandos do allegro para desenhar a cada frame
        }
        t_comando(comando, cmd, &num_param);
        interpreta(num_param, cmd);
        desenha();
    }
    
    return 0;
}
