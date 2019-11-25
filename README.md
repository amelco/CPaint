# CPaint

Software de primitivas gráficas feito em C.

### Compilação
Para compilar execute os scripts:
```bash
./gen_obj
./compile
```
- `gen_obj` gera os arquivos `.o` dos módulos
- `compile` linka os objetos com o arquivo principal `main.c` e gera o executável `cpaint`.
e execute com `./cpaint`.

### Documentação
Para gerar documentação, utilize o [Doxygen](http://www.doxygen.nl/index.html).
*Opcional*: mude o estilo da documentação com
```bash
cp *.css docs/html/.
```

# CPaint em ação
### Função `source`
![](cpaint_source.gif)

### Funcionalidades implementadas
* [x] Função help()     => mostra pequena documentação  (*Andre*)
* [x] Função list()     => lista conteudo do canvas (*Andre*)
* [x] Função clear()    => limpa o canvas com a cor atual (*Andre*)
* [x] Função image()    => redimensiona o canvas (*Andre*)
* [x] Função color()    => muda cor do pincel (*Andre*)
* [x] Função point()    => desenha um ponto (*Andre*)
* [x] Função line()     => desenha uma linha (*Andre*)
* [x] Função rect()     => desenha um retângulo (*Andre*)
* [x] Função circle()   => desenha um círculo (*Andre*)
* [x] Função polygon()  => desenha um polígono (*Andre*)
* [x] Função fill()     => preenche um polígono com a cor atual (*Marcell*)
* [x] Função save()     => grava o arquivo de imagem em disco (*Andre*)
* [x] Função open()     => abre um arquivo de imagem anterior (*Marcell*)
* [x] Função source()   => executa uma lista de comando de um arquivo externo (*Andre*)

### Opcionais implementados
* [x] Interpretador de comandos (*Andre*)
* [x] Criar documentação utilizando Doxygen (*Andre*)
* [x] Utilizar git (*Andre* e *Marcell*)
* [x] Utilizar valgrind (*Andre* e *Marcell*)
* [x] Aumentar espessura da linha (função brush()) (*Andre*)
* [x] Copiar/recortar e colar (funçôes copy(), cut(), paste()) (*Marcell*)
### Opcionais não implementados
* [ ] Visualizar primitivas na tela após executar comando (*Andre*)
* [ ] Escalar imagem (*Marcell*)

## O que seria feito diferetemente?
- função fill() iterativa (melhor desempenho)
- utilizar `switch case` aliado com um `enum` ao invés de `ifs` na função de interpretação de comandos



---
*Projeto de ITP 2019.2*.  
*Professor Júlio César*.  
*Grupo: Andre Herman e Marcell Santana*
