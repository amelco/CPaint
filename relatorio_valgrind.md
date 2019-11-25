## Relatório do Valgrind

Os seguintes arquivos de entrada foram utilizados
- espessuras.in -> testa o comando brush
- fill.in       -> testa o comando fill
- tcopy.in      -> testa os cooomandos copy, cut e paste
- teste.in      -> testa todas as primitivas

### Metodologia
Todos os arquivoss de entrada foram executados através do Valgrind da seguinte maneira:
```bash
valgrind --leak-check=yes ./cpaint
```
e os arquivos de teste foram executados utilizando a função source() do programa.

## Resultados
### espessuras.in
### saida 1
```
==8314== 72 bytes in 3 blocks are possibly lost in loss record 27 of 54
```
- Interpretação
Houve 72 bytes perdidos (vazamento de memória).

### saída 2
```
==8314==    by 0x10000282E: aloca_imagem (cpaint.c:357)
==8314==    by 0x100000E68: image (drawing.c:12)
==8314==    by 0x100002696: init (cpaint.c:31)
==8314==    by 0x100004615: main (main.c:11)
```
- Interpretação
Mostra em que parte do código o erro/vazamento foi encontrado. No caso, o vazamento iniciou na função `aloca_imagem`, linha 357 do arquivo `cpaint.c`. O *backtrace* é mostrado, significando que a função image que foi chamada pela função init que por sua vez foi chamada pela funçao `main`. Os respectivos arquivos e linhas são mostrados de forma análoga a `aloca_imagem` anteriormente citado.

### saída 3
```
==8314== LEAK SUMMARY:
==8314==    definitely lost: 288,340 bytes in 2,445 blocks
==8314==    indirectly lost: 269,420 bytes in 2,444 blocks
==8314==      possibly lost: 72 bytes in 3 blocks
==8314==    still reachable: 4,160 bytes in 3 blocks
==8314==         suppressed: 20,357 bytes in 163 blocks
==8314== Reachable blocks (those to which a pointer was found) are not shown.
==8314== To see them, rerun with: --leak-check=full --show-leak-kinds=all
```
- Interpretação
Aqui é mostrado a quantidade de memória perdida (*memory leaks*).

## Observação
Todos os outros caso de teste apresentaram erros semelhantes, nas mesmas funções, o que indica que o problema pode residir na forma em qua a memória é dinamicamente alocada.