#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "globals.h"
#include "drawing.h"
#include "cpaint.h"


int main() {
    init();             // inicialização da variaveis    
    msg_inicial();      // mostra apresentação do programa
    
    while (1) {
        char comando[TAM_MAX_CMD];              // comando digitado pelo usuario
        int num_param = 0;                      // numero de parâmetros do comando
        char cmd[NUM_MAX_PRM][TAM_MAX_CMD];     // vetor de strings contendo o comando e seus parametros

        printf(">> ");
        if (modo_leitura) {                     // modo leitura ON: lê comandos de um arquivo de entrada
            fscanf(arq_ent, " %[^\n]", comando);
            printf("%s\n", comando);
            printf("\b\b\b");
        } 
        else {                                  // modo leitura OFF: lê comando digitado pelo usuário
            scanf(" %[^\n]", comando);
        }

        t_comando(comando, cmd, &num_param);    // "traduz" o comando digitado para um vetor de strings
        interpreta(num_param, cmd);             // interpreta o comando digitado e chama a função apropriada
    }
    return 0;
}
