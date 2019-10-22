#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "globals.h"
#include "drawing.h"
#include "cpaint.h"


int main() {
    /*** Inicialização ***/
    isInit = true;

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

    isInit = false;
    
    /*** Início do programa ***/
    msg_inicial();
    
    while (1) {
        char comando[TAM_MAX_CMD];
        char cmd[NUM_MAX_PRM][TAM_MAX_CMD];
        int num_param = 0;

        printf(">> ");
        /** Para ler de um arquivo, basta mudar essa linha e ler do arquivo ao inves do teclado **/
        scanf(" %[^\n]", &comando);
        t_comando(comando, cmd, &num_param);
        interpreta(num_param, cmd);
        // print_matriz_tela();
    }
    
    // quit();
    return 0;
}
