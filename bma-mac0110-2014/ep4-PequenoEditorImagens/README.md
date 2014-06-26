# Considerações

Segui as instruções do enunciado de maneira geral, mas fiz alterações que
considerei interessantes, como por exemplo:

1. O usuário pode fazer várias transformações antes de decidir sair do programa.
2. Defini as funções do meu jeito.

# Compilando

## Versão em C

Para compilar a solução em C, deve, a partir deste diretório, executar os
seguintes comandos:

```bash
$ cd solucao-c
$ gcc src/main.c -o prog
```

O arquivo executável `prog` deve ser criado no diretório `solucao-c`.

# Executando

Para que o programa funcione corretamente, deve existir os diretórios `entrada`
e `saida`. O programa irá procurar as imagens dentro de `entrada` e salvará os
resultados dentro de `saida`.

A seguir, está um exemplo da execução do programa:

```bash
Escolha uma das opções:
   0 - Sair
   1 - Manipular uma nova imagem
Digite: 1

Digite o nome do arquivo a ser processado sem extensao .pgm: pernalonga

O arquivo 'entrada/pernalonga.pgm' foi carregado com sucesso.

Escolha o que deseja fazer com a imagem:
   p - imprimir na tela
   n - negativo
   h - rebater na horizontal
   v - rebater na vertical
   r - rotacao
   m - filtro da mediana
Digite: r

O arquivo 'saida/pernalonga-r.pgm' foi salvado com
sucesso.

Escolha uma das opções:
   0 - Sair
   1 - Manipular uma nova imagem
Digite: 0
```
